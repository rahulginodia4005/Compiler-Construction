#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#ifndef parseTree
#define parseTree

typedef struct NodeT{
    int name_rule;
    struct NodeT* children[10];
    int countOfChild;
    struct NodeT* parent;
    int terminal;
}NodeT;

NodeT* createRootNodeT(){
    NodeT* rootNodeT = (NodeT*) malloc(sizeof(NodeT));
    rootNodeT->name_rule=1;
    for(int i =0;i<10;i++){
        rootNodeT->children[i] = NULL;
    }
    rootNodeT->parent=NULL;
    rootNodeT->countOfChild=0;
    rootNodeT->terminal=0;
    return rootNodeT;
}
NodeT* createNodeT(int name,NodeT* parent){
    NodeT* nt = (NodeT*)malloc(sizeof(NodeT));
    nt->name_rule = name;
    for(int i =0;i<10;i++){
        nt->children[i]=NULL;
    }
    nt->parent=parent;
    nt->terminal=0;
    nt->countOfChild=0;
    parent->children[parent->countOfChild++] = nt;
    return nt;
}

NodeT* createTerminalNodeT(int name,NodeT* parent){
    NodeT* nt = (NodeT*)malloc(sizeof(NodeT));
    nt->name_rule = name;
    for(int i =0;i<10;i++){
        nt->children[i]=NULL;
    }
    nt->parent=parent;
    nt->terminal=1;
    nt->countOfChild=0;
    parent->children[parent->countOfChild++] = nt;
    return nt;
}
void inorder(NodeT* nt){
    if(nt->terminal==1){
        //printf("%d",nt->terminal);
        printf("%d",nt->name_rule);
        return;
    }
    inorder(nt->children[0]);
    printf("%d",nt->name_rule);
    for(int i =1;i<nt->countOfChild;i++){
        //printf("yo");
        inorder(nt->children[i]);
    }
}


#endif