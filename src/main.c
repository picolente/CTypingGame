#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../libs/wordbuffer.h"

#define MAX_CHAR 25
#define EXIT_STR ":exit"
#define START_GAME_STR ":start"
#define END_GAME_STR ":end"
#define WRITE_BUFFER_STR ":write"
#define SHO_BUFFER_STR ":show"

void game(TBuffer buffer);

int main(void) {
    TWordBuffer wordBuffer = {calloc(1,sizeof(char)),' ',1,0};

    //welcome text: :help, :writeBuffer, :exit, ...

    char input[MAX_CHAR] = {""};

    do {
        //note: reads console input, buffers it
        //and writes it to 'input' if there is enough memory
        fgets(input,sizeof(input),stdin);
        //writes '\0' at the pos of '\n'
        //because 'fgets' buffers the whole input
        input[strcspn(input,"\n")] = '\0';

        if(strcmp(input,WRITE_BUFFER_STR) == 0) {
            char filepath[256];

            printf("> Enter filepath:");
            fgets(filepath,sizeof(filepath),stdin);
            filepath[strcspn(filepath,"\n")] = '\0';
            printf("> Buffer Status: %d\n", writeBuffer(filepath,&wordBuffer));
            continue;
        }

        if(strcmp(input,SHO_BUFFER_STR) == 0) {
            printf("> Buffer:\n> ---\n%s\n> ---\n", wordBuffer.buffer);
            printf("> Divider: \'%c\'\n", wordBuffer.div);
            printf("> Size [Byte]: %d\n", wordBuffer.size);
            printf("> Words: %d\n", wordBuffer.numWords);
            continue;
        }

        if(strcmp(input,START_GAME_STR) == 0) {
            game(&wordBuffer);
            continue;
        }

        printf("! Unexpected Input: %s\n", input);
    } while(strcmp(input,EXIT_STR) != 0);

    return 0;
}

//tmp:
void game(TBuffer buffer) {
    char input[MAX_CHAR] = {""};
    char *tmp = NULL;

    srand(time(NULL));
    printf("> Start game...\n");

    do {
        tmp = getBufferedWord(rand() % buffer->numWords,buffer);

        printf("> %s\n", tmp);
        scanf("%s", input);

        //check input | write wrong words to second buffer | update score

        free(tmp);
        tmp = NULL;
    } while(strcmp(input,END_GAME_STR) != 0);

    printf("> End game...\n");
}