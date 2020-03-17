#include "moves.h"
#include "chess.h"


void save_state(){
	memcpy(&temp_player, &player, sizeof(PlayerState));
	memcpy(&temp_ep_square, &ep_square, sizeof(Pos));
	memcpy(&temp_currentPlayer, &CurrentPlayer, sizeof(PlayerColor));
}

void restore_state(){
	memcpy(&ep_square, &temp_ep_square, sizeof(Pos));
	memcpy(&CurrentPlayer, &temp_currentPlayer, sizeof(PlayerColor));
	memcpy(&player, &temp_player, sizeof(PlayerState));
}

void capture_piece();

/* clear bit of opponent piece, set bit of your piece at that position */

void make_move(Move *m, PlayerColor c){
	switch(m->piece){
			case ROOK:
				RESET_BIT(player[c].r,m->from);
				SET_BIT(player[c].r,m->to);
				break;
			case KING:
				RESET_BIT(player[c].k,m->from);
				SET_BIT(player[c].k,m->to);
				break;
			case QUEEN:
				RESET_BIT(player[c].q,m->from);
				SET_BIT(player[c].q,m->to);
				break;
			case BISHOP:
				RESET_BIT(player[c].b,m->from);
				SET_BIT(player[c].b,m->to);
				break;
			case NIGHT:
				RESET_BIT(player[c].n,m->from);
				SET_BIT(player[c].n,m->to);
				break;
			case PAWN:
				RESET_BIT(player[c].p,m->from);
				SET_BIT(player[c].p,m->to);
				break;
			case UNKNOWN: break;

		}
	Piece capture = get_piece_at(m->to, 1-c);
	/*check if any opponent piece where we are trying to move to*/
	if(capture){
		switch(capture){
			/*reset bit of opponent piece where we are trying to move to*/
			case ROOK:
				RESET_BIT(player[1-c].r,m->to);
				break;
			case KING:
			/*dont think this case should ever be hit*/
				RESET_BIT(player[1-c].k,m->to);
				break;
			case QUEEN:
				RESET_BIT(player[1-c].q,m->to);
				break;
			case BISHOP:
				RESET_BIT(player[1-c].b,m->to);
				break;
			case NIGHT:
				RESET_BIT(player[1-c].n,m->to);
				break;
			case PAWN:
				RESET_BIT(player[1-c].p,m->to);
				break;
			case UNKNOWN: break;
		}
	}

}


/*void make_move(PlayerColor c, Pos pos);
make a move without validating. Clear bit at current position for current player. Set bit for the new position for current player.
*/
Board get_king_moves(Pos pos, PlayerColor c) {
/*check if you are getting checked if you move & if piece exists on a spot (if bit in position is set to 1 on FULLBOARD)
*/

	Board king_board = BIT(pos);
	/*check if the direction is not out of board and if not occupied*/
	if((NORTH_OF(pos) != UNKNOWN_POS)) {
		/*
		if unoccupied then can set
					OR
		if occupied by opponent piece, can set
		if occupied by your own color piece, CANNOT set
		*/
		if( (UNOCCUPIED(NORTH_OF(pos))) || ( (get_piece_at(NORTH_OF(pos), 1-c) != UNKNOWN) )){
			SET_BIT(king_board, NORTH_OF(pos));
		}
	}
	if((SOUTH_OF(pos) != UNKNOWN_POS)) {
		if( (UNOCCUPIED(SOUTH_OF(pos))) || ( (get_piece_at(SOUTH_OF(pos), 1-c) != UNKNOWN) )){
			SET_BIT(king_board, SOUTH_OF(pos));
		}
	}
	if((WEST_OF(pos) != UNKNOWN_POS)){
		if( (UNOCCUPIED(WEST_OF(pos))) || ( (get_piece_at(WEST_OF(pos), 1-c) != UNKNOWN) )){
			SET_BIT(king_board, WEST_OF(pos));
		}
	}
	if((EAST_OF(pos) != UNKNOWN_POS)) {
		if( (UNOCCUPIED(EAST_OF(pos))) || ( (get_piece_at(EAST_OF(pos), 1-c) != UNKNOWN) )){
			SET_BIT(king_board, EAST_OF(pos));
		}
	}
	if((NW_OF(pos) != UNKNOWN_POS)){
		if( (UNOCCUPIED(NW_OF(pos))) || ( (get_piece_at(NW_OF(pos), 1-c) != UNKNOWN) )){
			SET_BIT(king_board, NW_OF(pos));
		}
	}
	if((NE_OF(pos) != UNKNOWN_POS)){
		if( (UNOCCUPIED(NE_OF(pos))) || ( (get_piece_at(NE_OF(pos), 1-c) != UNKNOWN) )){
			SET_BIT(king_board, NE_OF(pos));
		}
	}
	if((SW_OF(pos) != UNKNOWN_POS)){
		if( (UNOCCUPIED(SW_OF(pos))) || ( (get_piece_at(SW_OF(pos), 1-c) != UNKNOWN) )){
			SET_BIT(king_board, SW_OF(pos));
		}
	}
	if((SE_OF(pos) != UNKNOWN_POS)){
		if( (UNOCCUPIED(SE_OF(pos))) || ( (get_piece_at(SE_OF(pos), 1-c) != UNKNOWN) )){
			SET_BIT(king_board, SE_OF(pos));
		}
	}
/*also need to set all castle_flags to NO_CASTLE

	i think we need to set_bit for possible castling here but then we would have to save state before we call get_king_moves()
	or we can set bit here and somehow reset the castle_flags in a later function?
	but then we would need a way to check if we were making a castling move
	(we could make a global variable for that)
*/

	/*
	if((player[c].castle_flags == CASTLE_KING)){
		SET_BIT(king_board, BIT((pos+2)));
		player[c].castle_flags = NO_CASTLE;
	}else if ((player[c].castle_flags == CASTLE_QUEEN)){
		SET_BIT(king_board, BIT((pos-3)));
		player[c].castle_flags = NO_CASTLE;
	}
	*/
	RESET_BIT(king_board, pos);
	return king_board;
}

