#include<stdlib.h>
#include<stdio.h>
#include"parser.h"
#include"lexer.h"
#include"token.h"
#include"parse_tree.h"
#include"stackImplementation.h"
#include<time.h>
const int MAX_SIZE = 1000;

HashMap *strToI;
HashMapI *iToStr = NULL, *iToStruct, *ruleMapFirst;
ParserTable* table;
NodeT* root;
bool printparsetree = 1;

clock_t start_time, end_time;
double total_CPU_time, total_CPU_time_in_seconds;

void readGrammar() {
    FILE* fp = fopen("intAllocation.txt", "r");
    if(fp == NULL) {
        perror("Error in intAllocation File");
        return;
    }
    char data[200];
    int line_number = 0;
    while(fgets(data, 200, fp)) {
        line_number++;
        int ind = 0;
        while(data[ind] != '\n') ind++;
        char *newStr = (char*) malloc((ind + 1) * sizeof(char));
        memset(newStr, '\0', (ind + 1) * sizeof(char));
        for(int i = 0;i<ind;i++) newStr[i] = data[i];
        HM_insert(strToI, newStr, line_number);
        HMI_insert(iToStr, line_number, newStr);
        // if(line_number == 16) printf("%s", newStr);
        // printf("%s\t%d\t%d\n", newStr, HM_search(strToI, newStr), strlen(newStr));
    }
    fclose(fp);
    fp = fopen("grammarText.txt", "r");
    if(fp == NULL) {
        perror("Error in opening grammar file");
        return;
    }
    line_number = 0;
    while(fgets(data, 200, fp)) {
        Rule* newRule = NULL;
        bool lhs = false;
        NonTerminals* prev = NULL, *lhsNT = NULL;
        // printf("%s\n\n", data);
        line_number++;
        for(int i = 0;i<200;i++) {
            int ind = 0;
            if(data[i] == '<') {
                i++;
                char *non_terminal = (char*) malloc(50 * sizeof(char));
                memset(non_terminal, '\0', 50 * sizeof(char));
                int non_terminal_ind = 0;
                while(data[i] != '>') {
                    non_terminal[non_terminal_ind++] = data[i++];
                }
                char *newNonTerminal = (char*) malloc((non_terminal_ind + 1) * sizeof(char));
                memset(newNonTerminal, '\0', (non_terminal_ind + 1) * sizeof(char));
                for(int j = 0;j<non_terminal_ind;j++) {
                    newNonTerminal[j] = non_terminal[j];
                }
                int indNT = HM_search(strToI, newNonTerminal);
                if(strcmp(newNonTerminal, "outputParameters") == 0) indNT = 31;
                else if(strcmp(newNonTerminal, "fieldDefinitions") == 0)  indNT = 16;
                NonTerminals* newNT = NULL;
                if(HMI_search(iToStruct, indNT) == NULL) {
                    newNT = create_nonTerminal(indNT);
                    HMI_insert(iToStruct, indNT, newNT);
                }
                else newNT = HMI_search(iToStruct, indNT);
                if(!lhs) {
                    lhs = true;
                    lhsNT = newNT;
                }
                else{
                    newRule = addToRule(newRule, newNT);
                }
                HMI_insert(ruleMapFirst, indNT, false);
                prev = newNT;
                // printf("%d\t%d\n", indNT, newNT->name);
                // printf("%d\t%d\n", line_number, HM_search(strToI, newNonTerminal));
                free(non_terminal);
            }
            else if(data[i] == 'T' || data[i] == 'e') {
                char *terminal = (char*) malloc(50 * sizeof(char));
                memset(terminal, '\0', 50 * sizeof(char));
                int terminal_ind = 0;
                while(data[i] != ' ' && data[i] != '\n') {
                    terminal[terminal_ind++] = data[i++];
                }
                i--;
                char *newTerminal = (char*) malloc(terminal_ind * sizeof(char));
                memset(newTerminal, '\0', terminal_ind * sizeof(char));
                for(int j = 0;j<terminal_ind;j++) {
                    newTerminal[j] = terminal[j];
                }
                int indT = (int)HM_search(strToI, newTerminal);
                NonTerminals* newT = NULL;
                if(HMI_search(iToStruct, indT) == NULL) {
                    newT = create_terminal(indT);
                    HMI_insert(iToStruct, indT, newT);
                }
                else newT = HMI_search(iToStruct, indT);
                // printf("%d\t%d\n", indT, newT->name);
                // printf("%d\t%d\n", line_number, HM_search(strToI, newTerminal));
                newRule = addToRule(newRule, newT);
                prev = newT;
                HMI_insert(ruleMapFirst, indT, false);
                free(terminal);
            }
            else if(data[i] == '|') {
                // printf("%d\t", prev->name);
                if(!checkDuplicacyLhsFollowset(prev, lhsNT)) prev->lhsFollow[prev->lhsFollow_ind++] = lhsNT;
                addRuleToNonTerminal(lhsNT, newRule);
                newRule = NULL;

            }
            else if(data[i] == '\n'){
                if(!checkDuplicacyLhsFollowset(prev, lhsNT)) prev->lhsFollow[prev->lhsFollow_ind++] = lhsNT;
                addRuleToNonTerminal(lhsNT, newRule);
                prev = NULL;
                lhs = false;
                newRule = NULL;
                lhsNT = NULL;
                break;
            }
            else continue;
        }
    }
    HM_insert(strToI, "$", 0);
    HMI_insert(iToStr, 0, "$");
    NonTerminals* temp = HMI_search(iToStruct, 1);
    NonTerminals* dollar = create_terminal(0);
    temp->follow_set[temp->follow_set_ind++] = dollar;
    NonTerminals* curr = HMI_search(iToStruct, 50);
    curr->follow_set[curr->follow_set_ind++] = HMI_search(iToStruct, 76);
    curr = HMI_search(iToStruct, 51);
    curr->follow_set[curr->follow_set_ind++] = HMI_search(iToStruct, 76);
}

