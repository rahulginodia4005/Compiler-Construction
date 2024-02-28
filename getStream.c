#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

FILE* getStream(FILE* fp, char * buffer, int bufferSize){
    
    if(fp == NULL){
        return NULL;
    }

    if(feof(fp)){
        fclose(fp);
        return NULL;
    }

    // Read Characters ->

    int numberOfCharsRead = fread(buffer, sizeof(char), bufferSize,fp);
    
    if(numberOfCharsRead>0){
        buffer[numberOfCharsRead] = '\0'; // Null character at the end of the buffer
        return fp;
    }
    else{
        fclose(fp);
        return NULL;
    }
}