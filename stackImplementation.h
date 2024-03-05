#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "parse_tree.h"

#ifndef stackImple
#define stackImple

typedef struct Node
{
    int val;
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

Node *createNode(int val, Stack *stack)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->val = val;
    newNode->next = stack->head;
    return newNode;
}

void push( Stack* stack, int val)
{
    Node *newNode = createNode(val, stack);
    stack->head = newNode;
    stack->size++;
    // return newNode;
}

int pop(Stack *stack)
{
    if (stack->head == NULL)
    {
        return NULL;
    }
    else
    {
        int val = stack->head->val;
        Node *temp = stack->head;
        stack->head = stack->head->next;
        free(temp);
        stack->size--;
        return val;
    }
}

int peek(Stack *stack)
{
    if (stack->head == NULL)
    {
        return -1;
    }else{
        return stack->head->val;
    }
}

void printStack(Stack* stack){
    Node* temp = stack->head;
    while(temp){
        printf("%d\n", temp->val);
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