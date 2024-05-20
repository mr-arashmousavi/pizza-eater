#include "../headers/Player.h"
#include "../headers/Food.h"
#include "../headers/Game.h"

extern Game g;

void Player::levelUp() {
  if (g.p.playing && g.p.score >= 100) {
    Player current_player = g.p;
    current_player.level += 1;
    current_player.totalScore = current_player.score;
    current_player.score = 0;
    current_player.totalTakeFoodInLevel = 0;

    g.p = current_player;

    g.clearScreenAndDisplayMessage("WOW !! You Level Up");
    g.draw();
  }
}

void Player::levelDown() {
  if (g.p.playing && g.p.score <= 0) {
    if (g.p.level > 1) {
      g.p.enemyTaked += 1;
      g.p.level -= 1;
      g.clearScreenAndDisplayMessage("You are killed!");
      g.p.score = 0;
    } else {
      g.clearScreenAndDisplayMessage("Yo lose");
      g.die("Game Over !!!!!!!!");
    }
  }
}