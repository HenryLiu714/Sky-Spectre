#include <string>
#include <vector>
#include <stdlib.h>

#include "references.h"
#include "search.h"
#include "evaluation.h"
#include "moves.h"

namespace search {
    /**
     * If team is white, always chooses highest score (max)
     * Else, always chooses lowest score (min)
     * 
     * Note: board.perform_move() automatically switches the turn
     * TODO: Implement alpha-beta pruning
    */
    int search_score(re::Board& board, int depth) {
        /**
         * Base case:
         * if at bottom depth just return the score of the board
        */
        if (depth == 0) {
            return eval::evaluate(board);
        }

        /**
         * Recursive case:
         * If turn==W return the highest score
         * Else return lowest score
        */
       if (board.current_turn == re::W) {
            std::vector<re::Move> legal_moves = moves::get_all_legal_moves(board);

            if (legal_moves.size() == 0) {return eval::evaluate(board);}

            int current_max = INT_MIN;

            for (re::Move move : legal_moves) {
                re::Board board_copy = board.copy();

                board_copy.perform_move(move);

                int score = search_score(board_copy, depth-1);

                if (score > current_max) {
                    current_max = score;
                }
            }

            return current_max;
       }

       else {
            std::vector<re::Move> legal_moves = moves::get_all_legal_moves(board);

            if (legal_moves.size() == 0) {return eval::evaluate(board);}

            int current_min = INT_MAX;

            for (re::Move move : legal_moves) {
                re::Board board_copy = board.copy();

                board_copy.perform_move(move);

                int score = search_score(board_copy, depth-1);

                if (score < current_min) {
                    current_min = score;
                }
            }

            return current_min;
       }
    }

    /**
     * Same functions as search_score pretty much,
     * but returns the best move rather than the best score
    */
    re::Move search_depth(re::Board& board, int depth) {

        std::vector<re::Move> legal_moves = moves::get_all_legal_moves(board);

        // Edge case, stalemate/checkmate
        if (legal_moves.size() == 0) {return re::Move(0,0);}

        // Edge case, should always be 1 or more
        if (depth <= 0) {
            return legal_moves[rand() % legal_moves.size()];
        }

        re::Move current_best_move = re::Move(0,0);
        
        if (board.current_turn == re::W) {
            int current_max = INT_MIN;

            for (re::Move move : legal_moves) {
                re::Board board_copy = board.copy();

                board_copy.perform_move(move);

                int score = search_score(board_copy, depth-1);

                if (score > current_max) {
                    current_max = score;
                    current_best_move = move.copy();
                }
            }

            return current_best_move;
        }

        else {
            int current_min = INT_MAX;

            for (re::Move move : legal_moves) {
                re::Board board_copy = board.copy();

                board_copy.perform_move(move);

                int score = search_score(board_copy, depth-1);

                if (score < current_min) {
                    current_min = score;
                    current_best_move = move.copy();
                }
            }

            return current_best_move;
        }
    }

    re::Move search(re::Board& board, char side, int time_limit) {

        return re::Move{0,0};
    }

    std::string search_uci(re::Board& board, char side, int depth, int time_limit) {

        return "";
    }
};