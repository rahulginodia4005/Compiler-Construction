#include<stdlib.h>
#include<stdio.h>
#include"grammar.h"
#include"lexer.h"
#include"ParserTable.h"

#ifndef parser
#define parser

void readGrammar();

void produce_first_set();

void produce_follow_set();

void ComputeFirstAndFollowSets();

ParserTable* create_parser_table();

void parseInputSourceCode(char *fileName);

void init(char *fileName);

void printParseTree(char *fileName);

#endif