Board get_rook_moves(Pos pos,PlayerColor c) {
	/*check for your colored pieces if they are in the way. Check opponent colors for possible capture.
*/
	Board rook_board = BIT(pos);
	/* need to change position in these while loops so its not infinite loops
	ie. if pos was 16, NORTH_OF(16) is 8 then we need to check if NORTH_OF(8) is valid and it is, 0, so
	check if NORTH_OF(0) which is invalid
	*/
	Pos temp_pos = pos;
	/* we still need to retain the ORIGINAL position of the piece and reset it to find
	NORTH_OF that original position, WEST_OF and SOUTH_OF
	*/
	while(EAST_OF(pos) != UNKNOWN_POS) {
		if(UNOCCUPIED(EAST_OF(pos))){
			SET_BIT(rook_board, EAST_OF(pos));
			pos = EAST_OF(pos);
		}else{
			if(IS_SET(BOARD(player[c]), EAST_OF(pos))){
				break;
			}else{	/*opponent piece is there*/
				SET_BIT(rook_board, EAST_OF(pos));
				break;
			}
		}
	}
	pos = temp_pos;
	while(NORTH_OF(pos) != UNKNOWN_POS) {
		if(UNOCCUPIED(NORTH_OF(pos))){
			SET_BIT(rook_board, NORTH_OF(pos));
			pos = NORTH_OF(pos);
		}else{
			if(IS_SET(BOARD(player[c]), NORTH_OF(pos))){
				break;
			}else{
				SET_BIT(rook_board, NORTH_OF(pos));
				break;
			}
		}
	}
	pos = temp_pos;
	while(SOUTH_OF(pos) != UNKNOWN_POS) {
		if(UNOCCUPIED(SOUTH_OF(pos))){
			SET_BIT(rook_board, SOUTH_OF(pos));
			pos = SOUTH_OF(pos);
		}else{
			if(IS_SET(BOARD(player[c]), SOUTH_OF(pos))){
				break;
			}else{
				SET_BIT(rook_board, SOUTH_OF(pos));
				break;
			}
		}
	}
	pos = temp_pos;
	while(WEST_OF(pos) != UNKNOWN_POS) {
		if(UNOCCUPIED(WEST_OF(pos))){
			SET_BIT(rook_board, WEST_OF(pos));
			pos = WEST_OF(pos);
		}else{
			if(IS_SET(BOARD(player[c]), WEST_OF(pos))){
				break;
			}else{
				SET_BIT(rook_board, WEST_OF(pos));
				break;
			}
		}
	}
	/*
	if((player[c].castle_flags == CASTLE_KING)){
		SET_BIT(rook_board, BIT((pos-2)));
		player[c].castle_flags = NO_CASTLE;
	}else if ((player[c].castle_flags == CASTLE_QUEEN)){
		SET_BIT(rook_board, BIT((pos+3)));
		player[c].castle_flags = NO_CASTLE;
	}
	*/
	RESET_BIT(rook_board, temp_pos);
	return rook_board;

}


