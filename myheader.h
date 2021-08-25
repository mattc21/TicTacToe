#ifndef myheader_h
#define myheader_h
#include <stdio.h>
#include <stdbool.h>
#include "myheader.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

void changeState(bool board[3][3][2], int* pos, bool type){
    //Changes the state of the board
    if (pos[0] > 3 || pos[0] < 0 || pos[1] > 3 || pos[1] < 0){
        printf("Error! changeState received a non-existent position!");
    }
    int i = *pos;
    int j = *(pos+1);
    // board[i][j][0] = true;
    // board[i][j][1] = type;
}

int * choosePos(){
    //Function that asks for a position and converts it to a position that can be used to change state..
    char* sPos; //Apparently char sPos[2] doesn't work. I think it's to do with the size of the sPos string.
                //After checking sPos[3] works so I can confirm issue is sPos.
    printf("Enter position. ('19' represents position (1,9) ");
    scanf("%s", sPos);
    int x = atoi(sPos);
    //printf("Value of x %d \n", x);
    //int x = 21;
    static int pos[2]; //isn't this kind of retarded? you're creating a static int array anyways... this is accessible anywhere
    pos[0] = x/10;
    pos[1] = x%10;
    //printf("Value of pos[0] in choosePos %d \n", pos[0]);
    return(&pos);
}  

#endif 