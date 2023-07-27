#ifndef SEARCH_H
#define SEARCH_H

#include <string>

#include "references.h"

namespace search {
    /**
     * Searchs for the best move at a given depth
     * 
     * @param board The board to search from
     * @param depth The depth to search
     * @return A Move object representing the best move
    */
    re::Move search_depth(re::Board& board, int depth);

    /**
     * Searches for the best move
     * @param board The given board to search from
     * @param side The side that is making the move
     * @param time_limit The time limit for the search (milliseconds)
     * @return The best move found as a move object
    */
    re::Move search(re::Board& board, char side, int time_limit);

    /**
     * Same as search method, but returns the move in a string in uci format
     * 
     * @param board The board being searched
     * @param side The side searching from (W or B)
     * @param depth The depth being searched
     * @param time_limit THe time limit for the search (ms)
     * @return A string in uci function representing the best move
    */
    std::string search_uci(re::Board& board, char side, int depth, int time_limit);
};

#endif