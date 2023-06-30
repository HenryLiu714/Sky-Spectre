#include "moves.h"

namespace moves {
    u64 get_white_pawn_attacks(char square) {
        const u64 notAFile = 0xfefefefefefefefe; // ~0x0101010101010101
        const u64 notHFile = 0x7f7f7f7f7f7f7f7f; // ~0x8080808080808080

        if (square / 8 != 7) {
            if (square+9>63) {return (1ull << (square+7));} // Only happens if in square 55

            return ((1ull << (square+9)) & notAFile) | ((1ull << (square+7)) & notHFile);
        }
        
        else {
            return 0ull;
        }
    }

    u64 get_black_pawn_attacks(char square) {
        const u64 notAFile = 0xfefefefefefefefe; // ~0x0101010101010101
        const u64 notHFile = 0x7f7f7f7f7f7f7f7f; // ~0x8080808080808080

        if (square / 8 != 0) {
            if (square-9<0) {return (1ull << (square-7));} // Only happens if in square 8

            return ((1ull << (square-9)) & notHFile) | ((1ull << (square-7)) & notAFile);
        }
        
        else {
            return 0ull;
        }
    }

    /**
     * @param opponent_pieces Bitboard containing all black pieces
    */
    u64 get_white_pawn_moves(char square, u64 all_pieces, u64 opponent_pieces) {
        if (square+8 > 63) {
            return 0ull;
        }

        if ((1ull << (square+8) & all_pieces)) {
            return (get_white_pawn_attacks(square) & opponent_pieces);
        }

        if (square / 8 == 1) {
            if ((1ull << (square + 16)) & all_pieces) {
                return (1ull << (square+8)) | (get_white_pawn_attacks(square) & opponent_pieces);
            }
        }

        else {
            return (1ull << (square+8)) | (get_white_pawn_attacks(square) & opponent_pieces);
        }

        return (1ull << (square+8)) | (1ull << (square+16)) | (get_white_pawn_attacks(square) & opponent_pieces);
    }

    /**
     * @param opponent_pieces Bitboard containing all white pieces
    */
     u64 get_black_pawn_moves(char square, u64 all_pieces, u64 opponent_pieces) {
        if (square-8 < 0) {
            return 0ull;
        }

        if ((1ull << (square-8) & all_pieces)) {
            return (get_black_pawn_attacks(square) & opponent_pieces);
        }

        if (square / 8 == 6) {
            if ((1ull << (square - 16)) & all_pieces) {
                return (1ull << (square-8)) | (get_black_pawn_attacks(square) & opponent_pieces);
            }
        }

        else {
            return (1ull << (square-8)) | (get_black_pawn_attacks(square) & opponent_pieces);
        }

        return (1ull << (square-8)) | (1ull << (square-16)) | (get_white_pawn_attacks(square) & opponent_pieces);
    }
    /**
     * @return Bitboard showing the possible attacks of king, does not take into account friendly pieces and captures
    */
    u64 get_knight_attacks(char square) {
        return re::get_knight_bitmask(square);
    }

    u64 get_bishop_attacks(char square, u64 blockers) {
        u64 attacks = 0ull;

        // Northwest
        attacks |= re::get_sliding_bitmask(square, re::NORTHWEST);
        if (re::get_sliding_bitmask(square, re::NORTHWEST) & blockers) {
            u64 masked_blockers = re::get_sliding_bitmask(square, re::NORTHWEST) & blockers;
            attacks &= ~re::get_sliding_bitmask(re::bitscan_forward(masked_blockers), re::NORTHWEST);
        }

        // Northeast
        attacks |= re::get_sliding_bitmask(square, re::NORTHEAST);
        if (re::get_sliding_bitmask(square, re::NORTHEAST) & blockers) {
            u64 masked_blockers = re::get_sliding_bitmask(square, re::NORTHEAST) & blockers;
            attacks &= ~re::get_sliding_bitmask(re::bitscan_forward(masked_blockers), re::NORTHEAST);
        }

        // Southwest
        attacks |= re::get_sliding_bitmask(square, re::SOUTHWEST);
        if (re::get_sliding_bitmask(square, re::SOUTHWEST) & blockers) {
            u64 masked_blockers = re::get_sliding_bitmask(square, re::SOUTHWEST) & blockers;
            attacks &= ~re::get_sliding_bitmask(re::bitscan_reverse(masked_blockers), re::SOUTHWEST);
        }

        // Southeast
        attacks |= re::get_sliding_bitmask(square, re::SOUTHEAST);
        if (re::get_sliding_bitmask(square, re::SOUTHEAST) & blockers) {
            u64 masked_blockers = re::get_sliding_bitmask(square, re::SOUTHEAST) & blockers;
            attacks &= ~re::get_sliding_bitmask(re::bitscan_reverse(masked_blockers), re::SOUTHEAST);
        }

        return attacks;
    }