void produce_first_set() {
    mainGenerateFirstSets(iToStruct, ruleMapFirst);
}

void produce_follow_set() {
    mainGenerateNextToSets(iToStruct);
    mainGenerateFollowSets(iToStruct);
}

void ComputeFirstAndFollowSets() {
    strToI = create_table(MAX_SIZE); //will be used once, to map string to integer allocated
    ruleMapFirst = create_tableI(MAX_SIZE); //check whose first sets has been calculated
    iToStruct = create_tableI(MAX_SIZE); //main mapping from integer allocated to struct formed
    iToStr = create_tableI(MAX_SIZE);
    readGrammar();
    produce_first_set();
    produce_follow_set();
    for(int i = 1;i<=53;i++) {
        NonTerminals* curr = HMI_search(iToStruct, i);
        printf("FIRST SET: %s = {", HMI_search(iToStr, i));
        for(int j = 0;j<curr->first_set_ind;j++) {
            printf("%s", HMI_search(iToStr, curr->first_set[j]->name));
            if(j != curr->first_set_ind - 1) printf(",");
        }
        printf("}\n");
        printf("FOLLOW SET: %s = {", HMI_search(iToStr, i));
        for(int j = 0;j<curr->follow_set_ind;j++) {
            printf("%s", HMI_search(iToStr, curr->follow_set[j]->name));
            if(j != curr->follow_set_ind - 1) printf(",");
        }
        printf("}\n\n");
    }
}

ParserTable* create_parser_table() {
    ParserTable* table = create(53, 58);
    HMI_insert(iToStr, 200, "syn");
    HM_insert(strToI, "syn", 200);
    NonTerminals* syn = create_terminal(200);
    Rule* synRule = NULL;
    synRule = addToRule(synRule, syn);
    HMI_insert(iToStruct, 200, syn);
    int synAdd[9] = {28, 10, 31, 46, 13, 36, 47, 22, 33};
    fillParserTable(table, iToStruct, synRule);
    for(int j = 0;j<9;j++) {
        for(int i = 0;i<53;i++) {
            insert(table, synRule, i, synAdd[j]);
        }
    }
    return table;
}

