#pragma once
#include "Board.h"

class Game {
public:
    Game(int rows, int columns, int mineCount);

    void run();

private:
    Board board_;

    void printInstructions() const;
};
