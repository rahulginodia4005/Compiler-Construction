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

// void printTwinBuffer(struct twinBuffer *TwinBuffer);

void fillLookupTable();

TdNode *createLinkedList();

void printTokens(char *fileName)


#endif