#include<stdio.h>

int main() {
    if(0) {
        #define a b
        int b = 50;
        a = 30;
        printf("%d", b);
    }
    else{
        int b = 60;
        a = 30;
        printf("%d", b);
    }
    int b = 70;
    printf("%d", a);
}