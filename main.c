#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 25
//#define DIV " "

typedef struct TWordBuffer {
    char *buffer;
    char div;
    int size;
    int numWords;
} TWordBuffer, *TBuffer;

void writeBuffer(char *filename, TBuffer buffer);

char* getBufferedWord(int index, TBuffer buffer);

int main(void) {
    TWordBuffer testBuffer = {calloc(1,sizeof(char)),' ',1,0};

    writeBuffer("test.txt",&testBuffer);
    printf("%s\n\n", testBuffer.buffer);

    char *tmp = getBufferedWord(5,&testBuffer);

    printf("%s", tmp);
    free(tmp);

    return 0;
}

void writeBuffer(char *filename, TBuffer buffer) {
    FILE *fp = NULL;
    fp = fopen(filename,"r");

    if(fp == NULL) {
        printf("Could not open File at \"%s\"\n", filename);
    } else {
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
                        return;
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
    }
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