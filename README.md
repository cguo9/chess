# Chess - Solving Checkmate Puzzles
<br/>

## Introduction
A fully functiona chess engine capable of solving mate-in-1 and mate-in-2 chess puzzles. Given a intial chess board with both black and white chess pieces in place, as well as information about castling and en-passant moves and the player to move, the program will determine the correct move that the player can make to deliver a checkmate in one move or a checkmate in two moves depending on the mode in which the program is run in. A checkmate in two moves includes finding a move such that irrespective of what the opponent moves, there is a valid checkmate in one move on the next turn.

Chess Rules: https://www.chess.com/learn-how-to-play-chess

<br/>


## Features
* Full set of chess rules including:
    * Valid chess board
    * Piece movement
    * Pawn promotion
    * Castling
    * En-passant capture
* Draw due to stalemate
* Detection of checkmate and check

<br/>

## Input and Output
The input board, player color to play, castling status, en-passant square will be given to the program as input in the form of a string

Format:
1. The board representation comprises of lower case letters p, n, q, r, b and k that will be used to represent Black pieces and upper case letters P, N, Q, R, B and K that will be used to represent white pieces. Empty squares are represented by numbers, and each rank is separated by a ’/’. The representation starts from a8-h8 as the first rank followed by ’/’, then a7-h7, then ’/’, and so on. For example, the string rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR represents the standard starting position on a chess board shown on this link. 

https://lichess.org/editor/rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR_w_KQkq_-_0_1

You can also drag and drop pieces on the board on the website to alter the board. At the bottom, the input string will also be altered for your use.

2. The board representation is followed by a space followed by a single character 'w' or 'b' to represent whose turn it is, with 'w' representing white, and 'b' representing black.

3. The active player color is followed by a single space followed by either a '-' to represent no castling for either player or a string comprising of a single K, single Q, single k or single q. K implies white can castle king side, Q implies black can castle queen side and similarly for k and q implying white king side and white queen side castling, respectively.

4. Finally, the castling flags are followed by a single space follwed by a square (e.g., e6) that represents the en passant square. Whenever a pawn moves two squares forward, the square between the starting and the ending position becomes the en passant square.


A complete example is in the input: r3k2r/p4nb1/1p4Bp/2q1p1p1/pP1n4/P2Q2N1/5PP1/4K2R b K b3
https://lichess.org/editor/r3k2r/p4nb1/1p4Bp/2q1p1p1/pP1n4/P2Q2N1/5PP1/4K2R_b_Kq_b3_0_1

Click the link above to view the position of each chess piece. It is black's turn to move, king side castling is available for the black king and square b3 is the en passant square. Note that en passant is only valid for a single turn so on this turn only, Black can capture pawn on b4 by moving pawn a4 to b3. If the en passant square is not utilized on this turn, it becomes invalid on the next turn even if none of the pawns involved in the en passant are moved. 

You must provide an input file containing one or multiple valid input strings, one on each line. The program will read each input string on each line and execute the puzzle. The output will be a move printed to another file specified through the command line. The output will be formated as starting_square-ending_square.


Full Example of Input & Output:

Input string: 2bqkbn1/2pppp2/np2N3/r3P1p1/p2N2B1/5Q2/PPPPKPP1/RNB2r2 w - -

Output string: f3-f7

<br/>

## How To Use It
1. Clone repository and run the following commands:
```bash
$bash
$export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD
$make all
```
2. Run code with Puzzles.txt:
```bash
$./chess puzzles.txt solution.txt <mode>
```
Where "mode" is replaced with either a 1 or 2 representing mate-in-1 and mate-in-2, respectively. The puzzle.txt file contains the input string and the program will output the solution to solution.txt using the mate-in-1 function if the mode is specified as 1 or mate-in-2 if the mode is 2.

You may replace "puzzles.txt" with your own text file containing an input string in the proper format on each line. The program outputs the solution(s) to the puzzle strings into the "solution.txt" file or any other file you specify. If the file does not exist, the program will create a new one and append the solutions to that file.

