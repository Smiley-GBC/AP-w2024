#include "raylib.h"
#include "Math.h"
#include <array>

using namespace std;
constexpr float SCREEN_WIDTH = 1280.0f;
constexpr float SCREEN_HEIGHT = 720.0f;


constexpr float AI_RADIUS = 35.0f;
constexpr float WAYPOINT_RADIUS = 25.0f;
array<Vector2, 4> waypoints
{
    Vector2{ SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.25f },   // top left
    Vector2{ SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT * 0.25f },   // top right
    Vector2{ SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT * 0.75f },   // bot right
    Vector2{ SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.75f },   // bot left
};

Vector2 Seek(Vector2 target, Vector2 position, Vector2 velocity, float speed)
{
    return Normalize(target - position) * speed - velocity;
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");
    SetTargetFPS(60);

    float radius = 25.0f;
    Vector2 position{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f };
    Vector2 velocity{ Random(-10.0f, 10.0f), Random(-10.0f, 10.0f) };

    // Index of the waypoint we're currently seeking
    size_t waypoint = 0;
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        size_t previous = waypoint == 0 ? waypoints.size() - 1 : waypoint - 1;
        Vector2 proj = ProjectPointLine(waypoints[previous], waypoints[waypoint], position);

        if (CheckCollisionCircles(position, AI_RADIUS, waypoints[waypoint], WAYPOINT_RADIUS))
            ++waypoint %= waypoints.size();

        velocity = velocity + Seek(waypoints[waypoint], position, velocity, 1000.0f) * dt;
        position = position + velocity * dt;

        BeginDrawing();
        ClearBackground(RAYWHITE);


        for (size_t i = 0; i < waypoints.size(); i++)
        {
            Vector2 current = waypoints[i];
            Vector2 next = waypoints[(i + 1) % waypoints.size()];
            DrawLineEx(current, next, 5.0f, BLUE);
            DrawCircleV(current, WAYPOINT_RADIUS, SKYBLUE);
        }

        DrawCircleV(position, AI_RADIUS, RED);
        DrawCircleV(proj, AI_RADIUS, BLUE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
