#include "io.h"

/*
 * Implement each function in this file.
 */
 
void display_board() {
    /* Your implementation */
}

Bool parse_board(char *board) {
    /* Your implementation */
}

/* Parses the input move. 
 * This function repeatedly prompts for a move until a valid move is typed in. 
 * This function only validates that:
 *	 1) from and to are valid squares on the board.
 *	 2) from and to are separated by a '-' 
 * This function does not check the legality of the move.
 */ 
Move parse_move() {
    /* Your implementation */
}

/* This function accepts a move from the user. The move is not validated */
void prompt_move(Move *m, unsigned int move_number) {
    /* Your implementation */
}

/* This function prints a move on to the console */
void print_move(Move *m) {
    /* Your implementation */
}