void parseInputSourceCode(char *fileName) {
    root = createRootNodeT(iToStr);
    NodeT* parent = root;
    Stack* st = createStack();
    push(st, root); 
    printf("%d", table->table[27][28]->nt->name);

    // I need linked list of tokens.
    TdNode* ll = createLinkedList(fileName);
    
    TdNode* ll_temp = ll;
    printparsetree = 1;
    //I need pareser table
    bool syn_needed = false;
    while(ll_temp!=NULL){
        if(peek(st)==-1){
            printf("Stack is empty\n");
            break;
        }
        int ind = 0;
        while(ll_temp->tokenDet->token[ind]!='\0') ind++;
        char *token_seen = (char*) malloc(ind * sizeof(char));
        memset(token_seen, '\0', ind * sizeof(char));
        for(int i = 0;i<ind;i++) {
            token_seen[i] = ll_temp->tokenDet->token[i];
        }
        int stack_top = peek(st);
        int tp = HM_search(strToI,token_seen);
        // printf("Top of stack: %d\n",stack_top);
        if(peek(st) >= 54) {
            if(peek(st) == 111) {
                int popped = pop(st)->name_rule;
                //NodeT* popped = pop(st);
                printf("1Terminal found: %s\n", HMI_search(iToStr, popped));
                continue;
            }
            char* prevToken = (char*) malloc(sizeof(char)*strlen(ll_temp->tokenDet->lexeme));
            memset(prevToken,'\0',sizeof(char)*strlen(ll_temp->tokenDet->lexeme));
            for(int i=0;i<strlen(ll_temp->tokenDet->lexeme);i++){
                prevToken[i]=ll_temp->tokenDet->lexeme[i];
            }
            
            if(peek(st) != tp) {
                //printf("%s-----\t", prevToken);
                if(strcmp(ll_temp->tokenDet->token, "TK_INVALID_SIZE")==0){
                    printf("Line %d\tError: %s\n",ll_temp->tokenDet->lineNumber ,ll_temp->tokenDet->errMessage);
                    ll_temp=ll_temp->next;
                    printparsetree=0;
                    continue;
                }
                else if(strcmp(ll_temp->tokenDet->token, "TK_INVALID_PATTERN")==0){
                    printf("Line %d\tError: %s\n",ll_temp->tokenDet->lineNumber,ll_temp->tokenDet->errMessage);
                    ll_temp=ll_temp->next;
                    printparsetree=0;
                    continue;
                }
                else if(strcmp(ll_temp->tokenDet->token, "TK_UNKNOWN")==0){
                    printf("Line %d\tError: %s\n",ll_temp->tokenDet->lineNumber,ll_temp->tokenDet->errMessage);
                    ll_temp=ll_temp->next;
                    printparsetree=0;
                    continue;
                }
                else{
                    printf("Line %d\tError: The token %s for lexeme %s does not match with the expected token %s\n", ll_temp->tokenDet->lineNumber,token_seen, prevToken, HMI_search(iToStr,peek(st)));
                }
                pop(st);
                printparsetree=0;
                printf("--------\n");
                continue;
            }
            NodeT* popped = pop(st);
            if(strcmp(HMI_search(iToStr,popped->name_rule), "TK_NUM") == 0 || strcmp(HMI_search(iToStr,popped->name_rule), "TK_RNUM") == 0) passingLexeme(popped, ll_temp->tokenDet->lexeme, true);
            else passingLexeme(popped, ll_temp->tokenDet->lexeme, false);
            printf("3Terminal found: %s\n", HMI_search(iToStr, popped->name_rule));
            ll_temp = ll_temp->next;
            continue;
        }

        printf("Top of stack: %d\n",stack_top);
        int col = tp - 54;
        int row = stack_top - 1;
        Rule* rule = table->table[row][col];
        // if(col<0||col>58){
        //     if(strcmp(ll_temp->tokenDet->token,"TK_INVALID_PATTERN")==0){
        //         printf("Error: %s\n",ll_temp->tokenDet->errMessage);
        //         ll_temp=ll_temp->next;
        //     }
        // }
        if(rule == NULL) {
            if(strcmp(ll_temp->tokenDet->token,"TK_INVALID_PATTERN")==0){
                printf("Line %d\tError: %s\n",ll_temp->tokenDet->lineNumber,ll_temp->tokenDet->errMessage);
            }
            else if(strcmp(ll_temp->tokenDet->token,"TK_UNKNOWN")==0){
                printf("Line %d\tError: %s\n",ll_temp->tokenDet->lineNumber,ll_temp->tokenDet->errMessage);
            }
            else if(strcmp(ll_temp->tokenDet->token,"TK_INVALID_SIZE")==0){
                printf("Line %d\tError: %s\n",ll_temp->tokenDet->lineNumber,ll_temp->tokenDet->errMessage);
            }
            else{
                char* prevToken = (char*) malloc(sizeof(char)*strlen(ll_temp->tokenDet->lexeme));
                memset(prevToken,'\0',sizeof(char)*strlen(ll_temp->tokenDet->lexeme));
                for(int i=0;i<strlen(ll_temp->tokenDet->lexeme);i++){
                    prevToken[i]=ll_temp->tokenDet->lexeme[i];
                }
                syn_needed = true;
                // printf("4Error occured. Cannot parse %s.\n", token_seen);
                printf("Line %d\tError: The token %s for lexeme %s does not match with the expected token %s\n",ll_temp->tokenDet->lineNumber, token_seen, prevToken, HMI_search(iToStr,peek(st)));
            } 
            ll_temp = ll_temp->next;
            printparsetree=0;
            // printf("--------\n");
            continue;
        }
        else if(rule->nt->name == 200){
            syn_needed = false;
            int popped = pop(st)->name_rule;
            // printf("MisMatched with: %s\n", token_seen);
            // printf("Synch token captured. Popped %d\t%s\n", popped, HMI_search(iToStr, popped));
            printf("Line %d\tError: Invalid token %s encountered with value %s stack top %s\n",ll_temp->tokenDet->lineNumber,ll_temp->tokenDet->token,ll_temp->tokenDet->lexeme,HMI_search(iToStr,popped));
            printf("--------\n");
            printparsetree=0;
            continue;
        }
        else if(!syn_needed) {
            
            if(strcmp(ll_temp->tokenDet->token, "TK_INVALID_PATTERN")==0){
                    printf("Line %d\tError: %s\n",ll_temp->tokenDet->lineNumber,ll_temp->tokenDet->errMessage);
                    ll_temp=ll_temp->next;
                    printparsetree=0;
                    continue;
                //printf("row-%d col-%d",row,col);
            }
            Rule* temp_rule = rule;
            NodeT* popped = pop(st);
            printf("Matched with: %s\n", token_seen);
            printf("Rule found. Popped %d\t%s\n", popped->name_rule, HMI_search(iToStr, popped->name_rule));
            int rules[10];
            int i=0;
            while(temp_rule!=NULL){
                rules[i++] = temp_rule->nt->name;
                temp_rule = temp_rule->next;
            }
            NodeT* reversal[i];
            // for(int j=0;j<i;j++){
            //     reversal[j] = (NodeT*) malloc(sizeof(NodeT));
            // }
            for(int j=0;j<i;j++){
                printf("4223Pushed %d\t%s\n", rules[j], HMI_search(iToStr, rules[j]));
                NodeT* treeEntry;
                if(rules[j]>=54){
                    if(strcmp(HMI_search(iToStr,rules[j]), "TK_NUM") == 0 || strcmp(HMI_search(iToStr,rules[j]), "TK_RNUM") == 0) treeEntry = createTerminalNodeT(rules[j],popped, iToStr, ll_temp->tokenDet->lineNumber);
                    else treeEntry = createTerminalNodeT(rules[j],popped, iToStr, ll_temp->tokenDet->lineNumber);
                }
                else{
                    treeEntry  = createNodeT(rules[j],popped, iToStr);
                    //printf("%d\n",treeEntry->name_rule);
                }
                reversal[j] = treeEntry;
                
                //push(st, treeEntry);
            }

            for(int j =i-1;j>=0;j--){
                // printf("Pushed %d\t%s\n", reversal[j]->name_rule, HMI_search(iToStr, reversal[j]->name_rule));
                push(st,reversal[j]);
            }

            // if(peek(st) == tp) {
            //     // printf("Matched with: %s\n", token_seen);
            //     // ll_temp = ll_temp->next;
            // }
            free(token_seen);
            printf("--------\n");
        }
        else{
            if(strcmp(ll_temp->tokenDet->token,"TK_INVALID_PATTERN")==0){
                printf("Line %d\tError: %s\n",ll_temp->tokenDet->lineNumber,ll_temp->tokenDet->errMessage);
            }
            else if(strcmp(ll_temp->tokenDet->token,"TK_UNKNOWN")==0){
                printf("Line %d\tError: %s\n",ll_temp->tokenDet->lineNumber,ll_temp->tokenDet->errMessage);
            }
            else if(strcmp(ll_temp->tokenDet->token,"TK_INVALID_SIZE")==0){
                printf("Line %d\tError: %s\n",ll_temp->tokenDet->lineNumber,ll_temp->tokenDet->errMessage);
            }
            else{
                char* prevToken = (char*) malloc(sizeof(char)*strlen(ll_temp->tokenDet->lexeme));
                memset(prevToken,'\0',sizeof(char)*strlen(ll_temp->tokenDet->lexeme));
                for(int i=0;i<strlen(ll_temp->tokenDet->lexeme);i++){
                    prevToken[i]=ll_temp->tokenDet->lexeme[i];
                }
                syn_needed = true;
                // printf("4Error occured. Cannot parse %s.\n", token_seen);
                printf("Line %d\tError: The token %s for lexeme %s does not match with the expected token %s\n",ll_temp->tokenDet->lineNumber, token_seen, prevToken, HMI_search(iToStr,peek(st)));
            } 
            ll_temp = ll_temp->next;
            printparsetree=0;
        }
    }
}

