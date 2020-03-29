#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "io.h"
#include "chess.h"
#include "moves.h"
#include <stdlib.h>

/*
 * Implement each function in this file.
 */
 char get_piece(uint64_t i){
     if (((IS_SET(player[WHITE].r,i)) == 1)){
         return 'R';
     }else if(((IS_SET(player[WHITE].n,i)) == 1)){
         return 'N';
     }else if(((IS_SET(player[WHITE].b,i)) == 1)){
         return 'B';
     }else if(((IS_SET(player[WHITE].q,i)) == 1)){
         return 'Q';
     }else if(((IS_SET(player[WHITE].k,i)) == 1)){
         return 'K';
     }else if(((IS_SET(player[WHITE].p,i)) == 1)){
         return 'P';
     }else if(((IS_SET(player[BLACK].r,i)) == 1)){
         return 'r';
     }else if(((IS_SET(player[BLACK].n,i)) == 1)){
         return 'n';
     }else if(((IS_SET(player[BLACK].b,i)) == 1)){
         return 'b';
     }else if(((IS_SET(player[BLACK].q,i)) == 1)){
         return 'q';
     }else if(((IS_SET(player[BLACK].k,i)) == 1)){
         return 'k';
     }else if(((IS_SET(player[BLACK].p,i)) == 1)){
         return 'p';
     }else{
         return ' ';
     }
 }

void display_board() {
    /* Your implementation */
    unsigned int i = 0, j = 0;
    printf("\n −−−−−−−−−−−−−−−−−−−−−−−−−\n");
    for(i = 0; i < 8; i++){ /* Rank */
        printf("%d |", 8-i);
        for(j = 0; j < 8; j++){
            printf( "%c |", get_piece(i*8+j)) ; /* write get piece at function*/
        }
        printf("\n −−−−−−−−−−−−−−−−−−−−−−−−−\n");
    }
    printf("   a  b  c  d  e  f  g  h\n" ) ;
    printf("\n");

}

