#include "moves.h"
#include "chess.h"


void save_state(){
	temp_ep_square = ep_square;
	temp_player[0] = player[0];
	temp_player[1] = player[1];
	temp_currentPlayer = CurrentPlayer;
}

void save_state2(){
	temp_ep_square2 = ep_square;
	temp_player2[0] = player[0];
	temp_player2[1] = player[1];
	temp_currentPlayer2 = CurrentPlayer;
}


void save_state3(){
	temp_ep_square3 = ep_square;
	temp_player3[0] = player[0];
	temp_player3[1] = player[1];
	temp_currentPlayer3 = CurrentPlayer;
}

void save_state4(){
	temp_ep_square4 = ep_square;
	temp_player4[0] = player[0];
	temp_player4[1] = player[1];
	temp_currentPlayer4 = CurrentPlayer;
}

void save_state5(){
	temp_ep_square5 = ep_square;
	temp_player5[0] = player[0];
	temp_player5[1] = player[1];
	temp_currentPlayer5 = CurrentPlayer;
}

void save_state6(){
	temp_ep_square6 = ep_square;
	temp_player6[0] = player[0];
	temp_player6[1] = player[1];
	temp_currentPlayer6 = CurrentPlayer;
}

void save_state7(){
	temp_ep_square7 = ep_square;
	temp_player7[0] = player[0];
	temp_player7[1] = player[1];
	temp_currentPlayer7 = CurrentPlayer;
}

void restore_state(){
	ep_square = temp_ep_square;
	player[0] = temp_player[0];
	player[1] = temp_player[1];
	CurrentPlayer = temp_currentPlayer;
}

void restore_state2(){
	ep_square = temp_ep_square2;
	player[0] = temp_player2[0];
	player[1] = temp_player2[1];
	CurrentPlayer = temp_currentPlayer2;
}

void restore_state3(){
	ep_square = temp_ep_square3;
	player[0] = temp_player3[0];
	player[1] = temp_player3[1];
	CurrentPlayer = temp_currentPlayer3;
}

void restore_state4(){
	ep_square = temp_ep_square4;
	player[0] = temp_player4[0];
	player[1] = temp_player4[1];
	CurrentPlayer = temp_currentPlayer4;
}

void restore_state5(){
	ep_square = temp_ep_square5;
	player[0] = temp_player5[0];
	player[1] = temp_player5[1];
	CurrentPlayer = temp_currentPlayer5;
}

void restore_state6(){
	ep_square = temp_ep_square6;
	player[0] = temp_player6[0];
	player[1] = temp_player6[1];
	CurrentPlayer = temp_currentPlayer6;
}

void restore_state7(){
	ep_square = temp_ep_square7;
	player[0] = temp_player7[0];
	player[1] = temp_player7[1];
	CurrentPlayer = temp_currentPlayer7;
}

/* clear bit of opponent piece, set bit of your piece at that position, check if any opponent pieces
	where you are moving to, and if there is clear bit on the opponent piece's board
 */

