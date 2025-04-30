#include "scorebuffer.h"

#include <stdio.h>
#include <string.h>

bool updateScore(char *str, char *str2, TScore score) {
    ++score->numSpelled;

    if(strcmp(str,str2) != 0) {
        printf("> [X]\n");
        ++score->numMisspell;

        if(!extendBuffer(str2,score->misspelledBuffer)) {
            return false;
        }
    }

    return true;
}

void resetScore(TScore score) {
    printf("> Reset Score...\n");
    score->numSpelled = 0;
    score->numMisspell = 0;
    resetBuffer(score->misspelledBuffer);
}

void printScore(TScore score) {
    printf("> Score:\n> ---\n");
    printf("> Writen Words: %d\n", score->numSpelled);
    printf("> Misspelled Words: %d\n", score->numMisspell);

    if(score->misspelledBuffer->size > 1) {
        printBuffer(score->misspelledBuffer);
    }
}