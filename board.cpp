/* By Ulysses A. Butler */

#include <vector>
#include <iostream>

#include "board.h"

#define TOP "---"
#define SIDE "|"
#define INTER "+"

// Constructor
Board::Board(size_t s): size(s)
{
  height = (s * 2) + 1;
  width = (s * 4) + 1; 
  board = vector<vector<square>>(s, vector<square>(s, empty));

  getmaxyx(stdscr, startRow, startCol);

  startRow = (startRow - height) / 2;
  startCol = (startCol - width) / 2;

  size_t i;

  // Print top
  move(startRow, startCol);

  for(i = 0; i < size; i++)
    printw(INTER TOP); 

  printw(INTER);

  // Print sides
  for(i = startRow + 1; i < (2 * size) + (startRow + 1); i += 2)
  {
    mvprintw(i, startCol, SIDE);
    mvprintw(i + 1, startCol, INTER);

    mvprintw(i, startCol + (width - 1), SIDE);
    mvprintw(i + 1, startCol + (width - 1), INTER);
  }

  // Print bottom
  move(i - 1, startCol);

  for(i = 0; i < size; i++)
    printw(INTER TOP);

  // Print intersections
  for(size_t r = 0; r < size; r++)
  {
    for(size_t c = 0; c < size; c++)
    {
      mvprintw((2 * r) + 2 + startRow, (4 * c) + 4 + startCol, INTER);
    }
  }

  // Print sides
  for(size_t r = 0; r < size; r++)
  {
    for(size_t c = 0; c < size; c++)
    {
      mvprintw((2 * r) + 1 + startRow, (4 * c) + 4 + startCol, SIDE);
    }
  }

  // Print top and bottom
  for(size_t r = 0; r < size; r++)
  {
    for(size_t c = 0; c < size; c++)
    {
      mvprintw((2 * r) + 2 + startRow, (4 * c) + 1 + startCol, TOP);
    }
  }

  moveCursor(0, 0);

}

// Getter
int Board::getHeight()
{
  return height;
}

int Board::getWidth()
{
  return width;
}

size_t Board::getSize()
{
  return size;
}

square Board::getSquareAt(size_t r, size_t c)
{
  return board[r][c];
}

void Board::setSquareAt(size_t r, size_t c, square s)
{
  char center;

  if(s == x_piece) center = 'x';
  if(s == o_piece) center = 'o';
  if(s == empty) center = ' ';

  int oldRow = cursorRow, oldCol = cursorCol;
  moveCursor(r, c);
  printw("%c", center);;
  moveCursor(oldRow, oldCol);

  board[r][c] = s;
}

square Board::getSquare()
{
  return board[cursorRow][cursorCol];
}

void Board::update(square s)
{
  char center;

  if(s == x_piece) center = 'x';
  if(s == o_piece) center = 'o';
  if(s == empty) center = ' ';

  moveCursor(cursorRow, cursorCol);
  printw("%c", center);;
  moveCursor(cursorRow, cursorCol);

  refresh();
}

int Board::getRow()
{
  return cursorRow;
}

int Board::getCol()
{
  return cursorCol;
}

void Board::moveCursor(int r, int c)
{
  cursorRow = r;
  cursorCol = c;

  move((2 * r) + 1 + startRow, (4 * c) + 2 + startCol);
  refresh();
}

bool Board::checkWin()
{
  // TODO
  return false;
}

void Board::getUserMove(square piece)
{
  bool flag = true;
  int input;
  
  while(flag)
  {
    while(((input = getch()) != '\n') && (input != KEY_ENTER))
    {
      int newRow = cursorRow;
      int newCol = cursorCol;
      flag = false;

      if(input == KEY_UP)
        newRow--;
      else if(input == KEY_DOWN)
        newRow++;
      else if(input == KEY_RIGHT) 
        newCol++;
      else if(input == KEY_LEFT)
        newCol--;
      else
        flag = true;

      if(newRow >= size || newRow < 0 || newCol >= size || newCol < 0)
        flag = true;
      else
        moveCursor(newRow, newCol);
    }

    mvprintw(0, 0, "1");
    refresh();

    if(getSquare() != empty)
      flag = true;

    if(flag) cout << '\a';
  }

  update(piece);
}
