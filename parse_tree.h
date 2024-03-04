#include<string.h>
#include<stdlib.h>
#include<stdio.h>

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
void connecting(NodeT* parent,NodeT* child){
    parent->children[parent->countOfChild++] = child;
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
    connecting(parent,nt);
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
    connecting(parent,nt);
    return nt;
}
void inorder(NodeT* nt){
    if(nt->terminal==1){
        //printf("%d",nt->terminal);
        printf("%d",nt->name_rule);
        return;
    }
    printf("%d",nt->name_rule);
    for(int i =0;i<nt->countOfChild;i++){
        //printf("yo");
        inorder(nt->children[i]);
    }
    return;

}




