#include<stdlib.h>
#include"hashmap.h"
#include<stdbool.h>

typedef struct Rule {
    NonTerminals* nt;
    struct Rule* next;
} Rule;

typedef struct NonTerminals {
    Rule** grammar_rules;
    int size;
    char *name;
    bool terminal;
} NonTerminals;

NonTerminals* create_nonTerminal(char* name) {
    NonTerminals* newNT = (NonTerminals*) malloc(sizeof(NonTerminals));
    newNT->size = 0;
    newNT->terminal = false;
    strcpy(newNT->name, name);
    return newNT;
}

NonTerminals* create_terminal(char* name) {
    NonTerminals* newT = (NonTerminals*) malloc(sizeof(NonTerminals));
    newT->terminal = true;
    strcpy(newT->name, name);
    return newT;
}

void addRuleToNonTerminal(NonTerminals* nonTerminal, Rule* rule) {
    nonTerminal->size++;
    nonTerminal->grammar_rules = (Rule**) realloc(nonTerminal->grammar_rules, nonTerminal->size * sizeof(Rule*));
    nonTerminal->grammar_rules[nonTerminal->size - 1] = rule;
}

Rule* addToRule(Rule* rule, NonTerminals* nt) {
    if(rule) {
        Rule* newRule = (Rule*) malloc(sizeof(Rule));
        newRule->nt = nt;
        rule->next = newRule;
        newRule->next = NULL;
        return newRule;
    }
    else{
        rule = (Rule*) malloc(sizeof(Rule));
        rule->nt = nt;
        rule->next = NULL;
        return rule;
    }
}
