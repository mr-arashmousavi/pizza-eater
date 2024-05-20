#ifndef PLAYER_H
#define PLAYER_H

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

class Player {
public:
  Pos pos;
  int level;
  bool playing;
  int totalTakeFoodInLevel;
  int totalTakeFood;
  int score;
  int totalScore;
  int enemyTaked;

  // Constructor
  Player(int l = 1, bool p = true, int ttl = 0, int ttf = 0, int s = 0,
         Pos ppp = Pos(0, 0))
      : level(l), playing(p), totalTakeFoodInLevel(ttl), totalTakeFood(ttf),
        score(s), pos(ppp), enemyTaked(0), totalScore(0) {}

  void levelUp();
  void levelDown();
};

#endif