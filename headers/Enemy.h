#ifndef ENEMY_H
#define ENEMY_H

#include "Pos.h"
#include "PosFloat.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <curses.h>
#include <iostream>
#include <ncurses.h>
#include <stdexcept>
#include <string>
#include <vector>

class Enemy {
public:
  Pos pos;
  PosFloat posFloat;
  int attack;

  Enemy() : pos(0, 0), attack(0), posFloat(0, 0) {}

  Enemy makeNewEnemy();
  void eat_enemy();
  void move_enemy();

};

#endif // Enemy_H