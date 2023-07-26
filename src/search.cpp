#include <string>
#include <vector>
#include <stdlib.h>
#include <cstdlib>

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
     * Returns the score for a position like previous method, except 
     * uses the alpha-beta pruning algorithm
     * 
     * @param board Input Board& being evaluated
     * @param alpha Alpha var for pruning
     * @param beta Beta var for pruning
     * @param depth Depth still left to search
     * @return An integer representing the score of a position where > 0 favors white and < 0 favors black
    */
    int alpha_beta_search_score(re::Board& board, int alpha, int beta, int depth) {
        /**
         * Base case:
         * if at bottom depth just return the score of the board
        */
        if (depth<=0 || moves::in_stalemate(board) || moves::in_checkmate(board)) {
            return eval::evaluate(board);
        }

        std::vector<re::Move> legal_moves = moves::get_all_legal_moves(board);

        if (board.current_turn == re::W) {
            int max_eval = INT_MIN;

            for (re::Move move : legal_moves) {
                re::Board board_copy = board.copy();
                board_copy.perform_move(move);
                // Recursive call
                int eval = alpha_beta_search_score(board_copy, alpha, beta, depth-1);
                max_eval = std::max(max_eval, eval);
                alpha = std::max(alpha, eval);

                if (beta <= alpha) {
                    break;
                }
            }

            return max_eval;
        }

        else {
            int min_eval = INT_MAX;

            for (re::Move move : legal_moves) {
                re::Board board_copy = board.copy();
                board_copy.perform_move(move);

                // Recursive call
                int eval = alpha_beta_search_score(board_copy, alpha, beta, depth-1);
                min_eval = std::min(min_eval, eval);
                beta = std::min(beta, eval);

                if (beta <= alpha) {
                    break;
                }
            }

            return min_eval;
        }
    }

    /**
     * Same functions as search_score pretty much,
     * but returns the best move rather than the best score
    */
    re::Move search_depth(re::Board& board, int depth) {
        srand(time(0));
        std::vector<re::Move> best_moves;

        std::vector<re::Move> legal_moves = moves::get_all_legal_moves(board);
        int alpha = INT_MIN;
        int beta = INT_MAX;

        // Edge case, stalemate/checkmate
        if (legal_moves.size() == 0) {return re::Move(0,0);}

        // Edge case, should always be 1 or more
        if (depth <= 0) {
            return legal_moves[rand() % legal_moves.size()];
        }
        
        if (board.current_turn == re::W) {
            int current_max = INT_MIN;

            for (re::Move move : legal_moves) {
                re::Board board_copy = board.copy();

                board_copy.perform_move(move);

                int score = alpha_beta_search_score(board_copy, alpha, beta, depth-1);

                if (score == current_max) {
                    best_moves.push_back(move);
                }

                if (score > current_max) {
                    current_max = score;
                    best_moves.clear();
                    best_moves.push_back(move);
                }
            }
        }

        else {
            int current_min = INT_MAX;

            for (re::Move move : legal_moves) {
                re::Board board_copy = board.copy();

                board_copy.perform_move(move);

                int score = alpha_beta_search_score(board_copy, alpha, beta, depth-1);

                if (score == current_min) {
                    best_moves.push_back(move);
                }

                if (score < current_min) {
                    current_min = score;
                    best_moves.clear();
                    best_moves.push_back(move);
                }
            }
        }

        return best_moves[rand() % best_moves.size()];
    }

    re::Move search(re::Board& board, char side, int time_limit) {

        return re::Move{0,0};
    }

    std::string search_uci(re::Board& board, char side, int depth, int time_limit) {

        return "";
    }
};