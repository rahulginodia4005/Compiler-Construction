#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include "hashmap_int.h"
#ifndef parseTree
#define parseTree

typedef struct NodeT{
    int name_rule;
    char* lexeme;
    char* token_name;
    char* valueIfNumber;
    char* parentNodeSymbol;
    char* nodeSymbol;
    int lineNo;
    struct NodeT* children[10];
    int countOfChild;
    struct NodeT* parent;
    int isLeafNode;
}NodeT;

static NodeT* createRootNodeT(HashMapI* iToStr){
    NodeT* rootNodeT = (NodeT*) malloc(sizeof(NodeT));
    rootNodeT->name_rule=1;
    rootNodeT->nodeSymbol = HMI_search(iToStr,rootNodeT->name_rule);
    rootNodeT->parentNodeSymbol = "ROOT";
    rootNodeT->lexeme = "---";
    rootNodeT->token_name = "---"; 
    rootNodeT->lineNo = -1;
    for(int i =0;i<10;i++){
        rootNodeT->children[i] = NULL;
    }
    rootNodeT->parent=NULL;
    rootNodeT->countOfChild=0;
    rootNodeT->isLeafNode=false;
    return rootNodeT;
}
static NodeT* createNodeT(int name,NodeT* parent,HashMapI* iToStr){
    NodeT* node = (NodeT*) malloc(sizeof(NodeT));
    node->name_rule = name;
    node->nodeSymbol = HMI_search(iToStr,name);
    node->parentNodeSymbol = parent->nodeSymbol;
    node->lexeme = "---";
    node->token_name = "---"; 
    node->lineNo = -2;
    parent->children[parent->countOfChild++] = node;
    for(int i =0;i<10;i++){
        node->children[i] = NULL;
    }
    node->parent=parent;
    node->countOfChild=0;
    node->isLeafNode=false;
    return node;
}

static NodeT* createTerminalNodeT(int name, NodeT* parent, HashMapI* iToStr, int lineNo){
    NodeT* node = (NodeT*) malloc(sizeof(NodeT));
    node->name_rule = name;
    node->nodeSymbol = HMI_search(iToStr,name);
    node->parentNodeSymbol = parent->nodeSymbol;
    node->token_name = node->nodeSymbol; 
    parent->children[parent->countOfChild++] = node;
    node->lineNo = lineNo;
    for(int i =0;i<10;i++){
        node->children[i] = NULL;
    }
    node->parent=parent;
    node->countOfChild=0;
    node->isLeafNode=true;
    return node;
}

static void passingLexeme(NodeT* nt, char* lexeme, bool num) {
    if(num) {
        nt->valueIfNumber = (char*)malloc(sizeof(char) * (strlen(lexeme) + 1));
        memset(nt->valueIfNumber, '\0', sizeof(char) * (strlen(lexeme) + 1));
        for(int i = 0;i<strlen(lexeme);i++) {
            nt->valueIfNumber[i] = lexeme[i];
        }
    }
    nt->lexeme = (char*)malloc(sizeof(char) * (strlen(lexeme) + 1));
    memset(nt->lexeme, '\0', sizeof(char) * (strlen(lexeme) + 1));
    for(int i = 0;i<strlen(lexeme);i++) {
        nt->lexeme[i] = lexeme[i];
    }
}

static void giveValuesToFile(FILE* fp, NodeT* nt) {
    fprintf(fp, "\t");
    fprintf(fp, "%s\t\t", nt->lexeme);
    fprintf(fp, "%d\t\t", nt->lineNo);
    fprintf(fp, "%s\t\t", nt->token_name);
    fprintf(fp, "%s\t\t", nt->valueIfNumber);
    fprintf(fp, "%s\t\t", nt->parentNodeSymbol);
    if(nt->isLeafNode) fprintf(fp, "Yes\t\t");
    else fprintf(fp, "No\t\t");
    fprintf(fp, "%s\n", nt->nodeSymbol);
}

static void inorder(NodeT* nt,HashMapI* iToStr, FILE *fp){
    if(nt->countOfChild == 0){
        //printf("%d",nt->terminal);
        printf("%s\t",HMI_search(iToStr,nt->name_rule));
        giveValuesToFile(fp, nt);
        return;
    }
    inorder(nt->children[0],iToStr, fp);
    printf("%s\t",HMI_search(iToStr,nt->name_rule));
    giveValuesToFile(fp, nt);
    for(int i =1;i<nt->countOfChild;i++){
        //printf("yo");
        inorder(nt->children[i],iToStr, fp);
    }
}

static void inorderDriver(NodeT* nt, HashMapI* iToStr) {
    FILE *fp = fopen("parsingOutput.txt", "w");
    if(fp == NULL) {
        printf("Error in opening output file");
        return;
    }
    fprintf(fp, "\t");
    fprintf(fp, "Lexeme\t\t");
    fprintf(fp, "Line Number\t\t");
    fprintf(fp, "Token Name\t\t");
    fprintf(fp, "ValueIfNumber\t\t");
    fprintf(fp, "ParentNodeSymbol\t\t");
    fprintf(fp, "isLeafNode\t\t");
    fprintf(fp, "NodeSymbol\n");
    // printf("\t\t");
    // printf("Lexeme\t\t");
    // printf("Line Number\t\t");
    // printf("Token Name\t\t");
    // printf("ValueIfNumber\t\t");
    // printf("ParentNodeSymbol\t\t");
    // printf("isLeafNode\t\t");
    // printf("NodeSymbol\n");
    inorder(nt, iToStr, fp);
    fclose(fp);
}


#endif