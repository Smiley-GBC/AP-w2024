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
	array<Vector2, 4> waypoints
	{
		Vector2{ SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.2f },
		Vector2{ SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.2f },
		Vector2{ SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.8f },
		Vector2{ SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.8f }
	};

	Entity player;
	player.position = Vector2{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f };
	player.speed = 250.0f;	// 250 pixels per second

	Entity enemy;
	enemy.position = waypoints[0];
	enemy.speed = 200.0f;

	float detectionRadiusFar = 250.0f;
	float detectionRadiusNear = 100.0f;

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

		bool playerDetectedFar = CheckCollisionCircles(enemy.position, detectionRadiusFar, player.position, ENTITY_RADIUS);
		bool playerDetectedNear = CheckCollisionCircles(enemy.position, detectionRadiusNear, player.position, ENTITY_RADIUS);
		bool playerVisible = false;
		
		Color enemyColorFG = playerDetectedFar ? RED : GREEN;
		Color enemyColorBG = enemyColorFG;
		enemyColorBG.a = 64;

		// Within detection radius?
		if (playerDetectedFar)
		{
			// Has line of sight?
			if (playerVisible)
			{
				if (playerDetectedNear)
				{
					// Attack player
				}
				else
				{
					// Move to player
				}
			}
			else
			{
				// Move to line of sight
			}
		}
		else
		{
			// Patrol
			enemy.position = enemy.position + Normalize(waypoints[next] - waypoints[current]) * enemy.speed * dt;

			// Change interval if close to the destination
			if (Distance(waypoints[next], enemy.position) < 10.0f)
			{
				time = 0.0f;
				++current %= waypoints.size();
				++next %= waypoints.size();
			}
		}

		BeginDrawing();
		ClearBackground(RAYWHITE);
		for (const Vector2& waypoint : waypoints)
			DrawCircleV(waypoint, WAYPOINT_RADIUS, SKYBLUE);
		DrawCircleV(enemy.position, detectionRadiusFar, enemyColorBG);
		DrawCircleV(enemy.position, ENTITY_RADIUS, enemyColorFG);
		DrawCircleV(player.position, ENTITY_RADIUS, BLUE);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
