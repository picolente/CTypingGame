#ifndef SCORESYSTEM_H
#define SCORESYSTEM_H

#include "../libs/wordbuffer.h"

typedef struct TScoreBuffer {
    int numSpelled;
    int numMisspell;
    TBuffer misspelledBuffer;
} TScoreBuffer, *TScore;

void resetScore(TScore score);

void printScore(TScore score);

#endif //SCORESYSTEM_H
