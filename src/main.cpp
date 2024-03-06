#include "raylib.h"
#include "Math.h"
#include <array>
using namespace std;

const float TILE_WIDTH = 40.0f;
const float TILE_HEIGHT = 40.0f;
const size_t TILE_COUNT = 20;

struct Tile
{
    Vector2 position;
    Color color;
};

Color RandomColor()
{
    Color colors[3]{ RED, GREEN, BLUE };
    return colors[rand() % 3];  // random number between 0, 1 and 2
}

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Tile Map");
    SetTargetFPS(60);

    array<array<Tile, TILE_COUNT>, TILE_COUNT> tiles;
    for (size_t row = 0; row < TILE_COUNT; row++)
    {
        for (size_t col = 0; col < TILE_COUNT; col++)
        {
            tiles[row][col].position = Vector2{ col * TILE_WIDTH, row * TILE_HEIGHT };
            tiles[row][col].color = RandomColor();
        }
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (size_t row = 0; row < TILE_COUNT; row++)
        {
            for (size_t col = 0; col < TILE_COUNT; col++)
            {
                DrawRectangleV(tiles[row][col].position, { TILE_WIDTH, TILE_HEIGHT }, tiles[row][col].color);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
