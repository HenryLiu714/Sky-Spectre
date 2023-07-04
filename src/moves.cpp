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
     * @return unordered map containing the pinned square and the xray attack ray (possible moves)
    */
    std::unordered_map<char, u64> find_xray_attacks(char king_square, u64 blockers, u64 all_pieces, u64 bQ_squares, u64 rQ_squares) {
        std::unordered_map<char, u64> xray_attacks;

        // Northeast
        if (re::get_sliding_bitmask(king_square, re::NORTHEAST) & blockers) {
            char potential_pinned_piece = re::bitscan_forward((re::get_sliding_bitmask(king_square, re::NORTHEAST) & blockers));
            all_pieces ^= (1ull << potential_pinned_piece);

            if (re::get_sliding_bitmask(king_square, re::NORTHEAST) & all_pieces) {
                char pinner = re::bitscan_forward((re::get_sliding_bitmask(king_square, re::NORTHEAST) & all_pieces));

                if (bQ_squares & (1ull << pinner)) {
                    u64 attacking_ray = (re::get_sliding_bitmask(king_square, re::NORTHEAST) & ~re::get_sliding_bitmask(pinner, re::NORTHEAST));
                    xray_attacks.insert({potential_pinned_piece, attacking_ray});
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
                    xray_attacks.insert({potential_pinned_piece, attacking_ray});
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
                    xray_attacks.insert({potential_pinned_piece, attacking_ray});
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
                    xray_attacks.insert({potential_pinned_piece, attacking_ray});
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
                    xray_attacks.insert({potential_pinned_piece, attacking_ray});
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
                    xray_attacks.insert({potential_pinned_piece, attacking_ray});
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
                    xray_attacks.insert({potential_pinned_piece, attacking_ray});
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
                    xray_attacks.insert({potential_pinned_piece, attacking_ray});
                }
            }
        }

        return xray_attacks;
    }
    
    std::vector<u64> find_sliding_attacks(char king_square, u64 all_pieces, u64 bQ_squares, u64 rQ_squares) {
        std::vector<u64> sliding_attacks;

        u64 potential_bQ_attacks = get_bishop_attacks(king_square, all_pieces);
        u64 potential_rQ_attacks = get_rook_attacks(king_square, all_pieces);

        if (potential_bQ_attacks & bQ_squares) {
            if (re::get_sliding_bitmask(king_square, re::NORTHEAST) & all_pieces) {
                char attack_position = re::bitscan_forward(re::get_sliding_bitmask(king_square, re::NORTHEAST) & all_pieces);

                if ((1ull << attack_position) & bQ_squares) {
                    u64 attack_ray = re::get_sliding_bitmask(king_square, re::NORTHEAST) & ~re::get_sliding_bitmask(attack_position, re::NORTHEAST);
                    sliding_attacks.push_back(attack_ray);
                }
            }

            if (re::get_sliding_bitmask(king_square, re::NORTHWEST) & all_pieces) {
                char attack_position = re::bitscan_forward(re::get_sliding_bitmask(king_square, re::NORTHWEST) & all_pieces);

                if ((1ull << attack_position) & bQ_squares) {
                    u64 attack_ray = re::get_sliding_bitmask(king_square, re::NORTHWEST) & ~re::get_sliding_bitmask(attack_position, re::NORTHWEST);
                    sliding_attacks.push_back(attack_ray);
                }
            }

            if (re::get_sliding_bitmask(king_square, re::SOUTHEAST) & all_pieces) {
                char attack_position = re::bitscan_reverse(re::get_sliding_bitmask(king_square, re::SOUTHEAST) & all_pieces);

                if ((1ull << attack_position) & bQ_squares) {
                    u64 attack_ray = re::get_sliding_bitmask(king_square, re::SOUTHEAST) & ~re::get_sliding_bitmask(attack_position, re::SOUTHEAST);
                    sliding_attacks.push_back(1ull);
                }
            }

            if (re::get_sliding_bitmask(king_square, re::SOUTHWEST) & all_pieces) {
                char attack_position = re::bitscan_reverse(re::get_sliding_bitmask(king_square, re::SOUTHWEST) & all_pieces);

                if ((1ull << attack_position) & bQ_squares) {
                    u64 attack_ray = re::get_sliding_bitmask(king_square, re::SOUTHWEST) & ~re::get_sliding_bitmask(attack_position, re::SOUTHWEST);
                    sliding_attacks.push_back(1ull);
                }
            }
        }

        if (potential_rQ_attacks & rQ_squares) {
            if (re::get_sliding_bitmask(king_square, re::NORTH) & all_pieces) {
                char attack_position = re::bitscan_forward(re::get_sliding_bitmask(king_square, re::NORTH) & all_pieces);

                if ((1ull << attack_position) & rQ_squares) {
                    u64 attack_ray = re::get_sliding_bitmask(king_square, re::NORTH) & ~re::get_sliding_bitmask(attack_position, re::NORTH);
                    sliding_attacks.push_back(attack_ray);
                }
            }

            if (re::get_sliding_bitmask(king_square, re::EAST) & all_pieces) {
                char attack_position = re::bitscan_forward(re::get_sliding_bitmask(king_square, re::EAST) & all_pieces);

                if ((1ull << attack_position) & rQ_squares) {
                    u64 attack_ray = re::get_sliding_bitmask(king_square, re::EAST) & ~re::get_sliding_bitmask(attack_position, re::EAST);
                    sliding_attacks.push_back(attack_ray);
                }
            }

            if (re::get_sliding_bitmask(king_square, re::SOUTH) & all_pieces) {
                char attack_position = re::bitscan_reverse(re::get_sliding_bitmask(king_square, re::SOUTH) & all_pieces);

                if ((1ull << attack_position) & rQ_squares) {
                    u64 attack_ray = re::get_sliding_bitmask(king_square, re::SOUTH) & ~re::get_sliding_bitmask(attack_position, re::SOUTH);
                    sliding_attacks.push_back(attack_ray);
                }
            }

            if (re::get_sliding_bitmask(king_square, re::WEST) & all_pieces) {
                char attack_position = re::bitscan_reverse(re::get_sliding_bitmask(king_square, re::WEST) & all_pieces);

                if ((1ull << attack_position) & rQ_squares) {
                    u64 attack_ray = re::get_sliding_bitmask(king_square, re::WEST) & ~re::get_sliding_bitmask(attack_position, re::WEST);
                    sliding_attacks.push_back(attack_ray);
                }
            }
        }
    
        return sliding_attacks;
    }

    std::vector<u64> get_full_sliding_attacks(char king_square, u64 all_pieces, u64 bQ_squares, u64 rQ_squares) {
        std::vector<u64> sliding_attacks;

        u64 potential_bQ_attacks = get_bishop_attacks(king_square, all_pieces);
        u64 potential_rQ_attacks = get_rook_attacks(king_square, all_pieces);

        if (potential_bQ_attacks & bQ_squares) {
            if (re::get_sliding_bitmask(king_square, re::NORTHEAST) & all_pieces) {
                char attack_position = re::bitscan_forward(re::get_sliding_bitmask(king_square, re::NORTHEAST) & all_pieces);

                if ((1ull << attack_position) & bQ_squares) {
                    u64 attack_ray = re::get_sliding_bitmask(attack_position, re::SOUTHWEST);
                    sliding_attacks.push_back(attack_ray);
                }
            }

            if (re::get_sliding_bitmask(king_square, re::NORTHWEST) & all_pieces) {
                char attack_position = re::bitscan_forward(re::get_sliding_bitmask(king_square, re::NORTHWEST) & all_pieces);

                if ((1ull << attack_position) & bQ_squares) {
                    u64 attack_ray = re::get_sliding_bitmask(attack_position, re::SOUTHEAST);
                    sliding_attacks.push_back(attack_ray);
                }
            }

            if (re::get_sliding_bitmask(king_square, re::SOUTHEAST) & all_pieces) {
                char attack_position = re::bitscan_reverse(re::get_sliding_bitmask(king_square, re::SOUTHEAST) & all_pieces);

                if ((1ull << attack_position) & bQ_squares) {
                    u64 attack_ray = re::get_sliding_bitmask(attack_position, re::NORTHWEST);
                    sliding_attacks.push_back(1ull);
                }
            }

            if (re::get_sliding_bitmask(king_square, re::SOUTHWEST) & all_pieces) {
                char attack_position = re::bitscan_reverse(re::get_sliding_bitmask(king_square, re::SOUTHWEST) & all_pieces);

                if ((1ull << attack_position) & bQ_squares) {
                    u64 attack_ray = re::get_sliding_bitmask(attack_position, re::NORTHEAST);
                    sliding_attacks.push_back(1ull);
                }
            }
        }

        if (potential_rQ_attacks & rQ_squares) {
            if (re::get_sliding_bitmask(king_square, re::NORTH) & all_pieces) {
                char attack_position = re::bitscan_forward(re::get_sliding_bitmask(king_square, re::NORTH) & all_pieces);

                if ((1ull << attack_position) & rQ_squares) {
                    u64 attack_ray = re::get_sliding_bitmask(attack_position, re::SOUTH);
                    sliding_attacks.push_back(attack_ray);
                }
            }

            if (re::get_sliding_bitmask(king_square, re::EAST) & all_pieces) {
                char attack_position = re::bitscan_forward(re::get_sliding_bitmask(king_square, re::EAST) & all_pieces);

                if ((1ull << attack_position) & rQ_squares) {
                    u64 attack_ray = re::get_sliding_bitmask(attack_position, re::WEST);
                    sliding_attacks.push_back(attack_ray);
                }
            }

            if (re::get_sliding_bitmask(king_square, re::SOUTH) & all_pieces) {
                char attack_position = re::bitscan_reverse(re::get_sliding_bitmask(king_square, re::SOUTH) & all_pieces);

                if ((1ull << attack_position) & rQ_squares) {
                    u64 attack_ray = re::get_sliding_bitmask(attack_position, re::NORTH);
                    sliding_attacks.push_back(attack_ray);
                }
            }

            if (re::get_sliding_bitmask(king_square, re::WEST) & all_pieces) {
                char attack_position = re::bitscan_reverse(re::get_sliding_bitmask(king_square, re::WEST) & all_pieces);


                if ((1ull << attack_position) & rQ_squares) {
                    u64 attack_ray = re::get_sliding_bitmask(attack_position, re::EAST);
                    sliding_attacks.push_back(attack_ray);
                }
            }
        }
    
        return sliding_attacks; 
    }
    
    u64 get_all_attacks(re::Board& board, char attacker_color) {
        u64 attacks = 0ull;
        u64 piece_locations;

        if (attacker_color == re::W) {
            piece_locations = board.bitboards[re::W | re::PAWN];

            while (piece_locations) {
                attacks |= get_white_pawn_attacks(re::bitscan_forward(piece_locations));
                piece_locations &= piece_locations - 1;
            }
        }

        else {
            piece_locations = board.bitboards[re::B | re::PAWN];

            while (piece_locations) {
                attacks |= get_black_pawn_attacks(re::bitscan_forward(piece_locations));
                piece_locations &= piece_locations - 1;
            }
        }

        // Knights
        piece_locations = board.bitboards[attacker_color | re::KNIGHT];

        while (piece_locations) {
            attacks |= get_knight_attacks(re::bitscan_forward(piece_locations));
            piece_locations &= piece_locations - 1;
        }
        
        // Bishops
        piece_locations = board.bitboards[attacker_color | re::BISHOP];

        while (piece_locations) {
            attacks |= get_bishop_attacks(re::bitscan_forward(piece_locations), board.all_piece_locations);
            piece_locations &= piece_locations - 1;
        }
        
        // Rooks
        piece_locations = board.bitboards[attacker_color | re::ROOK];

        while (piece_locations) {
            attacks |= get_rook_attacks(re::bitscan_forward(piece_locations), board.all_piece_locations);
            piece_locations &= piece_locations - 1;
        }
        
        // Queens
        piece_locations = board.bitboards[attacker_color | re::QUEEN];

        while (piece_locations) {
            attacks |= get_queen_attacks(re::bitscan_forward(piece_locations), board.all_piece_locations);
            piece_locations &= piece_locations - 1;
        }
        
        // King
        attacks |= get_king_attacks(re::bitscan_forward(board.bitboards[attacker_color | re::KING]));

        return attacks;
    }

    /**
     * 
    */
    std::vector<re::Move> get_all_legal_moves(re::Board& board) {
        std::vector<re::Move> legal_moves;

        char king_square = re::bitscan_forward(board.bitboards[board.current_turn | re:: KING]);
        bool in_check = board.bitboards[board.current_turn | re::KING] & get_all_attacks(board, board.other_turn);
        u64 attacks = get_all_attacks(board, board.other_turn);

        std::unordered_map<char, u64> xray_attacks = find_xray_attacks(
            king_square, 
            board.piece_locations[board.current_turn], 
            board.all_piece_locations, 
            board.bitboards[board.other_turn | re::BISHOP] | board.bitboards[board.other_turn | re:: QUEEN],
            board.bitboards[board.other_turn | re::ROOK] | board.bitboards[board.other_turn | re:: QUEEN]
            );
        
        if (in_check) {
            std::vector<u64> sliding_attacks = find_sliding_attacks(
                king_square,
                board.all_piece_locations,
                board.bitboards[board.other_turn | re::BISHOP] | board.bitboards[board.other_turn | re::QUEEN],
                board.bitboards[board.other_turn | re::ROOK] | board.bitboards[board.other_turn | re::QUEEN]
            );

            u64 knight_locations = board.bitboards[board.other_turn | re::KNIGHT];
            u64 knight_check = 0ull;
            

            while (knight_locations) {
                if (get_knight_attacks(re::bitscan_forward(knight_locations)) & board.bitboards[board.current_turn | re::KING]) {
                    knight_check = get_knight_attacks(re::bitscan_forward(knight_locations));
                    break;
                }

                knight_locations &= knight_locations - 1;
            }

            // double check
            if (sliding_attacks.size() > 1 || (sliding_attacks.size() == 1 && knight_check)) {
                sliding_attacks = get_full_sliding_attacks(
                    king_square,
                    board.all_piece_locations,
                    board.bitboards[board.other_turn | re::BISHOP] | board.bitboards[board.other_turn | re::QUEEN],
                    board.bitboards[board.other_turn | re::ROOK] | board.bitboards[board.other_turn | re::QUEEN]);
                    
                // Presumably only double checks are legal
                u64 sliding_attack_bb = 0ull;
                if (sliding_attacks.size() == 1) {
                    sliding_attack_bb = sliding_attacks[0] | knight_check;
                }
                
                else {
                    sliding_attack_bb = sliding_attacks[0] | sliding_attacks[1] ;
                }
                
                u64 king_moves = (get_king_attacks(king_square) ^ (get_king_attacks(king_square) & board.piece_locations[board.current_turn]));
                king_moves &= ~sliding_attack_bb;

                while (king_moves != 0ull) {
                    char to = re::bitscan_forward(king_moves);

                    if (board.piece_locations[board.other_turn] & (1ull << to)) {
                        legal_moves.push_back(re::Move(king_square, to, re::CAPTURE, 0));
                    }

                    else {
                        legal_moves.push_back(re::Move(king_square, to));
                    }

                    king_moves &= king_moves - 1;
                }

                return legal_moves;
            }

            // In check by non sliding piece
            if (sliding_attacks.size() == 0) {
                u64 attacks = get_all_attacks(board, board.other_turn);

                u64 king_moves = (get_king_attacks(king_square) ^ (get_king_attacks(king_square) & board.piece_locations[board.current_turn]));
                king_moves &= ~attacks;

                while (king_moves) {
                    char to = re::bitscan_forward(king_moves);
                    
                    if (board.piece_locations[board.other_turn] & (1ull << to)) {
                        legal_moves.push_back(re::Move(king_square, to, re::CAPTURE, 0));
                    }

                    else {
                        legal_moves.push_back(re::Move(king_square, to));
                    }

                    king_moves &= king_moves - 1;
                }

                return legal_moves;
            }
 
            // In check by sliding piece 
            if (sliding_attacks.size() == 1) {
                u64 sliding_attack_block = sliding_attacks[0];

                sliding_attacks = get_full_sliding_attacks(
                    king_square,
                    board.all_piece_locations,
                    board.bitboards[board.other_turn | re::BISHOP] | board.bitboards[board.other_turn | re::QUEEN],
                    board.bitboards[board.other_turn | re::ROOK] | board.bitboards[board.other_turn | re::QUEEN]);
                    
                
                u64 king_moves = (get_king_attacks(king_square) ^ (get_king_attacks(king_square) & board.piece_locations[board.current_turn]));
                king_moves &= ~get_all_attacks(board, board.other_turn);
                king_moves &= ~sliding_attacks[0];

                while (king_moves != 0ull) {
                    char to = re::bitscan_forward(king_moves);

                    if (board.piece_locations[board.other_turn] & (1ull << to)) {
                        legal_moves.push_back(re::Move(king_square, to, re::CAPTURE, 0));
                    }

                    else {
                        legal_moves.push_back(re::Move(king_square, to));
                    }

                    king_moves &= king_moves - 1;
                }

                // Other piece moves
                u64 piece_locations = 0ull;

                // Pawn Moves
                piece_locations = board.bitboards[board.current_turn | re::PAWN];

                if (board.current_turn == re::W) {
                    while (piece_locations) {    
                        char from = re::bitscan_forward(piece_locations);
                        u64 moves = get_white_pawn_moves(from, board.all_piece_locations, board.piece_locations[board.other_turn]);
                        moves &= sliding_attack_block;

                        if (xray_attacks.find(from) != xray_attacks.end()) {
                            moves &= xray_attacks[from];
                        }

                        u64 capture_moves = moves & board.piece_locations[board.other_turn];
                        moves ^= capture_moves;

                        while (capture_moves) {
                            char to = re::bitscan_forward(capture_moves);

                            // Can change promo behavior if want
                            if (to / 8 == 7) {
                                legal_moves.push_back(re::Move(from, to, re::PROMO_CAPTURE, re::QUEEN));
                            }
                            
                            else {
                                legal_moves.push_back(re::Move(from, to, re::CAPTURE, 0));
                            }

                            capture_moves &= capture_moves - 1;
                        }

                        while (moves) {
                            char to = re::bitscan_forward(moves);
                            if (to / 8 == 7) {
                                legal_moves.push_back(re::Move(from, to, re::PROMOTION, re::QUEEN));
                            }

                            else {
                                legal_moves.push_back(re::Move(from, re::bitscan_forward(moves)));
                            }
                            
                            moves &= moves - 1;
                        }

                        piece_locations &= piece_locations - 1;
                    }
                }

                else {
                    while (piece_locations) {    
                        char from = re::bitscan_forward(piece_locations);
                        u64 moves = get_black_pawn_moves(from, board.all_piece_locations, board.piece_locations[board.other_turn]);
                        moves &= sliding_attack_block;

                        if (xray_attacks.find(from) != xray_attacks.end()) {
                            moves &= xray_attacks[from];
                        }

                        u64 capture_moves = moves & board.piece_locations[board.other_turn];
                        moves ^= capture_moves;

                        while (capture_moves) {
                            char to = re::bitscan_forward(capture_moves);

                            // Can change promo behavior if want
                            if (to / 8 == 0) {
                                legal_moves.push_back(re::Move(from, to, re::PROMO_CAPTURE, re::QUEEN));
                            }
                            
                            else {
                                legal_moves.push_back(re::Move(from, to, re::CAPTURE, 0));
                            }

                            capture_moves &= capture_moves - 1;
                        }

                        while (moves) {
                            char to = re::bitscan_forward(moves);
                            if (to / 8 == 0) {
                                legal_moves.push_back(re::Move(from, to, re::PROMOTION, re::QUEEN));
                            }

                            else {
                                legal_moves.push_back(re::Move(from, re::bitscan_forward(moves)));
                            }
                            
                            moves &= moves - 1;
                        }

                        piece_locations &= piece_locations - 1;
                    }
                }
            
                // Knight Moves
                piece_locations = board.bitboards[board.current_turn | re::KNIGHT];

                while (piece_locations) {    
                    char from = re::bitscan_forward(piece_locations);
                    u64 moves = get_knight_attacks(from) ^ (get_knight_attacks(from) & board.piece_locations[board.current_turn]);
                    moves &= sliding_attack_block;

                    if (xray_attacks.find(from) != xray_attacks.end()) {
                            moves &= xray_attacks[from];
                    }

                    u64 capture_moves = moves & board.piece_locations[board.other_turn];
                    moves ^= capture_moves;

                    while (capture_moves) {
                        legal_moves.push_back(re::Move(from, re::bitscan_forward(capture_moves), re::CAPTURE, 0));
                        capture_moves &= capture_moves - 1;
                    }

                    while (moves) {
                        legal_moves.push_back(re::Move(from, re::bitscan_forward(moves)));
                        moves &= moves - 1;
                    }

                    piece_locations &= piece_locations - 1;
                }

                // Bishop Moves
                piece_locations = board.bitboards[board.current_turn | re::BISHOP];

                while (piece_locations) {    
                    char from = re::bitscan_forward(piece_locations);
                    u64 moves = get_bishop_attacks(from, board.all_piece_locations) ^ (get_bishop_attacks(from, board.all_piece_locations) & board.piece_locations[board.current_turn]);
                    moves &= sliding_attack_block;

                    if (xray_attacks.find(from) != xray_attacks.end()) {
                            moves &= xray_attacks[from];
                    }

                    u64 capture_moves = moves & board.piece_locations[board.other_turn];
                    moves ^= capture_moves;

                    while (capture_moves) {
                        legal_moves.push_back(re::Move(from, re::bitscan_forward(capture_moves), re::CAPTURE, 0));
                        capture_moves &= capture_moves - 1;
                    }

                    while (moves) {
                        legal_moves.push_back(re::Move(from, re::bitscan_forward(moves)));
                        moves &= moves - 1;
                    }

                    piece_locations &= piece_locations - 1;
                }

                // Rook Moves
                piece_locations = board.bitboards[board.current_turn | re::ROOK];

                while (piece_locations) {    
                    char from = re::bitscan_forward(piece_locations);
                    u64 moves = get_rook_attacks(from, board.all_piece_locations) ^ (get_rook_attacks(from, board.all_piece_locations) & board.piece_locations[board.current_turn]);
                    moves &= sliding_attack_block;

                    if (xray_attacks.find(from) != xray_attacks.end()) {
                            moves &= xray_attacks[from];
                    }

                    u64 capture_moves = moves & board.piece_locations[board.other_turn];
                    moves ^= capture_moves;

                    while (capture_moves) {
                        legal_moves.push_back(re::Move(from, re::bitscan_forward(capture_moves), re::CAPTURE, 0));
                        capture_moves &= capture_moves - 1;
                    }

                    while (moves) {
                        legal_moves.push_back(re::Move(from, re::bitscan_forward(moves)));
                        moves &= moves - 1;
                    }

                    piece_locations &= piece_locations - 1;
                }

                // Queen Moves
                piece_locations = board.bitboards[board.current_turn | re::QUEEN];

                while (piece_locations) {    
                    char from = re::bitscan_forward(piece_locations);
                    u64 moves = get_queen_attacks(from, board.all_piece_locations) ^ (get_queen_attacks(from, board.all_piece_locations) & board.piece_locations[board.current_turn]);
                    moves &= sliding_attack_block;

                    if (xray_attacks.find(from) != xray_attacks.end()) {
                            moves &= xray_attacks[from];
                    }

                    u64 capture_moves = moves & board.piece_locations[board.other_turn];
                    moves ^= capture_moves;

                    while (capture_moves) {
                        legal_moves.push_back(re::Move(from, re::bitscan_forward(capture_moves), re::CAPTURE, 0));
                        capture_moves &= capture_moves - 1;
                    }

                    while (moves) {
                        legal_moves.push_back(re::Move(from, re::bitscan_forward(moves)));
                        moves &= moves - 1;
                    }

                    piece_locations &= piece_locations - 1;
                }
            }
             
            return legal_moves;
        }

        u64 pieces = board.bitboards[board.current_turn | re::PAWN];
        u64 moves;

        if (board.current_turn == re::W) {
            while (pieces) {
                char from = re::bitscan_forward(pieces);
                moves = get_white_pawn_moves(from, board.all_piece_locations, board.piece_locations[re::B]);

                if (xray_attacks.find(from) != xray_attacks.end()) {
                    moves &= xray_attacks[from];
                }

                u64 capture_moves = moves & board.piece_locations[board.other_turn];
                moves ^= capture_moves;

                while (capture_moves) {
                    legal_moves.push_back(re::Move(from, re::bitscan_forward(capture_moves), re::CAPTURE, 0));
                    capture_moves &= capture_moves - 1;
                }

                while (moves) {
                    legal_moves.push_back(re::Move(from, re::bitscan_forward(moves)));
                    moves &= moves - 1;
                }

                pieces &= pieces - 1;
            }
        }

        else {
            while (pieces) {
                char from = re::bitscan_forward(pieces);
                moves = get_black_pawn_moves(from, board.all_piece_locations, board.piece_locations[re::W]);

                if (xray_attacks.find(from) != xray_attacks.end()) {
                    moves &= xray_attacks[from];
                }

                u64 capture_moves = moves & board.piece_locations[board.other_turn];
                moves ^= capture_moves;

                while (capture_moves) {
                    legal_moves.push_back(re::Move(from, re::bitscan_forward(capture_moves), re::CAPTURE, 0));
                    capture_moves &= capture_moves - 1;
                }

                while (moves) {
                    legal_moves.push_back(re::Move(from, re::bitscan_forward(moves)));
                    moves &= moves - 1;
                }

                pieces &= pieces - 1;
            }
        }

        pieces = board.bitboards[board.current_turn | re::KNIGHT];
        while (pieces) {
            char from = re::bitscan_forward(pieces);
            moves = get_knight_attacks(from) ^ (get_knight_attacks(from) & board.piece_locations[board.current_turn]);

            if (xray_attacks.find(from) != xray_attacks.end()) {
                moves &= xray_attacks[from];
            }

            u64 capture_moves = moves & board.piece_locations[board.other_turn];
            moves ^= capture_moves;

            while (capture_moves) {
                legal_moves.push_back(re::Move(from, re::bitscan_forward(capture_moves), re::CAPTURE, 0));
                capture_moves &= capture_moves - 1;
            }

            while (moves) {
                legal_moves.push_back(re::Move(from, re::bitscan_forward(moves)));
                moves &= moves - 1;
            }

            pieces &= pieces - 1;
        }

        pieces = board.bitboards[board.current_turn | re::BISHOP];
        while (pieces) {
            char from = re::bitscan_forward(pieces);
            moves = get_bishop_attacks(from, board.all_piece_locations) ^ (get_bishop_attacks(from, board.all_piece_locations) & board.piece_locations[board.current_turn]);

            if (xray_attacks.find(from) != xray_attacks.end()) {
                moves &= xray_attacks[from];
            }

            u64 capture_moves = moves & board.piece_locations[board.other_turn];
            moves ^= capture_moves;

            while (capture_moves) {
                legal_moves.push_back(re::Move(from, re::bitscan_forward(capture_moves), re::CAPTURE, 0));
                capture_moves &= capture_moves - 1;
            }

            while (moves) {
                legal_moves.push_back(re::Move(from, re::bitscan_forward(moves)));
                moves &= moves - 1;
            }

            pieces &= pieces - 1;
        }

        pieces = board.bitboards[board.current_turn | re::ROOK];
        while (pieces) {
            char from = re::bitscan_forward(pieces);
            moves = get_rook_attacks(from, board.all_piece_locations) ^ (get_rook_attacks(from, board.all_piece_locations) & board.piece_locations[board.current_turn]);

            if (xray_attacks.find(from) != xray_attacks.end()) {
                moves &= xray_attacks[from];
            }

            u64 capture_moves = moves & board.piece_locations[board.other_turn];
            moves ^= capture_moves;

            while (capture_moves) {
                legal_moves.push_back(re::Move(from, re::bitscan_forward(capture_moves), re::CAPTURE, 0));
                capture_moves &= capture_moves - 1;
            }

            while (moves) {
                legal_moves.push_back(re::Move(from, re::bitscan_forward(moves)));
                moves &= moves - 1;
            }

            pieces &= pieces - 1;
        }

        pieces = board.bitboards[board.current_turn | re::QUEEN];
        while (pieces) {
            char from = re::bitscan_forward(pieces);
            moves = get_queen_attacks(from, board.all_piece_locations) ^ (get_queen_attacks(from, board.all_piece_locations) & board.piece_locations[board.current_turn]);

            if (xray_attacks.find(from) != xray_attacks.end()) {
                moves &= xray_attacks[from];
            }

            u64 capture_moves = moves & board.piece_locations[board.other_turn];
            moves ^= capture_moves;

            while (capture_moves) {
                legal_moves.push_back(re::Move(from, re::bitscan_forward(capture_moves), re::CAPTURE, 0));
                capture_moves &= capture_moves - 1;
            }

            while (moves) {
                legal_moves.push_back(re::Move(from, re::bitscan_forward(moves)));
                moves &= moves - 1;
            }

            pieces &= pieces - 1;
        }

        moves = get_king_attacks(king_square) ^ (get_king_attacks(king_square) & board.piece_locations[board.current_turn]);
        moves &= ~get_all_attacks(board, board.other_turn);

        u64 capture_moves = moves & board.piece_locations[board.other_turn];
        moves ^= capture_moves;

        while (capture_moves) {
            legal_moves.push_back(re::Move(king_square, re::bitscan_forward(capture_moves), re::CAPTURE, 0));
            capture_moves &= capture_moves - 1;
        }

        while (moves) {
            legal_moves.push_back(re::Move(king_square, re::bitscan_forward(moves)));
            moves &= moves - 1;
        }

        return legal_moves;
    }
}