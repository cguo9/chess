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

        Move *moves = NULL;
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
        }
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
                        fprintf(fptr2, "%c%c - %c%c\n",FILE_OF(itr->from), RANK_OF(itr->from), FILE_OF(itr->to), RANK_OF(itr->to) );
                        fclose(fptr2);
                        break;
                    }
                    restore_state2();
                    itr = itr->next_move;
                }
            }
            /*freeing_list(moves);*/
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
                        fprintf(fptr2, "First move: %c%c - %c%c\n",FILE_OF(itr->from), RANK_OF(itr->from), FILE_OF(itr->to), RANK_OF(itr->to) );
                        fclose(fptr2);
                        break;
                    }
                    restore_state2();
                    itr = itr->next_move;
                }       
            }
            /*freeing_list(moves);*/
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

Bool run_mate2(Move *soln){
/* main saves state
Move *soln is a move we can make with intial board.
1. make the move for current player.
2. generate a new list of legal moves for opponent
3. save state 6, make move.
4. generate a new list of legal moves for current player.
5. save state 7, make move, if there exists not mate in 1, ret FALSE, else write solution and ret TRUE
6. try the next legal move for us, looping step 5.
7. if there was no mate in 1 found then restore state 6 and continue going thru legal moves of opponent?
*** careful about saving states ***
- every move made should have a save state and restore state
- need to save state before run_mate1 and restore after cos it makes move.


*/

/* 1. make the move for currentplayer. */
    Bool flag_mate2 = TRUE;
    if(detect_castle_move(soln, CurrentPlayer)){
        perform_castle(detect_castle_move(soln, CurrentPlayer), CurrentPlayer);
    }else{
        make_move(soln, CurrentPlayer);
    }
/* after making move, check if opponent can make any moves that puts us under check
if there is a move, then there cannot be any mate in 2.
*/
    save_state3();
    Move *moves = NULL;
    unsigned int count = 0;
    Move *itr;

/* legal moves for opponent after our first move was made */
    if(legal_moves(&moves, 1-CurrentPlayer, &count)){
        itr = moves;
        /* for each legal move, make the move*/
        while(itr != NULL){
            save_state4();
            if(detect_castle_move(itr, 1-CurrentPlayer)){
                perform_castle(detect_castle_move(itr, 1-CurrentPlayer), 1-CurrentPlayer);
            }else{
                make_move(itr, 1-CurrentPlayer);
            }
/* check all the legal moves we can make, if theres no mate in 1 move for us
our first move was invalid. so there is no mate in 2 for the first move that we made
An opponent move makes us unable to mate in 1... */
            Move *moves5 = NULL;
            unsigned int count5 = 0;
            Move *itr5;
            if(legal_moves(&moves5, CurrentPlayer, &count5)){
                itr5 = moves5;
                while(itr5 != NULL){
                    save_state7();
                    if(run_mate1(itr5) == FALSE){
                        flag_mate2 = FALSE;
                        break;
                    }else{
                        flag_mate2 = TRUE;
                    }
                    restore_state7();
                    itr5 = itr5->next_move;
                }
            } /* opponent moved.
            if there was no mate in 1 for us in our next turn then there is no mate in 2*/
            /*freeing_list(moves5); error here*/ 

            restore_state4();
            itr = itr->next_move;
        }
    }
    /*freeing_list(moves); error here as well*/

    if(flag_mate2 == FALSE){
        return FALSE;
    }
    restore_state3();

    save_state5();
    Move *moves3 = NULL;
    unsigned int count3 = 0;
    Move *itr3;
    if(legal_moves(&moves3, CurrentPlayer, &count3)){
        itr3 = moves3;
        /*printf("================ Legal moves after OPPONENT MOVES ==============\n");*/
        while(itr3 != NULL){
            /* 5. save state 4, run mate in 1 function, if mate in 1, write solution and ret TRUE */
            save_state6();
             /*printf("PIECE:%d  MOVE: %u - %u  ||  Promotion: %d\n",(int)itr3->piece , itr3->from, itr3->to,
                (int)itr3->promotion_choice); */
            if(run_mate1(itr3) == TRUE){
                FILE *fptr2 = fopen(solutions, "a");
                if(fptr2 == NULL){
                    printf("Error opening file\n");
                    return 0;
                }
                fprintf(fptr2, "Second Move: %c%c - %c%c\n",FILE_OF(itr3->from), RANK_OF(itr3->from), FILE_OF(itr3->to), RANK_OF(itr3->to) );
                fclose(fptr2);
                return TRUE;
            }
            restore_state6();
            itr3 = itr3->next_move;
        }
    }
    /*freeing_list(moves3); */
    restore_state5();
    return FALSE;


/* 2. generate a new list of legal moves for opponent */
/*
    Move *moves = NULL;
    unsigned int count = 0;
    Move *itr;
    if(legal_moves(&moves, 1-CurrentPlayer, &count)){
        itr = moves;

        while(itr != NULL){

            save_state3();

            if(detect_castle_move(itr, 1-CurrentPlayer)){
                perform_castle(detect_castle_move(itr, 1-CurrentPlayer), 1-CurrentPlayer);
            }else{
                make_move(itr, 1-CurrentPlayer);
            }

            Move *moves2 = NULL;
            unsigned int count2 = 0;
            Move *itr2;
            if(legal_moves(&moves2, CurrentPlayer, &count2)){
                itr2 = moves2;

                while(itr2 != NULL){

                    save_state4();

                    if(run_mate1(itr2) == TRUE){

                        FILE *fptr2 = fopen(solutions, "a");
                        if(fptr2 == NULL){
                            printf("Error opening file\n");
                            return 0;
                        }
                        fprintf(fptr2, "Second Move: %c%c - %c%c\n",FILE_OF(itr2->from), RANK_OF(itr2->from), FILE_OF(itr2->to), RANK_OF(itr2->to) );
                        fclose(fptr2);
                        return TRUE;
                    }

                    restore_state4();
                    itr2 = itr2->next_move;
                }
            }

            restore_state3();
            itr = itr->next_move;
        }
    }
*/
/* no mate in 2 possibility for the first move we made. exit and continue checking
the rest of the legal moves we can make from the parsed board.
*/
    return FALSE;
}


