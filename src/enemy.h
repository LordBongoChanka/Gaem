#pragma once

class Ball; 

class Enemy
{
public:
    Enemy(int x, int y);
    void Update(const Ball& ball);
    void Draw() const;
    void SetTarget(const Ball& ball);
    int GetX() const;
    int GetY() const;
    int GetRadius() const;
    void HandleCollision(Enemy& other);
    int GetHealth() const;
    void TakeDamage(int damage);

private:
    int x;
    int y;
    int speedX;
    int speedY;
    int radius;
    int health;
    const Ball* target; 

    bool CheckCollision(const Enemy& other) const;
};