    u64 get_rook_attacks(char square, u64 blockers) {
        u64 attacks = 0ull;

        // North
        attacks |= re::get_sliding_bitmask(square, re::NORTH);
        if (re::get_sliding_bitmask(square, re::NORTH) & blockers) {
            u64 masked_blockers = re::get_sliding_bitmask(square, re::NORTH) & blockers;
            attacks &= ~re::get_sliding_bitmask(re::bitscan_forward(masked_blockers), re::NORTH);
        }

        // West
        attacks |= re::get_sliding_bitmask(square, re::WEST);
        if (re::get_sliding_bitmask(square, re::WEST) & blockers) {
            u64 masked_blockers = re::get_sliding_bitmask(square, re::WEST) & blockers;
            attacks &= ~re::get_sliding_bitmask(re::bitscan_forward(masked_blockers), re::WEST);
        }

        // East
        attacks |= re::get_sliding_bitmask(square, re::EAST);
        if (re::get_sliding_bitmask(square, re::EAST) & blockers) {
            u64 masked_blockers = re::get_sliding_bitmask(square, re::EAST) & blockers;
            attacks &= ~re::get_sliding_bitmask(re::bitscan_reverse(masked_blockers), re::EAST);
        }

        // South
        attacks |= re::get_sliding_bitmask(square, re::SOUTH);
        if (re::get_sliding_bitmask(square, re::SOUTH) & blockers) {
            u64 masked_blockers = re::get_sliding_bitmask(square, re::SOUTH) & blockers;
            attacks &= ~re::get_sliding_bitmask(re::bitscan_reverse(masked_blockers), re::SOUTH);
        }

        return attacks;
    }

    u64 get_queen_attacks(char square, u64 blockers) {
        return (get_bishop_attacks(square, blockers) | get_rook_attacks(square, blockers));
    }

    u64 get_king_attacks(char square) {
        return re::get_king_bitmask(square);
    }

