#include<stdlib.h>
#include<stdio.h>
#include"parser.h"
#include"lexer.h"
const int MAX_SIZE = 1000;

void readGrammar(HashMap* strToI, HashMapI* ruleMapFirst, HashMapI* iToStruct, HashMapI* iToStr) {
    FILE* fp = fopen("intAllocation.txt", "r");
    if(fp == NULL) {
        perror("Error in intAllocation File");
        return;
    }
    char data[200];
    int line_number = 0;
    while(fgets(data, 200, fp)) {
        line_number++;
        int ind = 0;
        while(data[ind] != '\n') ind++;
        char *newStr = (char*) malloc((ind + 1) * sizeof(char));
        memset(newStr, '\0', (ind + 1) * sizeof(char));
        for(int i = 0;i<ind;i++) newStr[i] = data[i];
        HM_insert(strToI, newStr, line_number);
        HMI_insert(iToStr, line_number, newStr);
        // if(line_number == 16) printf("%s", newStr);
        // printf("%s\t%d\t%d\n", newStr, HM_search(strToI, newStr), strlen(newStr));
    }
    fclose(fp);
    fp = fopen("grammarText.txt", "r");
    if(fp == NULL) {
        perror("Error in opening grammar file");
        return;
    }
    line_number = 0;
    while(fgets(data, 200, fp)) {
        Rule* newRule = NULL;
        bool lhs = false;
        NonTerminals* prev = NULL, *lhsNT = NULL;
        // printf("%s\n\n", data);
        line_number++;
        for(int i = 0;i<200;i++) {
            int ind = 0;
            if(data[i] == '<') {
                i++;
                char *non_terminal = (char*) malloc(50 * sizeof(char));
                memset(non_terminal, '\0', 50 * sizeof(char));
                int non_terminal_ind = 0;
                while(data[i] != '>') {
                    non_terminal[non_terminal_ind++] = data[i++];
                }
                char *newNonTerminal = (char*) malloc((non_terminal_ind + 1) * sizeof(char));
                memset(newNonTerminal, '\0', (non_terminal_ind + 1) * sizeof(char));
                for(int j = 0;j<non_terminal_ind;j++) {
                    newNonTerminal[j] = non_terminal[j];
                }
                int indNT = HM_search(strToI, newNonTerminal);
                if(strcmp(newNonTerminal, "outputParameters") == 0) indNT = 31;
                else if(strcmp(newNonTerminal, "fieldDefinitions") == 0)  indNT = 16;
                NonTerminals* newNT = NULL;
                if(HMI_search(iToStruct, indNT) == NULL) {
                    newNT = create_nonTerminal(indNT);
                    HMI_insert(iToStruct, indNT, newNT);
                }
                else newNT = HMI_search(iToStruct, indNT);
                if(!lhs) {
                    lhs = true;
                    lhsNT = newNT;
                }
                else{
                    newRule = addToRule(newRule, newNT);
                }
                HMI_insert(ruleMapFirst, indNT, false);
                prev = newNT;
                // printf("%d\t%d\n", indNT, newNT->name);
                // printf("%d\t%d\n", line_number, HM_search(strToI, newNonTerminal));
                free(non_terminal);
            }
            else if(data[i] == 'T' || data[i] == 'e') {
                char *terminal = (char*) malloc(50 * sizeof(char));
                memset(terminal, '\0', 50 * sizeof(char));
                int terminal_ind = 0;
                while(data[i] != ' ' && data[i] != '\n') {
                    terminal[terminal_ind++] = data[i++];
                }
                i--;
                char *newTerminal = (char*) malloc(terminal_ind * sizeof(char));
                memset(newTerminal, '\0', terminal_ind * sizeof(char));
                for(int j = 0;j<terminal_ind;j++) {
                    newTerminal[j] = terminal[j];
                }
                int indT = (int)HM_search(strToI, newTerminal);
                NonTerminals* newT = NULL;
                if(HMI_search(iToStruct, indT) == NULL) {
                    newT = create_terminal(indT);
                    HMI_insert(iToStruct, indT, newT);
                }
                else newT = HMI_search(iToStruct, indT);
                // printf("%d\t%d\n", indT, newT->name);
                // printf("%d\t%d\n", line_number, HM_search(strToI, newTerminal));
                newRule = addToRule(newRule, newT);
                prev = newT;
                HMI_insert(ruleMapFirst, indT, false);
                free(terminal);
            }
            else if(data[i] == '|') {
                // printf("%d\t", prev->name);
                if(!checkDuplicacyLhsFollowset(prev, lhsNT)) prev->lhsFollow[prev->lhsFollow_ind++] = lhsNT;
                addRuleToNonTerminal(lhsNT, newRule);
                newRule = NULL;

            }
            else if(data[i] == '\n'){
                if(!checkDuplicacyLhsFollowset(prev, lhsNT)) prev->lhsFollow[prev->lhsFollow_ind++] = lhsNT;
                addRuleToNonTerminal(lhsNT, newRule);
                prev = NULL;
                lhs = false;
                newRule = NULL;
                lhsNT = NULL;
                break;
            }
            else continue;
        }
    }
    HM_insert(strToI, "$", 0);
    HMI_insert(iToStr, 0, "$");
    NonTerminals* temp = HMI_search(iToStruct, 1);
    NonTerminals* dollar = create_terminal(0);
    temp->follow_set[temp->follow_set_ind++] = dollar;
    NonTerminals* curr = HMI_search(iToStruct, 50);
    curr->follow_set[curr->follow_set_ind++] = HMI_search(iToStruct, 76);
    curr = HMI_search(iToStruct, 51);
    curr->follow_set[curr->follow_set_ind++] = HMI_search(iToStruct, 76);
}

