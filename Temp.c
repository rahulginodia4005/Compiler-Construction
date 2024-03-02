#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int currLine = 1;

struct tokenDetails
{
    char token[100];
    char lexeme[100];
    int lineNumber;
    int value;
    bool err;
    char errMessage[100];
} TokenDetails;

struct twinBuffer
{
    int size;
    int fwd;
    int back;
    char buffer[2048];
};

struct twinBuffer *TwinBuffer;
// void makeToken(struct tokenInfo t, char *a, char *b) {
//     strcpy(t.lexeme, a);
//     strcpy(t.tokenName, b);
// }

char *findLexeme(int fwd, int back)
{
    char *currBuffer = TwinBuffer->buffer;
    char *lexeme = (char *)malloc(100 * sizeof(char));
    int i = 0;
    for (i = back; i < fwd; i++)
    {
        lexeme[i - back] = currBuffer[i];
    }
    lexeme[i - back] = '\0';
    return lexeme;
}

struct tokenDetails *setToken(struct tokenDetails *ptr, char *tokenName)
{
    ptr->err = false;
    strcpy(ptr->token, tokenName);
    ptr->lineNumber = currLine;
    strcpy(ptr->lexeme, findLexeme(TwinBuffer->fwd, TwinBuffer->back));
    TwinBuffer->back = TwinBuffer->fwd;
    return ptr;
}

struct tokenDetails *setError(struct tokenDetails *ptr)
{
    ptr->err = true;
    strcpy(ptr->errMessage, "Invalid Pattern");
    ptr->lineNumber = currLine;
    // TwinBuffer->fwd++;
    TwinBuffer->back = TwinBuffer->fwd;
    // return ptr;
    return ptr;
}

void getStream(FILE *fp, char *buffer)
{
    fgets(buffer, 1024, fp);
}

void printStruct(struct tokenDetails *ptr)
{
    printf("Token: %s\n", ptr->token);
    printf("Lexeme: %s\n", ptr->lexeme);
    printf("Line Number: %d\n", ptr->lineNumber);
    printf("Error: %d\n", ptr->err);
    printf("Error Message: %s\n", ptr->errMessage);
}



struct tokenDetails *getNextToken(FILE *f)
{

    // if(B.fwd)
    // struct tokenInfo t;
    // makeToken(t, )
    // return t;

    int currState = 0;
    // Check in twinBuffer which buffer is active
    // char *currBuffer;
    // if (TwinBuffer->activeBuffer == 0)
    // {
    //     // char* currBuffer = TwinBuffer->buffer1;
    //     // if(currBuffer == NULL){
    //     //     f = getStream(f,)
    //     // }
    // }

    char *currBuffer = TwinBuffer->buffer;

    char currChar = currBuffer[TwinBuffer->fwd];
    char beginChar = currBuffer[TwinBuffer->back];

    // printf("CurrChar: %c\n", currChar);
    // printf("BeginChar: %c\n", beginChar);

