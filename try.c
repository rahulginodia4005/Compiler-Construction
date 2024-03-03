#include<stdio.h>
// #include"hashmap.h"
#include"grammar.h"

int main() {
    HashMap* myHM = create_table(100);
    HM_insert(myHM, "abc", 5);
    HM_insert(myHM, "bcd", 10);
    HM_insert(myHM, "bcd", 15);
    HM_insert(myHM, "cde", 15);
    // printf("index is: %d", hash_function("bcd"));
    printf("%d", HM_search(myHM, "ghg"));
}