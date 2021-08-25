//Tic Tac Toe

#include <stdio.h>
#include <stdbool.h>
#include "myheader.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//What we're going to do is implement a 2D array thats 3/3. This corresponds perfectly to every position on the board
//perhaps board should be a struc that stores the array + whose turn it is


int main(){
    // create tic tac toe board. [first represents horizontal and j vertical position on board where top left is (0,0)]

    typedef struct{
        bool board[3][3][2]; // if you dont declare the values later its going to cause UH (Typedefs arent for declaring, just defining)
        bool turn;
    }game;
    
    game myGame = {.board = {0}, .turn = false};

    //ALTERNATIVE
    //game myGame;
    //memset(myGame.board, 0, sizeof myGame.board);



    int i;
    int j;
    // for(i = 0; i < 3; i++) {
    //     for(j = 0; j < 3; j++){
    //         printf("%u %u \n", board[i][j][0], board[i][j][1]);
    //     }
    // }
    printf("myGame.turn is: %d \n", myGame.turn);
    printBoard(myGame.board);
    int pos[] = {0, 1};
    //changeState(myGame.board, pos, myGame.turn);
    //printBoard(myGame.board);
    int(* gPos)[2] = &pos;
    changeState(myGame.board, gPos, myGame.turn);
    printBoard(myGame.board);
    //printf("%s", myGame.board[0][0][0] ? "true" : "false");
    int * cPos = choosePos();

    //printf("%d", myGame.board[0][0][0]);    
    //printf("%s", myGame.board[0][0][0] ? "true" : "false");
    //fputs(myGame.board[0][0][0] ? "true": "false", stdout);
    
    // printf("%d", cPos);
    // printf("value of cPos pointer [0] %d \n", *cPos);
    // printf("value of cPos pointer [1] %d \n", *(cPos + 1));
    changeState(myGame.board, cPos, myGame.turn);  //HERE'S A THOUGHT. DON'T MESS UP YOUR POINTER REFERENCE/DEREFERENCEs
    printBoard(myGame.board);
    printBoard(myGame.board);
}
 