    while (1)
    {

        // printf("IN \n");
        struct tokenDetails *ptr = (struct tokenDetails *)malloc(sizeof(struct tokenDetails));
        currChar = currBuffer[TwinBuffer->fwd];
        
        switch (currState)
        {

            // printf("CurrState: %d\n", currState);
            printf("IN SWITCH");

            currChar = currBuffer[TwinBuffer->fwd];
            case 0:
                switch (currChar)
                {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    currState = 1;
                    TwinBuffer->fwd++;
                    break;
                case 'a':
                case 'e':
                case 'f':
                case 'g':
                case 'h':
                case 'i':
                case 'j':
                case 'k':
                case 'l':
                case 'm':
                case 'n':
                case 'o':
                case 'p':
                case 'q':
                case 'r':
                case 's':
                case 't':
                case 'u':
                case 'v':
                case 'w':
                case 'x':
                case 'y':
                case 'z':
                    currState = 12;
                    TwinBuffer->fwd++;
                    break;

                case 'b':
                case 'c':
                case 'd':
                    currState = 14;
                    TwinBuffer->fwd++;
                    break;

                case '<':
                    currState = 19;
                    TwinBuffer->fwd++;
                    break;

                case '>':
                    currState = 25;
                    TwinBuffer->fwd++;
                    break;

                case '=':
                    currState = 28;
                    TwinBuffer->fwd++;
                    break;

                case '!':
                    currState = 30;
                    TwinBuffer->fwd++;
                    break;

                case '_':
                    currState = 32;
                    TwinBuffer->fwd++;
                    break;

                case '#':
                    currState = 36;
                    TwinBuffer->fwd++;
                    break;

                case '@':
                    currState = 39;
                    TwinBuffer->fwd++;
                    break;

                case '&':
                    currState = 42;
                    TwinBuffer->fwd++;
                    break;

                case '\t':
                case ' ':
                    currState = 45;
                    TwinBuffer->fwd++;
                    break;

                case '\n':
                    currState = 47;
                    TwinBuffer->fwd++;
                    // currLine++;
                    // Return Token
                    break;

                case '%':
                    currState = 48;
                    TwinBuffer->fwd++;
                    break;

                case '[':
                    currState = 51;
                    TwinBuffer->fwd++;
                    // Return Token
                    break;

                case ']':
                    currState = 50;
                    TwinBuffer->fwd++;
                    // Return Token
                    break;

                case '.':
                    currState = 52;
                    TwinBuffer->fwd++;
                    // Return Token
                    break;

                case ',':
                    currState = 53;
                    TwinBuffer->fwd++;
                    // Return Token
                    break;

                case ';':
                    currState = 54;
                    TwinBuffer->fwd++;
                    // Return Token
                    break;

                case ':':
                    currState = 55;
                    TwinBuffer->fwd++;
                    // Return Token
                    break;

                case '+':
                    currState = 56;
                    TwinBuffer->fwd++;
                    // Return Token
                    break;

                case '-':
                    currState = 57;
                    TwinBuffer->fwd++;
                    // Return Token
                    break;

                case '*':
                    currState = 58;
                    TwinBuffer->fwd++;
                    // Return Token
                    break;

                case '/':
                    currState = 59;
                    TwinBuffer->fwd++;
                    // Return Token
                    break;

                case '(':
                    currState = 60;
                    TwinBuffer->fwd++;
                    // Return Token
                    break;

                case ')':
                    currState = 61;
                    TwinBuffer->fwd++;
                    // Return Token
                    break;

                case '~':
                    currState = 62;
                    TwinBuffer->fwd++;
                    // Return Token
                    break;
                }

                break;

            case 1:
                if (currChar >= '0' && currChar <= '9')
                {
                    currState = 1;
                }
                else if (currChar == '.')
                {
                    currState = 3;
                }
                else
                {
                    currState = 2;
                }
                TwinBuffer->fwd++;

                break;

            case 2: // Return Token TK_NUM
                // int tempFwd = TwinBuffer->fwd - 1;
                TwinBuffer->fwd--;
                return setToken(ptr, "TK_NUM");
                break;

            case 3:
                if (currChar >= '0' && currChar <= '9')
                {
                    currState = 5;
                }
                else
                {
                    currState = 4;
                }
                TwinBuffer->fwd++;
                break;

            case 4: // Return Token TK_NUM
                TwinBuffer->fwd--;
                return setToken(ptr, "TK_NUM");
                break;

                // case 5:Done
                if (currChar >= '0' && currChar <= '9')
                {
                    currState = 6;
                }
                else
                {
                    return setError(ptr);
                    // return ptr;
                }
                TwinBuffer->fwd++;
                break;

            case 6:
                if (currChar == 'E')
                {
                    currState = 8;
                }
                else
                {
                    currState = 7;
                }
                TwinBuffer->fwd++;
                break;

            case 7:
                // Return Token TK_RNUM
                TwinBuffer->fwd--;
                return setToken(ptr, "TK_RNUM");

            case 8:
                if (currChar == '+' || currChar == '-')
                {
                    currState = 9;
                }
                else if (currChar >= '0' && currChar <= '9')
                {
                    currState = 10;
                }
                else
                {
                    currState = 16;
                }
                TwinBuffer->fwd++;
                break;

            case 9:
                if (currChar >= '0' && currChar <= '9')
                {
                    currState = 10;
                }
                else
                {
                    return setError(ptr);
                }
                TwinBuffer->fwd++;
                break;

            case 10:
                if (currChar >= '0' && currChar <= '9')
                {
                    currState = 11;
                } // what about else
                else
                {
                    return setError(ptr);
                    // return ptr;
                }
                TwinBuffer->fwd++;
                break;

            case 11:
                // Return Token TK_RNUM
                return setToken(ptr, "TK_RNUM");
                break;

            case 12:
                if (currChar >= 'a' && currChar <= 'z')
                {
                    currState = 12;
                }
                else
                {
                    currState = 13;
                }
                TwinBuffer->fwd++;
                break;

            case 13: // Return Token TK_
                TwinBuffer->fwd--;
                return setToken(ptr, "TK_FIELDID");
                break;

            case 14:
                if (currChar >= 'a' && currChar <= 'z')
                {
                    currState = 12;
                }
                else if (currChar == '2' && currChar == '7')
                {
                    currState = 15;
                }
                else
                {
                    currState = 13;
                }
                TwinBuffer->fwd++;
                break;

            case 15:
                if (currChar >= 'b' && currChar <= 'd')
                {
                    currState = 15;
                }
                else if (currChar >= '2' && currChar <= '7')
                {
                    currState = 17;
                }
                else
                {
                    currState = 18;
                }
                TwinBuffer->fwd++;
                break;

            case 16: // Return Token TK_RNUM
                TwinBuffer->fwd -= 2;
                return setToken(ptr, "TK_RNUM");
                break;

            case 17:
                if (currChar >= '2' && currChar <= '7')
                {
                    currState = 17;
                }
                else
                {
                    currState = 18;
                }
                TwinBuffer->fwd++;
                break;

            case 18: // Return Token TK_ID
                TwinBuffer->fwd--;
                return setToken(ptr, "TK_ID");
                break;

            case 19:
                if (currChar == '=')
                {
                    currState = 24;
                }
                else if (currChar == '-')
                {

                    currState = 21;
                }
                else
                {
                    currState = 20;
                }
                TwinBuffer->fwd++;
                break;

            case 20: // Return Token TK_LT
                TwinBuffer->fwd--;
                return setToken(ptr, "TK_LT");
                break;

            case 21:
                if (currChar == '-')
                {
                    currState = 22;
                }
                else
                {
                    currState = 63;
                }
                TwinBuffer->fwd++;
                break;

            case 22:
                if (currChar == '-')
                {
                    currState = 23;
                } // What about else
                else
                {
                    // Error
                    return setError(ptr);
                }
                TwinBuffer->fwd++;
                break;

            case 23: // Return Token TK_ASSIGNOP
                return setToken(ptr, "TK_ASSIGNOP");
                break;

            case 24: // Return Token TK_LE
                return setToken(ptr, "TK_LE");
                break;

            case 25:
                if (currChar == '=')
                {
                    currState = 27;
                }
                else
                {
                    currState = 26;
                }
                TwinBuffer->fwd++;
                break;

            case 26: // Return Token TK_GT
                TwinBuffer->fwd--;
                return setToken(ptr, "TK_GT");
                break;

            case 27: // Return Token TK_GE
                return setToken(ptr, "TK_GE");
                break;

            case 28:
                if (currChar == '=')
                {
                    currState = 29;
                } // What about else
                else
                {
                    return setError(ptr);
                }
                TwinBuffer->fwd++;
                break;

            case 29: // Return Token TK_EQ
                return setToken(ptr, "TK_EQ");
                break;

            case 30:
                if (currChar == '=')
                {
                    currState = 31;
                } // What about else
                else
                {
                    return setError(ptr);
                }
                TwinBuffer->fwd++;
                break;

            case 31: // Return Token TK_NE
                return setToken(ptr, "TK_NE");
                break;

            case 32:
                if (currChar >= 'a' && currChar <= 'z' || currChar >= 'A' && currChar <= 'Z')
                {
                    currState = 33;
                } // What about else
                else
                {
                    return setError(ptr);
                }
                break;

            case 33:
                if (currChar >= 'a' && currChar <= 'z' || currChar >= 'A' && currChar <= 'Z' || currChar >= '0' && currChar <= '9')
                {
                    currState = 33;
                }
                else if (currChar >= '0' && currChar <= '9')
                {
                    currState = 34;
                }
                else
                {
                    currState = 35;
                }
                TwinBuffer->fwd++;
                break;

            case 34:
                if (currChar >= '0' && currChar <= '9')
                {
                    currState = 34;
                }
                else
                {
                    currState = 35;
                }
                TwinBuffer->fwd++;
                break;

            case 35: // Return Token TK_FUNID
                TwinBuffer->fwd--;
                return setToken(ptr, "TK_FUNID");
                break;

            case 36:
                if (currChar >= 'a' && currChar <= 'z')
                {
                    currState = 37;
                } // What about else
                else
                {
                    return setError(ptr);
                }
                TwinBuffer->fwd++;
                break;

            case 37:
                if (currChar >= 'a' && currChar <= 'z')
                {
                    currState = 37;
                }
                else
                {
                    currState = 38;
                }
                TwinBuffer->fwd++;
                break;

            case 38: // Return Token TK_RUID
                TwinBuffer->fwd--;
                return setToken(ptr, "TK_RUID");
                break;

            case 39:
                if (currChar == '@')
                {
                    currState = 40;
                } // What about else
                else
                {
                    return setError(ptr);
                }

                TwinBuffer->fwd++;

                break;

            case 40:
                if (currChar == '@')
                {
                    currState = 41;
                } // What about else
                else
                {
                    return setError(ptr);
                }
                TwinBuffer->fwd++;
                break;

            case 41: // Return Token TK_OR
                return setToken(ptr, "TK_OR");
                break;

            case 42:
                if (currChar == '&')
                {
                    currState = 43;
                } // What about else
                else
                {
                    return setError(ptr);
                }
                TwinBuffer->fwd++;
                break;

            case 43:
                if (currChar == '&')
                {
                    currState = 44;
                } // What about else
                else
                {
                    return setError(ptr);
                }
                TwinBuffer->fwd++;
                break;

            case 44: // Return Token TK_AND
                return setToken(ptr, "TK_AND");
                break;

            case 45:
                if (currChar == '\t' || currChar == ' ')
                {
                    currState = 45;
                }
                else
                {
                    currState = 46;
                }
                TwinBuffer->fwd++;
                break;

            case 46:
                TwinBuffer->fwd++;
                break;

            case 47:
                currLine++;
                break;

            case 48:
                if (currChar == '\n')
                {
                    // currLine++
                    currState = 49;
                    // return
                }
                else
                {
                    currState = 48;
                }
                TwinBuffer->fwd++;
                break;

            case 49:
                currLine++;
                break;
                // Increase Line

            case 50:
                // Return TK_SQR
                return setToken(ptr, "TK_SQR");
                break;

            case 51:
                // Return TK_SQL
                return setToken(ptr, "TK_SQL");
                break;

            case 52:
                // Return TK_DOT
                return setToken(ptr, "TK_DOT");
                break;

            case 53:
                // Return TK_COMMA
                return setToken(ptr, "TK_COMMA");
                break;

            case 54:
                // Return TK_SEM
                return setToken(ptr, "TK_SEM");
                break;

            case 55:
                // Return TK_COLON
                return setToken(ptr, "TK_COLON");
                break;

            case 56:
                // Return TK_PLUS
                return setToken(ptr, "TK_PLUS");
                break;

            case 57:
                // Return TK_MINUS
                return setToken(ptr, "TK_MINUS");
                break;

            case 58:
                // Return TK_MUL
                return setToken(ptr, "TK_MUL");
                break;

            case 59:
                // Return TK_DIV
                return setToken(ptr, "TK_DIV");
                break;

            case 60:
                // Return TK_OP
                return setToken(ptr, "TK_OP");
                break;

            case 61:
                // Return TK_CL
                return setToken(ptr, "TK_CL");
                break;

            case 62:
                // Return TK_NOT
                return setToken(ptr, "TK_NOT");
                break;

            case 63:
                // Return TK_LT
                return setToken(ptr, "TK_LT");
                break;
        }
    }
}

