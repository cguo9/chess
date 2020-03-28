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

PlayerState temp_player3[2];
Pos temp_ep_square3;
PlayerColor temp_currentPlayer3;

PlayerState temp_player4[2];
Pos temp_ep_square4;
PlayerColor temp_currentPlayer4;

PlayerState temp_player5[2];
Pos temp_ep_square5;
PlayerColor temp_currentPlayer5;

PlayerState temp_player6[2];
Pos temp_ep_square6;
PlayerColor temp_currentPlayer6;

PlayerState temp_player7[2];
Pos temp_ep_square7;
PlayerColor temp_currentPlayer7;
/* used to test || delete later
void decToBinary(int n);
*/

char const *solutions;
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
    /* char const *solutions = argv[2]; */
    solutions = argv[2];
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

        /*Move *moves = NULL;
        unsigned int count = 0;
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
        } */
        /*freeing_list(moves); error here */

/* NEED TO FREE THIS LINKED LIST BEFORE PARSING NEXT BOARD */

        printf("================ Making moves and determining if checkmate ==============\n");
        /* temporarily, actually suppsoed to be argv[3]*/
        mode = atoi(argv[3]);
        Bool found_sol = FALSE;
        if(mode == 1){
            Move *moves = NULL;
            unsigned int count = 0;
            Move *itr;
	    /*Move *temp;*/
            if(legal_moves(&moves, CurrentPlayer, &count)){
                itr = moves;
                while(itr != NULL){
                    save_state2();
                    if(run_mate1(itr) == TRUE){
                        /* put into solutions.txt here */
                        found_sol = TRUE;
                        printf("CHECKMATE SOLUTION: Piece = %d  %d to %d, Promotion = %d\n", itr->piece, itr->from, itr->to, itr->promotion_choice);
                        printf("%c%c - %c%c\n",FILE_OF(itr->from), RANK_OF(itr->from), FILE_OF(itr->to), RANK_OF(itr->to));
                        FILE *fptr2 = fopen(solutions, "a");
                      	if(fptr2 == NULL){
                      		printf("Error opening file\n");
                      		return 0;
                      	}
                        fprintf(fptr2, "%c%c-%c%c\n",FILE_OF(itr->from), RANK_OF(itr->from), FILE_OF(itr->to), RANK_OF(itr->to) );
                        fclose(fptr2);
                        break;
                    }
                    restore_state2();
		    /*temp = itr;*/
                    itr = itr->next_move;
		    /*free(temp);*/
                }
		/*free(itr);*/
            }
            freeing_list(&moves);
            if(found_sol == FALSE) {
                printf("\ncannot find run_mate1 solution.\n");
                FILE *fptr2 = fopen(solutions, "a");
                if(fptr2 == NULL){
                    printf("Error opening file\n");
                    return 0;
                }
                fprintf(fptr2, "%d\n", 0);
                fclose(fptr2);
            }
            /* while(moves != NULL){
                freeing_list(moves);
            } */
        }else if(mode == 2){
            Move *moves = NULL;
            unsigned int count = 0;
            Move *itr;
	    Move *temp;
            if(legal_moves(&moves, CurrentPlayer, &count)){
                itr = moves;
                printf("Legal moves for original board: \n");
                while(itr != NULL){
                    save_state2();
                    if(run_mate2(itr) == TRUE){
                        printf("Found Checkmate\n");
                        found_sol = TRUE;
                        FILE *fptr2 = fopen(solutions, "a");
                      	if(fptr2 == NULL){
                      		printf("Error opening file\n");
                      		return 0;
                      	}
                        fprintf(fptr2, "%c%c-%c%c\n",FILE_OF(itr->from), RANK_OF(itr->from), FILE_OF(itr->to), RANK_OF(itr->to) );
                        fclose(fptr2);
                        break;
                    }
                    restore_state2();
		    temp = itr;
                    itr = itr->next_move;
		    free(temp);
                }      
	       free(itr);	
            }
           /* freeing_list(moves); */
            if(found_sol == FALSE) {
                printf("\ncannot find run_mate2 solution.\n");
                FILE *fptr2 = fopen(solutions, "a");
                if(fptr2 == NULL){
                    printf("Error opening file\n");
                    return 0;
                }
                fprintf(fptr2, "%d\n", 0);
                fclose(fptr2);
            }
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
    /* printf("\nMaking Move... Piece %d, %d to %d", soln->piece, soln->from, soln->to); */
    if(detect_castle_move(soln, CurrentPlayer)){
        perform_castle(detect_castle_move(soln, CurrentPlayer), CurrentPlayer);
    }else{
        make_move(soln, CurrentPlayer);
    }

    if(is_checkmate(CurrentPlayer) == TRUE){
        return TRUE;
    }
    return FALSE;
}

Bool existmate1(PlayerColor c) {
    Move *moves = NULL;
    unsigned int count;
    Move *itr = NULL;
    Bool mate_in_1_flag = FALSE;


    if(legal_moves(&moves, c, &count)) {
        itr = moves;
        while (itr != NULL) {
            save_state4();
            if (detect_castle_move(itr, c)) {
                perform_castle(detect_castle_move(itr, c), c);
            } else {
                make_move(itr, c);
            }
            if(run_mate1(itr)) {
                mate_in_1_flag = TRUE;
		/*freeing_list(&moves);*/ 
                return TRUE;
            }
	  
            itr = itr->next_move; 
            restore_state4();
        }
	/*freeing_list(&moves);*/
    } else {
        return FALSE;
    }
    /*freeing_list(&moves); */
    return mate_in_1_flag;
}


Bool run_mate2(Move *soln) {
    Bool mate2_flag = TRUE;
    if(detect_castle_move(soln, CurrentPlayer)) {
        perform_castle(detect_castle_move(soln, CurrentPlayer), CurrentPlayer);
    } else {
        /*printf("OUR MOVE PIECE:%d  MOVE: %u - %u  ||  Promotion: %d\n", (int)soln->piece, soln->from, soln->to,
               (int)soln->promotion_choice); */
        make_move(soln, CurrentPlayer);
    }

    /*check for enpassant here */
    detect_and_set_ep(soln, CurrentPlayer);


    Move *moves = NULL;
    unsigned int count = 0;
    Move *itr;
    /*Move *temp;*/
    if(legal_moves(&moves, 1-CurrentPlayer, &count)) {
        itr = moves;
        while(itr != NULL) {
            save_state7();
            /*rintf("OPPONENT MOVE PIECE:%d  MOVE: %u - %u  ||  Promotion: %d\n", (int)itr->piece, itr->from, itr->to,
                   (int)itr->promotion_choice); */
            if(detect_castle_move(itr, 1-CurrentPlayer), 1-CurrentPlayer) {
                perform_castle(detect_castle_move(itr, 1 - CurrentPlayer), 1 - CurrentPlayer);
            } else {
                make_move(itr, 1-CurrentPlayer);
      	     }
            detect_and_set_ep(itr, 1-CurrentPlayer);

            if(existmate1(CurrentPlayer) == FALSE) {
                /*display_board();
                printf("No mate in 1\n"); */
                mate2_flag = FALSE;
                return FALSE;
            }
           /* restore_state7();
	    temp = itr;*/
            itr = itr->next_move;
	    /*free(temp);*/
        }
	freeing_list(&moves);
	/*free(itr);*/
    } else {
        return FALSE;
    }
    return mate2_flag;
}


void freeing_list(Move **head){
    Move* temp;
    while ((*head) != NULL){
       temp = (*head);
       *head = (*head)->next_move;
       free(temp);
    }

}
