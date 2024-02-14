#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int main() {
    FILE *fl;
    fl = fopen("try.c", "r");
    if(fl == NULL) {
        printf("File not opened");
        exit(0);
    }
    char data1[1024], data2[1024];
    int fwd = 0;
    int curr = 0;
    bool flag = false;
    fgets(data1, 1024, fl);
    fgets(data2, 1024, fl);
    int current_state = 0;
    char lexeme[100];
    int curr_lexeme = 0;
    while(1) { // we need to implement double-buffering for I/O
        char c;
        if(curr == 0) {
            if(data1[fwd] == '\n') {
                if(flag) break;
                fwd = 0;
                curr = 1;
                if(fgets(data1, 1024, fl) == NULL) flag = true;
                continue;
            }
            else{
                c = data1[fwd++];
            }
        }
        else{
            if(data2[fwd] == '\n') {
                if(flag) break;
                fwd = 0;
                curr = 0;
                if(fgets(data2, 1024, fl) == NULL) flag = true;
                continue;
            }
            else c = data2[fwd++];
        }
        printf("%c", c);
        switch(current_state) {
            case 0:
                lexeme[curr_lexeme++] = c;
                if(c == '<') current_state = 1;
                else if(c == '>') current_state = 7;

                else if(c == '=') current_state = 10;

                else if(c == '!') current_state = 12;

                else if(c >= '0' && c <= '9') current_state = 15;

                else if(c == 'a' || (c >= 'e' && c <= 'z')) current_state = 55;

                else if(c >= 'b' && c <= 'd') current_state = 57;

                else if(c == '[') current_state = 54;

                else if(c == ']') current_state = 49;

                else if(c == '.') current_state = 50;

                else if(c == ',') current_state = 51; 

                else if(c == ';') current_state = 52;

                else if(c == ':') current_state = 53;

                else if(c == '&') current_state = 35;

                else if(c == '@') current_state = 38;

                else if(c == '#') current_state = 41;

                else if(c == '_') current_state = 44;

                else if(c == '%') current_state = 27;

                else if(c == '+') current_state = 29;

                else if(c == '-') current_state = 30;

                else if(c == '*') current_state = 31;

                else if(c == '/') current_state = 32;

                else if(c == '(') current_state = 33;

                else if(c == ')') current_state = 34;

                else if(c == '\t' || c == ' ') current_state = 63;

                else if(c == '\n') current_state = 62;
                

                break;

            case 1: 
        }

    }
    fclose(fl);

    return 0;
}