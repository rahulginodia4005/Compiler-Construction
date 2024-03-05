// Group Number : 22
// ID : 2020B3A70838P		Name : AYUSH GUPTA
// ID : 2020B3A71425P 		Name : BHAVISHYA GARG
// ID : 2020B3A70880P		Name : KARTIK DANG
// ID : 2020B3A70841P		Name : MAYANK VERMA
// ID : 2020B3A70784P		Name : RAHUL GINODIA
// ID : 2020B4A70836P		Name : SRIJAN KHATRI


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "parse_tree.h"

#ifndef stackImple
#define stackImple

typedef struct Node
{
    struct NodeT* val;
    struct Node *next;
} Node;

typedef struct Stack
{
    Node *head;
    int size;
} Stack;

Stack *createStack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->head = NULL;
    stack->size = 0;
    return stack;
}

Node *createNode(NodeT* treeNode, Stack *stack)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->val = treeNode;
    //newNode->val = val->name_rule;
    newNode->next = stack->head;
    return newNode;
}

void push( Stack* stack, NodeT* val)
{
    Node *newNode = createNode(val, stack);
    stack->head = newNode;
    stack->size++;
    // return newNode;
}

NodeT* pop(Stack *stack)
{
    if (stack->head == NULL)
    {
        return NULL;
    }
    else
    {
        NodeT* treeNode = stack->head->val;
        Node *temp = stack->head;
        stack->head = stack->head->next;
        free(temp);
        stack->size--;
        return treeNode;
    }
}

int peek(Stack *stack)
{
    if (stack->head == NULL)
    {
        return -1;
    }else{
        return stack->head->val->name_rule;
    }
}

void printStack(Stack* stack){
    Node* temp = stack->head;
    while(temp){
        printf("%d\n", temp->val->name_rule);
        temp = temp->next;
    }
}


// int main(){
//     Stack* st = createStack();
//     push(st, 1);
//     push(st, 2);
//     push(st, 3);

//     printStack(st);
//     printf("\n%d\n\n",pop(st));
//     printStack(st);
// }


#endif