#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "io.h"
#include "chess.h"
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
                     continue;
                     case 'n':
                     SET_BIT(player[BLACK].n, position);
                     position++;
                     continue;
                     case 'b':
                     SET_BIT(player[BLACK].b, position);
                     position++;
                     continue;
                     case 'q':
                     SET_BIT(player[BLACK].q, position);
                     position++;
                     continue;
                     case 'k':
                     SET_BIT(player[BLACK].k, position);
                     position++;
                     continue;
                     case 'p':
                     SET_BIT(player[BLACK].p, position);
                     position++;
                     continue;

                     case 'R':
                     SET_BIT(player[WHITE].r, position);
                     position++;
                     continue;
                     case 'N':
                     SET_BIT(player[WHITE].n, position);
                     position++;
                     continue;
                     case 'B':
                     SET_BIT(player[WHITE].b, position);
                     position++;
                     continue;
                     case 'Q':
                     SET_BIT(player[WHITE].q, position);
                     position++;
                     continue;
                     case 'K':
                     SET_BIT(player[WHITE].k, position);
                     position++;
                     continue;
                     case 'P':
                     SET_BIT(player[WHITE].p, position);
                     position++;
                     continue;
                 } /* end switch */
             } else{

                 continue;  /* end else if, will ignore the '/' */
             }
         } /* end while, position no longer less than 64, stop setting board  */
         /* Now this should have set up all the boards for each player*/

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
                 player[WHITE].castle_flags = CASTLE_KING;
                 continue;
             }else if(read_c == 'Q'){
                 player[WHITE].castle_flags = CASTLE_QUEEN;
                 continue;
             }else if(read_c == 'k'){
                 player[BLACK].castle_flags = CASTLE_KING;
                 continue;
             }else if(read_c == 'q'){
                 player[BLACK].castle_flags = CASTLE_QUEEN;
                 continue;
             }
         }

         /* parsing en passant square*/
         if(count_spaces == 3){
             if(read_c == '-'){
                 ep_square = UNKNOWN_POS;
                 continue;
             }else if((temp_val > 0) && (temp_val < 9) ){ /*(num 1-8)*/
                 rank_holder = read_c;
                 continue;
             }else{
                 file_holder = read_c;
                 continue;
             }
         }


     } /* program encounters \n character */

     ep_square = TO_POS(file_holder, rank_holder);
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
