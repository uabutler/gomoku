/* By Ulysses A. Butler */

#include <ncurses.h>

#include "board.h"
#include "boardPrinter.h"

#define TOP "---"
#define SIDE "|"
#define INTER "+"

BoardPrinter::BoardPrinter(GomokuBoard& b): board(b)
{
  height = (board.getSize() * 2) + 1;
  width = (board.getSize() * 4) + 1; 
}

int BoardPrinter::getHeight()
{
  return height;
}

int BoardPrinter::getWidth()
{
  return width;
}

void BoardPrinter::getHeightWidth(int& h, int& w)
{
  h = height;
  w = width;
}

void BoardPrinter::print(int r, int c)
{
  size_t i;
  row = r;
  col = c;

  // Print top
  move(row, col);

  for(i = 0; i < board.getSize(); i++)
    printw(INTER TOP); 

  printw(INTER);

  // Print sides
  for(i = row + 1; i < (2 * board.getSize()) + (row + 1); i += 2)
  {
    mvprintw(i, col, SIDE);
    mvprintw(i + 1, col, INTER);

    mvprintw(i, col + (width - 1), SIDE);
    mvprintw(i + 1, col + (width - 1), INTER);
  }

  // Print bottom
  move(i - 1, col);

  for(i = 0; i < board.getSize(); i++)
    printw(INTER TOP);

  update(0, 0);
}

void BoardPrinter::update(int r, int c)
{
  mvprintw((2 * r) + 1 + row, (4 * c) + 2 + col, "%c", (board.getSquare(r, c) == x_piece) ? 'x' : 'o');

  moveCursor(r, c);

  refresh();
}

void BoardPrinter::moveCursor(int r, int c)
{
  move((2 * r) + 1 + row, (4 * c) + 2 + col);
  refresh();
}
