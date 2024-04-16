#include "raylib.h"
#include "Math.h"
#include <array>

using namespace std;
constexpr float SCREEN_WIDTH = 1280.0f;
constexpr float SCREEN_HEIGHT = 720.0f;

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

bool LineCircle(Vector2 A, Vector2 B, Vector2 P, float r)
{
    Vector2 proj = ProjectPointLine(A, B, P);   // Find circle's position on line segment
    return Distance(proj, P) <= r;              // Check if projection is less than circle radius (touching if so)!
}

// mtv points from 2 to 1
bool CircleCircle(Vector2 p1, float r1, Vector2 p2, float r2, Vector2* mtv = nullptr)
{
    Vector2 direction = p1 - p2;
    float distance = Length(direction);
    if (distance <= r1 + r2 && mtv != nullptr)
    {
        float penetration = (r1 + r2) - distance;
        *mtv = Normalize(direction) * penetration;
    }
    return distance <= r1 + r2;
}

bool IsVisible(Vector2 viewer, float viewDistance, Vector2 target, float targetRadius, Vector2 obstacle, float obstacleRadius)
{
    Vector2 toTarget = Normalize(target - viewer);
    Vector2 A = viewer;
    Vector2 B = viewer + toTarget * viewDistance;

    bool obstacleHit = LineCircle(A, B, obstacle, obstacleRadius);
    bool targetHit = LineCircle(A, B, viewer, targetRadius);

    bool hasLoS = targetHit;
    if (targetHit && obstacleHit)
        hasLoS = Distance(viewer, target) <= Distance(viewer, obstacle);
    return hasLoS;
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");
    SetTargetFPS(60);

    constexpr float playerRadius = 35.0f;
    constexpr float enemyRadius = 35.0f;
    constexpr float waypointRadius = 25.0f;
    constexpr float obstacleRadius = 250.0f;

    Vector2 playerPosition{ SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.75f };
    float detectionRadius = 750.0f;
    float playerSpeed = 500.0f;
    
    Vector2 enemyPosition{ SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT * 0.25f };
    Vector2 enemyVelocity{ Random(-10.0f, 10.0f), Random(-10.0f, 10.0f) };

    Vector2 obstaclePosition{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f };

    // Index of the waypoint we're currently seeking
    size_t waypoint = 0;
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        Vector2 playerMoveDirection{};
        if (IsKeyDown(KEY_W))
        {
            playerMoveDirection.y -= 1.0f;
        }
        if (IsKeyDown(KEY_S))
        {
            playerMoveDirection.y += 1.0f;
        }
        if (IsKeyDown(KEY_A))
        {
            playerMoveDirection.x -= 1.0f;
        }
        if (IsKeyDown(KEY_D))
        {
            playerMoveDirection.x += 1.0f;
        }
        playerMoveDirection = Normalize(playerMoveDirection);
        playerPosition = playerPosition + playerMoveDirection * playerSpeed * dt;
        Vector2 toPlayer = Normalize(playerPosition - enemyPosition);

        bool playerDetected = CheckCollisionCircles(playerPosition, playerRadius, enemyPosition, detectionRadius);
        bool playerVisible = false;
        bool playerNear = false;
        if (playerDetected)
        {
            playerVisible = IsVisible(enemyPosition, detectionRadius, playerPosition, playerRadius, obstaclePosition, obstacleRadius);
            if (playerVisible)
            {
                playerNear = Distance(playerPosition, enemyPosition) <= detectionRadius * 0.5f;
                if (playerNear)
                {
                    // Perform attack
                }
                else
                {
                    // Move to attack range
                }
            }
            else
            {
                // Move to LoS
                // (Seek nearest waypoint with LoS to player)
            }
        }
        else
        {
            // Patrol
            size_t previous = waypoint == 0 ? waypoints.size() - 1 : waypoint - 1;
            Vector2 proj = ProjectPointLine(waypoints[previous], waypoints[waypoint], enemyPosition);
            if (CheckCollisionCircles(proj, enemyRadius, waypoints[waypoint], waypointRadius))
                ++waypoint %= waypoints.size();

            enemyVelocity = enemyVelocity + Seek(waypoints[waypoint], enemyPosition, enemyVelocity, 1000.0f) * dt;
            enemyPosition = enemyPosition + enemyVelocity * dt;
        }

        Vector2 mtv{};
        CircleCircle(playerPosition, playerRadius, obstaclePosition, obstacleRadius, &mtv);
        playerPosition = playerPosition + mtv;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (size_t i = 0; i < waypoints.size(); i++)
        {
            Vector2 current = waypoints[i];
            Vector2 next = waypoints[(i + 1) % waypoints.size()];
            DrawLineEx(current, next, 5.0f, BLUE);
            DrawCircleV(current, waypointRadius, SKYBLUE);
        }

        Color detection = playerVisible ? RED : GREEN;
        detection.a = 64;
        DrawCircleV(obstaclePosition, obstacleRadius, GRAY);
        DrawCircleV(playerPosition, playerRadius, GREEN);
        DrawCircleV(enemyPosition, enemyRadius, playerVisible ? RED : GREEN);
        DrawCircleV(enemyPosition, detectionRadius, detection);
        DrawLineV(enemyPosition, enemyPosition + toPlayer * detectionRadius, playerVisible ? RED : GREEN);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
