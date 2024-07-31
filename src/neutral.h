#pragma once

#include "raylib.h"

class Ball;

class Neutral
{
public:
    Neutral(int x, int y);

    void Update();
    void Draw() const;

    int GetX() const;
    int GetY() const;
    int GetRadius() const;

private:
    int x;
    int y;
    int radius;
    const Ball* player;
};
