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
    size_t waypointIndex = 0;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        if (CheckCollisionCircles(position, AI_RADIUS, waypoints[waypointIndex], WAYPOINT_RADIUS))
            ++waypointIndex %= waypoints.size();

        velocity = velocity + Seek(waypoints[waypointIndex], position, velocity, 1000.0f) * dt;
        position = position + velocity * dt;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (Vector2 waypoint : waypoints)
        {
            DrawCircleV(waypoint, WAYPOINT_RADIUS, SKYBLUE);
        }

        DrawCircleV(position, AI_RADIUS, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