void produce_first_set(HashMapI* iToStruct, HashMapI* ruleMapFirst) {
    mainGenerateFirstSets(iToStruct, ruleMapFirst);
}

void produce_follow_set(HashMapI* iToStruct) {
    mainGenerateNextToSets(iToStruct);
    mainGenerateFollowSets(iToStruct);
}

ParserTable* create_parser_table(HashMapI* iToStruct, HashMapI* iToStr, HashMap* strToI) {
    ParserTable* table = create(53, 58);
    fillParserTable(table, iToStruct);
    HMI_insert(iToStr, 200, "syn");
    HM_insert(strToI, "syn", 200);
    return table;
}

int main() {
    HashMap* strToI = create_table(MAX_SIZE); //will be used once, to map string to integer allocated
    HashMapI* ruleMapFirst = create_tableI(MAX_SIZE); //check whose first sets has been calculated
    HashMapI* iToStruct = create_tableI(MAX_SIZE); //main mapping from integer allocated to struct formed
    HashMapI* iToStr = create_tableI(MAX_SIZE);
    readGrammar(strToI, ruleMapFirst, iToStruct, iToStr);
    produce_first_set(iToStruct, ruleMapFirst);
    produce_follow_set(iToStruct);
    ParserTable* table = create_parser_table(iToStruct, iToStr, strToI);
    // TdNode *list = createLinkedList();
    // printLinkedList(list);
    // printf("Error,");
    // for(int j = 0;j<58;j++) {
    //     printf("%s", HMI_search(iToStr, j + 54));
    //     if(j != 57) printf(",");
    // }
    // printf("\n");
    
    // for(int i = 0;i<53;i++) {
    //     printf("%s,", HMI_search(iToStr, i + 1));
    //     for(int j = 0;j<58;j++) {
    //         Rule* curr = table->table[i][j];
    //         if(curr == NULL) {
    //             printf("Error");
    //         }
    //         else printf("%s", HMI_search(iToStr, curr->nt->name));
    //         if(j != 57) printf(",");
    //     }
    //     printf("\n");
    // }
    // for(int i = 0;i<iToStruct->size;i++) {
    //     if(iToStruct->vals[i] == NULL) continue;
    //     else {
    //         NonTerminals* curr = iToStruct->vals[i]->value;
    //         for(int j = 0;j<curr->first_set_ind;j++) {
    //             printf("%s ", curr->first_set[j])
    //         }
    //     }
    // }
}