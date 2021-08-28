#ifndef myheader_h
#define myheader_h
#include <stdio.h>
#include <stdbool.h>
#include "myheader.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

//Some people claim its better to just have declaration here and each of these actual functions in different files.
void printBoard(bool board[][3][2]){
    /*
    Board looks like:

        |_|_|o|
        |_|x|_|
        |_|_|_|
    
    */
    int i;
    int j;
    for(j = 0; j < 3; j++) {
        for(i = 0; i < 3; i++){
            bool isOccupied = board[i][j][0];
            bool type = board[i][j][1];
            if (isOccupied == false){
                printf("|_");
            } else if (type == false){
                printf("|x");
            } else if (type == true){
                printf("|o");
            }
        }
        printf("|\n");
    }
}

void changeState(bool board[3][3][2], int* pos, bool type){   //two choices, you either take a pointer or an array of pointers
    //Changes the state of the board
    if (pos[0] >= 3 || pos[0] < 0 || pos[1] >= 3 || pos[1] < 0){
        printf("Error! changeState received a non-existent position! \n");
        return;
    }
    int i = *pos;
    int j = *(pos+1);
    board[i][j][0] = true;
    board[i][j][1] = type;
}

int checkWin(bool board[3][3][2]){
    /*
    Returns -1 if nobody has won.
    Returns 0 if x has won.
    Return 1 if o has won.

    */
    //check diagonals
    //check vertical
    int i;
    int j;
    for (i= 0; i< 2; i++){
        for (j = 0; j < 2; j++ ){    
            //printf("%d \n", j);        
            if (board[i][j][0] == false || board[i][j+1][0] == false || board[i][j][1] != board[i][j+1][1]){ //
                break;           
            }
            
            if (j==1){
                return true;
            } 
        }
    }
    for (i= 0; i< 2; i++){
        for (j = 0; j < 2; j++ ){    
            //printf("%d \n", j);        
            if (board[j][i][0] == false || board[j+1][i][0] == false || board[j][i][1] != board[j+1][i][1]){ //
                break;           
            }
            
            if (j==1){
                return true;
            } 
        }
    }
    return false;

}

bool checkFull(bool board[3][3][2]){
    //Checks entire board to see if occupied.
    int i;
    int j;
    for (i= 0; i< 3; i++){
        for (j = 0; j < 3; j++ ){    
            //printf("%d \n", j);        
            if (board[i][j][0] == false){
                return false;
            }
        }
    }
    return true;
}

int mygetline(char *buf, size_t size) {
    //ripped from stackoverflow :)
    assert(size > 0 && size <= INT_MAX);
    size_t i = 0;
    int ch;
    while ((ch = fgetc(stdin)) != EOF) {  // Read until EOF ...
        if (i + 1 < size) {
            buf[i++] = ch;
        }
        if (ch == '\n') {  // ... or end of line
            break;  
        }
    } 
    buf[i] = '\0';
    if (i == 0) { 
        return EOF;
    }
    return i;
}

int * choosePos(){
    //Function that asks for a position and converts it to a position that can be used to change state..
    char sPos[3]; //the previous issue was u didnt malloc space to your fking pointers!!
    printf("Enter position. ('19' represents position (1,9) ");
    //fgets(&sPos[0], 3, stdin);
    mygetline(&sPos[0], 3);
    int x = atoi(sPos);
    //printf("Value of x %d \n", x);
    //int x = 21;
    static int returnPos[2]; //you're creating a static int array anyways... this is accessible anywhere. i mean you could use malloc instead and use heap
    returnPos[0] = x/10;
    returnPos[1] = x%10;
    //printf("Value of pos[0] in choosePos %d \n", pos[0]);
    return(&returnPos[0]);
}






#endif 