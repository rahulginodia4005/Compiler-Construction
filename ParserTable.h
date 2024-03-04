#include<stdlib.h>
#include<stdio.h>
#include"grammar.h"

typedef struct ParserTable{
    Rule*** table;
    int rows, cols;

    void create(int _rows, int _cols) {
        table = (Rule***) malloc(rows * sizeof(Rule**));
        rows = _rows;
        cols = _cols;
        for(int i = 0;i<rows;i++) {
            table[i] = (Rule**) malloc(cols * sizeof(Rule*));
        }
    }

    void insert(Rule* rule, int row, int col) {
        table[row][col] = rule;
    }
} ParserTable;

void create(ParserTable* table, int _rows, int _cols) {
    
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
                    table->insert(curr->grammar_rules[curr->first_set_to_grammar[j]], curr->name - 1, curr->first_set[j]->name - 54);
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
                    table->insert(curr->grammar_rules[curr->first_set_to_grammar[j]], curr->name - 1, curr->first_set[j]->name - 54);
                }
                head = head->next;
            }
        }
    }
}