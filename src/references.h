#ifndef REFERENCES_H
#define REFERENCES_H

#include <bits/stdc++.h>
#include <unordered_map>
#include <vector>
#include <string>
#include <list>
#include <bit>

typedef unsigned long long u64;

// Constants
const int screen_width = 1080;
const int screen_height = 720;
const int fps = 100;

const int box_size = screen_height / 8;

namespace re {
    enum Pieces {EMPTY, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING};
    enum Side {NEITHER=0, W=16, B=32, BOTH=48}; // can use mod 16 to just find piece, can use / 16 to find side 10001
    enum Squares {
        a1, b1, c1, d1, e1, f1, g1, h1,
        a2, b2, c2, d2, e2, f2, g2, h2,
        a3, b3, c3, d3, e3, f3, g3, h3,
        a4, b4, c4, d4, e4, f4, g4, h4,
        a5, b5, c5, d5, e5, f5, g5, h5,
        a6, b6, c6, d6, e6, f6, g6, h6,
        a7, b7, c7, d7, e7, f7, g7, h7,
        a8, b8, c8, d8, e8, f8, g8, h8
        }; // a1=0, h8=63
    enum SpecialFlags {NONE, CASTLE, CAPTURE, EN_PASSANT, PROMOTION, PROMO_CAPTURE};
    enum Sliding_Directions {NORTHEAST, NORTHWEST, SOUTHEAST, SOUTHWEST, NORTH, EAST, SOUTH, WEST};

    void display_bitboard(u64 bitboard);

    char chess_notation_to_space(char file, char rank);

    const int lookup67[67+1] = {
        64,  0,  1, 39,  2, 15, 40, 23,
        3, 12, 16, 59, 41, 19, 24, 54,
        4, -1, 13, 10, 17, 62, 60, 28,
        42, 30, 20, 51, 25, 44, 55, 47,
        5, 32, -1, 38, 14, 22, 11, 58,
        18, 53, 63,  9, 61, 27, 29, 50,
        43, 46, 31, 37, 21, 57, 52,  8,
        26, 49, 45, 36, 56,  7, 48, 35,
        6, 34, 33, -1 };

    /**
     * @return The least significant 1 bit in a u64 (i.e. lowest value)
    */
    char bitscan_forward(u64 bb);

    /**
     * @return The most significant 1 bit in a u64 (highest value)
    */
    char bitscan_reverse(u64 bb);
    
    /**
     * @return vector<char> of location of all bits in bb
    */
    std::vector<char> serialize_bitboard(u64 bb);

    struct Move {
        char from;
        char to;
        char special_move_flag; // 0 = no special move, 1 = castle, 2 = en_passant, 3 = capture, 4 = promotion, 5 = promotion + capture
        char promoted_piece;

        Move (char fromp, char top, char special_move_flagp=0, char promoted_piecep=0) {
            from = fromp;
            to = top;
            special_move_flag = special_move_flagp;
            promoted_piece = promoted_piecep;
        }

        Move copy() {
            return Move(from, to, special_move_flag, promoted_piece);
        }
    };

    struct Board {
        std::unordered_map<char, u64> bitboards = {
            {17, 0},
            {18, 0},
            {19, 0},
            {20, 0},
            {21, 0},
            {22, 0},
            {33, 0},
            {34, 0},
            {35, 0},
            {36, 0},
            {37, 0},
            {38, 0}
        };
        
        // Field variables
        char current_turn= W;
        char other_turn = B;
        bool castling_availability[4] = {0};
        char en_passant_target= 0;
        int halfmove_clock= 0;
        int fullmove_clock= 0;

        std::unordered_map<char, u64> piece_locations = {
            {W, 0},
            {B, 0}
        };

        std::unordered_map<char, u64> attacked_squares = {
            {W, 0},
            {B, 0}
        };

        u64 all_piece_locations = 0ull;

