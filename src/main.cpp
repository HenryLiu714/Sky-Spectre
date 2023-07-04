#include <iostream>
#include <vector>
#include <unordered_map>
#include <raylib.h>

#include "references.h"
#include "display.h"
#include "moves.h"
#include "evaluation.h"

Texture2D chess_pieces;

int main () {

    // Stuff to do from references.h
    re::intialize_move_lookups();

    InitWindow(screen_width, screen_height, "Chess Game");
    SetTargetFPS(fps); // Without this line, fps will be uncapped

    Image pieces_image = LoadImage("../assets/chess_pieces.png");
    Image* pieces_pointer = &pieces_image;

    ImageResize(pieces_pointer, box_size * 6, box_size * 2);

    chess_pieces = LoadTextureFromImage(pieces_image);

    re::Board board;
   //board.update_with_fen((char*) "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    board.update_with_fen((char*) "8/1k5P/5K2/8/8/8/8/R2q4 w KQkq - 0 1");

    board.perform_move(re::Move(55, 63, re::PROMO_CAPTURE, re::QUEEN));
    
    /**
     * Drawing things
     * -------------------
     * void DrawRectangle(int posX, int posY, int width, int height, Color color)
     * void DrawCircle(int centerX, int centerY, float radius, Color color)
     * void DrawLine(int startPosX, int startPostY, int endPosX, int endPosY, Color color)
     * void DrawPoly(Vector2 center, int sides, float radius, float rotation, Color color)
    */

    // Game loop
    while (WindowShouldClose() == false) {
        BeginDrawing(); // Creates blank canvas
        ClearBackground(WHITE);

        // Display background
        display::draw_background();

        // Display pieces
        display::draw_board(board, chess_pieces);

        // Display on click
        //display::display_possible_moves_from_click(board);
        // std::cout << moves::find_xray_attacks(
        //     re::bitscan_forward(board.bitboards[board.current_turn | re:: KING]),
        //     board.piece_locations[board.current_turn], 
        //     board.all_piece_locations, 
        //     board.bitboards[board.current_turn | re::BISHOP] | board.bitboards[board.current_turn | re:: QUEEN],
        //     board.bitboards[board.current_turn | re::ROOK] | board.bitboards[board.current_turn | re:: QUEEN]
        // ).size();
        
        EndDrawing(); // Ends canvas drawing
    }

    CloseWindow();
    return 0;
}