void init(char *fileName) {
    strToI = create_table(MAX_SIZE); //will be used once, to map string to integer allocated
    ruleMapFirst = create_tableI(MAX_SIZE); //check whose first sets has been calculated
    iToStruct = create_tableI(MAX_SIZE); //main mapping from integer allocated to struct formed
    iToStr = create_tableI(MAX_SIZE);
    readGrammar();
    if(table == NULL) {
        produce_first_set();
        produce_follow_set();
    } 
    // ComputeFirstAndFollowSets();
    table = create_parser_table();
    parseInputSourceCode(fileName);
    // free(strToI);
    // free(ruleMapFirst);
    // free(iToStruct);
    // free(iToStr);
    // free(root);
    // free(table);
}

void printParseTree(char *fileName) {
    if(iToStr == NULL) {
        start_time = clock();
        init(fileName);
        end_time = clock();
        total_CPU_time = (double)(end_time - start_time);
        total_CPU_time_in_seconds = total_CPU_time / CLOCKS_PER_SEC;
    }
    if(printparsetree==1){
        printf("Input source code is syntactically correct...........\n");
        inorderDriver(root,iToStr);
    }
    
}

void PrintTime(char *fileName) {
    if(iToStr == NULL) {
        start_time = clock();
        init(fileName);
        end_time = clock();
        total_CPU_time = (double)(end_time - start_time);
        total_CPU_time_in_seconds = total_CPU_time / CLOCKS_PER_SEC;
    }
    printf("Total CPU time: %f\n", total_CPU_time);
    printf("Total CPU time in seconds: %f\n", total_CPU_time_in_seconds);
}