        void update_with_fen(char* fen_string) {
            bitboards = {
                {17, 0},
                {18, 0},
                {19, 0},
                {20, 0},
                {21, 0},
                {22, 0},
                {33, 0},
                {34, 0},
                {35, 0},
                {36, 0},
                {37, 0},
                {38, 0}
            };

            // current_turn= W;
            // other_turn = B;
            // castling_availability[4] = {0};
            // en_passant_target= 0;
            // halfmove_clock= 0;
            // fullmove_clock= 0;

            piece_locations[W] = 0ull;
            piece_locations[B] = 0ull;

            // u64 all_piece_locations = 0ull;

            std::string row_string = "";
            std::vector<std::string> row_strings;

            int i = 0;
            while (1) {
                if (fen_string[i] == ' ') {
                    row_strings.push_back(row_string);
                    i++;
                    break;
                }

                else if (fen_string[i] == '/') {
                    row_strings.push_back(row_string);
                    row_string = "";
                    i++;
                }

                else {
                    row_string += fen_string[i];
                    i++;
                }
            }

            std::reverse(row_strings.begin(), row_strings.end());

            int current_square = 0;
            for (std::string row : row_strings) {
                for (char& c : row) {
                    if (c > 47 && c < 58) {
                        current_square += c - '0';
                    }

                    else {
                        all_piece_locations |= (1ull << current_square);

                        if (c > 64 && c < 91) {
                            piece_locations[W] |= (1ull << current_square);
                        }

                        else {
                            piece_locations[B] |= (1ull << current_square);
                        }
                        
                        switch (c) {
                            case 'P': 
                                bitboards[W | PAWN] |= (1ull  << current_square);
                                break;
                            
                            case 'B': 
                                bitboards[W | BISHOP] |= (1ull  << current_square);
                                break;

                            case 'N': 
                                bitboards[W | KNIGHT] |= (1ull  << current_square);
                                break;

                            case 'R': 
                                bitboards[W | ROOK] |= (1ull  << current_square);
                                break;
                            
                            case 'Q': 
                                bitboards[W | QUEEN] |= (1ull  << current_square);
                                break;

                            case 'K': 
                                bitboards[W | KING] |= (1ull  << current_square);
                                break;

                            case 'p': 
                                bitboards[B | PAWN] |= (1ull << current_square);
                                break;
                            
                            case 'b': 
                                bitboards[B | BISHOP] |= (1ull  << current_square);
                                break;

                            case 'n': 
                                bitboards[B | KNIGHT] |= (1ull  << current_square);
                                break;

                            case 'r': 
                                bitboards[B | ROOK] |= (1ull  << current_square);
                                break;
                            
                            case 'q': 
                                bitboards[B | QUEEN] |= (1ull  << current_square);
                                break;

                            case 'k': 
                                bitboards[B | KING] |= (1ull  << current_square);
                                break;

                            default:
                                break;
                        }

                        current_square++;
                    }
                }
            }
            
            if (fen_string[i] == 'w') {
                current_turn = W;
                other_turn = B;
            }
            
            else {
                current_turn = B;
                other_turn = W;
            }

            i+=2;

            while (1) {
                if (fen_string[i]=='-') {
                    i+=2;
                    castling_availability[0] = 0;
                    castling_availability[1] = 0;
                    castling_availability[2] = 0;
                    castling_availability[3] = 0;
                    break;
                }
                
                if (fen_string[i]==' ') {
                    i++;
                    break;
                }

                switch (fen_string[i]) {
                    case 'K':
                        castling_availability[0] = 1;
                        break;
                    case 'Q':
                        castling_availability[1] = 1;
                        break;
                    case 'k':
                        castling_availability[2] = 1;
                        break;
                    case 'q':
                        castling_availability[3] = 1;
                        break;
                    default:
                        break;
                }

                i++;
            }

            if (fen_string[i]=='-') {
                en_passant_target = 0;
                i+=2;
            }

            else {
                en_passant_target = chess_notation_to_space(fen_string[i], fen_string[i+1]);
                i+=3;
            }

            halfmove_clock = fen_string[i] - '0';
            i+=2;
            fullmove_clock = fen_string[i] - '0';
            display_bitboard(all_piece_locations);
        } 
    
