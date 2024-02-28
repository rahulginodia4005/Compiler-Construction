#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct tokenDetails
{
    char token[100];
    char lexeme[100];
    int lineNumber;
    int value;
    bool err;
    char errMessage[100];
} TokenDetails;

// void makeToken(struct tokenInfo t, char *a, char *b) {
//     strcpy(t.lexeme, a);
//     strcpy(t.tokenName, b);
// }

struct twinBuffer
{
    int size;
    char *fwd;
    char *back;
    bool activeBuffer; // 0 for buffer1 and 1 for buffer2
    char buffer1[1024], buffer2[1024];
} TwinBuffer;

void getStream(FILE *fp, char *buffer)
{
    fgets(buffer, 1024, fp);
}

struct tokenDetails *getNextToken(FILE *f)
{

    // if(B.fwd)
    // struct tokenInfo t;
    // makeToken(t, )
    // return t;

    int currState = 0;
    // Check in twinBuffer which buffer is active
    char *currBuffer;
    if (TwinBuffer.activeBuffer == 0)
    {
        // char* currBuffer = TwinBuffer.buffer1;
        // if(currBuffer == NULL){
        //     f = getStream(f,)
        // }
    }

    int currLine = 1;

    while (1)
    {
        switch (currState)
        {
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
                    break;

                case 'b':
                case 'c':
                case 'd':
                    currState = 14;
                    break;

                case '<':
                    currState = 19;
                    break;

                case '>':
                    currState = 25;
                    break;

                case '=':
                    currState = 28;
                    break;

                case '!':
                    currState = 30;
                    break;

                case '_':
                    currState = 32;
                    break;

                case '#':
                    currState = 36;
                    break;

                case '@':
                    currState = 39;
                    break;

                case '&':
                    currState = 42;
                    break;

                case '\t':
                case ' ':
                    currState = 45;
                    break;

                case '\n':
                    currState = 47;
                    // currLine++;
                    // Return Token
                    break;

                case '%':
                    currState = 48;
                    break;

                case '[':
                    currState = 51;
                    // Return Token
                    break;

                case ']':
                    currState = 50;
                    // Return Token
                    break;

                case '.':
                    currState = 52;
                    // Return Token
                    break;

                case ',':
                    currState = 53;
                    // Return Token
                    break;

                case ';':
                    currState = 54;
                    // Return Token
                    break;

                case ':':
                    currState = 55;
                    // Return Token
                    break;

                case '+':
                    currState = 56;
                    // Return Token
                    break;

                case '-':
                    currState = 57;
                    // Return Token
                    break;

                case '*':
                    currState = 58;
                    // Return Token
                    break;

                case '/':
                    currState = 59;
                    // Return Token
                    break;

                case '(':
                    currState = 60;
                    // Return Token
                    break;

                case ')':
                    currState = 61;
                    // Return Token
                    break;
                }

            case '~':
                currState = 62;
                // Return Token
                break;

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
                break;

            case 2: // Return Token TK_NUM
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
                break;

            case 4: // Return Token TK_NUM
                break;

            case 5:
                if (currChar >= '0' && currChar <= '9')
                {
                    currState = 6;
                } // what about else
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
                break;

            case 7:
                // Return Token TK_RNUM
                break;

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

                break;

            case 9:
                if (currChar >= '0' && currChar <= '9')
                {
                    currState = 10;
                } // what about else
                break;

            case 10:
                if (currChar >= '0' && currChar <= '9')
                {
                    currState = 11;
                } // what about else
                break;

            case 11:
                // Return Token TK_RNUM
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
                break;

            case 13: // Return Token TK_
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
                break;

            case 16: // Return Token TK_RNUM
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
                break;

            case 18: // Return Token TK_
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

                break;

            case 20: // Return Token TK_LT
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
                break;

            case 22:
                if (currChar == '-')
                {
                    currState = 23;
                } // What about else
                break;

            case 23: // Return Token TK_ASSIGNOP
                break;

            case 24: // Return Token TK_LE
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
                break;

            case 26: // Return Token TK_GT
                break;

            case 27: // Return Token TK_GE
                break;

            case 28:
                if (currChar == '=')
                {
                    currState = 29;
                } // What about else
                break;

            case 29: // Return Token TK_EQ
                break;

            case 30:
                if (currChar == '=')
                {
                    currState = 31;
                } // What about else
                break;

            case 31: // Return Token TK_NE
                break;

            case 32:
                if (currChar >= 'a' && currChar <= 'z' || currChar >= 'A' && currChar <= 'Z')
                {
                    currState = 33;
                } // What about else
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
                break;

            case 35: // Return Token TK_
                break;

            case 36:
                if (currChar >= 'a' && currChar <= 'z')
                {
                    currState = 37;
                } // What about else
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
                break;

            case 38: // Return Token TK_
                break;

            case 39:
                if (currChar == '@')
                {
                    currState = 40;
                } // What about else

                break;

            case 40:
                if (currChar == '@')
                {
                    currState = 41;
                } // What about else
                break;

            case 41: // Return Token TK_OR
                break;

            case 42:
                if (currChar == '&')
                {
                    currState = 43;
                } // What about else
                break;

            case 43:
                if (currChar == '&')
                {
                    currState = 44;
                } // What about else
                break;

            case 44: // Return Token TK_AND
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
                break;

            case 46: // Return Token TK_
                break;

            case 47:
                break;

            case 48:
                if (currChar == '/n')
                {
                    // currLine++;
                    currState = 49;
                    // return
                }
                else
                {
                    currState = 48;
                }
                break;

            case 49:
                currLine++;
                break;
                // Increase Line

            case 50:
                // Return TK_SQR
                break;

            case 51:
                // Return TK_SQL
                break;

            case 52:
                // Return TK_DOT
                break;

            case 53:
                // Return TK_COMMA
                break;

            case 54:
                // Return TK_SEM
                break;

            case 55:
                // Return TK_COLON
                break;

            case 56:
                // Return TK_PLUS
                break;

            case 57:
                // Return TK_MINUS
                break;

            case 58:
                // Return TK_MUL
                break;

            case 59:
                // Return TK_DIV
                break;

            case 60:
                // Return TK_OP
                break;

            case 61:
                // Return TK_CL
                break;

            case 62:
                // Return TK_NOT
                break;

            case 63:
                // Return TK_LT
                break;
            }
    }
}

