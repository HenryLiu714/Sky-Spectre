#include "references.h"

namespace re {
    void display_bitboard(u64 bitboard) {
        for (int i = 0; i < 64; i++, bitboard >>= 1) {
            if ((bitboard & 1ull) != 0) {
                std::cout << i << " ";
            }
        }

        std::cout << "\n";
    }

    char chess_notation_to_space(char file, char rank) {
        return file - 'a' + 8 * (rank - '0');
    }

    /**
     * @return The least significant 1 bit in a u64 (i.e. lowest value)
    */
    char bitscan_forward(u64 bb) {    
        return lookup67[(bb & -bb) % 67];
    }

    /**
     * @return The most significant 1 bit in a u64 (highest value)
    */
    char bitscan_reverse(u64 bb) {
        return 63 - std::__countl_zero(bb);
    }
    
    /**
     * @return vector<char> of location of all bits in bb
    */
    std::vector<char> serialize_bitboard(u64 bb) {
        std::vector<char> bit_locations;

        while (bb != 0) {
            bit_locations.push_back(bitscan_forward(bb));
            bb &= bb - 1;
        }

        return bit_locations;
    }

    u64 knight_move_bitmasks[64] = {0};
    u64 king_move_bitmasks[64] = {0};
    u64 sliding_move_bitmasks[8][64] = {0};

    void initialize_knight_moves() {
        std::vector<int> offsets = {6, 10, 15, 17};

        for (int space = 0; space < 64; space++) {
            for (int offset : offsets) {
                if (space-offset>=0) {
                    if (space%8 - (space-offset)%8 <= 2 && (space-offset)%8 - space%8 <= 2) {
                        knight_move_bitmasks[space] |= (1ull << (space-offset));
                    } 
                }

                if (space+offset<64) {
                    if (space%8 - (space+offset)%8 <= 2 && (space+offset)%8 - space%8 <= 2) {
                        knight_move_bitmasks[space] |= (1ull << (space+offset));
                    }
                }
            }
        }
    }

    void initialize_king_moves() {
        std::vector<int> offsets = {1, 7, 8, 9};

        for (int space = 0; space < 64; space++) {
            for (int offset : offsets) {
                if (space-offset>=0) {
                    if (space%8 - (space-offset)%8 <= 1 && (space-offset)%8 - space%8 <= 1) {
                        king_move_bitmasks[space] |= (1ull << (space-offset));
                    } 
                }

                if (space+offset<64) {
                    if (space%8 - (space+offset)%8 <= 2 && (space+offset)%8 - space%8 <= 2) {
                        king_move_bitmasks[space] |= (1ull << (space+offset));
                    }
                }
            }
        }
    }

    void initialize_sliding_moves() {
        u64 move = 0;

        for (int space = 0; space < 64; space++) {
            // North
            space+8 < 64 ? move = (1ull << (space + 8)) : move = 0;

            while (move != 0) {
                sliding_move_bitmasks[NORTH][space] |= move;
                move <<= 8;
            }

            // South
            space-8 >= 0 ? move = (1ull << (space - 8)) : move = 0;

            while (move != 0) {
                sliding_move_bitmasks[SOUTH][space] |= move;
                move >>= 8;
            }

            // East
            space+1 < 64 ? move = ((1ull << (space+1)) & notAFile) : move = 0;

            while (move !=0) {
                sliding_move_bitmasks[EAST][space] |= move;
                move = ((move << 1) & notAFile);
            }

            // West
            space-1 >= 0 ? move = ((1ull << (space-1)) & notHFile) : move = 0;

            while (move !=0) {
                sliding_move_bitmasks[WEST][space] |= move;
                move = ((move >> 1) & notHFile);
            }

            // Northeast
            space+9 < 64 ? move = ((1ull << (space+9)) & notAFile) : move = 0;

            while (move !=0) {
                sliding_move_bitmasks[NORTHEAST][space] |= move;
                move = ((move << 9) & notAFile);
            }

            // Southwest
            space-9 >= 0 ? move = ((1ull << (space-9)) & notHFile) : move = 0;

            while (move !=0) {
                sliding_move_bitmasks[SOUTHWEST][space] |= move;
                move = ((move >> 9) & notHFile);
            }

            // Northwest
            space+7 < 64 ? move = ((1ull << (space+7)) & notHFile) : move = 0;

            while (move !=0) {
                sliding_move_bitmasks[NORTHWEST][space] |= move;
                move = ((move << 7) & notHFile);
            }

            // Southeast
            space-7 >= 0 ? move = ((1ull << (space-7)) & notAFile) : move = 0;

            while (move !=0) {
                sliding_move_bitmasks[SOUTHEAST][space] |= move;
                move = ((move >> 7) & notAFile);
            }
        } 
    }

    void intialize_move_lookups() {
        initialize_knight_moves();
        initialize_king_moves();
        initialize_sliding_moves();
    }

    u64 get_knight_bitmask(char square) {
        return knight_move_bitmasks[(int) square];
    }
    u64 get_king_bitmask(char square) {
        return king_move_bitmasks[(int) square];
    }
    u64 get_sliding_bitmask(char square, char direction) {
        return sliding_move_bitmasks[(int) direction][(int) square];
    }
};