#pragma once

#include "ball.h"
#include "raylib.h"
#include <vector>

class Friendly {
public:
    Friendly(int x, int y, const Ball* player);

    void HandleInput();
    void Update(const Vector2& mousePosition, const std::vector<Friendly>& friendlies);
    void Draw() const;

    int GetX() const;
    int GetY() const;
    int GetRadius() const;
    int GetHealth() const;
    void TakeDamage(int damage);

private:
    int x, y;
    int radius;
    const Ball* player;
    int speed;
    int health; 

    bool CheckCollision(const Friendly& other) const;
};
