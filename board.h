/* By Ulysses A. Butler */

#ifndef BOARD_H
#define BOARD_H

#include <ncurses.h>
#include <vector>

using namespace std;

enum square {empty, x_piece, o_piece};

class Board
{
private:
  vector<vector<square>> board;

  int startRow;
  int startCol;

  int cursorRow;
  int cursorCol;

  size_t size;

  int height;
  int width;

public:
  // First, the constructor is initialized with a reference to the
  // board the user will manage
  Board(size_t s);

  // The height and width of the printed board. This isn't the same
  // as the number of squares on the board
  int getHeight();
  int getWidth();

  // The size of the underlying board. A 10x10 board has a size of 10
  size_t getSize();

  // Using indexes
  square getSquareAt(size_t r, size_t c);
  void setSquareAt(size_t r, size_t c, square piece);

  // This retrieves the current square
  square getSquare();
  // Updates the board and moves the cursor to the given coordinates
  void update(square peice);
  // Get the current location of the cursor, relative to the board
  int getRow();
  int getCol();
  // Moves the cursor the the given coordinates without updating the
  // whole board
  void moveCursor(int r, int c);
  // Has a player won the game
  bool checkWin();
  // play game
  void getUserMove(square piece);
};

#endif // BOARD_H