void removeComments(char *testcaseFile)
{
}

int main()
{
    TwinBuffer = (struct twinBuffer *)malloc(sizeof(struct twinBuffer));
    TwinBuffer->size = 2048;
    TwinBuffer->fwd = 0;
    TwinBuffer->back = 0;
    strcpy(TwinBuffer->buffer, "#adbs");
    // TwinBuffer->fwd++;
    // printf("Fwd: %d\n", TwinBuffer->fwd);
    struct tokenDetails *ptr = getNextToken(NULL);
    // printf("Hello \n");
    printStruct(ptr);
}

// int main()
// {
//     FILE *fp;
//     fp = fopen("try.c", "r");
//     if (fp == NULL)
//     {
//         printf("File not opened");
//         exit(0);
//     }
//     struct twinBuffer B;
//     B.size = 1024;
//     getStream(fp, B.buffer1);
//     B.fwd = B.buffer1;
//     // char data1[1024], data2[1024];
//     // int fwd = 0;
//     // int curr = 0;
//     // bool flag = false;
//     // fgets(data1, 1024, fl);
//     // fgets(data2, 1024, fl);
//     // int current_state = 0;
//     // char lexeme[100];
//     // int curr_lexeme = 0;
//     // while(1) { // we need to implement double-buffering for I/O
//     //     char c;
//     //     if(curr == 0) {
//     //         if(data1[fwd] == '\n') {
//     //             if(flag) break;
//     //             fwd = 0;
//     //             curr = 1;
//     //             if(fgets(data1, 1024, fl) == NULL) flag = true;
//     //             continue;
//     //         }
//     //         else{
//     //             c = data1[fwd++];
//     //         }
//     //     }
//     //     else{
//     //         if(data2[fwd] == '\n') {
//     //             if(flag) break;
//     //             fwd = 0;
//     //             curr = 0;
//     //             if(fgets(data2, 1024, fl) == NULL) flag = true;
//     //             continue;
//     //         }
//     //         else c = data2[fwd++];
//     //     }
//     //     printf("%c", c);
//     // switch(current_state) {
//     //     case 0:
//     //         lexeme[curr_lexeme++] = c;
//     //         if(c == '<') current_state = 1;
//     //         else if(c == '>') current_state = 7;

