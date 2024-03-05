// Group Number : 22
// ID : 2020B3A70838P		Name : AYUSH GUPTA
// ID : 2020B3A71425P 		Name : BHAVISHYA GARG
// ID : 2020B3A70880P		Name : KARTIK DANG
// ID : 2020B3A70841P		Name : MAYANK VERMA
// ID : 2020B3A70784P		Name : RAHUL GINODIA
// ID : 2020B4A70836P		Name : SRIJAN KHATRI


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "token.h"
#include"hashmap.h"

#ifndef Lexer
#define Lexer

int getStream(FILE* fp);

char *findLexeme(int fwd, int back);

struct tokenDetails *setToken(char *tokenName);

struct tokenDetails *dummyToken(char *tokenName);

struct tokenDetails *setError();

struct tokenDetails *setUnknownError();

int checkPointer(int ptr);

void printStruct(struct tokenDetails *ptr);

struct tokenDetails *getNextToken(FILE *f);

void removeComments(char *testcaseFile);


void fillLookupTable();

TdNode *createLinkedList(char* fileName);

void printTokens(char *fileName);


#endif