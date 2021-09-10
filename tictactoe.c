//Tic Tac Toe

#include <stdio.h>
#include <stdbool.h>
#include "myheader.h"
#include <string.h>
#include <stdlib.h>



typedef struct{
    /*
    board has 9 positions as by the 3x3
    The x2 represents both whether board is occupied and what occupies it.
    e.g. if board[0][0] = {true, false} it means that position (0,0) is occupied by 'x'

    Note false = 'x' and true = 'o'
    */


    bool board[3][3][2]; 
    bool turn;
}game;

void playGame(game myGame);

void debugBestMove(game myGame);
void debugBestMove2(game myGame);
void vsComputer(game myGame);
int main(){
    // create tic tac toe board. [first represents horizontal and j vertical position on board where top left is (0,0)]
    game myGame = {.board = {0}, .turn = cross};


    //debugBestMove(myGame);
    //vsHuman(myGame);
    //debugBestMove2(myGame);
    vsComputer(myGame);
} 


void vsComputer(game myGame){
    printBoard(myGame.board);
    int *cPos;
    int changeStateSuccess;
    while (checkWin(myGame.board) == 0 && !checkFull(myGame.board)){
        if (myGame.turn == false){
            printf("your turn!\n");
            fputs(myGame.turn ? "o turn\n" : "x turn\n", stdout);
            cPos = choosePos();
            changeStateSuccess = changeState(myGame.board, cPos, myGame.turn);  
            printBoard(myGame.board);
            
        }
        else{
            printf("computer turn! \n");
            int* bMove = bestMove(myGame.board, myGame.turn, -1000, 1000, 0);
            cPos[0] = bMove[0];
            cPos[1] = bMove[1];
            changeState(myGame.board, cPos, myGame.turn);  
            printBoard(myGame.board);
        } 
        if (changeStateSuccess){
            myGame.turn = !myGame.turn; 
        }
    }
    int checkWinResult = checkWin(myGame.board);
    fputs((checkWinResult == 1) ? "o wins\n" : (checkWinResult == -1) ? "x wins\n" : "draw \n", stdout);
}

void vsHuman(game myGame){
    printBoard(myGame.board);
    while (checkWin(myGame.board) == 0 && !checkFull(myGame.board)){
        fputs(myGame.turn ? "o turn\n" : "x turn\n", stdout);
        int * cPos = choosePos();
        changeState(myGame.board, cPos, myGame.turn); 
        printBoard(myGame.board);
        myGame.turn = !myGame.turn;
    }
    printf("Check win returned %d | (1 is circle win, -1 is cross win)", checkWin(myGame.board));
}

void debugBestMove2(game myGame){
    printf("debugger\n");
    int cPos[2];
    cPos[0] = 0;
    cPos[1] = 0;
    changeState(myGame.board, cPos, myGame.turn);
    myGame.turn = !myGame.turn;
    cPos[0] = 0;
    cPos[1] = 1;
    changeState(myGame.board, cPos, myGame.turn);
    myGame.turn = !myGame.turn;
    cPos[0] = 1;
    cPos[1] = 1;
    changeState(myGame.board, cPos, myGame.turn);
    myGame.turn = !myGame.turn;
    cPos[0] = 2;
    cPos[1] = 2;
    changeState(myGame.board, cPos, myGame.turn);
    myGame.turn = !myGame.turn;
    cPos[0] = 2;
    cPos[1] = 1;
    changeState(myGame.board, cPos, myGame.turn);
    myGame.turn = !myGame.turn;
    cPos[0] = 0;
    cPos[1] = 2;
    changeState(myGame.board, cPos, myGame.turn);
    myGame.turn = !myGame.turn;
    printBoard(myGame.board);
    printf("\n--- DEBUGGING PART ---\n\n");
    fputs(myGame.turn ? "o turn\n" : "x turn\n", stdout);
    int* smt = bestMove(myGame.board, myGame.turn, -1000, 1000, 0);
    printf("\nBestmoves (from main) is : %d, %d. Score is %d\n", *smt, *(smt+1), *(smt + 2));
    printBoard(myGame.board);
    
}

void debugBestMove(game myGame){
    fputs(myGame.turn ? "o turn\n" : "x turn\n", stdout);
    int * cPos = choosePos();
    changeState(myGame.board, cPos, myGame.turn); 
    printBoard(myGame.board);
    myGame.turn = !myGame.turn;
    fputs(myGame.turn ? "o turn\n" : "x turn\n", stdout);
    cPos = choosePos();
    changeState(myGame.board, cPos, myGame.turn);
    printBoard(myGame.board);
    myGame.turn = !myGame.turn;
    fputs(myGame.turn ? "o turn\n" : "x turn\n", stdout);
    cPos = choosePos();
    changeState(myGame.board, cPos, myGame.turn); 
    printBoard(myGame.board);
    myGame.turn = !myGame.turn;
    cPos = choosePos();
    changeState(myGame.board, cPos, myGame.turn);  
    printBoard(myGame.board);
    myGame.turn = !myGame.turn;
    printf("\n--- DEBUGGING PART ---\n\n");
    fputs(myGame.turn ? "o turn\n" : "x turn\n", stdout);
    int* smt = bestMove(myGame.board, myGame.turn, -1000, 1000, 0);
    printf("\nBestmoves (from main) is : %d, %d | Score is %d\n", *smt, *(smt+1), *(smt +2));
    printBoard(myGame.board);
}

