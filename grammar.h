#include<stdlib.h>
#include"hashmap.h"
#include<stdbool.h>

typedef struct Rule {
    struct NonTerminals* nt;
    struct Rule* next;
} Rule;

typedef struct NonTerminals {
    Rule** grammar_rules;
    struct NonTerminals* first_set[50], *follow_set[50];
    int first_set_ind, follow_set_ind;
    int size;
    char *name;
    bool terminal;
} NonTerminals;

NonTerminals* create_nonTerminal(char* name) {
    NonTerminals* newNT = (NonTerminals*) malloc(sizeof(NonTerminals));
    newNT->size = 0;
    newNT->first_set_ind = 0, newNT->follow_set_ind = 0;
    newNT->terminal = false;
    newNT->name = (char*) malloc(sizeof(name));
    strcpy(newNT->name, name);
    return newNT;
}

NonTerminals* create_terminal(char* name) {
    NonTerminals* newT = (NonTerminals*) malloc(sizeof(NonTerminals));
    newT->terminal = true;
    newT->first_set_ind = 0, newT->follow_set_ind = 0;
    newT->name = (char*) malloc(sizeof(name));
    strcpy(newT->name, name);
    return newT;
}

void addRuleToNonTerminal(NonTerminals* nonTerminal, Rule* rule) {
    nonTerminal->size++;
    nonTerminal->grammar_rules = (Rule**) realloc(nonTerminal->grammar_rules, nonTerminal->size * sizeof(Rule*));
    nonTerminal->grammar_rules[nonTerminal->size - 1] = rule;
}

Rule* addToRule(Rule* rule, NonTerminals* nt) {
    Rule* temp = rule;
    if(rule) {
        Rule* newRule = (Rule*) malloc(sizeof(Rule));
        newRule->nt = nt;
        newRule->next = NULL;
        while(temp->next) temp = temp->next;
        temp->next = newRule;
    }
    else{
        rule = (Rule*) malloc(sizeof(Rule));
        rule->nt = nt;
        rule->next = NULL;
    }
    return rule;
}
