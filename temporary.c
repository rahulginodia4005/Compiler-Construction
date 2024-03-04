#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include "parse_tree.h"
#include "stackImplementation.h"

int main(){
    NodeT* root = createRootNodeT();
    NodeT* n1 = createNodeT(2,root);
    NodeT* n2 = createNodeT(3,root);
    NodeT* n3 = createTerminalNodeT(4,n1);
    NodeT* n4 = createTerminalNodeT(5,n2);
    //printf("%d",root->terminal);
    //printf("%d\t%d",root->children[0]->name_rule,root->children[1]->name_rule);
    //inorder(root);
    Stack* st = createStack();
    Node* st1 = createNode(root,st);
    Node* ll = (Node*) malloc(sizeof(Node));
    //I need pareser table
    
}