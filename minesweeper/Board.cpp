#include "Board.h"

#include <algorithm>
#include <iomanip>
#include <ostream>
#include <queue>
#include <random>
#include <stdexcept>
#include <string>
#include <utility>

Board::Board(const int rows, const int columns, const int mineCount) {
    rows_ = rows;
    columns_ = columns;
    mineCount_ = mineCount;
    const int cellCount = rows * columns;
    if (rows <= 0 || columns <= 0 || mineCount <= 0 || rows > max_width || columns > max_width || mineCount > cellCount - 1) {
        throw std::invalid_argument("invalid arguments");
    }
    cells_.resize(cellCount);
}

bool Board::inBounds(const int x, const int y) const {
    return x >= 0 && x < columns_ && y >= 0 && y < rows_;
}

int Board::index(const int x, const int y) const {
    return y * columns_ + x;
}

void Board::placeMines(const int safeX, const int safeY) {

    std::vector<int> candidates;
    candidates.reserve(cells_.size() - 1);

    const int safeIndex = index(safeX, safeY);
    for (int i = 0; i < static_cast<int>(cells_.size()); i++) {
        if (i != safeIndex) {
            candidates.push_back(i);
        }
    }

    std::random_device seed;
    std::mt19937 generator(seed());
    std::ranges::shuffle(candidates, generator);

    for (int i = 0; i < mineCount_; ++i) {
        cells_[candidates[i]].mine = true;
    }

    countAdjacentMines();
    minesPlaced_ = true;
}

void Board::countAdjacentMines() {
    for (int y = 0; y < rows_; ++y) {
        for (int x = 0; x < columns_; ++x) {
            Cell& cell = cells_[index(x, y)];
            if (cell.mine) {
                continue;
            }

            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    const int neighborX = x + dx;
                    const int neighborY = y + dy;
                    if (inBounds(neighborX, neighborY) &&
                        cells_[index(neighborX, neighborY)].mine) {
                        ++cell.adjacentMines;
                    }
                }
            }
        }
    }
}

void Board::openEmptyArea(int startX, int startY) {
    std::queue<std::pair<int, int>> pending;
    pending.emplace(startX, startY);

    while (!pending.empty()) {
        const auto [x, y] = pending.front();
        pending.pop();

        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                const int neighborX = x + dx;
                const int neighborY = y + dy;
                if (!inBounds(neighborX, neighborY)) {
                    continue;
                }

                Cell& neighbor = cells_[index(neighborX, neighborY)];
                if (neighbor.open || neighbor.flagged || neighbor.mine) {
                    continue;
                }

                neighbor.open = true;
                ++openedSafeCells_;
                if (neighbor.adjacentMines == 0) {
                    pending.emplace(neighborX, neighborY);
                }
            }
        }
    }
}

OpenResult Board::open(const int x, const int y) {
    if (!inBounds(x, y)) {
        return OpenResult::OutOfBounds;
    }

    Cell& cell = cells_[index(x, y)];
    if (cell.open) {
        return OpenResult::AlreadyOpen;
    }
    if (cell.flagged) {
        return OpenResult::Flagged;
    }

    if (!minesPlaced_) {
        placeMines(x, y);
    }

    if (cell.mine) {
        cell.open = true;
        return OpenResult::Mine;
    }

    cell.open = true;
    ++openedSafeCells_;
    if (cell.adjacentMines == 0) {
        openEmptyArea(x, y);
    }
    return OpenResult::Opened;
}

FlagResult Board::toggleFlag(const int x, const int y) {
    if (!inBounds(x, y)) {
        return FlagResult::OutOfBounds;
    }

    Cell& cell = cells_[index(x, y)];
    if (cell.open) {
        return FlagResult::AlreadyOpen;
    }

    cell.flagged = !cell.flagged;
    return cell.flagged ? FlagResult::Placed : FlagResult::Removed;
}

void Board::print(std::ostream& out, const bool revealMines) const {
    const int labelWidth = static_cast<int>(std::max(std::to_string(rows_).size(),
        std::to_string(columns_).size()));
    const int cellWidth = labelWidth + 1;

    out << std::setw(labelWidth) << "    ";
    for (int x = 0; x < columns_; ++x) {
        out << std::setw(cellWidth) << x + 1;
    }
    out << '\n';

    for (int y = 0; y < rows_; ++y) {
        out << std::setw(labelWidth) << y + 1 << " | ";
        for (int x = 0; x < columns_; ++x) {
            const Cell& cell = cells_[index(x, y)];
            char c = '.';

            if ((revealMines || cell.open) && cell.mine) {
                c = '*';
            } else if (cell.flagged) {
                c = 'F';
            } else if (cell.open && cell.adjacentMines == 0) {
                c = ' ';
            } else if (cell.open) {
                c = static_cast<char>('0' + cell.adjacentMines);
            }

            out << std::setw(cellWidth) << c;
        }
        out << '\n';
    }
}

bool Board::hasWon() const {
    return minesPlaced_ && openedSafeCells_ == rows_ * columns_ - mineCount_;
}

int Board::rows() const {
    return rows_;
}

int Board::columns() const {
    return columns_;
}

int Board::mineCount() const {
    return mineCount_;
}
