#include <stdbool.h>

struct tokenDetails{
    char token[100];
    char lexeme[100];
    int lineNumber;
    int value;
    bool err;
    char errMessage[100];
}TokenDetails;