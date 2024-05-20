#include "../headers/Enemy.h"
#include "../headers/Game.h"
#include <cstdio>

extern Game g;
extern Player p;

#define CALCULATE_ENEMY_ATTACK(level)                                          \
  ((level * 10) / 2) // EX : L : 1 Attack : 5

Enemy Enemy::makeNewEnemy() {
  std::tuple<int, int> enemy_place = g.randomPlace();

  Enemy enemy;

  enemy.pos.line = std::get<0>(enemy_place);
  enemy.pos.col = std::get<1>(enemy_place);
  enemy.posFloat.line = std::get<0>(enemy_place);
  enemy.posFloat.col = std::get<1>(enemy_place);
  enemy.attack = CALCULATE_ENEMY_ATTACK(g.p.level);
  return enemy;
}

void Enemy::eat_enemy() {
  if (g.p.level > 1 || g.testMode) {
    for (int i = 0; i < g.enemies.size(); i++) {

      if (g.enemies[i].pos.line == g.p.pos.line &&
          g.enemies[i].pos.col == g.p.pos.col) {

        g.p.enemyTaked += 1;
        g.p.score -= g.enemies[i].attack;

        g.enemies[i] = makeNewEnemy();
        p.levelDown();
      }
    }
  }
}

void Enemy::move_enemy() {
  if (g.p.level > 2 || g.testMode) {
    for (int i = 0; i < g.enemies.size(); i++) {

      Player current_player = g.p;
      Enemy current_enemy = g.enemies[i];

      float mm = static_cast<float>(std::rand()) / RAND_MAX;
      float new_line = current_enemy.posFloat.line;
      float new_col = current_enemy.posFloat.col;
      // printf("%f\n", mm);
      float speed = 0.01 + (0.05 * current_player.level);

      // if (speed < 0.02) {
      //   speed = 0.02;
      // }

        if (current_enemy.pos.line > current_player.pos.line) {
          new_line -= speed;
        }
        if (current_enemy.pos.col > current_player.pos.col) {
          new_col -= speed;
        }
        if (current_enemy.pos.line < current_player.pos.line) {
          new_line += speed;
        }
        if (current_enemy.pos.col < current_player.pos.col) {
          new_col += speed;
        }

        Enemy new_enemy;
        new_enemy.attack = current_enemy.attack;

        new_enemy.posFloat.line = new_line;
        new_enemy.posFloat.col = new_col;

        new_enemy.pos.line = g.normalize(new_enemy.posFloat.line, g.max_lines - 1, 0);
        new_enemy.pos.col = g.normalize(new_enemy.posFloat.col, g.max_cols - 1, 0);
        g.enemies[i] = new_enemy;
    }
  }
}