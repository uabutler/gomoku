/* By Ulysses A. Butler */

#ifndef BOARD_H
#define BOARD_H

#include <vector>

using namespace std;

enum square {empty, x_piece, o_piece};

class GomokuBoard
{
 private:
  vector<vector<square>> squares;

  size_t size;

 public:
  GomokuBoard(size_t s);

  size_t getSize();
  
  square getSquare(size_t r, size_t c);
  void setSquare(size_t r, size_t c, square piece);
  bool checkWin();
};

#endif // BOARD_H
