#include<stdlib.h>
#include<stdio.h>
#include"grammar.h"
#include"hashmap.h"
const int MAX_SIZE = 1000;

void swap(int* xp, int* yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
// Function to perform Selection Sort 
void selectionSort(int arr[], int n) 
{ 
    int i, j, min_idx; 
  
    // One by one move boundary of 
    // unsorted subarray 
    for (i = 0; i < n - 1; i++) { 
        // Find the minimum element in 
        // unsorted array 
        min_idx = i; 
        for (j = i + 1; j < n; j++) 
            if (arr[j] < arr[min_idx]) 
                min_idx = j; 
  
        // Swap the found minimum element 
        // with the first element 
        swap(&arr[min_idx], &arr[i]); 
    } 
} 

int main() {
    HashMap* strToI = create_table(MAX_SIZE); //will be used once, to map string to integer allocated
    HashMapI* ruleMapFirst = create_tableI(MAX_SIZE); //check whose first sets has been calculated
    HashMapI* iToStruct = create_tableI(MAX_SIZE); //main mapping from integer allocated to struct formed
    FILE* fp = fopen("intAllocation.txt", "r");
    if(fp == NULL) {
        perror("Error in intAllocation File");
        return 0;
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
        // if(line_number == 16) printf("%s", newStr);
        // printf("%s\t%d\t%d\n", newStr, HM_search(strToI, newStr), strlen(newStr));
    }
    fclose(fp);
    fp = fopen("grammarText.txt", "r");
    if(fp == NULL) {
        perror("Error in opening grammar file");
        return 0;
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
                int indT = HM_search(strToI, newTerminal);
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
    NonTerminals* curr = HMI_search(iToStruct, 12);
    // for(int i = 0;i<curr->size;i++) {
    //     Rule* curr_rule = curr->grammar_rules[i];
    //     while(curr_rule) {
    //         printf("%d\t", curr_rule->nt->name);
    //         curr_rule = curr_rule->next;
    //     }
    // }
    curr = HMI_search(iToStruct, 50);
    curr->follow_set[curr->follow_set_ind++] = HMI_search(iToStruct, 76);
    curr = HMI_search(iToStruct, 51);
    curr->follow_set[curr->follow_set_ind++] = HMI_search(iToStruct, 76);
    mainGenerateFirstSets(iToStruct, ruleMapFirst);
    mainGenerateNextToSets(iToStruct);
    // generateFollowSets(HMI_search(iToStruct, 50));
    mainGenerateFollowSets(iToStruct);
    // generateFirstSets(HMI_search(iToStruct, 23), ruleMapFirst);
    curr = HMI_search(iToStruct, 45);
    // printf("%d\n", curr->terminal);
    // for(int i = 0;i<curr->first_set_ind;i++) {
    //     printf("%d\n", curr->first_set[i]->name);
    // }
    for(int i = 0;i<curr->follow_set_ind;i++) {
        printf("%d\n", curr->follow_set[i]->name);
    }

    // printf("%d", curr->name);
    // printf("%d", iToStruct->count);
    // int b[200];
    // memset(b, 1000, sizeof(b));
    // int ind = 0;
    // for(int i = 0;i<iToStruct->size;i++){
    //     if(iToStruct->vals[i]==NULL){
    //         continue;
    //     }
    //     else{
    //         b[ind++] = iToStruct->vals[i]->key;
    //         // printf("%d\n", iToStruct->vals[i]->key);
    //         LinkedList* head = iToStruct->collision_buckets[i];
    //         while(head){
    //             b[ind++] = head->val->key;
    //             // printf("%d\n",head->val->key);
    //             head = head->next;
    //         }
    //     }
    // }
    // selectionSort(b, 200);
    // for(int i = 0;i<200;i++) {
    //     printf("%d\n", b[i]);
    // }

}