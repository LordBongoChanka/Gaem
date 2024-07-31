#include "enemy.h"
#include "ball.h"
#include <raylib.h>
#include <cmath>

Enemy::Enemy(int x, int y)
    : x(x), y(y), speedX(3), speedY(3), radius(15), health(100), target(nullptr)
{
}

void Enemy::SetTarget(const Ball &ball)
{
    target = &ball;
}

void Enemy::Update(const Ball &ball)
{
    if (target != nullptr) {
        float dx = target->GetX() - x;
        float dy = target->GetY() - y;
        float distance = sqrt(dx * dx + dy * dy);

        if (distance < 200.0f) {
            float moveX = (dx / distance) * speedX;
            float moveY = (dy / distance) * speedY;

            x += moveX;
            y += moveY;
        }
    }
}

void Enemy::Draw() const
{
    DrawCircle(x, y, radius, RED);
}

int Enemy::GetX() const { return x; }
int Enemy::GetY() const { return y; }
int Enemy::GetRadius() const { return radius; }
int Enemy::GetHealth() const { return health; }

void Enemy::TakeDamage(int damage)
{
    health -= damage;
    if (health < 0) health = 0;
}

void Enemy::HandleCollision(Enemy &other)
{
    float dx = x - other.GetX();
    float dy = y - other.GetY();
    float distance = sqrt(dx * dx + dy * dy);
    float overlap = (radius + other.GetRadius()) - distance;

    if (overlap > 0) {
        float displacementX = (dx / distance) * (overlap / 2);
        float displacementY = (dy / distance) * (overlap / 2);

        x += displacementX;
        y += displacementY;

        other.x -= displacementX;
        other.y -= displacementY;
    }
}
