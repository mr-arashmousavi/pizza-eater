#ifndef FOOD_H
#define FOOD_H

#include "Pos.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <curses.h>
#include <iostream>
#include <ncurses.h>
#include <stdexcept>
#include <string>
#include <vector>

class Food {
public:
  Pos pos;
  int score;
  int age;
  
  Food() : pos(0, 0), score(0), age(0) {}


  static Food makeNewFood();
  void eat_food();
  void hideFood(Food food);
};

#endif // FOOD_H
