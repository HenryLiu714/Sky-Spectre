#ifndef MOVES_H
#define MOVES_H

#include <vector>
#include "references.h"

namespace moves {
    struct XRay_Attack {
        char pinner; // The location of the piece pinning the other piece
        char pinned_piece; // The piece being pinned
        u64 attacking_ray; // BB showing attacking ray from the attacker to the king, pinned piece legal moves
    };
    
    u64 get_white_pawn_attacks(char);

    u64 get_black_pawn_attacks(char square);

    /**
     * @param opponent_pieces Bitboard containing all black pieces
    */
    u64 get_white_pawn_moves(char square, u64 all_pieces, u64 opponent_pieces);

    /**
     * @param opponent_pieces Bitboard containing all white pieces
    */
     u64 get_black_pawn_moves(char square, u64 all_pieces, u64 opponent_pieces);
    /**
     * @return Bitboard showing the possible attacks of king, does not take into account friendly pieces and captures
    */
    u64 get_knight_attacks(char square);

    u64 get_bishop_attacks(char square, u64 blockers);
    
    u64 get_rook_attacks(char square, u64 blockers);

    u64 get_queen_attacks(char square, u64 blockers);

    u64 get_king_attacks(char square);

    bool is_square_under_attack(char square, char opponent_color, re::Board& board) ;
    /**
     * 1. Extend attack rays from the king square and intersect with blockers to find potential pinned pieces (only first one hit, bitscan forward)
     * 2. Remove the blockers that could act as pinned pieces
     * 3. Intersect with all pieces to find potential pinners
     * 4. Intersect potential pinners with sliding pieces of that type to find xray attacks
     * @param bQ_squares Bishop and Queen locations of opponent team
     * @param rQ_squares Rook and Queen locations of opponent team
     * @param blockers Pieces on the same team as the king on king_square
     * @return Vector<XRay_Attack> containing all xray attacks on the king_square
    */
    std::unordered_map<char, u64> find_xray_attacks(char king_square, u64 blockers, u64 all_pieces, u64 bQ_squares, u64 rQ_squares);

    std::vector<u64> find_sliding_attacks(char king_square, u64 all_pieces, u64 bQ_squares, u64 rQ_squares);

    /**
     * Main function used to generate a vector containing all the possible moves from a given board position
     * Uses the board's current move
     * @param board The input board, which should contain the correct current and opponent turn colors
     * @return A vector containing all the moves possible from that position, including special move flags
     * 
     * TODO: Add en passant behavior
     * TODO: Change promotion behavior (currently only queens)
     * TODO: Add castling behavior !!
    */
    std::vector<re::Move> get_all_legal_moves(re::Board& board);

    bool in_stalemate(re::Board& board);

    bool in_checkmate(re::Board& board);
};


#endif