void make_move(Move *m, PlayerColor c){
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
	switch(m->piece){
			case ROOK:
				RESET_BIT(player[c].r,m->from);
				SET_BIT(player[c].r,m->to);
				break;
			case KING:
				/*if(detect_castle_move(m, c)){
					printf("!!!!castling here !!!!!!! \n");
					unsigned int castling = detect_castle_move(m, c);

					perform_castle(castling, c);
					break;
				}else{
				}*/
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
				switch(m->promotion_choice){
					case ROOK:
						RESET_BIT(player[c].p,m->to);
						SET_BIT(player[c].r, m->to);
						break;
					case QUEEN:
						RESET_BIT(player[c].p,m->to);
						SET_BIT(player[c].q, m->to);
						break;
					case BISHOP:
						RESET_BIT(player[c].p,m->to);
						SET_BIT(player[c].b, m->to);
						break;
					case NIGHT:
						RESET_BIT(player[c].p,m->to);
						SET_BIT(player[c].n, m->to);
						break;
					/* promotion piece should never be pawn or king */
					case PAWN: break;
					case KING: break;
					case UNKNOWN: break;
				}
				break;
			case UNKNOWN: break;

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


	if(player[c].castle_flags == CASTLE_KING){
		SET_BIT(king_board, pos+2);
		/* player[c].castle_flags = NO_CASTLE; */
	}else if (player[c].castle_flags == CASTLE_QUEEN){
		SET_BIT(king_board, pos-2);
		/* player[c].castle_flags = NO_CASTLE; */
	}

	RESET_BIT(king_board, pos);
	return king_board;
}

Board get_rook_moves(Pos pos,PlayerColor c) {
	/*check for your colored pieces if they are in the way. Check opponent colors for possible capture. */
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
			if(SOUTH_OF(pos) != UNKNOWN_POS) {
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
			if(SOUTH_OF(pos) != UNKNOWN_POS) {
				if(UNOCCUPIED(SOUTH_OF(pos))){
					SET_BIT(pawn_board, SOUTH_OF(pos));
				}
			}
		}
		pos = temp_pos;
		/* regardless of position, check if it can move to a captured piece's position (diagonal capture) */
		if(SE_OF(pos) != UNKNOWN_POS) {
			if(IS_SET(BOARD(player[1-c]), (SE_OF(pos))) ){
				/* if theres an opponent piece SE of the pawn, the pawn can move there */
				SET_BIT(pawn_board, SE_OF(pos));
			}
		}
		if(SW_OF(pos) != UNKNOWN_POS) {
			if(IS_SET(BOARD(player[1-c]), (SW_OF(pos)))){
				/* if theres an opponent piece SW of the pawn, the pawn can move there */
				SET_BIT(pawn_board, SW_OF(pos));
			}
		}
	}else{ 		/* c == WHITE */
		pos = temp_pos;
		if((pos == 48) || (pos == 49) || (pos == 50) || (pos == 51) || (pos == 52) || (pos == 53)
		|| (pos == 54) || (pos == 55)){
			/* can move 1 or 2 spaces forward*/
			if(NORTH_OF(pos) != UNKNOWN_POS) {
				if(UNOCCUPIED(NORTH_OF(pos))){
					SET_BIT(pawn_board, NORTH_OF(pos));
					pos = NORTH_OF(pos);
					/* 2 squares are unoccupied */
					if(UNOCCUPIED(NORTH_OF(pos))){
						SET_BIT(pawn_board, NORTH_OF(pos));
					}
				} /* else if occupied directly infront the pawn cant move, do nothing */
			}
			/* end if pos = starting square for black*/
		}else{ /* pawn is not in a starting position can only move up 1*/
			pos = temp_pos; /* just in case */
			if(NORTH_OF(pos) != UNKNOWN_POS) {
				if(UNOCCUPIED(NORTH_OF(pos))){
					SET_BIT(pawn_board, NORTH_OF(pos));
				}
			}
		}
		pos = temp_pos;
		/* regardless of position, check if it can move to a captured piece's position (diagonal capture) */
		if(NE_OF(pos) != UNKNOWN_POS) {
			if(IS_SET(BOARD(player[1-c]), (NE_OF(pos))) ){
				/* if theres an opponent piece SE of the pawn, the pawn can move there */
				SET_BIT(pawn_board, NE_OF(pos));
			}
		}
		if(NW_OF(pos) != UNKNOWN_POS) {
			if(IS_SET(BOARD(player[1-c]), (NW_OF(pos)))){
				/* if theres an opponent piece SW of the pawn, the pawn can move there */
				SET_BIT(pawn_board, NW_OF(pos));
			}
		}
	}	/* end c == WHITE */

	if((ep_square >= 0) || (ep_square < 64)){
		/* if enpassant is available, check if it is a legal move for the pawn
			THERE CAN BE MULTIPLE PAWNS ON THE BOARD, CHECK IF THE EP_SQ IS FOR THIS SPECIFIC PAWN
			THAT WE ARE GETTING VALID MOVES FOR
		*/
		if(c == BLACK){
			/* for black, rank 3 should be valid enpassant to caputre white pawns */
			if(NW_OF(ep_square) != UNKNOWN_POS){
				if(pos == NW_OF(ep_square)){
					SET_BIT(pawn_board, ep_square);
				}
			}
			if(NE_OF(ep_square) != UNKNOWN_POS){
				if(pos == NE_OF(ep_square)){
					SET_BIT(pawn_board, ep_square);
				}
			}
		}else{
			/* for white, rank 6 should be valid enpassant to caputre black pawns */
			if(SW_OF(ep_square) != UNKNOWN_POS){
				if(pos == SW_OF(ep_square)){
					SET_BIT(pawn_board, ep_square);
				}
			}
			if(SE_OF(ep_square) != UNKNOWN_POS){
				if(pos == SE_OF(ep_square)){
					SET_BIT(pawn_board, ep_square);
				}
			}
		}
	}

	RESET_BIT(pawn_board, temp_pos);
	return pawn_board;
}

