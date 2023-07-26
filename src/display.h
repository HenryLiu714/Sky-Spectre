#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <raylib.h>
#include <vector>

#include "references.h"
#include "moves.h"

typedef unsigned long long u64;

namespace display {
    const float box_size = screen_height / 8;

    /**
     * Function to display the board background on screen
    */
    void draw_background();

    /**
     * Helper function to translate a board space number (0-63) to a Vector2 (x,y) of the location to draw the square
     * 
     * @param space The space (0-63) that is given
     * @return A vector (x,y) with the location that the space is on the screen
    */
    Vector2 number_to_location(int space);

    /**
     * Draws each piece in the correct locations relative to the board background
     * @param board The Board object containing the pieces that need the be drawn
     * @param chess_pieces A Texture2D object containing an image of all the pieces to be drawn
    */
    void draw_board (re::Board& board, Texture2D chess_pieces);

    /**
     * Highlights the background of a square
     * @param space The space (0-63) that is to be highlighted
    */
    void highlight_square(int space);
}

#endif