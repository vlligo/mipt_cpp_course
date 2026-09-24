cmake_minimum_required(VERSION 4.3)
project(minesweeper)

set(CMAKE_CXX_STANDARD 26)

add_executable(minesweeper main.cpp
        Board.cpp
        Board.h
        Game.cpp
        Game.h)
