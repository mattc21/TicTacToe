//Tic Tac Toe

#include <stdio.h>
#include <stdbool.h>
#include "myheader.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//What we're going to do is implement a 2D array thats 3/3. This corresponds perfectly to every position on the board
//perhaps board should be a struc that stores the array + whose turn it is


typedef struct{
    /*
    board has 9 positions as by the 3x3
    The x2 represents both whether board is occupied and what occupies it.
    e.g. if board[0][0] = {true, false} it means that position (0,0) is occupied by 'x'

    Note false = 'x' and true = 'o'
    */


    bool board[3][3][2]; // if you dont declare the values later its going to cause UH (Typedefs arent for declaring, just defining)
    bool turn;
}game;

void playGame(game myGame);

int main(){
    // create tic tac toe board. [first represents horizontal and j vertical position on board where top left is (0,0)]


    
    game myGame = {.board = {0}, .turn = false};

  


    playGame(myGame);
} 

void playGame(game myGame){
    printBoard(myGame.board);
    while (!checkWin(myGame.board)){
        int * cPos = choosePos();
        fputs(myGame.turn ? "o turn\n" : "x turn\n", stdout);
        changeState(myGame.board, cPos, myGame.turn);  //HERE'S A THOUGHT. DON'T MESS UP YOUR POINTER REFERENCE/DEREFERENCEs
        printBoard(myGame.board);
        myGame.turn = !myGame.turn;
    }
}
 
