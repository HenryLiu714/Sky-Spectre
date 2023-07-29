# Sky-Spectre

Sky Spectre is a chess engine primarily programmed in C/C++ and rendered using the Raylib graphics library. The engine currently includes the following features:
- Board representation using bit arrays (bitboards)
- Fast move generation using bit manipulations
- Position evaluations using piece tables
- Varying depth search function using the min-max algorithm, optimized with alpha-beta pruning
- Transposition hash table for fast position lookup based on zobrist hash function

The files for the chess engine are included in the src folder, while the build folder includes the CMake files and Raylib files.

## Running the program

To run the program, simply download and execute the file ./build/chess_engine.exe.

### With CMake
Alternatively, you can download the ./src and ./assets files and build and run an executable with the included CMakeLists.txt file

## Editing the program
If you would like to make changes to the behavior of the chess engine, feel free to do so.

### Files not to change (unless necessary)
The display and references files are used to display the program and contain the board and move representations respectively.
The moves file contains the procedure for generating legal moves.

### Files to change
main.cpp can be edited to search at varying depths/times by following the comments provided

evaluation.cpp - the evaluate function can be edited or replaced with any chess board evaluation function

search.cpp - the searching functions can also be altered or added to, and are called from main.cpp