import curses
import atexit
import sys
from enum import Enum

# The three possibilities for a given square
class square(Enum):
  empty = 0
  x_piece = 1
  o_piece = 2

# This is responsible for printing the actual board

# The most important peice of member data is board. It stores the
# abstract game board as a SIZExSIZE 2D array of squares. They are all
# initialized to square.empty by default.

# While it's ok too read the board directly, it should not be written to
# directly because it will then be unable to print the result.

# To write to board, the place() and update() functions should be used
class Board:
  
  # The constructor, takes the size of the board as its argument
  def __init__(self, s):
    self.stdscr = curses.initscr()
    atexit.register(curses.endwin)
    curses.noecho()
    curses.cbreak()
    self.stdscr.keypad(True)
    self.size = s
    self.height = (2 * s) + 1
    self.width = (4 * s) + 1
    self.board = [[square.empty for i in range (s)] for j in range (s)]
    maxrow, maxcol = self.stdscr.getmaxyx()
    if maxrow < self.height or maxcol < self.width:
      msg1 = "  ERROR: Screen cannot fit board of this size  "
      msg2 = "Please resize your terminal or shrink the board"
      self.stdscr.move((maxrow - 2) // 2, (maxcol - len(msg1)) // 2)
      self.stdscr.addstr(msg1)
      self.stdscr.move((maxrow - 2) // 2 + 1, (maxcol - len(msg2)) // 2)
      self.stdscr.addstr(msg2)
      self.wait()
      sys.exit()
    self.startRow = (maxrow - self.height) // 2
    self.startCol = (maxcol - self.width) // 2
    self.stdscr.move(self.startRow, self.startCol)
    top = "---"
    side = "|"
    inner = "+"
    for i in range (s):
      self.stdscr.addstr(inner + top)
    self.stdscr.addstr(inner)
    for i in range (self.startRow + 1, (2 * s) + (self.startRow + 2) - 1, 2):
      self.stdscr.move(i, self.startCol)
      self.stdscr.addstr(side)
      self.stdscr.move(i + 1, self.startCol)
      self.stdscr.addstr(inner)
      self.stdscr.move(i, self.startCol + (self.width - 1))
      self.stdscr.addstr(side)
      self.stdscr.move(i + 1, self.startCol + (self.width - 1))
      self.stdscr.addstr(inner)
    for r in range (s):
      for c in range (s):
        self.stdscr.move((2 * r) + 2 + self.startRow, (4 * c) + 4 + self.startCol)
        self.stdscr.addstr(inner)
    for r in range (s):
      for c in range (s):
        self.stdscr.move((2 * r) + 1 + self.startRow, (4 * c) + 4 + self.startCol)
        self.stdscr.addstr(side)
    for r in range (s):
      for c in range (s):
        self.stdscr.move((2 * r) + 2 + self.startRow, (4 * c) + 1 + self.startCol)
        self.stdscr.addstr(top)
    self.moveCursor(0, 0)

  # This is used by the AI to place a piece (s) at a given location (r,c) on the board
  # Does NOT check to make sure the square is empty
  def place(self, r, c, s):
    center = " "
    if s is square.x_piece:
      center = "x"
    if s is square.o_piece:
      center = "o"
    oldRow = self.cursorRow
    oldCol = self.cursorCol
    self.moveCursor(r, c)
    self.stdscr.addstr(center)
    self.moveCursor(oldRow, oldCol)
    self.board[r][c] = s

  # Returns the square currently under the cursor
  def getSquare(self):
    return self.board[self.cursorRow][self.cursorCol]

  # This places the a piece (s) under the cursor.
  # Does NOT check to make sure the square is empty
  def update(self, s):
    center = " "
    if s is square.x_piece:
      center = "x"
    if s is square.o_piece:
      center = "o"
    self.moveCursor(self.cursorRow, self.cursorCol)
    self.stdscr.addstr(center)
    self.moveCursor(self.cursorRow, self.cursorCol)
    self.board[self.cursorRow][self.cursorCol] = s

  # Moves the cursor to (r,c) on the board
  def moveCursor(self, r, c):
    self.cursorRow = r
    self.cursorCol = c
    self.stdscr.move((2 * r) + 1 + self.startRow, (4 * c) + 2 + self.startCol)
    self.stdscr.refresh()

  # Checks to see if someone has won the game.
  def checkWin(self):
    # TODO
    return False

  # This passes control of the program to the user. This function will
  # allow the user to move the cursor using the arrow keys. After the
  # user presses enter, this function will place the piece indicated by
  # (p) under the cursor and return the coordiates to the caller as a
  # tuple. This function will only allow the user to place their
  # piece on an empty square
  def getUserMove(self, p):
    flag = True
    keypress = 0
    while flag:
      while (keypress := self.stdscr.getch()) != ord('\n'):
        newRow = self.cursorRow
        newCol = self.cursorCol
        flag = False
        if keypress == curses.KEY_UP:
          newRow -= 1
        elif keypress == curses.KEY_DOWN:
          newRow += 1
        elif keypress == curses.KEY_RIGHT:
          newCol += 1
        elif keypress == curses.KEY_LEFT:
          newCol -= 1
        else:
          false = True
        if newRow >= self.size or newRow < 0 or newCol >= self.size or newCol < 0:
          flag = True
        else:
          self.moveCursor(newRow, newCol)
      if self.getSquare() is not square.empty:
        flag = True
    self.update(p)
    return self.cursorRow, self.cursorCol

  # Waits for the user to press any key before continuing. This allows
  # them to pause and view the screen before the program exits.
  def wait(self):
    self.stdscr.getch()
