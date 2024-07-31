#include "enemyFactory.h"
#include "worldDimensions.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>

void EnemyFactory::SpawnEnemies(std::vector<Enemy> &enemies, int &totalEnemies, const Ball &ball) {
    const int MAX_ENEMIES = 200; 
    const int MAX_NEW_ENEMIES = 5; 

    if (totalEnemies >= MAX_ENEMIES) return;

    int enemiesToSpawn = GetRandomNumber(1, MAX_NEW_ENEMIES);

    enemiesToSpawn = std::min(enemiesToSpawn, MAX_ENEMIES - totalEnemies);

    int groupCenterX, groupCenterY;
    do {
        groupCenterX = rand() % worldWidth;
        groupCenterY = rand() % worldHeight;
    } while (abs(groupCenterX - ball.GetX()) < 600 && abs(groupCenterY - ball.GetY()) < 600);

    for (int i = 0; i < enemiesToSpawn; ++i) {
        int spawnX = groupCenterX + (rand() % 31 - 15);
        int spawnY = groupCenterY + (rand() % 31 - 15);

        std::cout << "New enemy spawned at: " << spawnX << ";" << spawnY << std::endl;

        Enemy newEnemy(spawnX, spawnY);
        newEnemy.SetTarget(ball);
        enemies.push_back(newEnemy);
    }

    totalEnemies += enemiesToSpawn;
}

int EnemyFactory::GetRandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}
