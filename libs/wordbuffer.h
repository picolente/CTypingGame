#ifndef WORDBUFFER_H
#define WORDBUFFER_H

#include <stdbool.h>

typedef struct TWordBuffer {
    char *buffer;
    char div;
    int size;
    int numWords;
} TWordBuffer, *TBuffer;

bool writeBuffer(char *filename, TBuffer buffer);

bool extendBuffer(char *str, TBuffer buffer);

char* getBufferedWord(int index, TBuffer buffer);

#endif //WORDBUFFER_H
