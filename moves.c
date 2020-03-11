#include "moves.h"
#include "chess.h"

void save_state(); //save all global variables

void restore_state(); //restore all global variables

void capture_piece(); //clear bit of opponent piece, set bit of your piece at that position

void make_move(PlayerColor c, Pos pos); //make a move without validating. Clear bit at current position for current player. Set bit for the new position for current player.

Board get_king_moves(Pos pos, PlayerColor c) { //check if you are getting checked if you move & if piece exists on a spot (if bit in position is set to 1 on FULLBOARD)
	Board king_board = BIT(pos);
	king_board = SET_BIT(king_board, NORTH_OF(pos));
	king_board = SET_BIT(king_board, SOUTH_OF(pos));
	king_board = SET_BIT(king_board, WEST_OF(pos));
	king_board = SET_BIT(king_board, EAST_OF(pos));
	king_board = SET_BIT(king_board, NW_OF(pos));
	king_board = SET_BIT(king_board, NE_OF(pos));
	king_board = SET_BIT(king_board, SW_OF(pos));
	king_board = SET_BIT(king_board, SE_OF(pos));
	king_board = RESET_BIT(king_board, pos);

	return king_board;
}

Board get_rook_moves(Pos pos,PlayerColor c) { //check for your colored pieces if they are in the way. Check opponent colors for possible capture.
	Board rook_board = BIT(pos);
	while(EAST_OF(rook_board) != UNKNOWN_POS) {
		if(UNOCCUPIED(pos)){
			SET_BIT(rook_board, EAST_OF(pos));
		}else{
			if(IS_SET(BOARD(player[c]), EAST_OF(pos))){
				break;
			}else{	//opponent piece is there
				SET_BIT(rook_board, EAST_OF(pos));
			}
		}
	}

	while(NORTH_OF(rook_board) != UNKNOWN_POS) {
		if(UNOCCUPIED(pos)){
			SET_BIT(rook_board, NORTH_OF(pos));
		}else{
			if(IS_SET(BOARD(player[c]), NORTH_OF(pos))){
				break;
			}else{	//opponent piece is there
				SET_BIT(rook_board, NORTH_OF(pos));
			}
		}
	}

	while(SOUTH_OF(rook_board) != UNKNOWN_POS) {
		if(UNOCCUPIED(pos)){
			SET_BIT(rook_board, SOUTH_OF(pos));
		}else{
			if(IS_SET(BOARD(player[c]), SOUTH_OF(pos))){
				break;
			}else{	//opponent piece is there
				SET_BIT(rook_board, SOUTH_OF(pos));
			}
		}
	}

	while(WEST_OF(rook_board) != UNKNOWN_POS) {
		if(UNOCCUPIED(pos)){
			SET_BIT(rook_board, WEST_OF(pos));
		}else{
			if(IS_SET(BOARD(player[c]), WEST_OF(pos))){
				break;
			}else{	//opponent piece is there
				SET_BIT(rook_board, WEST_OF(pos));
			}
		}
	}
	if((player[c].castle_flags == CASTLE_KING)){
		SET_BIT(rook_board, BIT((pos-2)));
		player[c].castle_flags = NO_CASTLE;
	}else if ((player[c].castle_flags == CASTLE_QUEEN)){
		SET_BIT(rook_board, BIT((pos+3)));
		player[c].castle_flags = NO_CASTLE;	//do we set this here?
		//we can set castle_flags when we are actually making the move in validate_and_move
	}
	RESET_BIT(rook_board, pos);
	return rook_board;

}


Board get_pawn_moves(Pos pos,PlayerColor c) {
	Board pawn_board = BIT(pos);
	//if color is black, check if its still in starting pos, if it is you can move NORTH_OF or NORTH_OF(NORTH_OF())
	//check the same for white and black

}

Bool king_is_checked(PlayerColor c); //returns TRUE if king is under check, FALSE otherwise

/* Given a color, this function returns a singly linked list of all legal Moves with the head at *m.
 * The function returns TRUE if at least 1 legal move is available.
 * The total number of moves found is stored in the address pointed to by pcount. */
