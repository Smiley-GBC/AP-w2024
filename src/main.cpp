#include "raylib.h"
#include "Math.h"

#include <array>

#include <iostream>
using namespace std;

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 800;

constexpr float ENTITY_RADIUS = 25.0f;
constexpr float WAYPOINT_RADIUS = 15.0f;

// Basis for all game objects (Player & Enemy)
struct Entity
{
	Vector2 position;
	float angle;
	float speed;
};

int main()
{
	Entity player;
	player.position = Vector2{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f };
	player.speed = 250.0f;	// 250 pixels per second

	Entity enemy;
	float detectionRadius = 250.0f;

	array<Vector2, 4> waypoints
	{
		Vector2{ SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.2f },
		Vector2{ SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.2f },
		Vector2{ SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.8f },
		Vector2{ SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.8f }
	};

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");
	SetTargetFPS(60);

	float time = 0.0f;
	int current = 0;
	int next = 1;
	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();
		time += dt;

		Vector2 direction = Vector2Zero();
		if (IsKeyDown(KEY_W))
		{
			direction.y -= 1.0f;
		}
		if (IsKeyDown(KEY_S))
		{
			direction.y += 1.0f;
		}
		if (IsKeyDown(KEY_A))
		{
			direction.x -= 1.0f;
		}
		if (IsKeyDown(KEY_D))
		{
			direction.x += 1.0f;
		}
		direction = Normalize(direction);
		player.position = player.position + direction * player.speed * dt;

		Vector2 a = waypoints[current];
		Vector2 b = waypoints[next];
		Vector2 c = Lerp(a, b, time);
		enemy.position = c;

		// Change interval if close to the destination
		if (Distance(b, c) < 10.0f)
		{
			time = 0.0f;
			++current %= waypoints.size();
			++next %= waypoints.size();
		}

		bool playerDetected = CheckCollisionCircles(enemy.position, detectionRadius, player.position, ENTITY_RADIUS);
		Color enemyColorFG = playerDetected ? RED : GREEN;
		Color enemyColorBG = enemyColorFG;
		enemyColorBG.a = 64;

		BeginDrawing();
		ClearBackground(RAYWHITE);
		for (const Vector2& waypoint : waypoints)
			DrawCircleV(waypoint, WAYPOINT_RADIUS, SKYBLUE);
		DrawCircleV(enemy.position, detectionRadius, enemyColorBG);
		DrawCircleV(enemy.position, ENTITY_RADIUS, enemyColorFG);
		DrawCircleV(player.position, ENTITY_RADIUS, BLUE);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
