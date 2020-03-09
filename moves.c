#include "moves.h"

/* Given a color, this function returns a singly linked list of all legal Moves with the head at *m. 
 * The function returns TRUE if at least 1 legal move is available. 
 * The total number of moves found is stored in the address pointed to by pcount. */
Bool legal_moves(Move **m, PlayerColor c, unsigned int *pcount) {
    /* Your implementation */

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
}

/* Check if this move is trying to castle */
unsigned int detect_castle_move(Move move, PlayerColor c) {
    /* Your implementation */
}

/* Perform castling. Moves king and rook and resets castle flags */
void perform_castle(unsigned int castle, PlayerColor c) {
    /* Your implementation */
}

