#include "checkCollision.h"
#include "ball.h"
#include "enemy.h"
#include <cmath>
#include "friendly.h"

bool CheckCollision(const Ball &ball, const Enemy &enemy) {
    int dx = ball.GetX() - enemy.GetX();
    int dy = ball.GetY() - enemy.GetY();
    int distance = sqrt(dx * dx + dy * dy);

    return distance < (ball.GetRadius() + enemy.GetRadius());
}

bool CheckCollisionFriendlyEnemy(const Friendly &friendly, const Enemy &enemy) {
    int dx = friendly.GetX() - enemy.GetX();
    int dy = friendly.GetY() - enemy.GetY();
    int distance = sqrt(dx * dx + dy * dy);

    return distance < (friendly.GetRadius() + enemy.GetRadius());
}