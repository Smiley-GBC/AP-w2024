#include "raylib.h"
#include "Math.h"
#include <array>
using namespace std;

const float TILE_WIDTH = 80.0f;
const float TILE_HEIGHT = 80.0f;
const size_t TILE_COUNT = 10;

struct Tile
{
    Vector2 position;
};

enum TileType
{
    GRASS,
    WATER,
    MUD,
    STONE,
    COUNT
};

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Tile Map");
    SetTargetFPS(60);

    Color tileColors[COUNT]{ GREEN, BLUE, BROWN, DARKGRAY };
    int grid[TILE_COUNT][TILE_COUNT]
    {
        { 3, 1, 1, 1, 1, 1, 1, 1, 1, 3 },
        { 3, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
        { 3, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
        { 3, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
        { 3, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
        { 3, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
        { 3, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
        { 3, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
        { 3, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
        { 3, 2, 2, 2, 2, 2, 2, 2, 2, 3 }
    };

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (size_t row = 0; row < TILE_COUNT; row++)
        {
            for (size_t col = 0; col < TILE_COUNT; col++)
            {
                Vector2 position = Vector2{ col * TILE_WIDTH, row * TILE_HEIGHT };
                Color color = tileColors[grid[row][col]];
                DrawRectangleV(position, { TILE_WIDTH, TILE_HEIGHT }, color);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
