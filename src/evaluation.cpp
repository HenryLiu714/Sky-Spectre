#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <vector>
#include <unordered_map>

#include "evaluation.h"
#include "references.h"
#include "moves.h"


namespace eval {

    /**
     * An array of 20 random ints for the zobrist hash function created on program runtim
    */
    int random_numbers[64][12] = {0};
    int extra_random_numbers[5] = {0}; // Castling + turn

    /**
     * Transposition (hash) table mapping a hashed value to an evaluated number as to prevent
     * repetitive calls to evaluate function
    */
    std::unordered_map<u64, int> transposition_table;

    /**
     * List to keep track of items in table in order, as to remove in case of memory overflow
    */
    std::list<u64> transpositions;


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
     * Random u64 generator that helps with initialize_hash
     * @return Random unsigned 64 bit number
    */
    u64 random_u64() {
        u64 val = 0ull;
        for (int i = 0; i < 5; i++) {
            val <<= 5;
            u64 rand_num = (u64) rand();
            val |= rand_num;
        }

        return val;
    }
    /**
     * Initializes the hash functions by setting each value in random_numbers
     * to an int between 1 and 1000
    */
   void initialize_hash() {
        for (int i = 0; i < 64; i++) {
            for (int j = 0; j < 12; j++) {
                random_numbers[i][j] = random_u64();
                std::cout << random_numbers[i][j] << "\n";
            }
        }

        for (int i = 0; i < 5; i++) {
            extra_random_numbers[i] = rand() % 100 + 1001;
        }
   }

   u64 hash_piece(u64 bitboard, int piece, int hash) {
        std::vector<char> locations = re::serialize_bitboard(bitboard);

        for (char c : locations) {
            hash ^= random_numbers[(int) c][piece];
        }

        return hash;
   }

    /**
     * Hashing function for a board position
     * 
     * @param board The board position to be hashed
     * @return A u64 with the hashed value
    */
    u64 zobrist_hash(re::Board& board) {
        u64 hash_value = 0ull;

        hash_value = hash_piece(board.bitboards[re::W | re::PAWN], 0, hash_value);
        hash_value = hash_piece(board.bitboards[re::W | re::KNIGHT], 1, hash_value);
        hash_value = hash_piece(board.bitboards[re::W | re::BISHOP], 2, hash_value);
        hash_value = hash_piece(board.bitboards[re::W | re::ROOK], 3, hash_value);
        hash_value = hash_piece(board.bitboards[re::W | re::QUEEN], 4, hash_value);
        hash_value = hash_piece(board.bitboards[re::W | re::KING], 5, hash_value);
        hash_value = hash_piece(board.bitboards[re::B | re::PAWN], 6, hash_value);
        hash_value = hash_piece(board.bitboards[re::B | re::KNIGHT], 7, hash_value);
        hash_value = hash_piece(board.bitboards[re::B | re::BISHOP], 8, hash_value);
        hash_value = hash_piece(board.bitboards[re::B | re::ROOK], 9, hash_value);
        hash_value = hash_piece(board.bitboards[re::B | re::QUEEN], 10, hash_value);
        hash_value = hash_piece(board.bitboards[re::B | re::KING], 11, hash_value);

        hash_value += board.castling_availability[0] * extra_random_numbers[0];
        hash_value += board.castling_availability[1] * extra_random_numbers[1];
        hash_value += board.castling_availability[2] * extra_random_numbers[2];
        hash_value += board.castling_availability[3] * extra_random_numbers[3];
        hash_value += board.current_turn * extra_random_numbers[4];

        return hash_value;
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

    /**
     * Gets score from piece tables (piece locations on board)
     * @param board The board being evaluated
     * @return The total score from the positions of each of the pieces
    */
    int position_score(re::Board& board) {
        int position_score = 0;
        std::vector<char> positions;
        int num_pieces = 0;

        positions = re::serialize_bitboard(board.bitboards[re::W | re::PAWN]);
        for (char position : positions) {
            position_score += W_PAWN_TAB[(int) position];
        }

        positions = re::serialize_bitboard(board.bitboards[re::W | re::KNIGHT]);
        for (char position : positions) {
            position_score += KNIGHT_TAB[(int) position];
            num_pieces ++;
        }

        positions = re::serialize_bitboard(board.bitboards[re::W | re::BISHOP]);
        for (char position : positions) {
            position_score += KNIGHT_TAB[(int) position];
            num_pieces ++;
        }

        positions = re::serialize_bitboard(board.bitboards[re::W | re::ROOK]);
        for (char position : positions) {
            position_score += W_ROOK_TAB[(int) position];
            num_pieces ++;
        }

        positions = re::serialize_bitboard(board.bitboards[re::W | re::QUEEN]);
        for (char position : positions) {
            position_score += QUEEN_TAB[(int) position];
            num_pieces ++;
        }

        positions = re::serialize_bitboard(board.bitboards[re::B | re::PAWN]);
        for (char position : positions) {
            position_score -= B_PAWN_TAB[(int) position];
        }

        positions = re::serialize_bitboard(board.bitboards[re::B | re::KNIGHT]);
        for (char position : positions) {
            position_score -= KNIGHT_TAB[(int) position];
            num_pieces ++;
        }

        positions = re::serialize_bitboard(board.bitboards[re::B | re::BISHOP]);
        for (char position : positions) {
            position_score -= KNIGHT_TAB[(int) position];
            num_pieces ++;
        }

        positions = re::serialize_bitboard(board.bitboards[re::B | re::ROOK]);
        for (char position : positions) {
            position_score -= B_ROOK_TAB[(int) position];
            num_pieces ++;
        }

        positions = re::serialize_bitboard(board.bitboards[re::B | re::QUEEN]);
        for (char position : positions) {
            position_score -= QUEEN_TAB[(int) position];
            num_pieces ++;
        }

        // Endgame
        if (num_pieces < 5) {
            positions = re::serialize_bitboard(board.bitboards[re::W | re::KING]);
            for (char position : positions) {
                position_score += W_KING_END[(int) position];
            }

            positions = re::serialize_bitboard(board.bitboards[re::B | re::KING]);
            for (char position : positions) {
                position_score -= B_KING_END[(int) position];
            }
        } 

        else {
            positions = re::serialize_bitboard(board.bitboards[re::W | re::KING]);
            for (char position : positions) {
                position_score += W_KING_TAB[(int) position];
            }

            positions = re::serialize_bitboard(board.bitboards[re::B | re::KING]);
            for (char position : positions) {
                position_score -= B_KING_TAB[(int) position];
            }
        }

        return position_score;
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

        u64 hash_value = zobrist_hash(board);

        if (transposition_table.find(hash_value) != transposition_table.end()) {
            return transposition_table[hash_value];
        }

        if (moves::in_stalemate(board)) {
            return 0;
        }
        
        int piece_score = pieces_score(board);

        score += piece_score;
        score += position_score(board);
        score += checkmate_score(board);
        
        if (transpositions.size() >= MAX_TABLE_SIZE) {
            transposition_table.erase(transpositions.front());
            transpositions.pop_front();

            transposition_table[hash_value] = score;
            transpositions.push_back(hash_value);
        }

        else {
            transposition_table[hash_value] = score;
            transpositions.push_back(hash_value);
        }

        return score;
    }
}