Bool parse_board(char *board) { /* DOES NOT PARSE THE MODE YET */
    /* Your implementation */
    char read_c;
    int position = 0;
    int count_spaces = 0;
    char rank_holder;
    char file_holder;
    int temp_val = 0;
    int i;
    Bool ep_possible = FALSE;

    unsigned int black_rook = 0;
    unsigned int black_night = 0;
    unsigned int black_bishop = 0;
    unsigned int black_queen = 0;
    unsigned int black_king = 0;
    unsigned int black_pawn = 0;

    unsigned int white_rook = 0;
    unsigned int white_night = 0;
    unsigned int white_bishop = 0;
    unsigned int white_queen = 0;
    unsigned int white_king = 0;
    unsigned int white_pawn = 0;

    unsigned int num_slashes = 0;
/*
    while((read_c = fgetc(fp)) != '\n'){

     read single char*/
     for(i = 0; i < strlen(board); i++){
         read_c = board[i];
         temp_val = read_c - '0';
         if(position < 64){
             if((temp_val > 0) && (temp_val < 9) ){ /*(num 1-8)*/
                 position += temp_val; /*check if this might throw error? */
                 continue; /*read the next char*/
             }else if(read_c == 'r' || read_c == 'n' || read_c == 'b' || read_c == 'q' ||
             read_c == 'k' || read_c == 'p' || read_c == 'R' || read_c == 'N' || read_c == 'B'
             || read_c == 'Q' || read_c == 'K' || read_c == 'P'){
                 switch(read_c){
                     case 'r':
                     SET_BIT(player[BLACK].r, position);
                     position++;
                     black_rook++;
                     continue;
                     case 'n':
                     SET_BIT(player[BLACK].n, position);
                     position++;
                     black_night++;
                     continue;
                     case 'b':
                     SET_BIT(player[BLACK].b, position);
                     position++;
                     black_bishop++;
                     continue;
                     case 'q':
                     SET_BIT(player[BLACK].q, position);
                     position++;
                     black_queen++;
                     continue;
                     case 'k':
                     SET_BIT(player[BLACK].k, position);
                     position++;
                     black_king++;
                     continue;
                     case 'p':
                     SET_BIT(player[BLACK].p, position);
                     if((RANK_OF(position) == '1') || (RANK_OF(position) == '8')){
                         printf("black pawn cant be rank 1 or 8");
                         return FALSE;
                     }
                     position++;
                     black_pawn++;
                     continue;

                     case 'R':
                     SET_BIT(player[WHITE].r, position);
                     position++;
                     white_rook++;
                     continue;
                     case 'N':
                     SET_BIT(player[WHITE].n, position);
                     position++;
                     white_night++;
                     continue;
                     case 'B':
                     SET_BIT(player[WHITE].b, position);
                     position++;
                     white_bishop++;
                     continue;
                     case 'Q':
                     SET_BIT(player[WHITE].q, position);
                     position++;
                     white_queen++;
                     continue;
                     case 'K':
                     SET_BIT(player[WHITE].k, position);
                     position++;
                     white_king++;
                     continue;
                     case 'P':
                     SET_BIT(player[WHITE].p, position);
                     if((RANK_OF(position) == '1') || (RANK_OF(position) == '8')){
                          printf("white pawn cant be rank 1 or 8");
                         return FALSE;
                     }
                     position++;
                     white_pawn++;
                     continue;
                 } /* end switch */
             } else if (read_c == '/'){
                 num_slashes++;
                 if(num_slashes*8 == position){
                     continue;
                 }
                return FALSE;
                 /*continue;*/  /* end else if, will ignore the '/' */
             }
         } /* end while, position no longer less than 64, stop setting board  */
         /* Now this should have set up all the boards for each player*/

/* validates the board first, returns false if any violations found */
        unsigned int total_black = black_rook + black_night + black_bishop + black_queen + black_pawn;
        unsigned int total_white = white_rook + white_night + white_bishop + white_queen + white_pawn;
        if((white_king != 1) || (black_king != 1) || (black_pawn > 8) || (white_pawn > 8) || (total_black > 15) ||
            (total_white > 15) || (black_bishop > 10) || (black_night > 10) || (black_rook > 10) || (black_queen > 9)
            || (white_bishop > 10) || (white_night > 10) || (white_rook > 10) || (white_queen > 9)
        ){
             printf("something here wrong");
            return FALSE;

        }

         if(read_c == ' '){
             count_spaces++;
             continue; /* we want to read the next char after the space*/
         }


         /* reading whose turn it is */
         if(count_spaces == 1){
             if(read_c == 'w'){
                 CurrentPlayer = WHITE;
                 continue;
             }else if(read_c == 'b'){
                 CurrentPlayer = BLACK;
                 continue;
             }else{	/* used for error checking, not necessary */
                 printf("Invalid input for player turn.\n");
                 return -1;
             }
         }

         /* parsing castling privilege */
         if(count_spaces == 2){
             if(read_c == '-'){
                 player[WHITE].castle_flags = NO_CASTLE;
                 player[BLACK].castle_flags = NO_CASTLE;
                 continue;
             }else if(read_c == 'K'){
                 /*if(!( (IS_SET(player[CurrentPlayer].k, WKING_START_POS)) && (IS_SET(player[CurrentPlayer].r, 63)) ) ){
                      printf("castling white Kingside");
                     return FALSE;
                 }*/
                 if((IS_SET(player[WHITE].k, WKING_START_POS) == 0) || (IS_SET(player[WHITE].r, 63) == 0)){
                     printf("kingside; no white king or rook");
                     return FALSE;
                 }

                 player[WHITE].castle_flags = CASTLE_KING;
                 continue;
             }else if(read_c == 'Q'){
                /* if(!( (IS_SET(player[CurrentPlayer].k, WKING_START_POS)) && (IS_SET(player[CurrentPlayer].r, 56)) ) ){
                     printf("castling white qside");
                     return FALSE;
                 }*/
                 if((IS_SET(player[WHITE].k, WKING_START_POS) == 0) || (IS_SET(player[WHITE].r, 56) == 0)){
                     printf("queenside; no white king or rook");
                     return FALSE;
                 }
                 player[WHITE].castle_flags = CASTLE_QUEEN;
                 continue;
             }else if(read_c == 'k'){
                 /*if(!( (IS_SET(player[CurrentPlayer].k, BKING_START_POS)) && (IS_SET(player[CurrentPlayer].r, 7)) ) ){
                     printf("castling black Kingside");
                     return FALSE;
                 }*/
                 if((IS_SET(player[BLACK].k, BKING_START_POS) == 0) || (IS_SET(player[BLACK].r, 7) == 0)){
                     printf("kingnside; no black king or rook");
                     return FALSE;
                 }

                 player[BLACK].castle_flags = CASTLE_KING;
                 continue;
             }else if(read_c == 'q'){
                 /*if(!( (IS_SET(player[CurrentPlayer].k, BKING_START_POS)) && (IS_SET(player[CurrentPlayer].r, 0)) ) ){
                     printf("castling black qside");
                     return FALSE;
                 }*/
                 if((IS_SET(player[BLACK].k, BKING_START_POS) == 0) || (IS_SET(player[BLACK].r, 0) == 0)){
                     printf("kingside; no black king or rook");
                     return FALSE;
                 }

                 player[BLACK].castle_flags = CASTLE_QUEEN;
                 continue;
             }
         }

         /* parsing en passant square*/
         if(count_spaces == 3){
             if(read_c == '-'){
                 ep_square = UNKNOWN_POS;
                 ep_possible = FALSE;
                 continue;
             }else if((temp_val > 0) && (temp_val < 9) ){ /*(num 1-8)*/
                 /*printf("rank is : %c", rank_holder);*/
                 rank_holder = read_c;
                 ep_possible = TRUE;
                 if((rank_holder == '3') || (rank_holder == '6')){
                     continue;
                 }else{
                     printf("rank is : %c", rank_holder);
                     printf("ep_sq rank is not 3 or 6");
                     return FALSE;
                 }

             }else if((read_c >= 'a') && (read_c <= 'h') ){
                 file_holder = read_c;
                 continue;
             }else{
                 printf("rank is not 1-8 or file is not a-h");
                 return FALSE;
             }
         }


     } /* program encounters \n character */

     ep_square = TO_POS(file_holder, rank_holder);
     if((ep_possible == TRUE) && (ep_square < 0 || ep_square > 63)){
         printf("error with valid enpassant");
         return FALSE;
     }
     if(CurrentPlayer == WHITE){
     /* if white, check enpassant is valid if it exists, then check if black king already checked
     if black, check enpassant is valid if it exists, then check if white king already checked
     */
         if(ep_possible){
             if(!(IS_SET(player[BLACK].p, ep_square+8))){
                 printf("no black pawn above ep square");
                 return FALSE;
             }
             if(OCCUPIED(ep_square-8)){
                 printf("occupied below ep square");
                 return FALSE;
             }
             /*if(!((IS_SET(player[BLACK].p, ep_square+8)) || (UNOCCUPIED(ep_square-8)) )  ){
                 printf("error with valid enpassant black pawns");
                 return FALSE;
             }*/
         }
         int a;
         Pos b_king_pos = 0;
         for(a = 0; a < 64; a++){
             if(IS_SET(player[BLACK].k, a) == 1){
                 b_king_pos = a;
                 break;
             }
         }
         if(king_is_checked(b_king_pos, BLACK)){
             printf("black king is already checked");
             return FALSE;
         }
     }else if(CurrentPlayer == BLACK){
         if(ep_possible){
             if(!(IS_SET(player[WHITE].p, ep_square-8))){
                 printf("no white pawn below ep square");
                 return FALSE;
             }
             if(OCCUPIED(ep_square+8)){
                 printf("occupied above ep square");
                 return FALSE;
             }
             /*if(!((IS_SET(player[WHITE].p, ep_square-8)) || (UNOCCUPIED(ep_square+8)) )  ){
                 printf("error with valid enpassant white pawns");
                 return FALSE;
             }*/
         }
         int a;
         Pos w_king_pos = 0;
         for(a = 0; a < 64; a++){
             if(IS_SET(player[WHITE].k, a) == 1){
                 w_king_pos = a;
                 break;
             }
         }
         if(king_is_checked(w_king_pos, WHITE)){
             printf("white king is already checked");
             return FALSE;
         }
     }


     /*ep_square contains position of enpassant square */
     return 1; /* successful parsing of input */

}

/* Parses the input move.
 * This function repeatedly prompts for a move until a valid move is typed in.
 * This function only validates that:
 *	 1) from and to are valid squares on the board.
 *	 2) from and to are separated by a '-'
 * This function does not check the legality of the move.
 */

 /*
Move parse_move() {

}
*/

/* This function accepts a move from the user. The move is not validated */
/*
void prompt_move(Move *m, unsigned int move_number) {

}
*/
/* This function prints a move on to the console */
/*
void print_move(Move *m) {

}
*/