Board get_bishop_moves(Pos pos, PlayerColor c){
	Board bishop_board = BIT(pos);
	Pos temp_pos = pos;
	while(NE_OF(pos) != UNKNOWN_POS) {
		if(UNOCCUPIED(NE_OF(pos))){
			SET_BIT(bishop_board, NE_OF(pos));
			pos = NE_OF(pos);
		}else{
			if(IS_SET(BOARD(player[c]), NE_OF(pos))){
				break;
			}else{	/*opponent piece is there*/
				SET_BIT(bishop_board, NE_OF(pos));
				break;
			}
		}
	}

	pos = temp_pos;
	while(NW_OF(pos) != UNKNOWN_POS) {
		if(UNOCCUPIED(NW_OF(pos))){
			SET_BIT(bishop_board, NW_OF(pos));
			pos = NW_OF(pos);
		}else{
			if(IS_SET(BOARD(player[c]), NW_OF(pos))){
				break;
			}else{
				SET_BIT(bishop_board, NW_OF(pos));
				break;
			}
		}
	}

	pos = temp_pos;
	while(SE_OF(pos) != UNKNOWN_POS) {
		if(UNOCCUPIED(SE_OF(pos))){
			SET_BIT(bishop_board, SE_OF(pos));
			pos = SE_OF(pos);
		}else{
			if(IS_SET(BOARD(player[c]), SE_OF(pos))){
				break;
			}else{
				SET_BIT(bishop_board, SE_OF(pos));
				break;
			}
		}
	}

	pos = temp_pos;
	while(SW_OF(pos) != UNKNOWN_POS) {
		if(UNOCCUPIED(SW_OF(pos))){
			SET_BIT(bishop_board, SW_OF(pos));
			pos = SW_OF(pos);
		}else{
			if(IS_SET(BOARD(player[c]), SW_OF(pos))){
				break;
			}else{
				SET_BIT(bishop_board, SW_OF(pos));
				break;
			}
		}
	}
	RESET_BIT(bishop_board, temp_pos);
	return bishop_board;
}

Board get_queen_moves(Pos pos, PlayerColor c){
	Board queen_board = (get_rook_moves(pos,c)) | (get_bishop_moves(pos,c));
	return queen_board;
}


