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

    void draw_background();

    Vector2 number_to_location(int space);

    void draw_board (re::Board& board, Texture2D chess_pieces);

    void highlight_square(int space);
}

#endif