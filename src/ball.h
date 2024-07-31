#pragma once

class Ball
{
public:
    Ball();
    void Update();
    void Draw();
    void HandleInput();

    int GetX() const;
    int GetY() const;
    int GetRadius() const;
    int GetHealth() const; 
    void TakeDamage(int damage);

private:
    int x;
    int y;
    int speedX;
    int speedY;
    int radius;
    int health; 
};
