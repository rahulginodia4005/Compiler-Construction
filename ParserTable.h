#include<stdlib.h>
#include<stdio.h>
#include"grammar.h"

typedef struct ParserTable{
    Rule*** table;
    int rows, cols;
} ParserTable;

ParserTable* create(int rows, int cols) {
    ParserTable* newPT = (ParserTable*) malloc(sizeof(ParserTable));
    newPT->table = (Rule***) malloc(rows * sizeof(Rule**));
    newPT->rows = rows;
    newPT->cols = cols;
    for(int i = 0;i<rows;i++) {
        newPT->table[i] = (Rule**) malloc(cols * sizeof(Rule*));
    }
    return newPT;
}

void insert(ParserTable* pt, Rule* rule, int row, int col) {
    pt->table[row][col] = rule;
}

void fillParserTable(ParserTable* table, HashMapI* iToStruct) {
    for(int i = 0;i<iToStruct->size;i++){
        if(iToStruct->vals[i]==NULL){
            continue;
        }
        else{
            NonTerminals* curr = (NonTerminals*)iToStruct->vals[i]->value;
            // printf("%s\n", curr->name);
            if(!curr->terminal) {
                for(int j = 0;j<curr->first_set_ind;j++) {
                    printf("%d\t%d\t%d\n", curr->name, curr->first_set[j]->name, curr->first_set_to_grammar[j]);
                    insert(table, curr->grammar_rules[curr->first_set_to_grammar[j]], curr->name - 1, curr->first_set[j]->name - 54);
                }
            }
            LinkedListI* head = iToStruct->collision_buckets[i];
            while(head){
                curr = (NonTerminals*) head->val->value;
                if(curr->terminal) {
                    head = head->next;
                    continue;
                }
                for(int j = 0;j<curr->first_set_ind;j++) {
                    printf("%d\t%d\t%d\n", curr->name, curr->first_set[j]->name, curr->first_set_to_grammar[j]);
                    insert(table, curr->grammar_rules[curr->first_set_to_grammar[j]], curr->name - 1, curr->first_set[j]->name - 54);
                }
                head = head->next;
            }
        }
    }
}