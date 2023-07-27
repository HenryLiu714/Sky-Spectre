#ifndef MOVES_H
#define MOVES_H

#include <vector>
#include "references.h"

namespace moves {
    /**
     * Struct for representing an xray attack
     * 
     * @param pinner The location of the piece pinning the other piece
     * @param pinned_piece The piece being pinned
     * @param attacking_ray BB showing attacking ray from the attacker to the king, pinned piece legal moves
    */
    struct XRay_Attack {
        char pinner;
        char pinned_piece;
        u64 attacking_ray; 
    };

    /**
     * Returns a bitboard with all squares under attack
     * 
     * @param board The board containing all the pieces
     * @param attacker_color The side (white or black) attacking
     * @return A bitboard with all spaces being attacked
    */
    u64 get_all_attacks(re::Board& board, char attacker_color);

    /**
     * Main function used to generate a vector containing all the possible moves from a given board position
     * Uses the board's current move
     * @param board The input board, which should contain the correct current and opponent turn colors
     * @return A vector containing all the moves possible from that position, including special move flags
     * 
     * TODO: Add en passant behavior
    */
    std::vector<re::Move> get_all_legal_moves(re::Board& board);

    /**
     * Checks if board is in stalemate
     * @param board The board being checked
    */
    bool in_stalemate(re::Board& board);

    /**
     * Checks if board is in checkmate
     * @param board The board being checked
    */
    bool in_checkmate(re::Board& board);
};


#endif
