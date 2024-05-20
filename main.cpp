#include "headers/Enemy.h"
#include "headers/Food.h"
#include "headers/Game.h"
#include "headers/Player.h"
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <curses.h>
#include <iostream>
#include <ncurses.h>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

Food f;
Enemy e;
Game g;
Player pl;

void initGame() {
  g.world = new std::string *[g.max_lines];
  for (int i = 0; i < g.max_lines; ++i) {
    g.world[i] = new std::string[g.max_cols];
    for (int j = 0; j < g.max_cols; ++j) {
      float mm = static_cast<float>(std::rand()) / RAND_MAX;
      if (mm > 0.05) {
        g.world[i][j] = " ";
      } else {
        g.world[i][j] = ".";
      }
    }
  }

  // Initialize player position
  std::tuple<int, int> player_place = g.randomPlace();

  Player player_info;

  player_info.pos.line = std::get<0>(player_place);
  player_info.pos.col = std::get<1>(player_place);

  player_info.level = 1;
  player_info.playing = true;
  player_info.totalTakeFoodInLevel = 0;
  player_info.totalTakeFood = 0;
  player_info.totalScore = 0;
  player_info.enemyTaked = 0;

  g.p = player_info;

  // Initialize food positions
  for (int i = 0; i < g.MAX_FOOD_COUNT; i++) {
    try {

      Food food = f.makeNewFood();

      g.foods.push_back(food);
    } catch (const std::exception &e) {
      std::cerr << "An exception occurred on food creator: " << e.what()
                << std::endl;
    }
  }

  // Initialize enemy positions
  for (int i = 0; i < g.MAX_ENEMY_COUNT; i++) {
    try {

      Enemy enemy = e.makeNewEnemy();

      g.enemies.push_back(enemy);
    } catch (const std::exception &e) {
      std::cerr << "An exception occurred on enemy creator: " << e.what()
                << std::endl;
    }
  }
}

void jump(int ch) {

  int c_line = g.p.pos.line;
  int c_col = g.p.pos.col;

  // printf("%d\n", c_line);
  if (c_line == 00) {
    c_line += 1;

  } else if (c_col == 00) {
    c_col += 1;
  } else {

    if (ch == 'w' && g.world[g.p.pos.line - 1][g.p.pos.col] == " ") {
      c_line -= 1;
    }

    if (ch == 's' && g.world[g.p.pos.line + 1][g.p.pos.col] == " ") {
      c_line += 1;
    }

    if (ch == 'a' && g.world[g.p.pos.line][g.p.pos.col - 1] == " ") {
      c_col -= 1;
    }

    if (ch == 'd' && g.world[g.p.pos.line][g.p.pos.col + 1] == " ") {
      c_col += 1;
    }
  }

  g.p.pos.line = g.normalize(c_line, g.max_lines - 2, 0);
  g.p.pos.col = g.normalize(c_col, g.max_cols - 2, 0);
}

int main(void) {
  setlocale(LC_ALL, ""); // Enable wide character support

  std::srand(static_cast<unsigned int>(time(nullptr)));
  int ch;
  initscr();
  WINDOW *mainwin, *childwin;

  g.max_lines = LINES;
  g.max_cols = COLS;

  if (!has_colors() || start_color() != OK)
    g.die("Terminal failed to start colors");

  if (!can_change_color()) {
    g.die("Error: Terminal does not support Unicode");
  }

  init_pair(1, COLOR_BLACK, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  init_pair(3, COLOR_BLUE, COLOR_BLACK);
  curs_set(0);
  nodelay(stdscr, TRUE);

  if ((mainwin = initscr()) == NULL) {
    g.die("Error initialising ncurses.\n");
  }

  keypad(mainwin, TRUE);

  g.setWin(LINES, COLS);

  initGame();

  while (g.p.playing) {
    ch = getch();
    switch (ch) {
    case 'w':
    case 'a':
    case 's':
    case 'd':
      jump(ch);
      break;
    case 'q':
      g.p.playing = false;
      break;
    }
    f.eat_food();
    e.eat_enemy();
    e.move_enemy();
    g.tick();

    g.draw();
  }
  g.cleanUpWindow(mainwin, "The End!");

  return EXIT_SUCCESS;
}
