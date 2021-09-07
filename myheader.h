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
#define win 1
#define loss -1
#define draw 0
#define circle true
#define cross false


int max(int a, int b){
    if (a>=b){
        return a;
    }
    else{
        return b;
    }
}

int min(int a, int b){
    if (a<=b){
        return a;
    }
    else{
        return b;
    }
}

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

int changeState(bool board[3][3][2], int* pos, bool type){ 
    //Changes the state of the board. Returns 1 if successful and -1 if unsuccessful.
    if (pos[0] >= 3 || pos[0] < 0 || pos[1] >= 3 || pos[1] < 0){
        printf("Error! changeState received a non-existent position! \n");
        return;
    }
    int i = *pos;
    int j = *(pos+1);

    //checks if pos is already occupied
    if (board[i][j][0] == true){
        return -1;
    }
    board[i][j][0] = true;
    board[i][j][1] = type;
    return 1;
}

int checkWin(bool board[3][3][2]){
    /*
    Returns 0 if nobody has won.
    Returns -1 if x has won.
    Return 1 if o has won.
    */
    int i;
    int j;
    // check verticals
    for (i= 0; i< 3; i++){
        for (j = 0; j < 2; j++ ){    
            //printf("%d \n", j);        
            if (board[i][j][0] == false || board[i][j+1][0] == false || board[i][j][1] != board[i][j+1][1]){ //
                break;           
            }
            
            if (j==1){
                if (board[i][j][1] == circle) {
                    return 1;
                }
                return -1;
            } 
        }
    }

    //check horizontals
    for (i= 0; i< 3; i++){
        for (j = 0; j < 2; j++ ){    
            //printf("%d \n", j);        
            if (board[j][i][0] == false || board[j+1][i][0] == false || board[j][i][1] != board[j+1][i][1]){ //
                break;           
            }
            
            if (j==1){
                if (board[j][i][1] == circle) {
                    return 1;
                }
                return -1;
            } 
        }
    }
    //check diagonal top right to bottom left
    for (i=0; i< 2; i++){
        if (board[i][i][0] == false || board[i+1][i+1][0] == false || board[i][i][1] != board[i+1][i+1][1]){ //
                break;           
            }
            
            if (i==1){
                if (board[i][i][1] == circle) {
                    return 1;
                }
                return -1;
            } 
    }
    //check diagonal bottom left to top right
    for (i=0; i< 2; i++){
        j = 2-i;
        if (board[i][j][0] == false || board[i+1][j-1][0] == false || board[i][j][1] != board[i+1][j-1][1]){ //
                break;           
            }
            
            if (i==1){
                if (board[i][j][1] == circle) {
                    return 1;
                }
                return -1;
            } 
    }
    return 0;

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

int myGetLine(char *buf, size_t size) {
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
    //Function that asks for a position and converts it to a position that can be used to change state. Note due to use of static array, each call of choosepos will change your array
    char sPos[3]; 
    printf("Enter position. ('19' represents position (1,9) ");

    myGetLine(&sPos[0], 3);
    int x = atoi(sPos);
    static int returnPos[2];
    returnPos[0] = x/10;
    returnPos[1] = x%10;
    return(&returnPos[0]);
}

int (**legalMoves(bool board[3][3][2])){
    /*
    Returns an array of legal moves. Array is size 10 by 2.
    Legal moves are at start of array, followed by (-1, -1) signifying that from here onwards, data is useless.
    */
    int r = 10, c = 2, k; //Taking number of Rows and Columns
    int **moves = (int **)malloc(r * sizeof(int *));
    for (k=0; k<r; k++)
         moves[k] = (int *)malloc(c * sizeof(int));

    int i = 0;
    int j = 0;
    int count = 0;
    for (i= 0; i< 3; i++){
        for (j = 0; j < 3; j++ ){    
            //printf("%d \n", j);        
            if (board[i][j][0] == false){
                moves[count][0] = i;
                moves[count][1] = j; 
                count ++;
            }
        }
    }

    //Marking end of array. We used a fixed size array so we need to know what values are useful (legal moves).
    moves[count][0] = -1;
    moves[count][1] = -1;

    return(&moves[0]);
}

int *bestMove(bool board[3][3][2], bool turn, int alpha, int beta, int depth){
    /*
    Returns best move followed by score value that this move guarantees.
    Returns pointer to {xPos, yPos, score}
    */

    // Scores are:
    //    o wins: +1
    //    x wins: -1
    //    draw: 0
     
    int (*chosenMove) = (int*)malloc(3*sizeof(int));   //its gonna be the move + score
    int i = 0;
    int j = 0;
    int count = 0;
    int bestScore;
    chosenMove[0] = -1;
    chosenMove[1] = -1;
    if (turn == circle){  
        bestScore = loss;  //aim is to make bestScore = win
        chosenMove[2] = loss;
    } else{
        bestScore = win;  //aim is to make bestScore = lose
        chosenMove[2] = win;
    }
    
    int ** moves = legalMoves(board);
    int checkWinResult = checkWin(board);
    if (checkFull(board) || checkWinResult != 0){
        bestScore = checkWinResult;
        chosenMove[2] = bestScore;
        return chosenMove;
    }
    while (moves[count][0] != -1 && checkWinResult == 0) {
        int xPos = moves[count][0];
        int yPos = moves[count][1];
        board[xPos][yPos][0] = true;
        board[xPos][yPos][1] = turn;   
        if(turn == circle) {
            //time to maximise 
            int score[3];
            int *ptr  = bestMove(board, !turn, alpha, beta, depth);
            score[0] = ptr[0];
            score[1] = ptr[1];
            score[2] = ptr[2];
            if (bestScore < score[2]){
                bestScore = score[2];

                chosenMove[0] = xPos;
                chosenMove[1] = yPos;    
                chosenMove[2] = bestScore;

                alpha = max(alpha, bestScore);
                //if (beta <= alpha) break; 
				
            }
        } else{
            //time to minimise
            int score[3];
            int *ptr  = bestMove(board, !turn, alpha, beta, depth);
            score[0] = ptr[0];
            score[1] = ptr[1];
            score[2] = ptr[2];
            if (bestScore > score[2]){
                bestScore = score[2];

                chosenMove[0] = xPos;
                chosenMove[1] = yPos;    
                chosenMove[2] = bestScore;;

                alpha = min(alpha, bestScore);
                //if (beta <= alpha) break; 
				
            }
        }
        checkWinResult = checkWin(board);
        board[xPos][yPos][0] = false;
        count ++;
    }
    return (chosenMove);
}



#endif 