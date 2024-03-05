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
    rootNodeT->valueIfNumber = "---";
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
    node->valueIfNumber = "---";
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
    node->valueIfNumber = "---";
    node->lexeme = "---";
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
    fprintf(fp, "%s", nt->lexeme);
    for(int i = 0;i<50 - strlen(nt->lexeme);i++) fprintf(fp, " ");
    fprintf(fp, "%d", nt->lineNo);
    for(int i = 0;i<25 - 2;i++) fprintf(fp, " ");
    fprintf(fp, "%s", nt->token_name);
    for(int i = 0;i<25 - strlen(nt->token_name);i++) fprintf(fp, " ");
    fprintf(fp, "%s", nt->valueIfNumber);
    for(int i = 0;i<30 - strlen(nt->valueIfNumber);i++) fprintf(fp, " ");
    fprintf(fp, "%s", nt->parentNodeSymbol);
    for(int i = 0;i<25 - strlen(nt->parentNodeSymbol);i++) fprintf(fp, " ");
    if(nt->isLeafNode) {
        fprintf(fp, "Yes");
        for(int i = 0;i<25 - 3;i++) fprintf(fp, " ");
    }
    else{
        fprintf(fp, "No");
        for(int i = 0;i<25 - 2;i++) fprintf(fp, " ");
    }
    fprintf(fp, "%s", nt->nodeSymbol);
    fprintf(fp, "\n");
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
    FILE *fp = fopen("parsingOutput.txt", "w+");
    if(fp == NULL) {
        printf("Error in opening output file");
        return;
    }
    fprintf(fp, "\t");
    fprintf(fp, "Lexeme");
    for(int i = 0;i<50 - 6;i++) fprintf(fp, " ");
    fprintf(fp, "Line Number");
    for(int i = 0;i<25 - 14;i++) fprintf(fp, " ");
    fprintf(fp, "Token Name");
    for(int i = 0;i<25 - 13;i++) fprintf(fp, " ");
    fprintf(fp, "ValueIfNumber");
    for(int i = 0;i<35 - 16;i++) fprintf(fp, " ");
    fprintf(fp, "ParentNodeSymbol");
    for(int i = 0;i<25 - 19;i++) fprintf(fp, " ");
    fprintf(fp, "isLeafNode");
    for(int i = 0;i<32 - 13;i++) fprintf(fp, " ");
    fprintf(fp, "NodeSymbol");
    fprintf(fp, "\n");
    fprintf(fp, "\n");
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