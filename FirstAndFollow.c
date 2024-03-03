#include<stdlib.h>
#include<stdio.h>
#include"grammar.h"



NonTerminals** generateFirstSets(NonTerminals* curr) {
    if(curr->terminal) {
        curr->first_set[0] = curr;
        curr->first_set_ind++;
        return curr->first_set;
    }
    for(int i = 0;i<curr->size;i++){
        Rule* curr_rule = curr->grammar_rules[i];
        while(curr_rule) {
            NonTerminals** child = generateFirstSets(curr_rule);
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

NonTerminals* generateFollowSets(NonTerminals* curr) {
    
}

int main() {

}