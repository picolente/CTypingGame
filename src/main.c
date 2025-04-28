#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../libs/wordbuffer.h"
#include "../libs/scorebuffer.h"

#define MAX_CHAR 25
#define EXIT_STR ":exit"
#define LIST_COMMAND_STR ":list"
#define START_GAME_STR ":start"
#define END_GAME_STR ":end"
//Buffer:
#define WRITE_BUFFER_STR ":write"
#define SHOW_BUFFER_STR ":print"
#define CHANGE_BUFFER_DIV_STR ":div"
//Score:
#define SHOW_SCORE_STR ":show"
#define RESET_SCORE_STR ":reset"
#define SAVE_SCORE_BUFFER_STR ":save"

void game(TBuffer buffer, TScore score);

int main(void) {
    TWordBuffer buffer = {calloc(1,sizeof(char)),' ',1,0};
    TWordBuffer misspelledBuffer = {calloc(1,sizeof(char)),' ',1,0};
    TScoreBuffer score = {0,0,&misspelledBuffer};
    char input[MAX_CHAR] = {""};

    printf("> C - TypingGame\n> type \"%s\" for a list of commands\n", LIST_COMMAND_STR);

    do {
        fgets(input,sizeof(input),stdin);
        //writes '\0' at the pos of '\n' ore '\0' if no '\n'
        input[strcspn(input,"\n")] = '\0';

        if(strcmp(input,WRITE_BUFFER_STR) == 0) {
            char filepath[256] = {""};

            printf("> Enter filepath:");
            fgets(filepath,sizeof(filepath),stdin);
            filepath[strcspn(filepath,"\n")] = '\0';
            printf("> Buffer Status: %d\n", writeBuffer(filepath,&buffer));
            continue;
        }

        if(strcmp(input,SHOW_BUFFER_STR) == 0) {
            printBuffer(&buffer);
            continue;
        }

        if(strcmp(input,CHANGE_BUFFER_DIV_STR) == 0) {
            printf("> Current div: '%c'\n", buffer.div);
            printf("> Enter new div:");
            fgets(input,sizeof(input),stdin);
            buffer.div = input[0];
            continue;
        }

        if(strcmp(input,START_GAME_STR) == 0) {
            game(&buffer,&score);
            continue;
        }

        if(strcmp(input,RESET_SCORE_STR) == 0) {
            resetScore(&score);
            continue;
        }

        if(strcmp(input,SHOW_SCORE_STR) == 0) {
            printScore(&score);
            continue;
        }

        if(strcmp(input,SAVE_SCORE_BUFFER_STR) == 0) {
            char filepath[256] = {""};

            printf("> Enter filepath:");
            fgets(filepath,sizeof(filepath),stdin);
            filepath[strcspn(filepath,"\n")] = '\0';
            printf("> Save Status: %d\n", saveBuffer(filepath,score.misspelledBuffer));
            continue;
        }

        if(strcmp(input,LIST_COMMAND_STR) == 0) {
            printf("> Type:\n> ---\n");
            printf("> \"%s\" to write your Buffer\n", WRITE_BUFFER_STR);
            printf("> \"%s\" to display your Buffer\n", SHOW_BUFFER_STR);
            printf("> \"%s\" to reset your Score\n", RESET_SCORE_STR);
            printf("> \"%s\" to display your Score\n", SHOW_SCORE_STR);
            printf("> \"%s\" to save your misspelled Words\n", SAVE_SCORE_BUFFER_STR);
            printf("> \"%s\" to start typing\n", START_GAME_STR);
            printf("> \"%s\" to quit typing\n", END_GAME_STR);
            printf("> \"%s\" to exit the application\n", EXIT_STR);
            printf("> ---\n");
            printf("> \"%s\" to change the char that divides words\n", CHANGE_BUFFER_DIV_STR);
            continue;
        }

        printf("! Unexpected Input: \"%s\"\n", input);
    } while(strcmp(input,EXIT_STR) != 0);

    return 0;
}

//tmp:
void game(TBuffer buffer, TScore score) {
    char input[MAX_CHAR] = {""};
    char *tmp = NULL;

    srand(time(NULL));
    printf("> Start game...\n");

    do {
        tmp = getBufferedWord(rand() % buffer->numWords,buffer);

        printf("> %s\n", tmp);
        fgets(input,sizeof(input),stdin);
        input[strcspn(input,"\n")] = '\0';

        //update Score
        ++score->numSpelled;

        if(strcmp(input,tmp) != 0) {
            ++score->numMisspell;

            if(!extendBuffer(tmp,score->misspelledBuffer)) {
                return;
            }
        }

        free(tmp);
    } while(strcmp(input,END_GAME_STR) != 0);

    printf("> End game...\n");
}