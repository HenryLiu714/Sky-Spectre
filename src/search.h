#ifndef SEARCH_H
#define SEARCH_H

#include <string>

#include "references.h"

namespace search {
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
    */
    std::string search_uci(re::Board& board, char side, int depth, int time_limit);
};

#endif