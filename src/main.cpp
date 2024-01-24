#include "raylib.h"
#include "Math.h"

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;
    Vector2 centre{ screenWidth * 0.5f, screenHeight * 0.5f };
    Vector2 player = centre;
    float playerSpeed = 500.0f;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float tt = GetTime();
        float dt = GetFrameTime();
        float nsin = fabsf(sinf(tt));   // "normalized sin"
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

        BeginDrawing();
        ClearBackground(GRAY);

        DrawCircleV(centre, 100.0f, { 255, 0, 0, a });
        DrawCircleV(player, 100.0f, YELLOW);
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
