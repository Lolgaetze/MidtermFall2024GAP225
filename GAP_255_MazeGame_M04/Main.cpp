#include <iostream>

#include "MazeGame.h"

int main()
{

    // Seed the random number generator for random movements
    srand(static_cast<unsigned int>(time(0)));

    // The layout of the maze we want to make.
    // Legend:
    // '@' - Player
    // '#' - Wall
    // '.' - Empty space
    // 'x' - Exit
    // 'V' - Villager
    // 'M' - Monster


   //char map[]{
   //    '#','#','#','#','#','#','#','#',
   //    '#','@','V','#','M','.','.','#',
   //    '#','#','.','M','.','#','V','#',
   //    '#','#','#','#','V','#','.','#',
   //    '#','x','.','#','M','#','V','#',
   //    '#','#','.','V','#','#','.','#',
   //    '#','#','M','.','.','.','.','#',
   //    '#','#','#','#','#','#','#','#',
   //};

    char map[]{
        '#','#','#','#','#','#','#','#','#','#','#','#',
        '#','@','#','.','.','.','.','.','.','.','.','#',
        '#','.','#','.','.','.','.','.','.','.','.','#',
        '#','.','#','.','.','.','.','.','.','.','.','#',
        '#','.','#','.','.','.','#','.','.','.','.','#',
        '#','.','#','.','.','.','#','.','.','.','.','#',
        '#','.','#','.','.','.','#','.','.','.','.','#',
        '#','.','#','.','.','.','#','.','.','.','V','#',
        '#','.','.','.','.','.','#','.','.','.','.','#',
        '#','.','.','.','.','.','#','.','.','.','.','#',
        '#','.','.','.','V','.','#','.','.','.','x','#',
        '#','#','#','#','#','#','#','#','#','#','#','#',
    };

    // Layout, width, height
    MazeGame game{ map, 12, 12 };
    game.Play();

    return 0;
}