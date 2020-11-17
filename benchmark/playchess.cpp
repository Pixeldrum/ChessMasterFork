//#include <mcheck.h>
#include <cstdlib>
#include <cstdio>
#include <list>
#include "chessboard.h"
#include "humanplayer.h"
#include "aiplayer.h"
#include <time.h>
#include <omp.h>
using namespace std;

int main(void) {
	double cpu_time_used;
	clock_t start, end;
	   
	ChessBoard board;
	list<Move> regulars, nulls;
	int turn = WHITE;
	Move move;
	bool found;

	// Initialize players
	AIPlayer black(BLACK, 3);
	HumanPlayer white(WHITE);

	// setup board
	board.initDefaultSetup();

	for(;;) {
	 start = clock();
		// show board
		board.print();

		// query player's choice
		if(turn)
			found = black.getMove(board, move);
		else
			found = white.getMove(board, move);

		if(!found)
			break;

		// if player has a move get all moves
		regulars.clear();
		nulls.clear();
		board.getMoves(turn, regulars, regulars, nulls);

		// execute maintenance moves
		for(list<Move>::iterator it = nulls.begin(); it != nulls.end(); ++it)
			board.move(*it);

		// execute move
		board.move(move);
		move.print();

		// opponents turn
		turn = TOGGLE_COLOR(turn);
		
		
		end = clock();
	
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	  printf("CPU TIME USED: %f\n", cpu_time_used); 
	   
	}

	ChessPlayer::Status status = board.getPlayerStatus(turn);

	switch(status)
	{
		case ChessPlayer::Checkmate:
			printf("Checkmate\n");
			break;
		case ChessPlayer::Stalemate:
			printf("Stalemate\n");
			break;
	}
	
}