Bool legal_moves(Move **m, PlayerColor c, unsigned int *pcount) {
    /* Your implementation */
	/* TODO: Very unsure how **m works, what I wrote doesn't work but
	 * I wanted to get my ideas down, we can discuss at meeting*/
	int x = 0;
	for(int pos = 0; pos < 64; pos++){
		if (IS_SET(player[c].k, pos)) {
			Board king_moves = get_king_moves(pos,c);
			for(int i = 0; i < 64; i++) {
				if(IS_SET(king_moves, i)) {
					save_state();
					make_move(c, pos);

					if(king_is_checked(c) == TRUE) {
						restore_state();
						continue;
					} else {
						Move *temp = (Move *) malloc(sizeof(Move));
						temp->from = pos; //64 bit with 1 in the posiiton pos
						temp->to = pos; //64 bit with 1 in the position i
						temp->piece = KING;
						temp->promotion_choice = UNKNOWN;
						if (m == NULL) m = temp;
						else {
							m->next_move = temp;
							m = m->next_move;
						}
					}
				}
			}
		}
		/*if(get_piece(i) != ' '){
			if(get_piece_at(i, WHITE) == PAWN){
				if(NORTH_OF(i) < 64 && UNOCCUPIED(NORTH_OF(i))){
					char *temp;
					temp[0] = FILE_OF(i);
					temp[1] = RANK_OF(i);
					m[x].from = temp; //Obviously doesn't work but this is my thought process
					temp[0] = FILE_OF(NORTH_OF(i));
					temp[1] = RANK_OF(NORTH_OF(i));
					m[x].to = temp;
					m[x].piece = PAWN;
					x++;
				}
				if(get_piece_at(NE_OF(i), BLACK) != UNKNOWN){
					char *temp;
					temp[0] = FILE_OF(i);
					temp[1] = RANK_OF(i);
					m[x].from = temp;
					temp[0] = FILE_OF(NE_OF(i));
					temp[1] = RANK_OF(NE_OF(i));
					m[x].to = temp;
					m[x].piece = PAWN;
					x++;
				}
				if(get_piece_at(NW_OF(i), BLACK) != UNKNOWN){
					char *temp;
					temp[0] = FILE_OF(i);
					temp[1] = RANK_OF(i);
					m[x].from = temp;
					temp[0] = FILE_OF(NW_OF(i));
					temp[1] = RANK_OF(NW_OF(i));
					m[x].to = temp;
					m[x].piece = PAWN;
					x++;
				}
			}
			if(get_piece_at(i, BLACK) == PAWN){
				//Same as with white but south instead of north and fix colors
			}
		}*/
	}
	if(x != 0) return TRUE;
	return FALSE;
}

/* Returns TRUE if the CurrentPlayer is under checkmate, FALSE otherwise. */
Bool is_checkmate() {
    /* Your implementation */
    if (legal_moves != TRUE) return TRUE;
    return FALSE;
}

/* Validate a move and make it. Returns TRUE if successful, FALSE if not.
 *  Error message if any, are stored in *msg.
 * ep_square (if any) is stored in *ep_sq
 */
Bool validate_and_move(Move *move, char **msg, PlayerColor c, Pos *ep_sq) {
    /* Your implementation */

//set castle_flags if rook/king is moving and ep_sq if pawn is moving

}

/* Function to decide whether the current position is a draw */
/* Draw can be due to insufficient material, 3 move repetition or stalemate */
	/* 3 move repetition also covers perpetual check */
Bool is_draw() {
    /* Your implementation */
}

/* Returns the piece on a square belonging to player color c.
 * If there is no piece with color c, UNKNOWN is returned. */
Piece get_piece_at(Board pos, PlayerColor c) {
    /* Your implementation */
	if(c == WHITE){
		switch(get_piece(pos)){
			case 'R': return ROOK; break;
			case 'N': return NIGHT; break;
			case 'B': return BISHOP; break;
			case 'Q': return QUEEN; break;
			case 'K': return KING; break;
			case 'P': return PAWN; break;
			default: return UNKNOWN;
		}
	}
	else{
		switch(get_piece(pos)){
			case 'r': return ROOK; break;
			case 'n': return NIGHT; break;
			case 'b': return BISHOP; break;
			case 'q': return QUEEN; break;
			case 'k': return KING; break;
			case 'p': return PAWN; break;
			default: return UNKNOWN;
		}
	}
}

PlayerColor get_color_at(Pos pos){
    if((get_piece(pos) == 'R') || (get_piece(pos) == 'N') || (get_piece(pos) == 'B') || (get_piece(pos) == 'Q')
    || (get_piece(pos) == 'K') || (get_piece(pos) == 'P')) return WHITE;
    else return BLAK;
}

/* Check if this move is trying to castle */
unsigned int detect_castle_move(Move move, PlayerColor c) {
    /* Your implementation */
}

/* Perform castling. Moves king and rook and resets castle flags */
void perform_castle(unsigned int castle, PlayerColor c) {
    /* Your implementation */
}
