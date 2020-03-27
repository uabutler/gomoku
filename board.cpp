/* By Ulysses A. Butler */

#include <vector>
#include <random>
#include <chrono>

#include <iostream>

#include "board.h"

// Constructor
GomokuBoard::GomokuBoard(size_t s): size(s)
{
  squares = vector<vector<square>>(s, vector<square>(s, empty));
}

// Getter
size_t GomokuBoard::getSize()
{
  return size;
}

// Check to see if a square has a bomb
square GomokuBoard::getSquare(size_t r, size_t c)
{
  return squares[r][c];
}

void GomokuBoard::setSquare(size_t r, size_t c, square piece)
{
  squares[r][c] = piece;
}

bool GomokuBoard::checkWin()
{
  // TODO
  return false;
}
