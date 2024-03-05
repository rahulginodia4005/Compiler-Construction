#include<stdlib.h>
#include<stdio.h>
#include"grammar.h"
#include"lexer.h"
#include"parserDef.h"

#ifndef parser
#define parser

void readGrammar();

void produce_first_set();

void produce_follow_set();

void ComputeFirstAndFollowSets(char *fileName);

ParserTable* create_parser_table();

bool parseInputSourceCode(char *fileName);

void init(char *fileName);

void printParseTree(char *fileName);

void PrintTime(char *fileName);

#endif