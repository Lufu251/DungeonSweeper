#pragma once

#include <lfgl.hpp>

struct Tile{
    bool mBomb = false;
    bool open = false;
    size_t count;

    Tile(){}
    Tile(bool bomb) : mBomb(bomb){}

};

struct GameBoard{
    lfgl::Array2D<Tile> grid;

    GameBoard();
    GameBoard(size_t x, size_t y);

    void CalculateNumbers();
};