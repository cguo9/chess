#include "moves.h"
#include "chess.h"
#include <stdio.h>

#include <string.h>
#include <stdlib.h>
#include <stdint.h>

PlayerState player[2];
Pos ep_square;
PlayerColor CurrentPlayer;
Mode mode;

PlayerState temp_player[2];
Pos temp_ep_square;
PlayerColor temp_currentPlayer;

PlayerState temp_player2[2];
Pos temp_ep_square2;
PlayerColor temp_currentPlayer2;
/* used to test || delete later
void decToBinary(int n);
*/
int main(int argc, char const *argv[]) {
  /* Your testing code here. */
  /*	outline:
  #if 0
  	for each line in puzzles.txt
  		parse_board(line)
  		if mode == 1:
  			run_mate1()
  		else
  			run_mate2()
  		store_solution to result.txt
  #endif

  parse board will initialize each variable
  need to memset the players and moves for the next line to be read in
  */
  	int x;
  	char const *filename = argv[1];
  	char *board_str = (char *)malloc(150);
  	memset(board_str, 0, 150);
  	FILE *fptr = fopen(filename, "r");
  	if(fptr == NULL){
  		printf("Error opening file\n");
  		return 0;
  	}

  	while((x = fscanf(fptr, "%[^\n]\n", board_str)) != EOF){
  		/*assumes valid input  */
  		printf("string read = %s\n", board_str);
  		if(parse_board(board_str)){
  			display_board();
  			printf("Current Player: %d\n", CurrentPlayer);
  			printf("Castle flags for WHITE PLAYER: %d\n", player[WHITE].castle_flags);
  			printf("Castle flags for BLACK PLAYER: %d\n", player[BLACK].castle_flags);
  			printf("En Passant square: %d\n", ep_square);
  			printf("done parsing.\n");
  			/*return 0; testing purposes */
  		}else{
  			printf("Error parsing input.\n");
  			return 0;
  		}


        Move *moves = NULL;
        unsigned int count = 0;
        /* Move *temp_head = moves; */
	    Move *itr;
        printf("================ Legal Moves for Current Player ==============\n");
        if(legal_moves(&moves, CurrentPlayer, &count) == TRUE){
            itr = moves;
    	    while(itr != NULL){
    	        printf("PIECE:%d  MOVE: %u - %u  ||  Promotion: %d\n",(int)itr->piece , itr->from, itr->to,
    				(int)itr->promotion_choice);
                itr = itr->next_move;
            }
            printf("Number of moves in linked list: %d\n", count);
        }

/* NEED TO FREE THIS LINKED LIST BEFORE PARSING NEXT BOARD */

        printf("================ Making moves and determining if checkmate ==============\n");
        /* temporarily, actually suppsoed to be argv[3]*/
        mode = atoi(argv[2]);
        Bool found_sol = FALSE;
        if(mode == 1){
            Move *moves = NULL;
            unsigned int count = 0;
            Move *itr;
            if(legal_moves(&moves, CurrentPlayer, &count)){
                itr = moves;
                while(itr != NULL){
                    /* if(run_mate1(itr) == TRUE){ */

                    save_state2();
                    make_move(itr, CurrentPlayer);
                    printf("\nMaking Move... Piece %d, %d to %d", itr->piece, itr->from, itr->to);
                    /*if(is_checkmate(1-CurrentPlayer) == TRUE){*/
                    if(is_checkmate(CurrentPlayer) == TRUE){
                        found_sol = TRUE;
                        printf("CHECKMATE SOLUTION: Piece = %d  %d to %d\n", itr->piece, itr->from, itr->to);
            /* put into solutions.txt later but print for now */
                        break;
                    }
                    restore_state2();
                    itr = itr->next_move;
                }
            }
            if(found_sol == FALSE) printf("cannot find run_mate1 solution.\n");

        }else if(mode == 2){
            /*run_mate2();*/
        }else{
            printf("Invalid Mode (Must be 1 or 2).\n");
        }

  		/* store solution in result.txt*/
  		memset(board_str, 0, 150); /* reset everything for next puzzle */

		int z;
  		for(z = 0; z < 2; z++){
  			player[z].r &= 0;
  			player[z].n &= 0;
  			player[z].b &= 0;
  			player[z].q &= 0;
  			player[z].k &= 0;
  			player[z].p &= 0;
  			player[z].castle_flags = NO_CASTLE;
  		}
  		/* probably not necessary since theyre gonna be overwritten */
  		ep_square = 0;
  		CurrentPlayer = 0;
  		mode = 0;
  	} /* end of file here */

  	fclose(fptr); /* dont forget to close the file */
  	free(board_str);

  	return 0;
}

Bool run_mate1(Move *soln){
    return FALSE;

}


/* function to convert decimal to binary */
/*
void decToBinary(int n)
{
    int binaryNum[32];
    int i = 0;
    while (n > 0) {
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
    for (int j = i - 1; j >= 0; j--)
         printf("%d", binaryNum[j]);
}
*/