Board get_night_moves(Pos pos, PlayerColor c){
	Board night_board = BIT(pos);

	if(NORTH_OF(NW_OF(pos)) != UNKNOWN_POS) {
		if(IS_SET(BOARD(player[c]), NORTH_OF(NW_OF(pos)))) {
			/* if your own piece is there, you cannot set, otherwise, its either unoccupied or opponent piece */
		} else {
				SET_BIT(night_board, NORTH_OF(NW_OF((pos))));
		}
	}
	if(WEST_OF(NW_OF(pos)) != UNKNOWN_POS) {
		if(IS_SET(BOARD(player[c]), WEST_OF(NW_OF(pos)))) {
		} else {
				SET_BIT(night_board, WEST_OF(NW_OF((pos))));
		}
	}

	if(NORTH_OF(NE_OF(pos)) != UNKNOWN_POS) {
			if(IS_SET(BOARD(player[c]), NORTH_OF(NE_OF(pos)))) {

			} else {
					SET_BIT(night_board, NORTH_OF(NE_OF((pos))));
			}
		}
	if(EAST_OF(NE_OF(pos)) != UNKNOWN_POS) {
				if(IS_SET(BOARD(player[c]), EAST_OF(NE_OF(pos)))) {

				} else {
						SET_BIT(night_board, EAST_OF(NE_OF((pos))));
				}
			}

	if(SOUTH_OF(SW_OF(pos)) != UNKNOWN_POS) {
			if(IS_SET(BOARD(player[c]), SOUTH_OF(SW_OF(pos)))) {

			} else {
					SET_BIT(night_board, SOUTH_OF(SW_OF((pos))));
			}
		}
	if(WEST_OF(SW_OF(pos)) != UNKNOWN_POS) {
			if(IS_SET(BOARD(player[c]), WEST_OF(SW_OF(pos)))) {

			} else {
					SET_BIT(night_board, WEST_OF(SW_OF((pos))));
			}
		}

	if(SOUTH_OF(SE_OF(pos)) != UNKNOWN_POS) {
			if(IS_SET(BOARD(player[c]), SOUTH_OF(SE_OF(pos)))) {

			} else {
					SET_BIT(night_board, SOUTH_OF(SE_OF((pos))));
			}
		}
	if(EAST_OF(SE_OF(pos)) != UNKNOWN_POS) {
			if(IS_SET(BOARD(player[c]), EAST_OF(SE_OF(pos)))) {

			} else {
					SET_BIT(night_board, EAST_OF(SE_OF((pos))));
			}
		}
	RESET_BIT(night_board, pos);
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
	/* printf("Position of king: %u\n", pos);*/
	for(i = 0; i < 64; i++){
		/*
		if(c == WHITE){	idk if we actually need to check the color
		getting board of all possible opponent moves
		*/
		temp = get_piece_at(i, (1-c));
		switch(temp){
			case ROOK:
				all_possible_captures |= (get_rook_moves(i, 1-c));

				   break;
			case NIGHT:
				all_possible_captures |= (get_night_moves(i, 1-c));

				   break;
			case BISHOP:
				all_possible_captures |= (get_bishop_moves(i, 1-c));

				   break;
			case QUEEN:
				all_possible_captures |= (get_queen_moves(i, 1-c));

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

				   break;
			case UNKNOWN:
				break;
		}

	}

	/* printf("all-possible captures: %lu\n", all_possible_captures); */
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

	int y;
	int king_pos;
	*pcount = 0;
	/* position of king on the board, so we can check if moving a piece allows your
	king to be under check by opponent. Dont change this value.
	*/
	for(y = 0; y < 64; y++){
		/* if (IS_SET(player[c].k, y)) { */
		if (IS_SET(player[c].k, y) == 1) {
			/* assumes only 1 king on board*/
			king_pos = y;
		}
	}



	for(pos = 0; pos < 64; pos++){

		if (IS_SET(player[c].k, pos) == 1) {
			Board king_moves = get_king_moves(pos,c);
			for(i = 0; i < 64; i++) {
				if(IS_SET(king_moves, i) == 1) {
					/* printf("bit of king saved: %llu\n", player[c].k); */
					save_state();
					Move *temp = (Move *) malloc(sizeof(Move));
					temp->from = pos;
					temp->to = i;
					temp->piece = KING;
					temp->promotion_choice = UNKNOWN;
					make_move(temp, c); /* need to restore since we're not actually moving here*/
					if(king_is_checked(i, c) == TRUE) {
					/* every other piece uses king_is_checked(king_pos,c) */
						restore_state();
						free(temp);
						/* printf("moving the king and the move results in us being checked \n"); */

						continue;
					} else {
						(*pcount)++; /*increment whats in pointer */
						/* printf("pcount incr in k\n"); */
						/* printf("bit of king after change: %llu\n", player[c].k); */
						restore_state();
						/* printf("bit of king after restore: %llu\n", player[c].k); */
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


		if (IS_SET(player[c].p, pos) == 1) {
			Board pawn_moves = get_pawn_moves(pos,c);
			/* printf("pos; %d		board: %llu\n", pos, pawn_moves); */
			for(i = 0; i < 64; i++) {
				if(IS_SET(pawn_moves, i)) {
				/*not a promotional space for either white or black*/
					/* printf("Position: %d ----> to pos: %d\n", pos, i); */
					Bool promo = FALSE;
					if(c == WHITE){
						promo = ((i != 0) && (i != 1) && (i != 2) && (i != 3) && (i != 4) && (i != 5) && (i != 6) && (i != 7));
						promo = !promo;
					}else if(c == BLACK){
						promo = ((i != 56) && (i != 57) && (i != 58) && (i != 59) && (i != 60) && (i != 61) && (i != 62) && (i != 63));
						promo = !promo;
					}


					if(promo == FALSE){
						/* printf("not a promotion... \n"); */
						save_state();
						Move *temp = (Move *) malloc(sizeof(Move));
						temp->from = pos;
						temp->to = i;
						temp->piece = PAWN;
						temp->promotion_choice = UNKNOWN;
						make_move(temp, c); /* need to restore since we're not actually moving here*/
						if(king_is_checked(king_pos, c) == TRUE) {
							restore_state();
							free(temp);
							/* printf("king is being checked when moving pawn \n"); */
							continue;
						} else {
							(*pcount)++;
							/* printf("pcount incr in p\n"); */
							restore_state();
							if ((*m) == NULL) {
								(*m) = temp;
								head = temp;
							}else {
								(*m)->next_move = temp;
								(*m) = (*m)->next_move;
							}
						}
					}else{ /* is a promotional space */

						save_state();
						Move *temp = (Move *) malloc(sizeof(Move));
						temp->from = pos;
						temp->to = i;
						temp->piece = PAWN;
						temp->promotion_choice = ROOK;
						make_move(temp, c); /* need to restore since we're not actually moving here*/
						if(king_is_checked(king_pos, c) == TRUE) {
							restore_state();
							free(temp);
							/* printf("king is being checked when promoting pawn \n"); */
							/* only need to check once since same move but diff
							promotion choice. should exit if moving the pawn up results in
							your own king being checked */
							continue;
						} else {
							(*pcount)++;
							/* printf("pcount incr in p1\n"); */
							restore_state();
							if ((*m) == NULL) {
								(*m) = temp;
								head = temp;
							}else {
								(*m)->next_move = temp;
								(*m) = (*m)->next_move;
							}
						}
						/* Continue storing the same move with diff promotion pieces */
						save_state();
						Move *temp2 = (Move *) malloc(sizeof(Move));
						temp2->from = pos;
						temp2->to = i;
						temp2->piece = PAWN;
						temp2->promotion_choice = NIGHT;
						make_move(temp2, c);
						(*pcount)++;
						/* printf("pcount incr in p2\n"); */
						restore_state();
						if ((*m) == NULL) {
							(*m) = temp2;
							head = temp2;
						}else {
							(*m)->next_move = temp2;
							(*m) = (*m)->next_move;
						}
						/* Continue storing the same move with diff promotion pieces */
						save_state();
						Move *temp3 = (Move *) malloc(sizeof(Move));
						temp3->from = pos;
						temp3->to = i;
						temp3->piece = PAWN;
						temp3->promotion_choice = BISHOP;
						make_move(temp3, c);
						(*pcount)++;

						restore_state();
						if ((*m) == NULL) {
							(*m) = temp3;
							head = temp3;
						}else {
							(*m)->next_move = temp3;
							(*m) = (*m)->next_move;
						}
						/* Continue storing the same move with diff promotion pieces */
						save_state();
						Move *temp4 = (Move *) malloc(sizeof(Move));
						temp4->from = pos;
						temp4->to = i;
						temp4->piece = PAWN;
						temp4->promotion_choice = QUEEN;
						make_move(temp4, c);
						(*pcount)++;
						/* printf("pcount incr in p4\n");*/
						restore_state();
						if ((*m) == NULL) {
							(*m) = temp4;
							head = temp4;
						}else {
							(*m)->next_move = temp4;
							(*m) = (*m)->next_move;
						}


					} /* end of is promotional space */

				} /* end of if(IS_SET(pawn_moves, i)) */
			}
		} /*end of if (IS_SET(player[c].p, pos))*/

		if (IS_SET(player[c].r, pos) == 1) {
			Board rook_moves = get_rook_moves(pos,c);
			for(i = 0; i < 64; i++) {
				if(IS_SET(rook_moves, i) == 1) {
					save_state();
					Move *temp = (Move *) malloc(sizeof(Move));
					temp->from = pos;
					temp->to = i;
					temp->piece = ROOK;
					temp->promotion_choice = UNKNOWN;
					make_move(temp, c); /* need to restore since we're not actually moving here*/
					if(king_is_checked(king_pos, c) == TRUE) {
					/* every other piece uses king_is_checked(king_pos,c) */
						restore_state();
						free(temp);
						/* printf("moving the rook and the move results in our king being checked \n"); */
						continue;
					} else {
						(*pcount)++;
						/* printf("pcount incr in r\n"); */
						restore_state();
						if ((*m) == NULL) {
							(*m) = temp;
							head = temp;
						}else {
							(*m)->next_move = temp;
							(*m) = (*m)->next_move;
						}
					}
				}
			}
		} /*end of if (IS_SET(player[c].r, pos))*/


		if (IS_SET(player[c].n, pos) == 1) {
			/* printf("night pos on board %d\n",pos); */
			Board night_moves = get_night_moves(pos,c);
			/* printf("night pos on board %llu\n",night_moves); */
			for(i = 0; i < 64; i++) {
				if(IS_SET(night_moves, i) == 1) {
					save_state();
					Move *temp = (Move *) malloc(sizeof(Move));
					temp->from = pos;
					temp->to = i;
					temp->piece = NIGHT;
					temp->promotion_choice = UNKNOWN;
					make_move(temp, c); /* need to restore since we're not actually moving here*/
					if(king_is_checked(king_pos, c) == TRUE) {
					/* every other piece uses king_is_checked(king_pos,c) */

						restore_state();
						free(temp);
						/* printf("moving the night and the move results in our king being checked \n"); */
						continue;
					} else {
						(*pcount)++;
						/* printf("pcount incr in n\n"); */
						restore_state();
						if ((*m) == NULL) {
							(*m) = temp;
							head = temp;
						}else {
							(*m)->next_move = temp;
							(*m) = (*m)->next_move;
						}
					}
				}
			}
		} /*end of if (IS_SET(player[c].n, pos))*/


		if (IS_SET(player[c].b, pos) == 1) {

			Board bishop_moves = get_bishop_moves(pos,c);
			for(i = 0; i < 64; i++) {
				if(IS_SET(bishop_moves, i) == 1) {
					save_state();
					Move *temp = (Move *) malloc(sizeof(Move));
					temp->from = pos;
					temp->to = i;
					temp->piece = BISHOP;
					temp->promotion_choice = UNKNOWN;
					make_move(temp, c); /* need to restore since we're not actually moving here*/
					if(king_is_checked(king_pos, c) == TRUE) {
					/* every other piece uses king_is_checked(king_pos,c) */
						restore_state();
						free(temp);
						/* printf("moving the bishop and the move results in our king being checked \n"); */
						continue;
					} else {
						(*pcount)++;
						/* printf("pcount incr in bishop\n"); */

						restore_state();
						if ((*m) == NULL) {
							(*m) = temp;
							head = temp;
						}else {
							(*m)->next_move = temp;
							(*m) = (*m)->next_move;
						}
					}
				}
			}
		} /*end of if (IS_SET(player[c].b, pos))*/


		if (IS_SET(player[c].q, pos) == 1) {
			Board queen_moves = get_queen_moves(pos,c);
			for(i = 0; i < 64; i++) {
				if(IS_SET(queen_moves, i) == 1) {
					save_state();
					Move *temp = (Move *) malloc(sizeof(Move));
					temp->from = pos;
					temp->to = i;
					temp->piece = QUEEN;
					temp->promotion_choice = UNKNOWN;
					make_move(temp, c); /* need to restore since we're not actually moving here*/
					if(king_is_checked(king_pos, c) == TRUE) {
					/* every other piece uses king_is_checked(king_pos,c) */
						restore_state();
						free(temp);
						/* printf("moving the queen and the move results in our king being checked \n"); */
						continue;
					} else {
						(*pcount)++;
						/* printf("pcount incr in queen\n"); */
						restore_state();
						if ((*m) == NULL) {
							(*m) = temp;
							head = temp;
						}else {
							(*m)->next_move = temp;
							(*m) = (*m)->next_move;
						}
					}
				}
			}
		} /*end of if (IS_SET(player[c].q, pos))*/

	}
	*m = head;
	if((*pcount) > 0) {
		return TRUE;
	}
	return FALSE;

}

/* Returns TRUE if the opponent of CurrentPlayer is under checkmate, FALSE otherwise. */
Bool is_checkmate(PlayerColor c) {
	/* if king is undercheck and has no moves it can make to get out of check
     kings_pos is position of opponent king

     if king is checked and no legal moves left for opponent then it is checkmate
     else  their king is under check but they can still move somewhere
    */

	int a;
	Pos kings_pos = 0;
	for(a = 0; a < 64; a++){
		if(IS_SET(player[1-c].k, a) == 1){
			kings_pos = a;
			break;
		}
	}
	/* printf("   opponent kings position: %d\n", kings_pos); */
	Move *moves = NULL;
	unsigned int moves_can_make = 0;
	if(king_is_checked(kings_pos, 1-c)){
		/* printf("!!! king is checked !!!\n"); */

		if((legal_moves(&moves, 1-c, &moves_can_make) == FALSE)){
			 /*printf("*** we have no legal moves ***\n");*/

			return TRUE;
		}
		/*while(moves != NULL) { 
			temp = moves;
			moves = moves->next_move;
			free(temp);
		} */
		
		
		freeing_list(&moves);

		restore_state();
		/*
		Move *moves = NULL;
		unsigned int moves_can_make = 0;
		if(legal_moves(&moves, c, &moves_can_make) == FALSE){
			return TRUE;
		}else{
			return FALSE;
		}*/

	}

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
	/* stalemate if opponent king not checked and we ran out of legal moves?
		maybe pass in our moves LL and check if its null inside the if opponent king is not checked
	*/
	int a;
	Pos kings_pos = 0;
	for(a = 0; a < 64; a++){
		if(IS_SET(player[CurrentPlayer].k, a) == 1){
			kings_pos = a;
			break;
		}
	}

	if(king_is_checked(kings_pos, CurrentPlayer) == FALSE){
		 /* if CurrentPlayer has no moves left */
		 Move *moves = NULL;
		 Move *temp;
	  	 unsigned int moves_can_make = 0;
		 if((legal_moves(&moves, CurrentPlayer, &moves_can_make) == FALSE)){
 			 printf("*** we have no legal moves ***\n");

 			return TRUE;
 		}
		 while(moves != NULL) {
			 temp = moves;
			 moves = moves->next_move;
			 free(temp);
		}
		free(moves);
		/*freeing_list(moves); */
	}

	return FALSE;
	/*return TRUE;*/
}

/* Returns the piece on a square belonging to player color c.
 * If there is no piece with color c, UNKNOWN is returned. */
Piece get_piece_at(Board pos, PlayerColor c) {
    /* Your implementation */
	if(c == WHITE){
		if (((IS_SET(player[WHITE].r,pos)) == 1)){
            return ROOK;
        }else if(((IS_SET(player[WHITE].n,pos)) == 1)){
            return NIGHT;
        }else if(((IS_SET(player[WHITE].b,pos)) == 1)){
            return BISHOP;
        }else if(((IS_SET(player[WHITE].q,pos)) == 1)){
            return QUEEN;
        }else if(((IS_SET(player[WHITE].k,pos)) == 1)){
            return KING;
        }else if(((IS_SET(player[WHITE].p,pos)) == 1)){
            return PAWN;
		}
		return UNKNOWN;
		/*switch(get_piece(pos)){
			case 'R': return ROOK; break;
			case 'N': return NIGHT; break;
			case 'B': return BISHOP; break;
			case 'Q': return QUEEN; break;
			case 'K': return KING; break;
			case 'P': return PAWN; break;
			default: return UNKNOWN;
		}*/
	}
	else{
		if (((IS_SET(player[BLACK].r,pos)) == 1)){
            return ROOK;
        }else if(((IS_SET(player[BLACK].n,pos)) == 1)){
            return NIGHT;
        }else if(((IS_SET(player[BLACK].b,pos)) == 1)){
            return BISHOP;
        }else if(((IS_SET(player[BLACK].q,pos)) == 1)){
            return QUEEN;
        }else if(((IS_SET(player[BLACK].k,pos)) == 1)){
            return KING;
        }else if(((IS_SET(player[BLACK].p,pos)) == 1)){
            return PAWN;
		}
		return UNKNOWN;
		/*switch(get_piece(pos)){
			case 'r': return ROOK; break;
			case 'n': return NIGHT; break;
			case 'b': return BISHOP; break;
			case 'q': return QUEEN; break;
			case 'k': return KING; break;
			case 'p': return PAWN; break;
			default: return UNKNOWN;
		}*/
	}
}

PlayerColor get_color_at(Pos pos){
    if((get_piece(pos) == 'R') || (get_piece(pos) == 'N') || (get_piece(pos) == 'B') || (get_piece(pos) == 'Q')
    || (get_piece(pos) == 'K') || (get_piece(pos) == 'P')) return WHITE;
    else return BLACK;
}

void detect_and_set_ep(Move *move, PlayerColor c) {
	if (c == BLACK) {
		if (move->piece == PAWN) {
			if ((move->from < 16) && (move->from > 7) && (move->to > 23) && (move->to <32)) {
				ep_square = (move->from + 8);
			}
		}
	} else if (c == WHITE) {
		if (move->piece == PAWN) {
			if((move->from > 47) && (move->from < 56) && (move->to > 31) && (move->to < 40)) {
				ep_square = (move->from - 8);
			}
		}
	}
}

/* Check if this move is trying to castle */
unsigned int detect_castle_move(Move *move, PlayerColor c) {
    /* Your implementation */

	if(c == BLACK){
		if(move->piece == KING){
			if((move->from == BKING_START_POS) && (move->to == 6)){
				/*printf("1 move->from = %d, move->to = %d\n", move->from, move->to);*/
				return CASTLE_KING;
			}else if((move->from == BKING_START_POS) && (move->to == 2)){
				/*printf("2 move->from = %d, move->to = %d\n", move->from, move->to);*/
				return CASTLE_QUEEN;
			}
			return NO_CASTLE;
		}
	}else if (c == WHITE){
		if(move->piece == KING){
			if((move->from == WKING_START_POS) && (move->to == 62)){
				/*printf("3 move->from = %d, move->to = %d\n", move->from, move->to);*/
				return CASTLE_KING;
			}else if((move->from == WKING_START_POS) && (move->to == 58)){
				/*printf("4 move->from = %d, move->to = %d\n", move->from, move->to);*/
				return CASTLE_QUEEN;
			}
			return NO_CASTLE;
		}
	}
	/* shouldnt ever reach here */
	return NO_CASTLE;
}

/* Perform castling. Moves king and rook and resets castle flags */
void perform_castle(unsigned int castle, PlayerColor c) {
    /* Your implementation */
	if(castle == CASTLE_KING){
		if(c == BLACK){
			RESET_BIT(player[c].k, BKING_START_POS);
			SET_BIT(player[c].k, BKING_START_POS+2);
			RESET_BIT(player[c].r, 7);
			SET_BIT(player[c].r, 5);

		}else if (c == WHITE){
			RESET_BIT(player[c].k, WKING_START_POS);
			SET_BIT(player[c].k, WKING_START_POS+2);
			RESET_BIT(player[c].r, 63);
			SET_BIT(player[c].r, 61);
		}

		player[c].castle_flags = NO_CASTLE;
	}else if(castle == CASTLE_QUEEN){
		if(c == BLACK){
			RESET_BIT(player[c].k, BKING_START_POS);
			SET_BIT(player[c].k, BKING_START_POS-2);
			RESET_BIT(player[c].r, 0);
			SET_BIT(player[c].r, 3);

		}else if (c == WHITE){
			RESET_BIT(player[c].k, WKING_START_POS);
			SET_BIT(player[c].k, WKING_START_POS-2);
			RESET_BIT(player[c].r, 56);
			SET_BIT(player[c].r, 59);
		}

		player[c].castle_flags = NO_CASTLE;
	}else if (castle == NO_CASTLE){
		/* do nothing
but when calling this function, wrap in if(!= NO_CASTLE) */
	}
}
