#include <iostream>
#include <raylib.h>
#include <vector>

#include "references.h"
#include "moves.h"

typedef unsigned long long u64;

namespace display {
    void draw_background() {
        float start_point = screen_width * 0.5 - screen_height * 0.5;
        Color color1 = Color{160, 180, 200, 255};
        Color color2 = Color{90, 100, 130, 255};

        Color color = color1;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                DrawRectangle(box_size * i + start_point, box_size * j, box_size, box_size, color);

                if (color.r == color1.r) {color = color2;}
                else {color = color1;}   
            }

            if (color.r == color1.r) {color = color2;}
            else {color = color1;}        
        }
    }

    Vector2 number_to_location(int space) {
        float start_point = screen_width * 0.5 - screen_height * 0.5;
        return Vector2{start_point + (space%8) * box_size, (float) (7-space/8) * box_size};
    }

    std::unordered_map<int, Rectangle> pieces = {
        {17, Rectangle{box_size * 5, 0, box_size, box_size}},
        {18, Rectangle{box_size * 3, 0, box_size, box_size}},
        {19, Rectangle{box_size * 2, 0, box_size, box_size}},
        {20, Rectangle{box_size * 4, 0, box_size, box_size}},
        {21, Rectangle{box_size * 1, 0, box_size, box_size}},
        {22, Rectangle{box_size * 0, 0, box_size, box_size}},
        {33, Rectangle{box_size * 5, box_size, box_size, box_size}},
        {34, Rectangle{box_size * 3, box_size, box_size, box_size}},
        {35, Rectangle{box_size * 2, box_size, box_size, box_size}},
        {36, Rectangle{box_size * 4, box_size, box_size, box_size}},
        {37, Rectangle{box_size * 1, box_size, box_size, box_size}},
        {38, Rectangle{box_size * 0, box_size, box_size, box_size}},
    };

    void draw_board (re::Board& board, Texture2D chess_pieces) {
        u64 piece_locations = board.all_piece_locations;

        for (int i = 0; i < 64; i++, piece_locations >>= 1) {
            if ((piece_locations & 1ull) != 0) {
 
                for (auto bitboard : board.bitboards) {
                    if ((bitboard.second & (1ull << i)) != 0) {
                        DrawTextureRec(
                            chess_pieces,
                            pieces[bitboard.first],
                            number_to_location(i),
                            RAYWHITE
                        );
                    }   
                }
            }
        }       
    }  

    void highlight_square(int space) {
        Vector2 location = number_to_location(space);
        DrawRectangle(location.x, location.y, box_size, box_size, ORANGE);
    }
}