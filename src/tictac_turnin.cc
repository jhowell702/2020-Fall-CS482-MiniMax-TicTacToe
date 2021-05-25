#include <stdio.h>

#include "../include/tictac_support.h"
/**
	make_move: takes a board state and makes a legal
	(hopefully optimal) move

	args:
		int [][3] board: 3x3 array of ints representing the
		board state. The values of board are altered based
		on the move
			0: empty
			1: x
		 -1: o

	returns (int):
		the number of steps it took to choose the best move
		(current implementation returns 1 by default, 0 if no move made)
**/

int checkWin(int board[3][3]){

	int adder = 0;

	for(int x=0; x<3; x++){ //check rows
		adder = board[x][0] + board[x][1] + board[x][2];
		if(adder == 3){
			return 1;//maximizer wins
		}else if(adder == -3){
			return -1;//minimizer wins
		}
	}
	for (int y=0; y<3; y++){
		adder = board[0][y] + board[1][y] + board[2][y];
		if(adder == 3){
			return 1;//maximizer wins
		}else if(adder == -3){
			return -1;//minimizer wins
		}
	}

	//check diaganol #1
	adder = board[0][0] + board[1][1] + board[2][2];
	if(adder == 3){
		return 1;//maximizer wins
	}else if(adder == -3){
		return -1;//minimizer wins
	}

	//check diaganol #2
	adder = board[0][2] + board[1][1] + board[2][0];
	if(adder == 3){
		return 1;//maximizer wins
	}else if(adder == -3){
		return -1;//minimizer wins
	}

	int total = 0;
	for(int x=0; x<3; x++){
		for(int y=0; y<3; y++){
			if(board[x][y] != 0){
				total++;
			}
		}
	}

	if(total == 9){
		return 0;//no win, draw
	}

	return 2; //no win, no draw, return state flag 2 to show game is not over

}

int max(int value1, int value2){

	if(value1 >= value2){
		return value1;
	}else{
		return value2;
	}
}

int min(int value1, int value2){
	if(value1 <= value2){
		return value1;
	}else{
		return value2;
	}
}

int miniMax(int board[3][3], bool playerMax){ /*cpu is maximizer,
								so if playerMax = 1, CPU is making move*/

	switch(checkWin(board)){
		case 0: //draw on board
			return 0;
			break;
		case 1: //AI wins
			return 1;
			break;
		case -1: //human wins
			return -1;
			break;
		case 2: //no win but open spaces left, continue to minimax
			break;
	}

	//traverse all open spaces, if none return 0 for draw
	if(playerMax == true){ //if maximizer

		int best = -100; //set best to be max negative value, 0 could null negative values when choosing max

		for(int x=0; x<3; x++){
			for(int y=0; y<3; y++){
				if(board[x][y] == 0){ //if empty space
					board[x][y] = playerMax; //change value of board choice
					best = max(best, miniMax(board, !playerMax));
					board[x][y] = 0; //undo board choice for next square chosen
				}
			}
		}

		return best;
	}

	if(playerMax == false){

		int best = 100; //set best to be max negative value, 0 could null negative values when choosing max

		for(int x=0; x<3; x++){
			for(int y=0; y<3; y++){
				if(board[x][y] == 0){ //if empty space
					board[x][y] = playerMax; //change value of board choice
					best = min(best, miniMax(board, !playerMax));
					board[x][y] = 0; //undo board choice for next square chosen
				}
			}
		}
		return best;
	}
}

int make_move( int board[][3] )
{

	if(checkWin(board) != 2){
		printf("Board is full or there is a win");
		return 0; //board was full from checkWin function
	}

	// figure out what move it is
	int state = 0;
	for( int i = 0; i < 3; i++ )
		for( int j = 0; j < 3; j++ )
			state += board[i][j];

	state = -state;
	if( state == 0 ){
		state = 1;
	}

	bool player;
	if(state == 1){
		player = true;
	}else if (state == -1){
		player = false;
	}

	int bestMoveValue = -1000;
	int bestX = -1;
	int bestY = -1;

	for(int x=0; x<3; x++){
		for(int y=0; y<3; y++){
			if(board[x][y] == 0){
				board[x][y] = state; //make cpu move

				if(checkWin(board) == state){//if cpu wins from this move, don't bother with minimax
					printf( "player 1 made move: [%d,%d]\n", x, y );
					return 1;
				}

				int currentMoveValue = miniMax(board, player); //we've made the first move, goes back to minimizer

				board[x][y] = 0; //undo move for next cpu check

				if(currentMoveValue > bestMoveValue){
					bestX = x;
					bestY = y;
					bestMoveValue = currentMoveValue;
				}

			}
		}
	}

	printf( "player %d made move: [%d,%d]\n",state, bestX, bestY );
	board[bestX][bestY] = state;
	return 1;
}
