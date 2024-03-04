#include<stdlib.h>
#include<stdio.h>
#include"grammar.h"
#include"hashmap.h"
#include"ParserTable.h"

void readGrammar(HashMap* strToI, HashMapI* ruleMapFirst, HashMapI* iToStruct, HashMapI* iToStr);

void produce_first_set(HashMapI* iToStruct, HashMapI* ruleMapFirst);

void produce_follow_set(HashMapI* iToStruct);

ParserTable* create_parser_table(HashMapI* iToStruct, HashMapI* iToStr, HashMap* strToI);