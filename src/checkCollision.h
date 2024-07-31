#pragma once

class Ball;
class Enemy;
class Friendly;

bool CheckCollision(const Ball &ball, const Enemy &enemy);
bool CheckCollision(const Enemy &enemy1, const Enemy &enemy2);
bool CheckCollisionFriendlyEnemy(const Friendly &friendly, const Enemy &enemy);
