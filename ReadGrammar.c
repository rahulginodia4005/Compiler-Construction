#include<stdlib.h>
#include<stdio.h>
#include"grammar.h"

NonTerminals** generateFirstSets(NonTerminals* curr) {
    // printf("%s\n", curr->name);
    // printf("%d\n", curr->size);
    if(curr->terminal) {
        curr->first_set[0] = curr;
        curr->first_set_ind = 1;
        return curr->first_set;
    }
    for(int i = 0;i<curr->size;i++){
        Rule* curr_rule = curr->grammar_rules[i];
        while(curr_rule) {
            NonTerminals** child = generateFirstSets(curr_rule->nt);
            bool eps = false;
            int j = 0;
            while(child[j] != NULL) {
                if(strcmp(child[j]->name, "eps") == 0) eps = true;
                curr->first_set[curr->first_set_ind++] = child[j++];
            }
            if(!eps) break;
            curr_rule = curr_rule->next;
        }
    }
    return curr->first_set;
}



int main() {
    HashMap* strToStruct = create_table(1000);
    FILE* fp = fopen("/Users/rahulginodia/Desktop/Compiler/grammarText.txt", "r");
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
                NonTerminals* newNT;
                if(HM_search(strToStruct, newNonTerminal) == NULL) {
                    newNT = create_nonTerminal(newNonTerminal);
                    HM_insert(strToStruct, newNonTerminal, newNT);
                }
                else newNT = HM_search(strToStruct, newNonTerminal);
                if(!lhs) {
                    lhs = true;
                    lhsNT = newNT;
                }
                else{
                    newRule = addToRule(newRule, newNT);
                }
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
                newRule = addToRule(newRule, newT);
            }
            else if(data[i] == '|') {
                addRuleToNonTerminal(lhsNT, newRule);
                newRule = NULL;
            }
            else if(data[i] == '\n') {
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
    generateFirstSets(HM_search(strToStruct, "program"));
    NonTerminals* pro = HM_search(strToStruct, "parameter_list");
    for(int i = 0;i<pro->first_set_ind;i++) {
        printf("%s\n", pro->first_set[i]->name);
    }
    fclose(fp);
}