#include "evaluation.h"
#include "references.h"
#include "moves.h"

namespace eval {
    /**
     * Same procedure as bitboard serialization in reference.h
     * @param value The value that each piece of the type is given
    */
    int score_from_pieces(u64 piece_bitboard, int value) {
        int score = 0;

        while (piece_bitboard != 0) {
            score += value;
            piece_bitboard &= piece_bitboard - 1;
        }

        return score;
    }

    /**
     * Gather the eval score for all piece values on the board
    */
    int pieces_score(re::Board& board) {
        int score = 0;

        score += score_from_pieces(board.bitboards[re::W | re::PAWN], PAWN_VAL);
        score += score_from_pieces(board.bitboards[re::W | re::KNIGHT], KNIGHT_VAL);
        score += score_from_pieces(board.bitboards[re::W | re::BISHOP], BISHOP_VAL);
        score += score_from_pieces(board.bitboards[re::W | re::ROOK], ROOK_VAL);
        score += score_from_pieces(board.bitboards[re::W | re::QUEEN], QUEEN_VAL);

        score += score_from_pieces(board.bitboards[re::B| re::PAWN], -PAWN_VAL);
        score += score_from_pieces(board.bitboards[re::B | re::KNIGHT], -KNIGHT_VAL);
        score += score_from_pieces(board.bitboards[re::B | re::BISHOP], -BISHOP_VAL);
        score += score_from_pieces(board.bitboards[re::B | re::ROOK], -ROOK_VAL);
        score += score_from_pieces(board.bitboards[re::B | re::QUEEN], -QUEEN_VAL);

        return score;
    }

    int checkmate_score(re::Board& board) {
        if (moves::in_checkmate(board)) {
            if (board.current_turn == re::W) {return 10000000;}
            else {return -1000000;}
        }

        return 0;
    }

    int evaluate(re::Board& board) {
        int score = 0;

        score += pieces_score(board);
        score += checkmate_score(board);

        return score;
    }
}
