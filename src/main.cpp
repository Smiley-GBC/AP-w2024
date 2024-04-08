#include "raylib.h"
#include "Math.h"
#include <vector>

#include <iostream>
using namespace std;

constexpr float SCREEN_WIDTH = 1280.0f;
constexpr float SCREEN_HEIGHT = 720.0f;

// Project circle-position onto line segment, then perform a point-circle collision check with the projected point!
bool LineCircle(Vector2 lineStart, Vector2 lineEnd, Vector2 circlePosition, float circleRadius)
{
    Vector2 nearest = ProjectPointLine(lineStart, lineEnd, circlePosition);
    return DistanceSqr(nearest, circlePosition) <= circleRadius * circleRadius;
    // More optimal to compare squared distance instead of using a more expensive square-root calculation!
}

using byte = unsigned char;

//constexpr int LAYER_PLAYER = 1;
//constexpr int LAYER_TARGET = 2;
//constexpr int LAYER_OBSTACLE = 3;
//constexpr int LAYER_ALL = 4;

// TODO -- figure out how to actually use bitmasking to achieve this xD
constexpr int LAYER_ALL = 1;
constexpr int LAYER_IGNORE_RAYCAST = 2;

struct Entity
{
	Vector2 position;
	Vector2 direction;
	float radius;
	int layer;
};

// If hit, write the position of the object to the hit parameter
bool RayCast(const Entity& caster, const std::vector<Entity>& objects, Vector2& hitPosition, float viewDistance = FLT_MAX)
{
	Vector2 lineStart = caster.position;
	Vector2 lineEnd = caster.position + caster.direction * viewDistance;

	std::vector<Vector2> hitPositions;

	for (const Entity& entity : objects)
	{
		bool hit = LineCircle(lineStart, lineEnd, entity.position, entity.radius);
		bool layer = caster.layer != LAYER_IGNORE_RAYCAST;//caster.layer == entity.layer;
		//bool mask = caster.mask & entity.mask;
		// Still have the same problem of testing the player against itself...
		// The only point of layer masks is to support multiple layers by combining layers via bitwise!
		if (hit && layer) hitPositions.push_back(entity.position);
	}

	size_t nearestIndex = 0;
	float nearestDistance = FLT_MAX;
	for (size_t i = 0; i < hitPositions.size(); i++)
	{
		float objectDistance = Distance(caster.position, hitPositions[i]);
		if (objectDistance < nearestDistance)
		{
			nearestDistance = objectDistance;
			nearestIndex = i;
		}
	}

	if (!hitPositions.empty()) hitPosition = hitPositions[nearestIndex];
	return !hitPositions.empty();
}

int main()
{
	// The memory window uses "hexadecimal" which is base 16.
	// This is convenient because 16 is a multiple of 2, so its easy to map to binary.
	// Hexadecimal counts 0 1 2 3 4 5 6 7 8 9 A B C D E F where F == 15 in decimal.
	
	// Example of how to multiply by 2 via bit-shifting
	byte bytes[8];
	for (int i = 0; i < 8; i++)
	{
		byte digit = 0b00000001;
		bytes[i] = digit << i;
		// Uncomment to revert
		//bytes[i] >>= i;
	}

	byte hex[16]
	{
		0b00000000, 0b00000001, 0b00000010, 0b00000011,
		0b00000100, 0b00000101, 0b00000110, 0b00000111,
		0b00001000, 0b00001001, 0b00001010, 0b00001011,
		0b00001100, 0b00001101, 0b00001110, 0b00001111,
	};

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game");
    SetTargetFPS(60);

	float obstacleRadius = 100.0f;
	float playerRadius = 10.0f;
	float targetRadius = 25.0f;
	float rayLength = 750.0f;

	Entity player, target, obstacle;
	player.position = { SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.75f };
	target.position = { SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT * 0.25f };
	obstacle.position = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f };

	player.radius = 10.0f;
	target.radius = 25.0f;
	obstacle.radius = 100.0f;

	// By default, everything can get hit with a raycast
	player.layer = LAYER_IGNORE_RAYCAST;
	target.layer = LAYER_ALL;
	obstacle.layer = LAYER_ALL;

	vector<Entity> objects;
	objects.push_back(player);
	objects.push_back(target);
	objects.push_back(obstacle);

    while (!WindowShouldClose())
    {
        // AB = B - A
        player.direction = Normalize(GetMousePosition() - player.position);
        //player.direction = Normalize(target.position - player.position);
        Vector2 lineStart = player.position;
        Vector2 lineEnd = player.position + player.direction * rayLength;

		Vector2 hit{};
		RayCast(player, objects, hit, rayLength);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircleV(player.position, player.radius, GREEN);
        DrawCircleV(target.position, target.radius, RED);
        DrawCircleV(obstacle.position, obstacle.radius, GRAY);
        DrawLineEx(lineStart, lineEnd, 5.0f, BLUE);
		DrawText(TextFormat("x: %f y: %f", hit.x, hit.y), 10, 10, 20, RED);
        EndDrawing();
    }

    CloseWindow();
	return 0;
}
