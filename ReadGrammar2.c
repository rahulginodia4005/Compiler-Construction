#include<stdlib.h>
#include<stdio.h>
#include"grammar.h"
#include"hashmap.h"
const int MAX_SIZE = 1000;

int main() {
    HashMap* strToI = create_table(MAX_SIZE);
    HashMapI* ruleMapFirst = create_tableI(MAX_SIZE);
    HashMapI* iToStruct = create_tableI(MAX_SIZE);
    FILE* fp = fopen("intAllocation.txt", "r");
    if(fp == NULL) {
        perror("Error in opening Grammar File");
        return 0;
    }
    char data[1024];
    int line_number = 0;
    while(fgets(data, 1024, fp)) {
        // printf("%s\n\n", data);
        line_number++;
        bool lhs = false;
        NonTerminals* lhsNT;
        Rule* newRule = NULL;
        NonTerminals* prev;
        for(int i = 0;i<1024;i++) {
            // printf("%d ", i);
            if(data[i] == '<') {
                i++;
                // char* non_terminal = (char*) malloc(50 * sizeof(char));
                char non_terminal[50];
                for(int j = 0;j<50;j++) non_terminal[j] = '\0';
                int non_terminal_ind = 0;
                while(data[i] != '>') {
                    non_terminal[non_terminal_ind++] = data[i++];
                }
                char *newNonTerminal = (char*) malloc((non_terminal_ind + 1) * sizeof(char));
                memset(newNonTerminal, '\0', (non_terminal_ind + 1) * sizeof(char));
                for(int j = 0;j<non_terminal_ind;j++) newNonTerminal[j] = non_terminal[j];
                // printf("%d\t%d\t%s\n",non_terminal_ind, strlen(newNonTerminal), newNonTerminal);
                NonTerminals* newNT;
                    // printf("%d %d %s\n", strlen(newNonTerminal), non_terminal_ind, newNonTerminal);
                if(HM_search(strToStruct, newNonTerminal) == NULL) {
                    newNT = create_nonTerminal(newNonTerminal);
                    HM_insert(strToStruct, newNonTerminal, newNT);
                }
                else newNT = HM_search(strToStruct, newNonTerminal);
                // printf("%d\t%d\t%s\n",non_terminal_ind, sizeof(newNT->name), newNT->name);
                // printf("%s\n", newNT->name);
                HM_insert(ruleMapFirst, newNonTerminal, false);
                if(!lhs) {
                    lhs = true;
                    lhsNT = newNT;
                }
                else{
                    newRule = addToRule(newRule, newNT);
                }
                prev = newNT;
                // break;

            }
            else if(data[i] == 'T' || data[i] == 'e') {
                // char* terminal = (char*) malloc(50 * sizeof(char));
                // memset(terminal, '\0', 50 * sizeof(char));
                char terminal[50];
                for(int j = 0;j<50;j++) terminal[j] = '\0';
                int terminal_ind = 0;
                while(data[i] != '<' && data[i] != ' ' && data[i] != '\n') {
                    terminal[terminal_ind++] = data[i++];
                }
                i--;
                // continue;
                // char *newTerminal = (char*) malloc((terminal_ind) * sizeof(char));
                // memset(newTerminal, '\0', terminal_ind * sizeof(char));
                char *newTerminal = (char*) malloc((terminal_ind + 1) * sizeof(char));
                memset(newTerminal, '\0', (terminal_ind + 1) * sizeof(char));
                for(int j = 0;j<terminal_ind;j++) {
                    newTerminal[j] = terminal[j];
                }
                NonTerminals* newT;
                if(HM_search(strToStruct, newTerminal) == NULL) {
                    newT = create_terminal(newTerminal);
                    // printf("%d %s\n", strlen(newTerminal), newTerminal);
                    HM_insert(strToStruct, newTerminal, newT);
                }
                else newT = HM_search(strToStruct, newTerminal);
                HM_insert(ruleMapFirst, newTerminal, false);
                newRule = addToRule(newRule, newT);
                prev = newT;
            }
            else if(data[i] == '|') {
                if(!checkDuplicacyLhsFollowset(prev, lhsNT) && prev != lhsNT) prev->lhsFollow[prev->lhsFollow_ind++] = lhsNT;
                addRuleToNonTerminal(lhsNT, newRule);
                newRule = NULL;
            }
            else if(data[i] == '\n') {
                if(!checkDuplicacyLhsFollowset(prev, lhsNT) && prev != lhsNT) prev->lhsFollow[prev->lhsFollow_ind++] = lhsNT;
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
    // printf("svsvssvsvbd");
    // generateFirstSets(HM_search(strToStruct, "term"), ruleMapFirst);
    mainGenerateFirstSets(strToStruct, ruleMapFirst);
    // NonTerminals* pro = HM_search(strToStruct, "declarations");
    // for(int i = 0;i<pro->first_set_ind;i++) {
    //     printf("%s\n", pro->first_set[i]->name);
    // }
    // bool pro2 = HM_search(ruleMapFirst, "fieldDefinitions");
    // printf("%d\n", pro2);
    NonTerminals* temp = HM_search(strToStruct, "program");
    NonTerminals* dollar = create_terminal("$");
    temp->follow_set[temp->follow_set_ind++] = dollar;
    // mainGenerateNextToSets(strToStruct);
    temp = HM_search(strToStruct, "actualOrRedefined");
    // generateFollowSets(temp);
    // printf("\nLHS Follow: \n");
    // for(int i = 0;i<temp->lhsFollow_ind;i++) {
    //     printf("%s\n", temp->lhsFollow[i]->name);
    // }
    // printf("\nNext to: \n");
    // for(int i = 0;i<temp->nextTo_ind;i++) {
    //     printf("%s\n", temp->nextTo[i]->name);
    // }
    // printf("\nFollow: \n");
    // for(int i = 0;i<temp->follow_set_ind;i++) {
    //     printf("%s\n", temp->follow_set[i]->name);
    // }
    fclose(fp);
}