/* Bool matein2(Move *soln) {
    Bool mate2_flag = TRUE;
    if(detect_castle_move(soln, CurrentPlayer)) {
        perform_castle(detect_castle_move(soln, CurrentPlayer), CurrentPlayer);
    } else {
        make_move(soln, CurrentPlayer);
    }

    save_state3();
    
    while(mate2_flag == TRUE) {
        Move *moves = NULL;
        unsigned int count = 0;
        Move *itr;
        if(legal_moves(&moves, 1-CurrentPlayer, &count)) {
            itr = moves;
            while(itr != NULL) {
                save_state4();
                if(detect_castle_move(itr, 1-CurrentPlayer), 1-CurrentPlayer) {
                    perform_castle(detect_castle_move(itr, 1 - CurrentPlayer), 1 - CurrentPlayer);
                } else {
                    make_move(itr, 1-CurrentPlayer);

                }

                Move *moves2 = NULL;
                unsigned int count2 = 0;
                Move *itr2;
                if(legal_moves(&moves2, CurrentPlayer, &count2)) {   
                    itr2 = moves2;
                    while(itr2 != NULL) {
                        display_board();
                        save_state5();
                        if(run_mate1(itr2) == FALSE) {
                            return FALSE;
                        }
                        restore_state5();
                        itr2 = itr2->next_move;
                    }
                }
            
            restore_state4();
            itr = itr->next_move;
            }
        }
    
    }
    printf("TRUE\n");
    return TRUE;
}
*/

void freeing_list(Move *head){
    Move* temp;
    while (head != NULL){
       temp = head;
       head = head->next_move;
       free(temp);
    }

}
