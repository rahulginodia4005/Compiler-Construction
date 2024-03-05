// Group Number : 22
// ID : 2020B3A70838P		Name : AYUSH GUPTA
// ID : 2020B3A71425P 		Name : BHAVISHYA GARG
// ID : 2020B3A70880P		Name : KARTIK DANG
// ID : 2020B3A70841P		Name : MAYANK VERMA
// ID : 2020B3A70784P		Name : RAHUL GINODIA
// ID : 2020B4A70836P		Name : SRIJAN KHATRI


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