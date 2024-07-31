#include "ball.h"
#include <raylib.h>
#include "worldDimensions.h"

Ball::Ball()
    : x(2500), y(2500), speedX(5), speedY(5), radius(15), health(100) 
{
}

void Ball::Update()
{
    if (x + radius >= worldWidth && speedX > 0)
    {
        x -= speedX;
    }

    if (x - radius <= 0 && speedX > 0)
    {
        x += speedX;
    }

    if (y + radius >= worldHeight && speedY > 0)
    {
        y -= speedY;
    }

    if (y - radius <= 0 && speedX > 0)
    {
        y += speedY;
    }
}

void Ball::Draw()
{
    DrawCircle(x, y, radius, WHITE);
}

void Ball::HandleInput()
{
    if (IsKeyDown(KEY_W)) y -= speedY;
    if (IsKeyDown(KEY_S)) y += speedY;
    if (IsKeyDown(KEY_A)) x -= speedX;
    if (IsKeyDown(KEY_D)) x += speedX;
}

int Ball::GetX() const { return x; }
int Ball::GetY() const { return y; }
int Ball::GetRadius() const { return radius; }
int Ball::GetHealth() const { return health; }

void Ball::TakeDamage(int damage)
{
    health -= damage;
    if (health < 0) health = 0; 
}
