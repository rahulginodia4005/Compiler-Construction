#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

struct tokenDetails
{
    char token[100];
    char lexeme[100];
    int lineNumber;
    int value;
    bool err;
    char errMessage[100];
};

typedef struct LinkedList{
    int value;
    struct LinkedList* next;
} LinkedList;

typedef struct Stack{
    LinkedList* list;
};

LinkedList* allocate_list() {
    LinkedList* newList = (LinkedList*) malloc(sizeof(LinkedList));
    return newList;
}

struct Stack* allocate_stack(){
    struct Stack* newStack = (struct Stack*) malloc(sizeof(struct Stack));
    return newStack;
}

LinkedList* list_insert(LinkedList* list, int value) {
    if(!list) {
        LinkedList* head = allocate_list();
        head->val = val;
        head->next = NULL;
        list = head;
        return list;
    }
    else if(list->next == NULL){
        LinkedList* node = allocate_list();
        node->val = val;
        node->next = NULL;
        list->next = node;
        return list;
    }

    LinkedList* temp = list;

    while(temp->next->next) temp = temp->next;
    LinkedList* node = allocate_list();
    node->val = val;
    node->next = NULL;
    temp->next = node;
    return list;
}

