#ifndef POSFLOAT_H
#define POSFLOAT_H

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <curses.h>
#include <iostream>
#include <ncurses.h>
#include <stdexcept>
#include <string>
#include <vector>

class PosFloat {
public:
  float line;
  float col;

  // Constructor
  PosFloat(float line, float col) : line(line), col(col) {}
};

#endif