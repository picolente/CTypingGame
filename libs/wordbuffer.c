#include "wordbuffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CHAR 25
#define CHAR_FILTER "!?.,<>()[]{}@#$%^&*-_=+\\|/`~\"\';: \n\t"
#define ADDITIONAL_DIVS "\n\t"

bool writeBuffer(char *filename, TBuffer buffer) {
    FILE *fp = NULL;
    fp = fopen(filename,"r");

    if(fp == NULL) {
        printf("! Could not open File at \"%s\"\n", filename);
        return false;
    }

    if(buffer->size > 1) {
        resetBuffer(buffer);
    }

    char str[MAX_CHAR] = {""};
    char tmp = '\0';
    short count = 0;

    while((tmp = (char) fgetc(fp)) != EOF) {
        if(strchr(CHAR_FILTER,tmp) == NULL && count < MAX_CHAR - 1) {
            str[count] = tmp;
            ++count;
            continue;
        }

        if(strchr(ADDITIONAL_DIVS,tmp) != NULL || tmp == buffer->div) {
            //removes leftovers
            str[count] = '\0';

            if(!extendBuffer(str,buffer)) {
                return false;
            }

            count = 0;
        }
    }

    fclose(fp);
    return true;
}

bool extendBuffer(char *str, TBuffer buffer) {
    if(strstr(buffer->buffer,str) == NULL) {
        buffer->size += (int) strlen(str) + 1;
        ++buffer->numWords;

        char *tmpP = realloc(buffer->buffer,sizeof(char) * buffer->size);

        if(tmpP == NULL) {
            printf("! Could not reallocate enough memory\n> Wanted Size: %d\n", buffer->size);
            return false;
        }

        buffer->buffer = tmpP;

        //append str with divider on buffer
        char tmp[2] = {""};
        tmp[0] = buffer->div;
        strcat(str,tmp);
        strcat(buffer->buffer,str);
    }

    return true;
}

bool saveBuffer(char *filepath, TBuffer buffer) {
    FILE *fp = NULL;
    fp = fopen(filepath,"w");

    if(fp == NULL) {
        printf("! Could not open/creat file \"%s\"\n", filepath);
        return false;
    }

    if(fprintf(fp,"%s", buffer->buffer) < 0) {
        printf("! File Error\n");
        return false;
    }

    printf("> Wrote File successfully\n");
    fclose(fp);
    return true;
}

char* getBufferedWord(int index, TBuffer buffer) {
    char *pBuffer = buffer->buffer;

    //find first letter
    while(index > 0) {
        if(*pBuffer == buffer->div) {
            --index;
        }

        ++pBuffer;
    }

    //count till buffer.div is reached
    int count = (int) strcspn(pBuffer,&buffer->div);
    char *tmp = malloc(sizeof(char) * (count + 1));

    //copy chars
    strncpy(tmp,pBuffer,count);
    tmp[count] = '\0';

    return tmp;
}

void resetBuffer(TBuffer buffer) {
    printf("> Clear Buffer...\n");
    free(buffer->buffer);
    buffer->buffer = calloc(1,sizeof(char));
    buffer->size = 1;
    buffer->numWords = 0;
}

void printBuffer(TBuffer buffer) {
    printf("> Buffer:\n> ---\n%s\n> ---\n", buffer->buffer);
    printf("> Divider: \'%c\'\n", buffer->div);
    printf("> Size [Byte]: %d\n", buffer->size);
    printf("> Words: %d\n", buffer->numWords);
}