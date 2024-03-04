#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include "parse_tree.h"
#include "stackImplementation.h"
#include "token.h"
#include "ParserTable.h"

int main(){
    NodeT* root = createRootNodeT();
    NodeT* n1 = createNodeT(2,root);
    NodeT* n2 = createNodeT(3,root);
    NodeT* n3 = createTerminalNodeT(4,n1);
    NodeT* n4 = createTerminalNodeT(5,n2);
    //printf("%d",root->terminal);
    // printf("%d\t%d",root->children[0]->name_rule,root->children[1]->name_rule);
    inorder(root);
    Stack* st = createStack();
    push(st, root->name_rule); 
    TdNode* ll = (TdNode*) malloc(sizeof(TdNode));
    //I need pareser table
    TdNode* prev = ll;
    TdNode* temp = ll;
    ParserTable* table = create(5,6);
    while(temp!=NULL){
        char token_seen[50];
        strcpy(token_seen, temp->tokenDet->token);
        int stack_top = pop(st);
        HMI_search() // mapping top of stack to an integer


        prev = temp;
        temp = temp->next;
    }  
     

    

}