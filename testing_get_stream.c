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

struct twinBuffer
{
    int size;
    int fwd;
    int begin;
    char buffer[2048];
} * TwinBuffer;


int getStream(FILE *fp, struct twinBuffer* buf)
{
    // size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);

    int char_read;
    if(buf->fwd==2047){
        printf("if\n");
        char_read = fread(buf->buffer,1, 1024, fp);
    }
    else{
        printf("else\n");
        char_read = fread(buf->buffer+1024, 1,1024, fp);
    }    
    return char_read;
}

char* findLexeme(struct twinBuffer* buf){

    char* lexeme = (char*)malloc(100*sizeof(char));
    if(buf->fwd >= buf->begin){
        int size = buf->fwd - buf->begin;
        memcpy(lexeme, buf->buffer + buf->begin, size);
    }
    else{
        int size1 = 2048 - buf->begin ;
        memcpy(lexeme, buf->buffer + buf->begin, 2048 - buf->fwd );
        memcpy(lexeme+size1, buf->buffer + buf->fwd, buf->fwd-1);
    }
    return lexeme;
}

int main(){
    FILE* fp;
    char ch;
 
    // Opening file in reading mode
    fp = fopen("t2.txt", "r");
    if(fp==NULL){
        printf("Can't open the file");
    }
    
    TwinBuffer = (struct twinBuffer*)malloc(sizeof(struct twinBuffer));
    TwinBuffer->begin=0;
    TwinBuffer->fwd=2047;

    // getStream(fp, TwinBuffer);
    int where = 0;
    int i = 0;
    while (getStream(fp, TwinBuffer) != NULL) {
        printf("%d\n", i++);
        printf("%s\n", TwinBuffer->buffer+where);
        printf("%d , %d\n",TwinBuffer->begin, TwinBuffer->fwd);
        TwinBuffer -> fwd == 2047 ? (TwinBuffer->fwd=0) : (TwinBuffer->fwd=2047);   
        where == 0 ? (where=1024) : (where=0) ; 
    }

    return 0;
}