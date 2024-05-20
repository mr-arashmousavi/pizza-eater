#ifndef POS_H
#define POS_H

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <curses.h>
#include <iostream>
#include <ncurses.h>
#include <stdexcept>
#include <string>
#include <vector>

class Pos {
public:
  int line;
  int col;

  // Constructor
  Pos(int line, int col) : line(line), col(col) {}
};

#endif