#include "friendly.h"
#include "ball.h"
#include <cmath>
#include "raylib.h"
#include <vector>

Friendly::Friendly(int x, int y, const Ball* player)
    : x(x), y(y), radius(10), player(player), speed(5), health(100)
{
}

void Friendly::HandleInput()
{
    if (IsKeyDown(KEY_W)) y -= speed;
    if (IsKeyDown(KEY_S)) y += speed;
    if (IsKeyDown(KEY_A)) x -= speed;
    if (IsKeyDown(KEY_D)) x += speed;
}

void Friendly::Update(const Vector2& mousePosition, const std::vector<Friendly>& friendlies)
{
    HandleInput();

    float blendFactor = 0.5f;

    Vector2 playerPosition = { (float)player->GetX(), (float)player->GetY() };
    Vector2 targetPosition = { playerPosition.x * (1.0f - blendFactor) + mousePosition.x * blendFactor,
                                playerPosition.y * (1.0f - blendFactor) + mousePosition.y * blendFactor };

    Vector2 direction = { targetPosition.x - (float)x, targetPosition.y - (float)y };
    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 1.0f)
    {
        direction.x /= distance;
        direction.y /= distance;

        float moveSpeed = 3.0f;
        x += static_cast<int>(direction.x * moveSpeed);
        y += static_cast<int>(direction.y * moveSpeed);
    }

    Vector2 ballPosition = { (float)player->GetX(), (float)player->GetY() };
    Vector2 toBallDirection = { ballPosition.x - (float)x, ballPosition.y - (float)y };
    float distanceToBall = sqrt(toBallDirection.x * toBallDirection.x + toBallDirection.y * toBallDirection.y);

    if (distanceToBall > 70.0f) // layernum[0,1,2...] * 20 + 70
    {
        toBallDirection.x /= distanceToBall;
        toBallDirection.y /= distanceToBall;

        x = static_cast<int>(ballPosition.x - toBallDirection.x * 70.0f);
        y = static_cast<int>(ballPosition.y - toBallDirection.y * 70.0f);
    }

    if (distanceToBall < 50.0f) // layernum[0,1,2...] * 20 + 50
    {
        toBallDirection.x /= distanceToBall;
        toBallDirection.y /= distanceToBall;

        x = static_cast<int>(ballPosition.x - toBallDirection.x * 50.0f);
        y = static_cast<int>(ballPosition.y - toBallDirection.y * 50.0f);
    }


    for (const auto& other : friendlies)
    {
        if (&other != this && CheckCollision(other))
        {
            Vector2 collisionDirection = { (float)x - (float)other.GetX(), (float)y - (float)other.GetY() };
            float collisionDistance = sqrt(collisionDirection.x * collisionDirection.x + collisionDirection.y * collisionDirection.y);

            if (collisionDistance < radius * 2)
            {
                float overlap = radius * 2 - collisionDistance;
                collisionDirection.x /= collisionDistance;
                collisionDirection.y /= collisionDistance;

                x += static_cast<int>(collisionDirection.x * overlap / 2);
                y += static_cast<int>(collisionDirection.y * overlap / 2);
            }
        }
    }
}

bool Friendly::CheckCollision(const Friendly& other) const
{
    Vector2 distance = { (float)x - (float)other.x, (float)y - (float)other.y };
    return sqrt(distance.x * distance.x + distance.y * distance.y) < (radius * 2);
}

void Friendly::Draw() const
{
    DrawCircle(x, y, radius, GREEN);
}

int Friendly::GetX() const { return x; }
int Friendly::GetY() const { return y; }
int Friendly::GetRadius() const { return radius; }
int Friendly::GetHealth() const { return health; }

void Friendly::TakeDamage(int damage)
{
    health -= damage;
    if (health < 0) health = 0;
}
