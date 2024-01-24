#include "raylib.h"
#include "Math.h"
#include <vector>   // Same as List<> in C#

const int screenWidth = 1280;
const int screenHeight = 720;

// TODO -- make movement awesome with Seek behaviour
struct Enemy
{
    Vector2 position{};
    float radius = 75.0f;
    Color color = RED;
    float speed = 300.0f;

    static void Create()
    {
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
            // enemy.radius is the current enemy's radius. Enemy::baseRadius is the radius common to all enemies
            enemies[i].radius = baseRadius + Random(-25.0f, 25.0f);

            // enemy.speed is the current enemy's speed. Enemy::baseSpeed is the speed common to all enemies
            enemies[i].speed = baseSpeed + Random(-250.0f, 250.0f);
        }
    }

    static void Update(Vector2 targetPosition, float targetRadius, float dt)
    {
        for (int i = 0; i < enemies.size(); i++)
        {
            enemies[i].Move(targetPosition, targetRadius, dt);
        }
    }

    static void Draw(unsigned char a)
    {
        for (int i = 0; i < enemies.size(); i++)
        {
            enemies[i].color.a = a;
            DrawCircleV(enemies[i].position, enemies[i].radius, enemies[i].color);
        }
    }

    void Move(Vector2 targetPosition, float targetRadius, float dt)
    {
        bool collision = CheckCollisionCircles(position, radius * 3.0f, targetPosition, targetRadius);
        if (collision)
        {
            // AB = B - A
            position = position + Normalize(targetPosition - position) * speed * dt;
        }
    }

    // When used within an object, "static" means "common to all objects" (memory sharing).
    // The value of baseRadius and baseSpeed will be shared across all enemies.

    // When we say "static float n;" inside an object, we *declare* a static member
    static float baseRadius;
    static float baseSpeed;
    static std::vector<Enemy> enemies;
};

// We still need to *define* each static member otherwise we get linker errors.
// You can do so with the "scope-resolution" operator which is the ::
float Enemy::baseRadius = 50.0f;
float Enemy::baseSpeed = 250.0f;
std::vector<Enemy> Enemy::enemies;

// ie we have multiply baseRadius members so we "resolve the scope" of the class:
//struct Player
//{
//    static float baseRadius;
//};
//
//float Player::baseRadius = 50.0f;

int main()
{
    Vector2 centre{ screenWidth * 0.5f, screenHeight * 0.5f };

    Vector2 player = centre;
    float playerSpeed = 500.0f;
    float playerRadius = 50.0f;

    Enemy::Create();
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
        Enemy::Update(player, playerRadius, dt);

        BeginDrawing();
        ClearBackground(GRAY);
        Enemy::Draw(a);
        DrawCircleV(player, playerRadius, YELLOW);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
