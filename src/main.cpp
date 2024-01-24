#include "raylib.h"
#include "Math.h"
#include <vector>   // Same as List<> in C#

// TODO -- make movement awesome with Seek behaviour

struct Enemy
{
    Vector2 position{};
    float radius = 75.0f;
    Color color = RED;
    float speed = 300.0f;
};

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;
    Vector2 centre{ screenWidth * 0.5f, screenHeight * 0.5f };
    Vector2 enemy = centre;
    Vector2 player = centre;
    float playerSpeed = 500.0f;
    float playerRadius = 50.0f;
    float enemySpeed = 300.0f;
    float enemyRadius = 75.0f;

    std::vector<Enemy> enemies;
    Enemy enemy1, enemy2, enemy3, enemy4;
    enemy1.position = Vector2{ screenWidth * 0.1f, screenHeight * 0.1f };
    enemy2.position = Vector2{ screenWidth * 0.9f, screenHeight * 0.1f };
    enemy3.position = Vector2{ screenWidth * 0.9f, screenHeight * 0.9f };
    enemy4.position = Vector2{ screenWidth * 0.1f, screenHeight * 0.9f };
    enemies.push_back(enemy1);
    enemies.push_back(enemy2);
    enemies.push_back(enemy3);
    enemies.push_back(enemy4);

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float tt = GetTime();
        float dt = GetFrameTime();
        //float nsin = fabsf(sinf(tt));   // "normalized sin"
        float nsin = 1.0f - (sinf(tt) * 0.25f + 0.75f);
        unsigned char a = nsin * 255.0f;

        Vector2 direction{};
        if (IsKeyDown(KEY_W))
        {
            direction.y = -1.0f;
        }
        if (IsKeyDown(KEY_S))
        {
            direction.y = 1.0f;
        }
        if (IsKeyDown(KEY_A))
        {
            direction.x = -1.0f;
        }
        if (IsKeyDown(KEY_D))
        {
            direction.x = 1.0f;
        }
        direction = Normalize(direction);
        player = player + direction * playerSpeed * dt;

        bool collision = CheckCollisionCircles(enemy, enemyRadius * 3.0f, player, playerRadius);
        Color playerColor = collision ? RED : YELLOW;
        if (collision)
        {
            // AB = B - A
            Vector2 toPlayer = Normalize(player - enemy);
            enemy = enemy + toPlayer * enemySpeed * dt;
        }

        BeginDrawing();
        ClearBackground(GRAY);

        for (int i = 0; i < enemies.size(); i++)
        {
            enemies[i].color.a = a;
            DrawCircleV(enemies[i].position, enemies[i].radius, enemies[i].color);
        }

        DrawCircleV(enemy, enemyRadius, { 255, 0, 0, a });
        DrawCircleV(player, playerRadius, playerColor);
        // Proof of concept:
        //unsigned char a1 = fabsf(sinf(tt)) * 255.0f;
        //unsigned char a2 = (sinf(tt) * 0.5f + 0.5f) * 255.0f;
        //Color enemy1 = { 255, 0, 0, a1 };
        //Color enemy2 = { 255, 0, 0, a2 };
        //DrawCircleV({ screenWidth * 0.25f, screenHeight * 0.5f }, 125.0f, enemy1);
        //DrawCircleV({ screenWidth * 0.75f, screenHeight * 0.5f }, 125.0f, enemy2);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