        void perform_move(Move move) {
            if (move.special_move_flag > 0) {
                if (move.special_move_flag == CAPTURE) {
                    u64 move_board = (1ull << move.to) | (1ull << move.from);
                    u64 capture_board = (1ull << move.to);

                    if (bitboards[current_turn | PAWN] & (1ull << move.from)) {
                        bitboards[current_turn | PAWN] ^= move_board;
                    }

                    else if (bitboards[current_turn | KNIGHT] & (1ull << move.from)) {
                        bitboards[current_turn | KNIGHT] ^= move_board;
                    }
                    
                    else if (bitboards[current_turn | BISHOP] & (1ull << move.from)) {
                        bitboards[current_turn | BISHOP] ^= move_board;
                    }

                    else if (bitboards[current_turn | ROOK] & (1ull << move.from)) {
                        bitboards[current_turn | ROOK] ^= move_board;
                    }

                    else if (bitboards[current_turn | QUEEN] & (1ull << move.from)) {
                        bitboards[current_turn | QUEEN] ^= move_board;
                    }

                    else if (bitboards[current_turn | KING] & (1ull << move.from)) {
                        bitboards[current_turn | KING] ^= move_board;
                    }

                    if (bitboards[other_turn | PAWN] & capture_board) {
                        bitboards[other_turn | PAWN] ^= capture_board;
                    }

                    else if (bitboards[other_turn | KNIGHT] & capture_board) {
                        bitboards[other_turn | KNIGHT] ^= capture_board;
                    }
                    
                    else if (bitboards[other_turn | BISHOP] & capture_board) {
                        bitboards[other_turn | BISHOP] ^= capture_board;
                    }

                    else if (bitboards[other_turn | ROOK] & capture_board) {
                        bitboards[other_turn | ROOK] ^= capture_board;
                    }

                    else if (bitboards[other_turn | QUEEN] & capture_board) {
                        bitboards[other_turn | QUEEN] ^= capture_board;
                    }

                    else if (bitboards[other_turn | KING] & capture_board) {
                        bitboards[other_turn | KING] ^= capture_board;
                    }

                    if (move.to == 7) {castling_availability[0]=0;}
                    else if (move.to == 0) {castling_availability[1]=0;}
                    else if (move.to == 63) {castling_availability[2]=0;}
                    else if (move.to == 56) {castling_availability[3]=0;}

                    all_piece_locations ^= (1ull << move.from);
                    piece_locations[current_turn] ^= move_board;
                    piece_locations[other_turn] ^= capture_board;
                }
            
                else if (move.special_move_flag == CASTLE) {
                    u64 move_board = 0ull;
                    if (move.to == 6) {
                        move_board = (1ull << 4) | (1ull << 6) | (1ull << 5) | (1ull << 7);
                        bitboards[re::W | re::KING] ^= (1ull << 4) | (1ull << 6);
                        bitboards[re::W | re::ROOK] ^= (1ull << 5) | (1ull << 7);

                        castling_availability[0] = 0;
                        castling_availability[1] = 0;
                    }

                    else if (move.to == 2) {
                        move_board = (1ull << 4) | (1ull << 2) | (1ull << 0) | (1ull << 3);
                        bitboards[re::W | re::KING] ^= (1ull << 4) | (1ull << 2);
                        bitboards[re::W | re::ROOK] ^= (1ull << 0) | (1ull << 3);

                        castling_availability[0] = 0;
                        castling_availability[1] = 0;
                    }

                    else if (move.to == 62) {
                        move_board = (1ull << 60) | (1ull << 62) | (1ull << 63) | (1ull << 61);
                        bitboards[re::B | re::KING] ^= (1ull << 60) | (1ull << 62);
                        bitboards[re::B | re::ROOK] ^= (1ull << 63) | (1ull << 61);

                        castling_availability[2] = 0;
                        castling_availability[3] = 0;
                    }

                    else if (move.to == 58) {
                        move_board = (1ull << 60) | (1ull << 58) | (1ull << 56) | (1ull << 59);
                        bitboards[re::B | re::KING] ^= (1ull << 60) | (1ull << 58);
                        bitboards[re::B | re::ROOK] ^= (1ull << 56) | (1ull << 59);

                        castling_availability[2] = 0;
                        castling_availability[3] = 0;
                    }

                    all_piece_locations ^= move_board;
                    piece_locations[current_turn] ^= move_board;

                    
                }
            
                else if (move.special_move_flag == PROMOTION) {
                    bitboards[current_turn | PAWN] ^= (1ull << move.from);
                    bitboards[current_turn | move.promoted_piece] ^= (1ull << move.to);

                    u64 move_board = (1ull << move.from) | (1ull << move.to);
                    all_piece_locations ^= move_board;
                    piece_locations[current_turn] ^= move_board;
                }

                else if (move.special_move_flag == PROMO_CAPTURE) {
                    u64 move_board = (1ull << move.from) | (1ull << move.to);
                    u64 capture_board = (1ull << move.to);

                    if (bitboards[other_turn | PAWN] & capture_board) {
                        bitboards[other_turn | PAWN] ^= capture_board;
                    }

                    else if (bitboards[other_turn | KNIGHT] & capture_board) {
                        bitboards[other_turn | KNIGHT] ^= capture_board;
                    }
                    
                    else if (bitboards[other_turn | BISHOP] & capture_board) {
                        bitboards[other_turn | BISHOP] ^= capture_board;
                    }

                    else if (bitboards[other_turn | ROOK] & capture_board) {
                        bitboards[other_turn | ROOK] ^= capture_board;
                    }

                    else if (bitboards[other_turn | QUEEN] & capture_board) {
                        bitboards[other_turn | QUEEN] ^= capture_board;
                    }

                    else if (bitboards[other_turn | KING] & capture_board) {
                        bitboards[other_turn | KING] ^= capture_board;
                    }

                    bitboards[current_turn | PAWN] ^= (1ull << move.from);
                    bitboards[current_turn | move.promoted_piece] ^= (1ull << move.to);

                    all_piece_locations ^= move_board;
                    piece_locations[current_turn] ^= move_board;
                }
            
                if (!(bitboards[re::W | re::KING] & (1ull << 4))) {
                    castling_availability[0] = 0;
                    castling_availability[1] = 0;
                }

                if (!(bitboards[re::B | re::KING] & (1ull << 60))) {
                    castling_availability[2] = 0;
                    castling_availability[3] = 0;
                }

                if (!(bitboards[re::W | re::ROOK] & (1ull << 0))) {
                    castling_availability[0] = 0;
                }

                if (!(bitboards[re::W | re::ROOK] & (1ull << 7))) {
                    castling_availability[1] = 0;
                }

                if (!(bitboards[re::B | re::ROOK] & (1ull << 56))) {
                    castling_availability[3] = 0;
                }

                if (!(bitboards[re::B | re::ROOK] & (1ull << 63))) {
                    castling_availability[2] = 0;
                }
            }

            else {
                u64 move_board = (1ull << move.to) | (1ull << move.from);

                if (bitboards[current_turn | PAWN] & (1ull << move.from)) {
                    bitboards[current_turn | PAWN] ^= move_board;
                }

                else if (bitboards[current_turn | KNIGHT] & (1ull << move.from)) {
                    bitboards[current_turn | KNIGHT] ^= move_board;
                }
                
                else if (bitboards[current_turn | BISHOP] & (1ull << move.from)) {
                    bitboards[current_turn | BISHOP] ^= move_board;
                }

                else if (bitboards[current_turn | ROOK] & (1ull << move.from)) {
                    bitboards[current_turn | ROOK] ^= move_board;
                    
                    if (move.from == 7) {castling_availability[0]=0;}
                    else if (move.from == 0) {castling_availability[1]=0;}
                    else if (move.from == 63) {castling_availability[2]=0;}
                    else if (move.from == 56) {castling_availability[3]=0;}
                }

                else if (bitboards[current_turn | QUEEN] & (1ull << move.from)) {
                    bitboards[current_turn | QUEEN] ^= move_board;
                }

                else if (bitboards[current_turn | KING] & (1ull << move.from)) {
                    bitboards[current_turn | KING] ^= move_board;
                    if (current_turn == W) {
                        castling_availability[0] = 0;
                        castling_availability[1] = 0;
                    }

                    else {
                        castling_availability[2] = 0;
                        castling_availability[3] = 0;
                    }
                }

                all_piece_locations ^= move_board;
                piece_locations[current_turn] ^= move_board;

                if (!(bitboards[re::W | re::KING] & (1ull << 4))) {
                    castling_availability[0] = 0;
                    castling_availability[1] = 0;
                }

                if (!(bitboards[re::B | re::KING] & (1ull << 60))) {
                    castling_availability[2] = 0;
                    castling_availability[3] = 0;
                }

                if (!(bitboards[re::W | re::ROOK] & (1ull << 0))) {
                    castling_availability[0] = 0;
                }

                if (!(bitboards[re::W | re::ROOK] & (1ull << 7))) {
                    castling_availability[1] = 0;
                }

                if (!(bitboards[re::B | re::ROOK] & (1ull << 56))) {
                    castling_availability[3] = 0;
                }

                if (!(bitboards[re::B | re::ROOK] & (1ull << 63))) {
                    castling_availability[2] = 0;
                }
            }
        
            if (current_turn == W) {
                current_turn = B;
                other_turn = W;
            }

            else {
                current_turn = W;
                other_turn = B;
                fullmove_clock += 1;
            }
        }
    
        Board copy() {
            Board board;

            board.bitboards = bitboards;
            board.current_turn= current_turn;
            board.other_turn = other_turn;

            for (int i = 0; i < 4; i++) {
                board.castling_availability[i] = castling_availability[i];
            }

            board.en_passant_target = en_passant_target;
            board.halfmove_clock= halfmove_clock;
            board.fullmove_clock= fullmove_clock;

            board.piece_locations = piece_locations;
            board.attacked_squares = attacked_squares;

            return board;
        }
    };

    void initialize_knight_moves();

    void initialize_king_moves();

    const u64 notAFile = 0xfefefefefefefefe; // ~0x0101010101010101
    const u64 notHFile = 0x7f7f7f7f7f7f7f7f; // ~0x8080808080808080

    void initialize_sliding_moves();
    
    void intialize_move_lookups();

    u64 get_knight_bitmask(char square);
    u64 get_king_bitmask(char square);
    u64 get_sliding_bitmask(char square, char direction);

    // Other useful functions

    /**
     * Used to find the team
     * Example input: (W | PAWN)
     * Example return: W
    */
    char get_team(char piece); 

    void display_move_list(std::vector<Move> move_list);

    void display_move(Move move);
}

#endif