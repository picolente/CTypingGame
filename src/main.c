#include <stdio.h>
#include <stdlib.h>
#include "../libs/wordbuffer.h"

#define MAX_CHAR 25
// #define EXIT_STR ":exit"
// #define START_GAME_STR ":start"
// #define END_GAME_STR ":end"
// #define LOAD_BUFFER_STR ":load"
// #define SHO_BUFFER_STR ":sho buffer"

int main(void) {
    TWordBuffer wordBuffer = {calloc(1,sizeof(char)),' ',1,0};
    TBuffer pWordBuffer = &wordBuffer;

    writeBuffer("test.txt",pWordBuffer);
    printf("%s\n", wordBuffer.buffer);

    writeBuffer("test2.txt",pWordBuffer);
    printf("%s\n", wordBuffer.buffer);

    return 0;
}
