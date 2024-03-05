#include <stdlib.h>
#include <stdbool.h>
#include "parser.h"
#include "lexer.h"

int main(int argc, char *argv[])
{


    // char* file_name = (char)malloc(100 * sizeof(char));
    // printf("Welcome to the menu driven program\n");
    // printf("%s\n",argv[1]);
    // // memset(file_name, '\0', 100);
    // // strcpy(file_name, argv[1]);
    char* file_name = argv[1];
    char choice;
    printf("Welcome to the menu driven program\n");
    printf("Both lexical and syntax analysis modules are implemented in this project\n\n");
    printf("The team members are as follows:\n");
    printf("1.Ayush Gupta (2020B3A70838P) \n");
    printf("2.Bhavishya Garg(2020B3A71425P) \n");
    printf("3.Kartik Dang(2020B3A70880P) \n");
    printf("4.Mayank Verma(2020B3A70841P) \n");
    printf("5.Rahul Ginodia(2020B3A70784P) \n");
    printf("6. Srijan Khatri(2020B4A70836P)\n\n");
    printf("Welcome to the menu driven program\n");
    printf("Enter your choice:\n");
    printf("0 : For exit \n");
    printf("1. Remove comments\n");
    printf("2. Print tokens\n");
    printf("3.Print Errors and parse tree\n");
    printf("4. Print time\n");
    scanf("%c", &choice);
    while (choice != '0')
    {
        if (choice == '1')
        {
            removeComments(file_name);
        }
        else if (choice == '2')
        {
            // printTokens(file_name);
            printTokens(file_name);
        }
        else if (choice == '3')
        {
            // parseTree(file_name);
        }
        else if (choice == '4')
        {
            // printTime(file_name);
        }
        else
        {
            printf("Invalid choice\n");
        }
        printf("0 : For exit \n1 : For removal of comments print the comment free code on the console \n2 : For printing the token list (on the console) generated by the lexer. This option performs lexical analysis and prints all tokens and lexemes line number wise. Here, the tokens are not passed  to the parser, but printed on the console only. Each token appears in a new line along with the corresponding lexeme and line number. (invoke only lexer) \n3 : For parsing to verify the syntactic correctness of the input source code and printing the parse tree appropriately. This option prints all errors - lexical and syntactic, line number wise, on the console and prints parse tree in the file as mentioned in the command line below. (Invoke both lexer and parser). \n4: For printing (on the console) the total time taken by your project code of lexer and parser to verify the syntactic correctness. ");
        scanf("%c", &choice);
    }
}