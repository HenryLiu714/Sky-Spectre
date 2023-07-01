#include "references.h"

namespace eval {
    const int PAWN_VAL = 100;
    const int KNIGHT_VAL = 300;
    const int BISHOP_VAL = 310;
    const int ROOK_VAL = 500;
    const int QUEEN_VAL = 900;

    /**
     * Function used to evaluate a current board position where a positive number is beneficial to white and negative is 
     * good for black
     * 
     * @return Integer value denoting the evaluation score for a certain position on a chess board, where 
     * INT_MAX represents a checkmate for white and INT_MIN is a checkmate for black
    */
    int evaluate(re::Board& board);
}