#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include<string.h>

#ifndef tokenImple
#define tokenImple

typedef struct tokenDetails{
    char token[100];
    char lexeme[100];
    int lineNumber;
    int value;
    bool err;
    char errMessage[100];
}TokenDetails;

typedef struct tdNode{
    struct tokenDetails* tokenDet;
    struct tdNode* next;
}TdNode;

static TdNode* createNewLinkedList(){
    TdNode* head = (TdNode*)malloc(sizeof(TdNode));
    head->tokenDet = NULL;
    head->next = NULL;
    return head;
}

static TdNode* addNewNode(TdNode* head, struct tokenDetails* tokenDets){
    if(strcmp(tokenDets->token,"Dummy")==0){
        return head;
    }
    if(head->tokenDet == NULL){
        head->tokenDet = tokenDets;
        return head;
    }else{
        TdNode* temp = head;
        while(temp->next!=NULL){
            temp = temp->next;
        }
        TdNode* newNode = (TdNode*)malloc(sizeof(TdNode));
        newNode->tokenDet = tokenDets;
        newNode->next = NULL;
        temp->next = newNode;
        return head;
    }
}

static void printLinkedList(TdNode* head){
    TdNode* temp = head;
    while(temp!=NULL){
        printf("Line No: %d \t Lexeme: %s \t Token:%s \t\n", temp->tokenDet->lineNumber, temp->tokenDet->lexeme, temp->tokenDet->token, temp->tokenDet->errMessage);
        temp = temp->next;
    }
}

#endif  