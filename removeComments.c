#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void removeComments(char *testcaseFile) {
    FILE *srcFile = fopen(testcaseFile, "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (srcFile == NULL || tempFile == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    char line[1024];
    while (fgets(line, sizeof(line), srcFile) != NULL) {
        char* commentStart = strchr(line, '%');
        if (commentStart != NULL) {
            
            char* newlinePos = strchr(commentStart, '\n');
            if (newlinePos != NULL) {
                *commentStart = '\n';
                *(commentStart + 1) = '\0';
            } else {
                *commentStart = '\0';
            }
        }
        fputs(line, tempFile);
    }

    fclose(srcFile);
    fclose(tempFile);

    rename("temp.txt", "commentRemoval.txt");
}

int main(){
    removeComments("t2.txt");
    return 0;
}