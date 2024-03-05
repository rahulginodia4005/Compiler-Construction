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
    char *file_name = argv[1];
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
            printParseTree(file_name);
        }
        else if (choice == '4')
        {
            // printTime(file_name);
        }
        else
        {
            printf("Invalid choice\n");
        }

        printf("Enter your choice:\n");
        printf("0 : For exit \n");
        printf("1. Remove comments\n");
        printf("2. Print tokens\n");
        printf("3.Print Errors and parse tree\n");
        printf("4. Print time\n");
        scanf("%c", &choice);
    }
}