#include<stdlib.h>
#include"hashmap_int.h"
#include<stdbool.h>

#ifndef grammar
#define grammar

typedef struct Rule {
    struct NonTerminals* nt;
    struct Rule* next;
} Rule;

typedef struct NonTerminals {
    Rule* grammar_rules[10];
    struct NonTerminals *nextTo[40],*first_set[40], *follow_set[40], *lhsFollow[40];
    int first_set_to_grammar[40];
    int first_set_ind, follow_set_ind, nextTo_ind, lhsFollow_ind;
    bool follow_in_process;
    bool eps_in_first;
    int size;
    int name;
    bool terminal;
} NonTerminals;

NonTerminals* create_nonTerminal(int name) {
    NonTerminals* newNT = (NonTerminals*) malloc(sizeof(NonTerminals));
    newNT->size = 0;
    newNT->first_set_ind = 0, newNT->follow_set_ind = 0, newNT->nextTo_ind = 0, newNT->lhsFollow_ind = 0;
    newNT->terminal = false;
    newNT->follow_in_process = false;
    newNT->eps_in_first = false;
    newNT->name = name;
    return newNT;
}

NonTerminals* create_terminal(int name) {
    NonTerminals* newT = (NonTerminals*) malloc(sizeof(NonTerminals));
    newT->terminal = true;
    newT->first_set_ind = 0, newT->follow_set_ind = 0, newT->nextTo_ind = 0, newT->lhsFollow_ind = 0;
    newT->eps_in_first = false;
    newT->follow_in_process = false;
    newT->name = name;
    return newT;
}


void addRuleToNonTerminal(NonTerminals* nonTerminal, Rule* rule) {
    nonTerminal->size++;
    // nonTerminal->grammar_rules = (Rule**) realloc(nonTerminal->grammar_rules, nonTerminal->size * sizeof(Rule*));
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

NonTerminals** generateFirstSets(NonTerminals* curr, HashMapI* ruleToMapFirst) {
    // if(curr->first_set_ind != 0) return curr->first_set;
    if(HMI_search(ruleToMapFirst, curr->name)) return curr->first_set;
    HMI_insert(ruleToMapFirst, curr->name, true);
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
                if(child[j]->name == 111) {
                    eps = true;
                    curr->eps_in_first = true;
                    if(curr_rule->next == NULL) {
                        curr->first_set[curr->first_set_ind] = child[j];
                        curr->first_set_to_grammar[curr->first_set_ind++] = i;
                    }
                }
                else {
                    curr->first_set[curr->first_set_ind] = child[j];
                    curr->first_set_to_grammar[curr->first_set_ind++] = i;
                }
                j++;
            }
            if(!eps) break;
            curr_rule = curr_rule->next;
        }
    }
    return curr->first_set;
}

void mainGenerateFirstSets(HashMapI* iToStruct,HashMapI* ruleToMapFirst){
    for(int i = 0;i<iToStruct->size;i++){
        if(iToStruct->vals[i]==NULL){
            continue;
        }
        else{
            if(!HMI_search(ruleToMapFirst,iToStruct->vals[i]->key)){
                generateFirstSets(iToStruct->vals[i]->value, ruleToMapFirst);
            }
            LinkedListI* head = iToStruct->collision_buckets[i];
            while(head){
                if(!HMI_search(ruleToMapFirst,head->val->key)){
                    generateFirstSets(head->val->value,ruleToMapFirst);
                }
                head = head->next;
            }
        }
    }
}

void generateNextToSets(Rule* rule) {
    Rule* temp1 = rule;
    Rule* temp2 = NULL;
    while(temp1) {
        temp2 = temp1->next;
        while(temp2) {
            if(!checkDuplicacyNextToset(temp1->nt, temp2->nt) && temp2->nt->name != 111) temp1->nt->nextTo[temp1->nt->nextTo_ind++] = temp2->nt;
            if(!temp2->nt->eps_in_first) break;
            if(temp2->next == NULL) {
                for(int i = 0;i<temp2->nt->lhsFollow_ind;i++) {
                    if(!checkDuplicacyLhsFollowset(temp1->nt, temp2->nt->lhsFollow[i])) {
                        temp1->nt->lhsFollow[temp1->nt->lhsFollow_ind++] = temp2->nt->lhsFollow[i];
                    }
                }
            }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
}

void mainGenerateNextToSets(HashMapI* iToStruct){
    int ct = 0;
    for(int i = 0;i<iToStruct->size;i++){
        if(iToStruct->vals[i]==NULL){
            continue;
        }
        else{
            NonTerminals* curr = iToStruct->vals[i]->value;
            // printf("%s\n", curr->name);
            for(int j = 0;j<curr->size;j++) {
                generateNextToSets(curr->grammar_rules[j]);
            }
            LinkedListI* head = iToStruct->collision_buckets[i];
            while(head){
                curr = head->val->value;
                // printf("%s\n", curr->name);
                for(int j = 0;j<curr->size;j++) {
                    generateNextToSets(curr->grammar_rules[j]);
                }
                head = head->next;
            }
        }
    }
}

NonTerminals** generateFollowSets(NonTerminals* curr) {
    if(curr->follow_in_process) return curr->follow_set;
    if(curr->follow_set_ind != 0) return curr->follow_set;
    curr->follow_in_process = true;
    // printf("%d\n", curr->name);
    for(int i = 0;i<curr->nextTo_ind;i++) {
        NonTerminals* child = curr->nextTo[i];
        // printf("%s\n", child->name);
        for(int j = 0;j<child->first_set_ind;j++) if(!checkDuplicacyFollowset(curr, child->first_set[j])) curr->follow_set[curr->follow_set_ind++] = child->first_set[j];
    }
    for(int i = 0;i<curr->lhsFollow_ind;i++) {
        NonTerminals* child = curr->lhsFollow[i];
        if(child->name == curr->name) continue;
        NonTerminals** childFollow = generateFollowSets(child);
        int j = 0;
        while(childFollow[j] != NULL) {
            if(!checkDuplicacyFollowset(curr, childFollow[j])) curr->follow_set[curr->follow_set_ind++] = childFollow[j];
            j++;
        }
    }
    curr->follow_in_process = false;
    return curr->follow_set;
}

void mainGenerateFollowSets(HashMapI* iToStruct){
    int ct = 0;
    for(int i = 0;i<iToStruct->size;i++){
        if(iToStruct->vals[i]==NULL){
            continue;
        }
        else{
            generateFollowSets(iToStruct->vals[i]->value);
            // printf("%s\n", curr->name);
            LinkedListI* head = iToStruct->collision_buckets[i];
            while(head){
                // curr = head->val->value;
                generateFollowSets(head->val->value);
                // printf("%s\n", curr->name);
                // for(int j = 0;j<curr->size;j++) {
                //     generateNextToSets(curr->grammar_rules[j]);
                // }
                head = head->next;
            }
        }
    }
}

#endif