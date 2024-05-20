#include "../headers/Game.h"
#include "../headers/Food.h"
#include "../headers/Player.h"

Food food;
Enemy enemy;

int Game::normalize(int c_p, int max, int min) {
  if (c_p >= max) {
    return max -1 ;
  }

  if (c_p <= min) {
    return min;
  }
  return c_p;
}

void Game::clearScreenAndDisplayMessage(const std::string &message) {
  clear();
  mvprintw(max_lines / 2, max_cols / 2 - message.size() / 2, "%s",
           message.c_str());

  for (int i = 0; i < foods.size(); i++) {
    p.totalTakeFood += 1;
    p.totalTakeFoodInLevel += 1;
    foods[i] = food.makeNewFood();
  }

  if (p.playing && p.level > 1 || testMode) {
    for (int i = 0; i < enemies.size(); i++) {
      enemies[i] = enemy.makeNewEnemy();
    }
  }

  refresh();
  napms(2000);
}

void Game::draw() {

  // draw map
  for (int i = 0; i < max_lines; i++) {
    for (int j = 0; j < max_cols; j++) {
      mvprintw(i, j, "%s", world[i][j].c_str());
    }
  }

  // draw food
  for (int i = 0; i < foods.size(); i++) {
    mvprintw(foods[i].pos.line, foods[i].pos.col, "%s", FOOD_CHAR);
  }

  // draw enemy
  if (p.playing && p.level > 1 || testMode) {
    for (int i = 0; i < enemies.size(); i++) {
      mvprintw(enemies[i].pos.line, enemies[i].pos.col, "%s", ENEMY_CHAR);
    }
  }

  // draw player
  mvprintw(p.pos.line, p.pos.col, "%s", PLAYER_CHAR);

  // draw alerts
  mvprintw(0, 0, "Level : %d ", p.level);
  mvprintw(1, 0, "Score : %d ", p.score);

  refresh();
}