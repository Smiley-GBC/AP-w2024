#include "raylib.h"
#include "Math.h"

#include <array>
#include <vector>

#include <iostream>
using namespace std;

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 800;

constexpr float ENTITY_RADIUS = 25.0f;
constexpr float WAYPOINT_RADIUS = 15.0f;
constexpr float OBSTACLE_RADIUS = 150.0f;

constexpr Vector2 CENTRE{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f };

// Project circle-position onto line segment, then perform a point-circle collision check with the projected point!
bool LineCircle(Vector2 lineStart, Vector2 lineEnd, Vector2 circlePosition, float circleRadius)
{
	Vector2 nearest = ProjectPointLine(lineStart, lineEnd, circlePosition);
	return DistanceSqr(nearest, circlePosition) <= circleRadius * circleRadius;
	// More optimal to compare squared distance instead of using a more expensive square-root calculation!
}

bool CircleCircle(Vector2 position1, Vector2 position2, float radius1, float radius2, Vector2* mtv = nullptr)
{
	float distance = Distance(position1, position2);
	float radiiSum = radius1 + radius2;
	bool collision = distance <= radiiSum;
	if (collision && mtv != nullptr)
	{
		*mtv = Normalize(position1 - position2) * (radiiSum - distance);
	}
	return collision;
}

// Basis for all game objects (Player & Enemy)
struct Entity
{
	Vector2 position;
	float angle;
	float speed;
};

array<Vector2, 4> waypoints
{
	Vector2{ SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.2f },
	Vector2{ SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.2f },
	Vector2{ SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.8f },
	Vector2{ SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.8f }
};

void Patrol(Entity& entity, float& time, int& current, int& next)
{
	entity.position = entity.position + Normalize(waypoints[next] - entity.position) * entity.speed * GetFrameTime();

	// Change interval if close to the destination
	if (Distance(waypoints[next], entity.position) < 10.0f)
	{
		time = 0.0f;
		++current %= waypoints.size();
		++next %= waypoints.size();
	}
}

// Move to waypoint from which target is visible to viewer (line of sight from viewer to target)
void MoveToVisibility(Entity& viewer/*enemy*/, Entity& target/*players*/)
{
	// Move to line of sight
	float shortestDistance = FLT_MAX;
	size_t nearestIndex = 0;
	for (size_t i = 0; i < waypoints.size(); i++)
	{
		// If there's a line of sight from waypoint to player, see if its the nearest waypoint (to the enemy)
		if (!LineCircle(waypoints[i], target.position, CENTRE, OBSTACLE_RADIUS))
		{
			float waypointDistance = DistanceSqr(waypoints[i], viewer.position);
			if (waypointDistance < shortestDistance)
			{
				shortestDistance = waypointDistance;
				nearestIndex = i;
			}
		}
	}

	Vector2 nearestWaypoint = waypoints[nearestIndex];
	viewer.position = viewer.position + Normalize(nearestWaypoint - viewer.position) * viewer.speed * GetFrameTime();
}

int main()
{
	Entity player;
	player.position = Vector2{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f };
	player.speed = 250.0f;	// 250 pixels per second

	Entity enemy;
	enemy.position = waypoints[0];
	enemy.speed = 200.0f;

	float detectionRadiusFar = 400.0f;
	float detectionRadiusNear = 100.0f;

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");
	SetTargetFPS(60);

	vector<Vector2> projectiles;

	float patrolTime = 0.0f;
	float projectileTime = 0.0f;
	int current = 0;
	int next = 1;
	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();
		patrolTime += dt;

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

		bool playerDetectedFar = CircleCircle(enemy.position, player.position, detectionRadiusFar, ENTITY_RADIUS);
		bool playerDetectedNear = CircleCircle(enemy.position, player.position, detectionRadiusNear, ENTITY_RADIUS);
		
		// Player is visible if there's NOT a collision between the line from enemy to player & the obstacle
		bool playerVisible = !LineCircle(enemy.position, player.position, CENTRE, OBSTACLE_RADIUS);
		
		Color enemyColorFG = playerVisible ? RED : GREEN;
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
					if (projectileTime >= 0.5f)
					{
						projectileTime = 0.0f;
						float x = Random(0.0f, SCREEN_WIDTH - ENTITY_RADIUS);
						float y = Random(0.0f, SCREEN_HEIGHT - ENTITY_RADIUS);
						projectiles.push_back({ x, y });
					}
					projectileTime += dt;
				}
				else
				{
					// Move to player
					enemy.position = enemy.position + Normalize(player.position - enemy.position) * enemy.speed * dt;
				}
			}
			else
			{
				MoveToVisibility(enemy, player);
			}
		}
		else
		{
			Patrol(enemy, patrolTime, current, next);
		}

		Vector2 enemyMTV = Vector2Zero();
		Vector2 playerMTV = Vector2Zero();
		CircleCircle(enemy.position, CENTRE, ENTITY_RADIUS, OBSTACLE_RADIUS, &enemyMTV);
		CircleCircle(player.position, CENTRE, ENTITY_RADIUS, OBSTACLE_RADIUS, &playerMTV);
		enemy.position = enemy.position + enemyMTV;
		player.position = player.position + playerMTV;

		for (const Vector2& projectile : projectiles)
		{
			if (CircleCircle(projectile, player.position, ENTITY_RADIUS, ENTITY_RADIUS))
				return -1;
		}

		BeginDrawing();
		ClearBackground(RAYWHITE);

		for (const Vector2& waypoint : waypoints)
			DrawCircleV(waypoint, WAYPOINT_RADIUS, SKYBLUE);

		for (const Vector2& projectile : projectiles)
		DrawCircleV(projectile, ENTITY_RADIUS, RED);

		DrawCircleV(CENTRE, OBSTACLE_RADIUS, GRAY);
		DrawCircleV(enemy.position, detectionRadiusFar, enemyColorBG);
		DrawCircleV(enemy.position, ENTITY_RADIUS, enemyColorFG);
		DrawCircleV(player.position, ENTITY_RADIUS, BLUE);

		// Visualize line of sight check
		//DrawLineEx(enemy.position, player.position, 5.0f, enemyColorFG);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}

// Move to line of sight
//float shortestDistance = FLT_MAX;
//size_t nearestIndex = 0;
//for (size_t i = 0; i < waypoints.size(); i++)
//{
//	// If there's a line of sight from waypoint to player, see if its the nearest waypoint
//	if (LineCircle(waypoints[i], player.position, CENTRE, OBSTACLE_RADIUS))
//	{
//		float waypointDistance = DistanceSqr(waypoints[i], player.position);
//		if (waypointDistance < shortestDistance)
//		{
//			shortestDistance = waypointDistance;
//			nearestIndex = i;
//		}
//	}
//}
//
//Vector2 nearestWaypoint = waypoints[nearestIndex];
//enemy.position = enemy.position + Normalize(nearestWaypoint - enemy.position) * enemy.speed * dt;