Board get_pawn_moves(Pos pos,PlayerColor c) {
	Board pawn_board = BIT(pos);
	/*if color is black, check if its still in starting pos, if it is you can move NORTH_OF or NORTH_OF(NORTH_OF())
	check the same for white and black
	*/
	Pos temp_pos = pos;
	if(c == BLACK){
		if((pos == 8) || (pos == 9) || (pos == 10) || (pos == 11) || (pos == 12) || (pos == 13)
		|| (pos == 14) || (pos == 15)){
			/* can move 1 or 2 spaces forward*/
			if(WEST_OF(pos) != UNKNOWN_POS) {
				if(UNOCCUPIED(SOUTH_OF(pos))){
					SET_BIT(pawn_board, SOUTH_OF(pos));
					pos = SOUTH_OF(pos);
					/* 2 squares are unoccupied */
					if(UNOCCUPIED(SOUTH_OF(pos))){
						SET_BIT(pawn_board, SOUTH_OF(pos));
					}
				} /* else if occupied directly infront the pawn cant move, do nothing */
			}
			/* end if pos = starting square for black*/
		}else{ /* pawn is not in a starting position can only move up 1*/
			pos = temp_pos; /* just in case */
			if(WEST_OF(pos) != UNKNOWN_POS) {
				if(UNOCCUPIED(WEST_OF(pos))){
					SET_BIT(pawn_board, WEST_OF(pos));
				}
			}
		}
		pos = temp_pos;
		/* regardless of position, check if it can move to a captured piece's position (diagonal capture) */
		if((SOUTH_OF(EAST_OF(pos))) != UNKNOWN_POS) {
			if(IS_SET(BOARD(player[1-c]), (SOUTH_OF(EAST_OF(pos)))) ){
				/* if theres an opponent piece SE of the pawn, the pawn can move there */
				SET_BIT(pawn_board, (SOUTH_OF(EAST_OF(pos))) );
			}
		}
		if((SOUTH_OF(WEST_OF(pos))) != UNKNOWN_POS) {
			if(IS_SET(BOARD(player[1-c]), (SOUTH_OF(WEST_OF(pos)))) ){
				/* if theres an opponent piece SW of the pawn, the pawn can move there */
				SET_BIT(pawn_board, (SOUTH_OF(WEST_OF(pos))) );
			}
		}
	}
	pos = temp_pos;
	/* reset position for white just in case*/


	if((ep_square >= 0) || (ep_square < 64)){
		/* if enpassant is available, check if it is a legal move for the pawn
			THERE CAN BE MULTIPLE PAWNS ON THE BOARD, CHECK IF THE EP_SQ IS FOR THIS SPECIFIC PAWN
			THAT WE ARE GETTING VALID MOVES FOR
		*/
	}
	RESET_BIT(pawn_board, temp_pos);
	return pawn_board;
}

Board get_bishop_moves(Pos pos, PlayerColor c){
	Board bishop_board = BIT(pos);

	return bishop_board;
}

Board get_queen_moves(Pos pos, PlayerColor c){
	Board queen_board = (get_rook_moves(pos,c)) | (get_bishop_moves(pos,c));
	return queen_board;
}


Board get_night_moves(Pos pos, PlayerColor c){
	Board night_board = BIT(pos);
	return night_board;
}

/*
generate a 64 bit with 1s where all the places the opponents will move.
check if your king position (whether youre moving it or moving another piece)
is going to overlap with that 64 bit. if it is, then it is under check and it
is not a legal move. if not, then it is legal and put it into the linked list.
*/
Bool king_is_checked(Pos pos, PlayerColor c){
	/*
	**POS PASSED IN SHOULD BE 0-63**
	pos of the king , c is color of that king
	*/
	Board all_possible_captures = 0;
	Piece temp;
	int i;
	printf("Position of king: %u\n", pos);
	for(i = 0; i < 64; i++){
		/*
		if(c == WHITE){	idk if we actually need to check the color
		getting board of all possible opponent moves
		*/
		temp = get_piece_at(i, (1-c));
		switch(temp){
			case ROOK:
				all_possible_captures |= (get_rook_moves(i, 1-c));
				/*printf("Piece is: ROOK \n");*/
				   break;
			case NIGHT:
				all_possible_captures |= (get_night_moves(i, 1-c));
				/*printf("Piece is NIGHT \n");*/
				   break;
			case BISHOP:
				all_possible_captures |= (get_bishop_moves(i, 1-c));
				/*printf("Piece is BISHOP\n");*/
				   break;
			case QUEEN:
				all_possible_captures |= (get_queen_moves(i, 1-c));
				/*printf("Piece is QUEEN\n");*/
				   break;
			case KING:
				all_possible_captures |= (get_king_moves(i, 1-c));
			/*
				printf("position of opposing piece: %d\n", i);
				printf("KING and:  board is ");
			       	printf("~~~~ %lu ~~~~\n", (get_king_moves(i, 1-c)) );
			*/
			     	break;
			case PAWN:
				all_possible_captures |= (get_pawn_moves(i, 1-c));
				/*printf("Piece is PAWN\n");*/
				   break;
			case UNKNOWN:
				break;
		}

	}
	printf("all-possible captures: %lu\n", all_possible_captures);
	/*got a board with 1s in places where you can get captured*/
	if((IS_SET(all_possible_captures, pos)) == 1){
		return TRUE;
	}
	return FALSE;
}

