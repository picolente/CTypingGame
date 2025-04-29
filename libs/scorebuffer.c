#include "scorebuffer.h"

#include <stdio.h>

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