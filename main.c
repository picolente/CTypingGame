#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CHAR 25
#define EXIT_STR ":exit"
#define START_GAME_STR ":start"
#define END_GAME_STR ":end"
#define LOAD_BUFFER_STR ":load"
#define SHO_BUFFER_STR ":sho buffer"

typedef struct TWordBuffer {
    char *buffer;
    char div;
    int size;
    int numWords;
} TWordBuffer, *TBuffer;

bool writeBuffer(char *filename, TBuffer buffer);

char* getBufferedWord(int index, TBuffer buffer);

int main(void) {
    TWordBuffer wordBuffer = {calloc(1,sizeof(char)),' ',1,0};
    TBuffer pWordBuffer = &wordBuffer;

    writeBuffer("test.txt",pWordBuffer);
    printf("%s\n", wordBuffer.buffer);

    writeBuffer("test2.txt",pWordBuffer);
    printf("%s\n", wordBuffer.buffer);

    return 0;
}

bool writeBuffer(char *filename, TBuffer buffer) {
    FILE *fp = NULL;
    fp = fopen(filename,"r");

    if(fp == NULL) {
        printf("Could not open File at \"%s\"\n", filename);
        return false;
    }

    //reset buffer if needed
    if(buffer->size > 1) {
        printf("Clear Buffer...\n");
        free(buffer->buffer);
        buffer->buffer = calloc(1,sizeof(char));
        buffer->size = 1;
        buffer->numWords = 0;
    }

    char str[MAX_CHAR] = "";
    char tmp = (char) fgetc(fp);
    short count = 0;

    while(tmp != EOF) {
        if(tmp != buffer->div && tmp != '\n' && tmp != ',' && tmp != '.') {
            str[count] = tmp;
            ++count;
        } else {
            //removes any leftovers from other words
            str[count] = '\0';

            if(strstr(buffer->buffer,str) == NULL && count > 0) {
                buffer->size += count + 1;
                ++buffer->numWords;

                //get new memory
                char *tmpP = realloc(buffer->buffer,sizeof(char) * buffer->size);

                if(tmpP == NULL) {
                    printf("Could not reallocate enough memory\nSize: %d", buffer->size);
                    return false;
                }

                buffer->buffer = tmpP;
                //append str with divider on buffer
                strcat(str," \0");
                strcat(buffer->buffer,str);
            }

            count = 0;
        }

        tmp = (char) fgetc(fp);
    }

    fclose(fp);
    return true;
}

char* getBufferedWord(int index, TBuffer buffer) {
    char *pBuffer = buffer->buffer;
    int divCount = 0;
    int count = 0;

    while(divCount <= index) {
        if(*pBuffer == buffer->div) {
            ++divCount;
        } else if(divCount == index) {
            ++count;
        }

        ++pBuffer;
    }

    //set pointer to the first letter
    pBuffer -= count + 1;
    char *tmp = malloc(sizeof(char) * (count + 1));
    strncpy(tmp,pBuffer,count);
    //prevents '☺'
    tmp[count] = '\0';

    return tmp;
}