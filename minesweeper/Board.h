#pragma once

#include <ostream>
#include <vector>

enum class OpenResult {
    Opened,
    Mine,
    AlreadyOpen,
    Flagged,
    OutOfBounds
};

enum class FlagResult {
    Placed,
    Removed,
    AlreadyOpen,
    OutOfBounds
};

class Board {
public:
    Board(int rows, int columns, int mineCount);

    OpenResult open(int x, int y); // zero-based
    FlagResult toggleFlag(int x, int y); // zero-based
    void print(std::ostream& out, bool revealMines = false) const; // printing the field in out stream

    [[nodiscard]] bool hasWon() const;

    [[nodiscard]] int rows() const;
    [[nodiscard]] int columns() const;
    [[nodiscard]] int mineCount() const;

private:
    struct Cell {
        bool mine = false;
        bool open = false;
        bool flagged = false;
        int adjacentMines = 0;
    };

    int rows_;
    int columns_;
    int mineCount_;
    int openedSafeCells_ = 0;
    const int max_width = 10;
    bool minesPlaced_ = false;
    std::vector<Cell> cells_;

    [[nodiscard]] bool inBounds(int x, int y) const;
    [[nodiscard]] int index(int x, int y) const;

    void placeMines(int safeX, int safeY);
    void countAdjacentMines();
    void openEmptyArea(int startX, int startY);
};
