#ifndef _MOVES_H_
#define _MOVES_H_

#include "chess.h"
#include "io.h"

/* Given a color, this function returns a singly linked list of all legal Moves with the head at *m.
 * The function returns TRUE if at least 1 legal move is available.
 * The total number of moves found is stored in the address pointed to by pcount. */
Bool legal_moves(Move **m, PlayerColor c, unsigned int *pcount);

/* Returns TRUE if the CurrentPlayer is under checkmate, FALSE otherwise. */
Bool is_checkmate(PlayerColor c);

/* Validate a move and make it. Returns TRUE if successful, FALSE if not.
 *  Error message if any, are stored in *msg.
 * ep_square (if any) is stored in *ep_sq
 */
Bool validate_and_move(Move *move, char **msg, PlayerColor c, Pos *ep_sq);

/* Function to decide whether the current position is a draw */
/* Draw can be due to insufficient material, 3 move repetition or stalemate */
	/* 3 move repetition also covers perpetual check */
Bool is_draw();

/* Returns the piece on a square belonging to player color c.
 * If there is no piece with color c, UNKNOWN is returned. */
Piece get_piece_at(Board pos, PlayerColor c);

/* Check if this move is trying to castle
unsigned int detect_castle_move(Move move, PlayerColor c); */
unsigned int detect_castle_move(Move *move, PlayerColor c);

/* Perform castling. Moves king and rook and resets castle flags */
void perform_castle(unsigned int castle, PlayerColor c);

void detect_and_set_ep(Move *move, PlayerColor c);

void save_state(); /*save all global variables*/
void save_state2();
void save_state3();
void save_state4();
void save_state5();
void save_state6();
void save_state7();
void restore_state(); /*restore all global variables*/
void restore_state2();
void restore_state3();
void restore_state4();
void restore_state5();
void restore_state6();
void restore_state7();

void capture_piece(); /*clear bit of opponent piece, set bit of your piece at that position*/

Bool king_is_checked(Pos pos, PlayerColor c); /*returns TRUE if king is under check, FALSE otherwise*/

void make_move(Move *m, PlayerColor c);

Board get_king_moves(Pos pos, PlayerColor c);
Board get_rook_moves(Pos pos,PlayerColor c);
Board get_pawn_moves(Pos pos,PlayerColor c);
Board get_bishop_moves(Pos pos, PlayerColor c);
Board get_queen_moves(Pos pos, PlayerColor c);
Board get_night_moves(Pos pos, PlayerColor c);



#endif
