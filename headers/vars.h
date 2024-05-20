
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <curses.h>
#include <iostream>
#include <ncurses.h>
#include <stdexcept>
#include <string>
#include <vector>

class Variables {
public:
  struct Pos {
    int line;
    int col;
  };
  struct Food {
    Pos pos;
    int score;
    int age;
  };
  struct Player {
    Pos pos;
    int level;
    int score;
    bool playing;
    int totalTakeFood;
    int totalTakeFoodInLevel;
  };

  struct Game {
    int max_lines;
    int max_cols;
    Player p;
    std::string **world;
    Food food;
    std::vector<Food> foods;
  };
};