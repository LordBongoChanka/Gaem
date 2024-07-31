#include "neutral.h"

Neutral::Neutral(int x, int y)
    : x(x), y(y), radius(15)
{
}

void Neutral::Draw() const
{
    DrawCircle(x, y, radius, GRAY);
}

int Neutral::GetX() const { return x; } 
int Neutral::GetY() const { return y; } 
int Neutral::GetRadius() const { return radius; }

