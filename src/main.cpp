#include <iostream>
#include <raylib.h>
#include <ctime>
#include <vector>
#include "ball.h"
#include "enemy.h"
#include "friendly.h"
#include "neutral.h"
#include "checkCollision.h"
#include "worldDimensions.h"
#include "cameraUtils.h"
#include "enemyFactory.h"

const float SPAWN_INTERVAL = 0.1f;

int main()
{
    const Color darkGreen = {20, 160, 133, 255};
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    if (!IsWindowReady()) {
        std::cerr << "Failed to initialize window." << std::endl;
        return 1;
    }
    SetTargetFPS(60);

    Ball ball;
    std::vector<Enemy> enemies;
    std::vector<Friendly> friendlies;
    std::vector<Neutral> neutrals; 
    int totalEnemies = 0;
    float spawnTimer = 0.0f;
    float spacebarHoldTime = 0.0f;

    srand(static_cast<unsigned int>(time(nullptr)));

    Camera2D camera = { 0 };
    camera.target = { (float)ball.GetX(), (float)ball.GetY() };
    camera.offset = { (float)screenWidth / 2, (float)screenHeight / 2 }; 
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    for (int i = 0; i < 5; ++i) {
        int x = ball.GetX() + (rand() % 61 - 30);
        int y = ball.GetY() + (rand() % 61 - 30);
        friendlies.emplace_back(x, y, &ball);
    }

    std::cout << "Game loop started." << std::endl;

        while (!WindowShouldClose())
        {
            ball.HandleInput();
            ball.Update();

            spawnTimer += GetFrameTime();
            if (spawnTimer >= SPAWN_INTERVAL)
            {
                EnemyFactory::SpawnEnemies(enemies, totalEnemies, ball);
                spawnTimer = 0.0f;
            }

            Vector2 mousePosition = GetMousePosition();
            Vector2 adjustedMousePosition = {
                mousePosition.x + camera.target.x - screenWidth / 2.0f,
                mousePosition.y + camera.target.y - screenHeight / 2.0f
            };

            for (auto &enemy : enemies)
            {
                enemy.Update(ball);
            }

            for (auto &friendly : friendlies)
            {
                friendly.Update(adjustedMousePosition, friendlies);
            }

            for (size_t i = 0; i < enemies.size(); ++i)
            {
                for (size_t j = i + 1; j < enemies.size(); ++j)
                {
                    enemies[i].HandleCollision(enemies[j]);
                }
            }

                for (auto it = friendlies.begin(); it != friendlies.end();)
            {
                bool friendlyRemoved = false;
                for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();)
                {
                    if (CheckCollisionFriendlyEnemy(*it, *enemyIt))
                    {
                        it->TakeDamage(10);
                        enemyIt->TakeDamage(10);

                        if (it->GetHealth() <= 0)
                        {
                            it = friendlies.erase(it);
                            friendlyRemoved = true;
                            break;
                        }

                        if (enemyIt->GetHealth() <= 0)
                        {
                            Neutral newNeutral(enemyIt->GetX(), enemyIt->GetY());
                            neutrals.push_back(newNeutral);

                            enemyIt = enemies.erase(enemyIt);
                            totalEnemies--;
                        }
                        else
                        {
                            ++enemyIt;
                        }
                    }
                    else
                    {
                        ++enemyIt;
                    }
                }

                if (!friendlyRemoved)
                {
                    ++it;
                }
            }

            if (IsKeyDown(KEY_SPACE))
            {
                spacebarHoldTime += GetFrameTime();
                if (spacebarHoldTime >= 2.0f && !neutrals.empty())
                {
                    Neutral neutralToTransform = neutrals.back();
                    neutrals.pop_back();
                    friendlies.emplace_back(neutralToTransform.GetX(), neutralToTransform.GetY(), &ball);
                    spacebarHoldTime = 0.0f;
                    totalEnemies--; 
                    std::cout << "Neutral transformed into friendly at (" << neutralToTransform.GetX() << ", " << neutralToTransform.GetY() << ")" << std::endl;
                }
            }
            else
            {
                spacebarHoldTime = 0.0f;
            }

            camera.target = { (float)ball.GetX(), (float)ball.GetY() };
            UpdateCamera(camera, worldWidth, worldHeight);

            BeginDrawing();
            ClearBackground(darkGreen);

            BeginMode2D(camera); 
            ball.Draw();
            for (const auto &enemy : enemies)
            {
                enemy.Draw();
            }
            for (const auto &friendly : friendlies)
            {
                friendly.Draw();
            }
            for (const auto &neutral : neutrals)
            {
                neutral.Draw();
            }
            EndMode2D(); 

            std::string positionText = "Player Position: X = " + std::to_string(ball.GetX()) + " Y = " + std::to_string(ball.GetY());
            std::string healthText = "Ball Health: " + std::to_string(ball.GetHealth());
            DrawText(positionText.c_str(), 10, 10, 20, WHITE);
            DrawText(healthText.c_str(), 10, 30, 20, WHITE);

            EndDrawing();
        }


    CloseWindow();
    return 0;
}