/* Given a color, this function returns a singly linked list of all legal Moves with the head at *m.
 * The function returns TRUE if at least 1 legal move is available.
 * The total number of moves found is stored in the address pointed to by pcount. */
Bool legal_moves(Move **m, PlayerColor c, unsigned int *pcount) {
    /* Your implementation */
	/* TODO: Very unsure how **m works, what I wrote doesn't work but
	 * I wanted to get my ideas down, we can discuss at meeting*/
	/*make a head and assign m to point to head*/
/*	Move *head = (Move *) malloc(sizeof(Move));
	m = &head;
*/
	/*use head_iterator to build up linked list
	NEVER MOVE HEAD since m is pointing to it so we always have a pointer to start of list*/
/*	Move *head_iterator = &m;

	Move *head_iterator = *m;
*/
	int pos;
	int i;
	Move *head = NULL;

	for(pos = 0; pos < 64; pos++){
		if (IS_SET(player[c].k, pos)) {
			Board king_moves = get_king_moves(pos,c);
			for(i = 0; i < 64; i++) {
				if(IS_SET(king_moves, i)) {
					save_state();
					Move *temp = (Move *) malloc(sizeof(Move));
					temp->from = pos; /*64 bit with 1 in the posiiton pos*/
					temp->to = i; /*64 bit with 1 in the position i*/
					temp->piece = KING;
					temp->promotion_choice = UNKNOWN;
					make_move(temp, c); /* need to restore since we're not actually moving here*/
					if(king_is_checked(i, c) == TRUE) {
						restore_state();
						free(temp);
						printf("king is being checked \n");

						continue;
					} else {
						(*pcount)++; /*increment whats in pointer */
						restore_state();
						if ((*m) == NULL) {
							(*m) = temp;
							head = temp;
							/* printf("setting as head\n");*/
/*THE ONE TIME WE SET HEAD, rest will be using head_iterator*/
						}else {
							(*m)->next_move = temp;
							(*m) = (*m)->next_move;
							/* printf("creating link and iterating ptr \n"); */
/*this if/else should be same for the rest of these -> if (IS_SET(player[c].r, pos)) ... if (IS_SET(player[c].q, pos)) ...
*/
						}
					}
				}
			}
		} /*end of if (IS_SET(player[c].k, pos))*/


		/*if(get_piece(i) != ' '){
			if(get_piece_at(i, WHITE) == PAWN){
				if(NORTH_OF(i) < 64 && UNOCCUPIED(NORTH_OF(i))){
					char *temp;
					temp[0] = FILE_OF(i);
					temp[1] = RANK_OF(i);
					m[x].from = temp; Obviously doesn't work but this is my thought process
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
				Same as with white but south instead of north and fix colors
			}
		}*/
	}
	*m = head;
	if((*pcount) > 0) return TRUE;
	return FALSE;

}

/* Returns TRUE if the CurrentPlayer is under checkmate, FALSE otherwise. */
Bool is_checkmate() {
    /* Your implementation */
/*
	if (legal_moves != TRUE) return TRUE;
    return FALSE;*/
	return FALSE;
}

/* Validate a move and make it. Returns TRUE if successful, FALSE if not.
 *  Error message if any, are stored in *msg.
 * ep_square (if any) is stored in *ep_sq
 */
Bool validate_and_move(Move *move, char **msg, PlayerColor c, Pos *ep_sq) {
    /* Your implementation */
	return TRUE;
/*set castle_flags if rook/king is moving and ep_sq if pawn is moving*/

}

/* Function to decide whether the current position is a draw */
/* Draw can be due to insufficient material, 3 move repetition or stalemate */
	/* 3 move repetition also covers perpetual check */
Bool is_draw() {
    /* Your implementation */
	return TRUE;
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
    else return BLACK;
}

/* Check if this move is trying to castle */
unsigned int detect_castle_move(Move move, PlayerColor c) {
    /* Your implementation */
	return 0;
}

/* Perform castling. Moves king and rook and resets castle flags */
void perform_castle(unsigned int castle, PlayerColor c) {
    /* Your implementation */
}
