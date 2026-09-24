#include "Game.h"

#include <iostream>
#include <sstream>
#include <string>

Game::Game(const int rows, const int columns, const int mineCount)
    : board_(rows, columns, mineCount) {}

void Game::printInstructions() const {
    std::cout << "Minesweeper (" << board_.rows() << " rows, "
              << board_.columns() << " columns, " << board_.mineCount()
              << " mines)\n";
    std::cout << "Commands:\n"
              << "  o x y  Open the cell in column x, row y\n"
              << "  f x y  Place or remove a flag\n"
              << "Coordinates start at 1.\n";
}

void Game::run() {
    printInstructions();

    while (!board_.hasWon()) {
        board_.print(std::cout);
        std::cout << "Enter command: ";
        std::string line;
        if (!std::getline(std::cin, line)) {
            std::cout << "Game ended.\n";
            return;
        }
        std::istringstream input(line);
        std::string command;
        if (!(input >> command)) {
            std::cout << "Enter a command.\n";
            continue;
        }
        if (command != "o" && command != "f") {
            std::cout << "Unknown command. Use o or f\n";
            continue;
        }
        int x, y;
        std::string rubbish;
        if (!(input >> x >> y) || (input >> rubbish)) {
            std::cout << "Follow declared command format\n";
            continue;
        }
        if (command == "f") {
            const auto result = board_.toggleFlag(x - 1, y - 1);
            if (result == FlagResult::OutOfBounds) {
                std::cout << "Coordinates are invalid\n";
            }
            if (result == FlagResult::Placed) {
                std::cout << "Flag placed.\n";
            }
            if (result == FlagResult::Removed) {
                std::cout << "Flag removed.\n";
            }
            if (result == FlagResult::AlreadyOpen) {
                std::cout << "This cell is already open.\n";
            }
        }
        if (command == "o") {
            const auto result = board_.open(x - 1, y - 1);
            if (result == OpenResult::OutOfBounds) {
                std::cout << "Coordinates are invalid\n";
            }
            if (result == OpenResult::Opened) {
                if (board_.hasWon()) {
                    board_.print(std::cout);
                    std::cout << "You won!\n";
                }
            }
            if (result == OpenResult::Mine) {
                board_.print(std::cout, true);
                std::cout << "You hit a mine. Game over.\n";
                return;
            }
            if (result == OpenResult::AlreadyOpen) {
                std::cout << "This cell is already open.\n";
            }
            if (result == OpenResult::Flagged) {
                std::cout << "Remove the flag before opening this cell.\n";
            }
        }
    }
}