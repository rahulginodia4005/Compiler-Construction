#include<stdlib.h>
#include"hashmap.h"
#include<stdbool.h>

typedef struct Rule {
    struct NonTerminals* nt;
    struct Rule* next;
} Rule;

typedef struct NonTerminals {
    Rule** grammar_rules;
    struct NonTerminals *nextTo[20],*first_set[20], *follow_set[20], *lhsFollow[20];
    int first_set_ind, follow_set_ind, nextTo_ind, lhsFollow_ind;
    int size;
    char *name;
    bool terminal;
} NonTerminals;

NonTerminals* create_nonTerminal(char* name) {
    NonTerminals* newNT = (NonTerminals*) malloc(sizeof(NonTerminals));
    newNT->size = 0;
    newNT->first_set_ind = 0, newNT->follow_set_ind = 0, newNT->nextTo_ind = 0, newNT->lhsFollow_ind = 0;
    newNT->terminal = false;
    newNT->name = (char*) malloc(sizeof(name));
    strcpy(newNT->name, name);
    return newNT;
}

NonTerminals* create_terminal(char* name) {
    NonTerminals* newT = (NonTerminals*) malloc(sizeof(NonTerminals));
    newT->terminal = true;
    newT->first_set_ind = 0, newT->follow_set_ind = 0, newT->nextTo_ind = 0, newT->lhsFollow_ind = 0;
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

bool checkDuplicacyFirstset(NonTerminals* curr,NonTerminals* child){
    bool test = false;
    for(int i =0;i<curr->first_set_ind;i++){
        if(curr->first_set[i]->name==child->name){
            test = true;
            break;
        }
    }
    return test;
}

bool checkDuplicacyFollowset(NonTerminals* curr,NonTerminals* child){
    bool test = false;
    for(int i =0;i<curr->follow_set_ind;i++){
        if(curr->follow_set[i]->name==child->name){
            test = true;
            break;
        }
    }
    return test;
}

bool checkDuplicacyNextToset(NonTerminals* curr,NonTerminals* child){
    bool test = false;
    for(int i =0;i<curr->nextTo_ind;i++){
        if(curr->nextTo[i]->name==child->name){
            test = true;
            break;
        }
    }
    return test;
}

bool checkDuplicacyLhsFollowset(NonTerminals* curr,NonTerminals* child){
    bool test = false;
    for(int i =0;i<curr->lhsFollow_ind;i++){
        if(curr->lhsFollow[i]->name==child->name){
            test = true;
            break;
        }
    }
    return test;
}

NonTerminals** generateFirstSets(NonTerminals* curr, HashMap* ruleToMapFirst) {
    if(curr->first_set_ind != 0) return curr->first_set;
    HM_insert(ruleToMapFirst, curr->name, true);
    if(curr->terminal) {
        curr->first_set[0] = curr;
        curr->first_set_ind = 1;
        return curr->first_set;
    }
    for(int i = 0;i<curr->size;i++){
        Rule* curr_rule = curr->grammar_rules[i];
        while(curr_rule) {
            NonTerminals** child = generateFirstSets(curr_rule->nt, ruleToMapFirst);
            bool eps = false;
            int j = 0;
            while(child[j] != NULL) {
                if(strcmp(child[j]->name, "eps") == 0) eps = true;
                if(!checkDuplicacyFirstset(curr, child[j])) curr->first_set[curr->first_set_ind++] = child[j];
                j++;
            }
            if(!eps) break;
            curr_rule = curr_rule->next;
        }
    }
    return curr->first_set;
}

void mainGenerateFirstSets(HashMap* strToStruct,HashMap* ruleToMapFirst){
    int ct = 0;
    for(int i = 0;i<strToStruct->size;i++){
        if(strToStruct->vals[i]==NULL){
            continue;
        }
        else{
            if(!HM_search(ruleToMapFirst,strToStruct->vals[i]->key)){
                // NonTerminals* curr = HM_search(strToStruct,ruleToMapFirst->vals[i]->key);
                generateFirstSets(strToStruct->vals[i]->value, ruleToMapFirst);
                // printf("%s\n", strToStruct->vals[i]->key);
            }
            LinkedList* head = strToStruct->collision_buckets[i];
            while(head){
                if(!HM_search(ruleToMapFirst,head->val->key)){
                    generateFirstSets(head->val->value,ruleToMapFirst);
                }
                head = head->next;
            }
        }
    }
}