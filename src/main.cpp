#include "raylib.h"
#include "Math.h"

Vector2 Seek(Vector2 target, Vector2 position, Vector2 velocity, float speed)
{
    return Normalize(target - position) * speed - velocity;
}

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    float radius = 25.0f;
    Vector2 position{ screenWidth * 0.5f, screenHeight * 0.5f };
    Vector2 velocity{ Random(-10.0f, 10.0f), Random(-10.0f, 10.0f) };

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        Vector2 mouse = GetMousePosition();
        velocity = velocity + Seek(mouse, position, velocity, 1000.0f) * dt;
        position = position + velocity * dt;

        if (CheckCollisionPointCircle(mouse, position, radius))
            break;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Don't let the circle touch the cursor!", 10, 10, 20, RED);
        DrawCircleV(position, radius, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
