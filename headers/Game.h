#ifndef GAME_H
#define GAME_H

#include "Enemy.h"
#include "Food.h"
#include "Player.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <curses.h>
#include <iostream>
#include <ncurses.h>
#include <stdexcept>
#include <string>
#include <vector>
#include <thread>

class Game {
public:
  std::string **world;
  std::vector<Food> foods;
  std::vector<Enemy> enemies;
  Player p;
  int max_lines;
  int max_cols;

  int MAX_FOOD_COUNT = 10;
  int MAX_ENEMY_COUNT = 3;
  int MAX_ENEMY_ATTACK = 10;
  int MAX_FOOD_AGE = 20000;
  const int TICK_INTERVAL_MS = 50;

  void tick() {
    // refresh();

    std::this_thread::sleep_for(std::chrono::milliseconds(TICK_INTERVAL_MS));
  }

  void die(const std::string &v) {
    for (int i = 0; i < max_lines; ++i) {
      delete[] world[i];
    }
    delete[] world;

    addstr(v.c_str());
    refresh();
    endwin();
    exit(EXIT_FAILURE);
  }
  const bool testMode = false;

  void draw();

  int normalize(int c_p, int max, int min);
  void clearScreenAndDisplayMessage(const std::string &message);

  void setWin(int lines, int cols) {
    max_lines = lines;
    max_cols = cols;
  };

  void cleanUpWindow(WINDOW *mainwin, const std::string &end_txt) {
    for (int i = 0; i < max_lines; ++i) {
      delete[] world[i];
    }
    delete[] world;
    addstr(end_txt.c_str());
    // delwin(childwin);
    delwin(mainwin);
    endwin();
    refresh();
  };

  int randomInt(int minValue, int maxValue) {
    int range = maxValue - minValue + 1;
    int randomNum = std::rand() % range;

    return minValue + randomNum;
  }

  std::tuple<int, int> randomPlace() {
    int a, b;
    do {
      a = randomInt(0, max_lines - 1);
      b = randomInt(0, max_cols - 1);
    } while (world[a][b] != " ");

    return std::make_tuple(a, b);
  }

private:
  const char *PLAYER_CHAR = "P";
  const char *FOOD_CHAR = "F";
  const char *ENEMY_CHAR = "🕱";
};

#endif