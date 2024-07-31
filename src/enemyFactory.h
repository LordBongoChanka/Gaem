#pragma once

#include "enemy.h"
#include "ball.h"
#include <vector>

class EnemyFactory {
public:
    static void SpawnEnemies(std::vector<Enemy> &enemies, int &totalEnemies, const Ball &ball);

private:
    static int GetRandomNumber(int min, int max);
};
