#include "../headers/Food.h"
#include "../headers/Game.h"
#include "../headers/Player.h"
#include "../headers/vars.h"

extern Game g;
Player p;

#define CALCULATE_FOOD_SCORE(level) ((level)*10) // EX : LEVEL 1  ---> score == 10 , attack == 5
#define CALCULATE_FOOD_AGE(level) (g.MAX_FOOD_AGE - ((level - 1) / 1000))

Food Food::makeNewFood() {
  std::tuple<int, int> food_place = g.randomPlace();

  Food food;

  food.pos.line = std::get<0>(food_place);
  food.pos.col = std::get<1>(food_place);
  food.score = CALCULATE_FOOD_SCORE(g.p.level);
  food.age = CALCULATE_FOOD_AGE(g.p.level);
  return food;
}

void Food::eat_food() {
  for (int i = 0; i < g.foods.size(); i++) {
    hideFood(g.foods[i]);

    if (g.foods[i].pos.line == g.p.pos.line &&
        g.foods[i].pos.col == g.p.pos.col) {
      g.p.score += g.foods[i].score;

      g.p.totalTakeFood += 1;
      g.p.totalTakeFoodInLevel += 1;

      g.foods[i] = makeNewFood();
      p.levelUp();
    }
  }
}
void Food::hideFood(Food food) {
  if (g.p.level > 1) {
    food.age -= 1;
    if (food.age <= 0) {
      food = makeNewFood();
    }
  }
}