//     //         else if(c == '=') current_state = 10;

//     //         else if(c == '!') current_state = 12;

//     //         else if(c >= '0' && c <= '9') current_state = 15;

//     //         else if(c == 'a' || (c >= 'e' && c <= 'z')) current_state = 55;

//     //         else if(c >= 'b' && c <= 'd') current_state = 57;

//     //         else if(c == '[') current_state = 54;

//     //         else if(c == ']') current_state = 49;

//     //         else if(c == '.') current_state = 50;

//     //         else if(c == ',') current_state = 51;

//     //         else if(c == ';') current_state = 52;

//     //         else if(c == ':') current_state = 53;

//     //         else if(c == '&') current_state = 35;

//     //         else if(c == '@') current_state = 38;

//     //         else if(c == '#') current_state = 41;

//     //         else if(c == '_') current_state = 44;

//     //         else if(c == '%') current_state = 27;

//     //         else if(c == '+') current_state = 29;

//     //         else if(c == '-') current_state = 30;

//     //         else if(c == '*') current_state = 31;

//     //         else if(c == '/') current_state = 32;

//     //         else if(c == '(') current_state = 33;

//     //         else if(c == ')') current_state = 34;

//     //         else if(c == '\t' || c == ' ') current_state = 63;

//     //         else if(c == '\n') current_state = 62;

//     //         break;

//     //     case 1:
//     // }

//     // }
//     fclose(fp);

//     return 0;
// }