void removeComments(char *testcaseFile)
{
}

int main()
{
    FILE *fp;
    fp = fopen("try.c", "r");
    if (fp == NULL)
    {
        printf("File not opened");
        exit(0);
    }
    struct twinBuffer B;
    B.size = 1024;
    getStream(fp, B.buffer1);
    B.fwd = B.buffer1;
    // char data1[1024], data2[1024];
    // int fwd = 0;
    // int curr = 0;
    // bool flag = false;
    // fgets(data1, 1024, fl);
    // fgets(data2, 1024, fl);
    // int current_state = 0;
    // char lexeme[100];
    // int curr_lexeme = 0;
    // while(1) { // we need to implement double-buffering for I/O
    //     char c;
    //     if(curr == 0) {
    //         if(data1[fwd] == '\n') {
    //             if(flag) break;
    //             fwd = 0;
    //             curr = 1;
    //             if(fgets(data1, 1024, fl) == NULL) flag = true;
    //             continue;
    //         }
    //         else{
    //             c = data1[fwd++];
    //         }
    //     }
    //     else{
    //         if(data2[fwd] == '\n') {
    //             if(flag) break;
    //             fwd = 0;
    //             curr = 0;
    //             if(fgets(data2, 1024, fl) == NULL) flag = true;
    //             continue;
    //         }
    //         else c = data2[fwd++];
    //     }
    //     printf("%c", c);
    // switch(current_state) {
    //     case 0:
    //         lexeme[curr_lexeme++] = c;
    //         if(c == '<') current_state = 1;
    //         else if(c == '>') current_state = 7;

    //         else if(c == '=') current_state = 10;

    //         else if(c == '!') current_state = 12;

    //         else if(c >= '0' && c <= '9') current_state = 15;

    //         else if(c == 'a' || (c >= 'e' && c <= 'z')) current_state = 55;

    //         else if(c >= 'b' && c <= 'd') current_state = 57;

    //         else if(c == '[') current_state = 54;

    //         else if(c == ']') current_state = 49;

    //         else if(c == '.') current_state = 50;

    //         else if(c == ',') current_state = 51;

    //         else if(c == ';') current_state = 52;

    //         else if(c == ':') current_state = 53;

    //         else if(c == '&') current_state = 35;

    //         else if(c == '@') current_state = 38;

    //         else if(c == '#') current_state = 41;

    //         else if(c == '_') current_state = 44;

    //         else if(c == '%') current_state = 27;

    //         else if(c == '+') current_state = 29;

    //         else if(c == '-') current_state = 30;

    //         else if(c == '*') current_state = 31;

    //         else if(c == '/') current_state = 32;

    //         else if(c == '(') current_state = 33;

    //         else if(c == ')') current_state = 34;

    //         else if(c == '\t' || c == ' ') current_state = 63;

    //         else if(c == '\n') current_state = 62;

    //         break;

    //     case 1:
    // }

    // }
    fclose(fp);

    return 0;
}