    bool is_square_under_attack(char square, char opponent_color, re::Board& board) {
        u64 opponent_pawn_attacks;

        opponent_color == re::W ? opponent_pawn_attacks = get_black_pawn_attacks(square) : opponent_pawn_attacks = get_white_pawn_attacks(square);

        u64 bQ_attacks = get_bishop_attacks(square, board.all_piece_locations);
        u64 rQ_attacks = get_rook_attacks(square, board.all_piece_locations);

        return (
            (bQ_attacks & (board.bitboards[opponent_color | re::BISHOP] | board.bitboards[opponent_color | re::QUEEN])) |
            (rQ_attacks & (board.bitboards[opponent_color | re::ROOK] | board.bitboards[opponent_color | re::QUEEN])) |
            (get_knight_attacks(square) & board.bitboards[opponent_color | re::KNIGHT]) |
            (get_king_attacks(square) & board.bitboards[opponent_color | re::KING]) | 
            (opponent_pawn_attacks & board.bitboards[opponent_color | re::PAWN])
        );
    }

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
    std::vector<XRay_Attack> find_xray_attacks(char king_square, u64 blockers, u64 all_pieces, u64 bQ_squares, u64 rQ_squares) {
        std::vector<XRay_Attack> xray_attacks;

        // Northeast
        if (re::get_sliding_bitmask(king_square, re::NORTHEAST) & blockers) {
            char potential_pinned_piece = re::bitscan_forward((re::get_sliding_bitmask(king_square, re::NORTHEAST) & blockers));
            all_pieces ^= (1ull << potential_pinned_piece);

            if (re::get_sliding_bitmask(king_square, re::NORTHEAST) & all_pieces) {
                char pinner = re::bitscan_forward((re::get_sliding_bitmask(king_square, re::NORTHEAST) & all_pieces));

                if (bQ_squares & (1ull << pinner)) {
                    u64 attacking_ray = (re::get_sliding_bitmask(king_square, re::NORTHEAST) & ~re::get_sliding_bitmask(pinner, re::NORTHEAST));
                    xray_attacks.push_back(XRay_Attack{pinner, potential_pinned_piece, attacking_ray});
                }
            }
        }

        // Northwest
        if (re::get_sliding_bitmask(king_square, re::NORTHWEST) & blockers) {
            char potential_pinned_piece = re::bitscan_forward((re::get_sliding_bitmask(king_square, re::NORTHWEST) & blockers));
            all_pieces ^= (1ull << potential_pinned_piece);

            if (re::get_sliding_bitmask(king_square, re::NORTHWEST) & all_pieces) {
                char pinner = re::bitscan_forward((re::get_sliding_bitmask(king_square, re::NORTHWEST) & all_pieces));

                if (bQ_squares & (1ull << pinner)) {
                    u64 attacking_ray = (re::get_sliding_bitmask(king_square, re::NORTHWEST) & ~re::get_sliding_bitmask(pinner, re::NORTHWEST));
                    xray_attacks.push_back(XRay_Attack{pinner, potential_pinned_piece, attacking_ray});
                }
            }
        }

        // Southeast
        if (re::get_sliding_bitmask(king_square, re::SOUTHEAST) & blockers) {
            char potential_pinned_piece = re::bitscan_forward((re::get_sliding_bitmask(king_square, re::SOUTHEAST) & blockers));
            all_pieces ^= (1ull << potential_pinned_piece);

            if (re::get_sliding_bitmask(king_square, re::SOUTHEAST) & all_pieces) {
                char pinner = re::bitscan_reverse((re::get_sliding_bitmask(king_square, re::SOUTHEAST) & all_pieces));

                if (bQ_squares & (1ull << pinner)) {
                    u64 attacking_ray = (re::get_sliding_bitmask(king_square, re::SOUTHEAST) & ~re::get_sliding_bitmask(pinner, re::SOUTHEAST));
                    xray_attacks.push_back(XRay_Attack{pinner, potential_pinned_piece, attacking_ray});
                }
            }
        }

        // Southwest
        if (re::get_sliding_bitmask(king_square, re::SOUTHWEST) & blockers) {
            char potential_pinned_piece = re::bitscan_forward((re::get_sliding_bitmask(king_square, re::SOUTHWEST) & blockers));
            all_pieces ^= (1ull << potential_pinned_piece);

            if (re::get_sliding_bitmask(king_square, re::SOUTHWEST) & all_pieces) {
                char pinner = re::bitscan_reverse((re::get_sliding_bitmask(king_square, re::SOUTHWEST) & all_pieces));

                if (bQ_squares & (1ull << pinner)) {
                    u64 attacking_ray = (re::get_sliding_bitmask(king_square, re::SOUTHWEST) & ~re::get_sliding_bitmask(pinner, re::SOUTHWEST));
                    xray_attacks.push_back(XRay_Attack{pinner, potential_pinned_piece, attacking_ray});
                }
            }
        }

        // North
        if (re::get_sliding_bitmask(king_square, re::NORTH) & blockers) {
            char potential_pinned_piece = re::bitscan_forward((re::get_sliding_bitmask(king_square, re::NORTH) & blockers));
            all_pieces ^= (1ull << potential_pinned_piece);

            if (re::get_sliding_bitmask(king_square, re::NORTH) & all_pieces) {
                char pinner = re::bitscan_forward((re::get_sliding_bitmask(king_square, re::NORTH) & all_pieces));

                if (bQ_squares & (1ull << pinner)) {
                    u64 attacking_ray = (re::get_sliding_bitmask(king_square, re::NORTH) & ~re::get_sliding_bitmask(pinner, re::NORTH));
                    xray_attacks.push_back(XRay_Attack{pinner, potential_pinned_piece, attacking_ray});
                }
            }
        }

        // East
        if (re::get_sliding_bitmask(king_square, re::EAST) & blockers) {
            char potential_pinned_piece = re::bitscan_forward((re::get_sliding_bitmask(king_square, re::EAST) & blockers));
            all_pieces ^= (1ull << potential_pinned_piece);

            if (re::get_sliding_bitmask(king_square, re::EAST) & all_pieces) {
                char pinner = re::bitscan_forward((re::get_sliding_bitmask(king_square, re::EAST) & all_pieces));

                if (bQ_squares & (1ull << pinner)) {
                    u64 attacking_ray = (re::get_sliding_bitmask(king_square, re::EAST) & ~re::get_sliding_bitmask(pinner, re::EAST));
                    xray_attacks.push_back(XRay_Attack{pinner, potential_pinned_piece, attacking_ray});
                }
            }
        }

        // South
        if (re::get_sliding_bitmask(king_square, re::SOUTH) & blockers) {
            char potential_pinned_piece = re::bitscan_forward((re::get_sliding_bitmask(king_square, re::SOUTH) & blockers));
            all_pieces ^= (1ull << potential_pinned_piece);

            if (re::get_sliding_bitmask(king_square, re::SOUTH) & all_pieces) {
                char pinner = re::bitscan_reverse((re::get_sliding_bitmask(king_square, re::SOUTH) & all_pieces));

                if (bQ_squares & (1ull << pinner)) {
                    u64 attacking_ray = (re::get_sliding_bitmask(king_square, re::SOUTH) & ~re::get_sliding_bitmask(pinner, re::SOUTH));
                    xray_attacks.push_back(XRay_Attack{pinner, potential_pinned_piece, attacking_ray});
                }
            }
        }

        // West
        if (re::get_sliding_bitmask(king_square, re::WEST) & blockers) {
            char potential_pinned_piece = re::bitscan_forward((re::get_sliding_bitmask(king_square, re::WEST) & blockers));
            all_pieces ^= (1ull << potential_pinned_piece);

            if (re::get_sliding_bitmask(king_square, re::WEST) & all_pieces) {
                char pinner = re::bitscan_reverse((re::get_sliding_bitmask(king_square, re::WEST) & all_pieces));

                if (bQ_squares & (1ull << pinner)) {
                    u64 attacking_ray = (re::get_sliding_bitmask(king_square, re::WEST) & ~re::get_sliding_bitmask(pinner, re::WEST));
                    xray_attacks.push_back(XRay_Attack{pinner, potential_pinned_piece, attacking_ray});
                }
            }
        }

        return xray_attacks;
    }
    
    std::vector<re::Move> get_moves_from_piece(re::Board& board, int space) {
        std::vector<re::Move> possible_moves;

        return possible_moves;
    }

    std::vector<re::Move> get_all_legal_moves(re::Board& board) {
        std::vector<re::Move> legal_moves;

        return legal_moves;
    }
}