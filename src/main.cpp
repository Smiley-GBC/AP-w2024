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

    void Move(Vector2 targetPosition, float targetRadius, float dt)
    {
        bool collision = CheckCollisionCircles(position, radius * 3.0f, targetPosition, targetRadius);
        if (collision)
        {
            // AB = B - A
            position = position + Normalize(targetPosition - position) * speed * dt;
        }
    }

    // When used within an object, "static" means "common to all objects"
    // So the value of baseRadius and baseSpeed will be shared across all enemies
    static float baseRadius;
    static float baseSpeed;
};

float Enemy::baseRadius = 50.0f;
float Enemy::baseSpeed = 250.0f;

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;
    Vector2 centre{ screenWidth * 0.5f, screenHeight * 0.5f };

    Vector2 player = centre;
    float playerSpeed = 500.0f;
    float playerRadius = 50.0f;


    std::vector<Enemy> enemies;
    
    // {} creates an empty object, so we're adding 4 empty enemies to our list
    enemies.push_back({});
    enemies.push_back({});
    enemies.push_back({});
    enemies.push_back({});

    enemies[0].position = Vector2{ screenWidth * 0.1f, screenHeight * 0.1f };
    enemies[1].position = Vector2{ screenWidth * 0.9f, screenHeight * 0.1f };
    enemies[2].position = Vector2{ screenWidth * 0.9f, screenHeight * 0.9f };
    enemies[3].position = Vector2{ screenWidth * 0.1f, screenHeight * 0.9f };

    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].radius = Enemy::baseRadius + Random(-25.0f, 25.0f);
        enemies[i].speed = Enemy::baseSpeed + Random(-250.0f, 250.0f);
    }

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float tt = GetTime();
        float dt = GetFrameTime();
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

        for (int i = 0; i < enemies.size(); i++)
        {
            enemies[i].Move(player, playerRadius, dt);
        }

        BeginDrawing();
        ClearBackground(GRAY);

        for (int i = 0; i < enemies.size(); i++)
        {
            enemies[i].color.a = a;
            DrawCircleV(enemies[i].position, enemies[i].radius, enemies[i].color);
        }

        DrawCircleV(player, playerRadius, YELLOW);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
