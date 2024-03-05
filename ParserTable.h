#include<stdlib.h>
#include<stdio.h>
#include"grammar.h"


typedef struct ParserTable{
    Rule*** table;
    int rows, cols;
} ParserTable;

static ParserTable* create(int rows, int cols) {
    ParserTable* newPT = (ParserTable*) malloc(sizeof(ParserTable));
    newPT->table = (Rule***) malloc(rows * sizeof(Rule**));
    newPT->rows = rows;
    newPT->cols = cols;
    for(int i = 0;i<rows;i++) {
        newPT->table[i] = (Rule**) malloc(cols * sizeof(Rule*));
    }
    for(int i = 0;i<rows;i++) {
        for(int j = 0;j<cols;j++) {
            newPT->table[i][j] = NULL;
        }
    }
    return newPT;
}

static void insert(ParserTable* pt, Rule* rule, int row, int col) {
    if(pt->table[row][col] != NULL) return;
    pt->table[row][col] = rule;
}

static void fillParserTable(ParserTable* table, HashMapI* iToStruct) {
    NonTerminals* syn = create_terminal(200);
    Rule* synRule = NULL;
    synRule = addToRule(synRule, syn);
    HMI_insert(iToStruct, 200, syn);
    for(int i = 0;i<iToStruct->size;i++){
        if(iToStruct->vals[i]==NULL){
            continue;
        }
        else{
            NonTerminals* curr = (NonTerminals*)iToStruct->vals[i]->value;
            // printf("%s\n", curr->name);
            if(!curr->terminal) {
                for(int j = 0;j<curr->first_set_ind;j++) {
                    // printf("%d\t%d\t%d\n", curr->name, curr->first_set[j]->name, curr->first_set_to_grammar[j]);
                    insert(table, curr->grammar_rules[curr->first_set_to_grammar[j]], curr->name - 1, curr->first_set[j]->name - 54);
                }
                if(curr->derive_eps != -1) {
                    for(int j = 0;j<curr->follow_set_ind;j++) {
                        // printf("%d\t%d\t%d\n", curr->name, curr->follow_set[j]->name, curr->derive_eps);
                        insert(table, curr->grammar_rules[curr->derive_eps], curr->name - 1, curr->follow_set[j]->name - 54);
                    }
                }
                else{
                    for(int j = 0;j<curr->follow_set_ind;j++) {
                        // printf("%d\t%d\t%d\n", curr->name, curr->follow_set[j]->name, synRule->nt->name);
                        insert(table, synRule, curr->name - 1, curr->follow_set[j]->name - 54);
                    }
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
                    // printf("%d\t%d\t%d\n", curr->name, curr->first_set[j]->name, curr->first_set_to_grammar[j]);
                    insert(table, curr->grammar_rules[curr->first_set_to_grammar[j]], curr->name - 1, curr->first_set[j]->name - 54);
                }
                if(curr->derive_eps != -1) {
                    for(int j = 0;j<curr->follow_set_ind;j++) {
                        // printf("%d\t%d\t%d\n", curr->name, curr->follow_set[j]->name, curr->derive_eps);
                        insert(table, curr->grammar_rules[curr->derive_eps], curr->name - 1, curr->follow_set[j]->name - 54);
                    }
                }
                else{
                    for(int j = 0;j<curr->follow_set_ind;j++) {
                        // printf("%d\t%d\t%d\n", curr->name, curr->follow_set[j]->name, synRule->nt->name);
                        insert(table, synRule, curr->name - 1, curr->follow_set[j]->name - 54);
                    }
                }
                head = head->next;
            }
        }
    }
}
