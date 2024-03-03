#include<stdlib.h>
#include<stdio.h>
#include"grammar.h"
const int MAX_SIZE = 1000;

NonTerminals** generateFollowSets(NonTerminals* curr) {
    if(curr->follow_set_ind != 0) return curr->follow_set;
    for(int i = 0;i<curr->nextTo_ind;i++) {
        NonTerminals* child = curr->nextTo[i];
        for(int j = 0;j<child->first_set_ind;j++) if(!checkDuplicacyFollowset(curr, child->first_set[j])) curr->follow_set[curr->follow_set_ind++] = child->first_set[j];
    }
    for(int i = 0;i<curr->lhsFollow_ind;i++) {
        NonTerminals* child = curr->lhsFollow[i];
        NonTerminals** childFollow = generateFollowSets(child);
        int j = 0;
        while(childFollow[j] != NULL) {
            if(!checkDuplicacyFollowset(curr, childFollow[j])) curr->follow_set[curr->follow_set_ind++] = childFollow[j++];
        }
    }
}

int main() {
    HashMap* strToStruct = create_table(MAX_SIZE);
    HashMap* ruleMapFirst = create_table(MAX_SIZE);

    FILE* fp = fopen("/Users/srijan/Desktop/BITS Pilani/Compiler/Test Cases/Compiler-Construction/grammarText.txt", "r");
    if(fp == NULL) {
        perror("Error in opening Grammar File");
        return 0;
    }
    char data[1024];
    int line_number = 0;
    while(fgets(data, 1024, fp)) {
        line_number++;
        bool lhs = false;
        NonTerminals* lhsNT;
        Rule* newRule;
        NonTerminals* prev;
        for(int i = 0;i<1024;i++) {
            if(data[i] == '<') {
                i++;
                char non_terminal[50] = "";
                int non_terminal_ind = 0;
                while(data[i] != '>') {
                    non_terminal[non_terminal_ind++] = data[i++];
                }
                char* newNonTerminal = (char*) malloc(non_terminal_ind * sizeof(char));
                for(int j = 0;j<non_terminal_ind;j++) {
                    newNonTerminal[j] = non_terminal[j];
                }
                // printf("%s\n", newNonTerminal);
                NonTerminals* newNT;
                if(HM_search(strToStruct, newNonTerminal) == NULL) {
                    newNT = create_nonTerminal(newNonTerminal);
                    HM_insert(strToStruct, newNonTerminal, newNT);
                }
                else newNT = HM_search(strToStruct, newNonTerminal);
                HM_insert(ruleMapFirst, newNonTerminal, false);
                if(!lhs) {
                    lhs = true;
                    lhsNT = newNT;
                }
                else{
                    if(newRule != NULL && !checkDuplicacyNextToset(prev, newNT)) prev->nextTo[prev->nextTo_ind++] = newNT;
                    newRule = addToRule(newRule, newNT);
                }
                prev = newNT;
                // break;

            }
            else if(data[i] == 'T' || data[i] == 'e') {
                char terminal[50] = "";
                int terminal_ind = 0;
                while(data[i] != '<' && data[i] != ' ' && data[i] != '\n') {
                    terminal[terminal_ind++] = data[i++];
                }
                i--;
                char* newTerminal = (char*) malloc(terminal_ind * sizeof(char));
                for(int j = 0;j<terminal_ind;j++) {
                    newTerminal[j] = terminal[j];
                }
                NonTerminals* newT;
                if(HM_search(strToStruct, newTerminal) == NULL) {
                    newT = create_terminal(newTerminal);
                    HM_insert(strToStruct, newTerminal, newT);
                }
                else newT = HM_search(strToStruct, newTerminal);
                HM_insert(ruleMapFirst, newTerminal, false);
                if(newRule != NULL && !checkDuplicacyNextToset(prev, newT)) prev->nextTo[prev->nextTo_ind++] = newT;
                newRule = addToRule(newRule, newT);
                prev = newT;
            }
            else if(data[i] == '|') {
                if(!checkDuplicacyLhsFollowset(prev, lhsNT)) prev->lhsFollow[prev->lhsFollow_ind++] = lhsNT;
                addRuleToNonTerminal(lhsNT, newRule);
                newRule = NULL;
            }
            else if(data[i] == '\n') {
                if(!checkDuplicacyLhsFollowset(prev, lhsNT)) prev->lhsFollow[prev->lhsFollow_ind++] = lhsNT;
                addRuleToNonTerminal(lhsNT, newRule);
                lhs = false;
                newRule = NULL;
                lhsNT = NULL;
                break;
            }
            else continue;
        }
    }
    // NonTerminals* pro = HM_search(strToStruct, "program");
    // for(int i = 0;i<pro->size;i++) {
    //     Rule* temp = pro->grammar_rules[i];
    //     while(temp) {
    //         printf("%s ", temp->nt->name);
    //         temp = temp->next;
    //     }
    //     printf("\n");
    // }
    // char *aa = pro->first_set[0]->name;
    // printf("%d", pro->grammar_rules[0]->nt->size);
    // generateFirstSets(HM_search(strToStruct, "term"), ruleMapFirst);
    mainGenerateFirstSets(strToStruct, ruleMapFirst);
    NonTerminals* pro = HM_search(strToStruct, "arithmeticExpression");
    for(int i = 0;i<pro->first_set_ind;i++) {
        printf("%s\n", pro->first_set[i]->name);
    }
    // bool pro2 = HM_search(ruleMapFirst, "fieldDefinitions");
    // printf("%d\n", pro2);
    fclose(fp);
}