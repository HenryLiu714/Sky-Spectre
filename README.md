# Sky-Spectre

Sky Spectre is a chess engine primarily programmed in C/C++ and rendered using the Raylib graphics library. The engine currently includes the following features:
- Board representation using bit arrays (bitboards)
- Fast move generation using bit manipulations
- Position evaluations using piece tables
- Varying depth search function using the min-max algorithm, optimized with alpha-beta pruning
- Transposition hash table for fast position lookup based on zobrist hash function

The files for the chess engine are included in the src folder, while the build folder includes the CMake files and Raylib files.
