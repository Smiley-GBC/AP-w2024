#include "raylib.h"
#include "Math.h"

#include <array>

#include <iostream>
using namespace std;

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 800;

int main()
{
	array<Vector2, 4> waypoints
	{
		Vector2{ SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.2f },
		Vector2{ SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.2f },
		Vector2{ SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.8f },
		Vector2{ SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.8f }
	};

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");
	SetTargetFPS(60);
	float r = 20.0f;
	float time = 0.0f;

	int current = 0;
	int next = 1;

	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();
		time += dt;
		Vector2 a = waypoints[current];
		Vector2 b = waypoints[next];
		Vector2 c = Lerp(a, b, time);

		// Change interval if close to the destination
		if (Distance(b, c) < 10.0f)
		{
			time = 0.0f;
			++current %= waypoints.size();
			++next %= waypoints.size();
		}

		BeginDrawing();
		ClearBackground(RAYWHITE);
		for (const Vector2& waypoint : waypoints)
			DrawCircleV(waypoint, r, SKYBLUE);
		DrawCircleV(c, r, BLUE);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
