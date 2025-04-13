#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIV " "

typedef struct TWordBuffer {
    char *buffer;
    char div;
    int size;
} TWordBuffer, *TBuffer;

void writeBuffer(char *filename, TBuffer buffer);

int main(void) {
    TWordBuffer testBuffer = {calloc(1,sizeof(char)),' ',0};

    writeBuffer("proto.txt",&testBuffer);
    printf("%s", testBuffer.buffer);

    return 0;
}

void writeBuffer(char *filename, TBuffer buffer) {
    FILE *fp = NULL;
    fp = fopen(filename,"r");

    if(fp == NULL) {
        printf("Could not open File at \"%s\"\n", filename);
    } else {
        //I don't think there are any longer words
        //that you would commonly use
        char str[25] = "";
        char tmp = (char) fgetc(fp);
        short count = 0;

        while(tmp != EOF) {
            if(tmp != buffer->div && tmp != '\n' && tmp != ',') {
                str[count] = tmp;
                ++count;
            } else {
                //removes any leftovers from other words
                str[count] = '\0';

                if(strstr(buffer->buffer,str) == NULL && count > 0) {
                    buffer->size += count + 1;
                    //get new memory
                    buffer->buffer = realloc(buffer->buffer,sizeof(char) * buffer->size);
                    //append str with a divider on buffer
                    strcat(str,DIV);
                    strcat(buffer->buffer,str);
                }

                count = 0;
            }

            tmp = (char) fgetc(fp);
        }

        fclose(fp);
    }
}