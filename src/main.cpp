#include "raylib.h"
#include "Math.h"
#include <array>
using namespace std;

const float TILE_WIDTH = 60.0f;
const float TILE_HEIGHT = 40.0f;

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
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Tile Map");
    SetTargetFPS(60);

    array<Tile, 10> tiles;
    for (size_t i = 0; i < tiles.size(); i++)
    {
        tiles[i].position = Vector2{ i * TILE_WIDTH, 0.0f };
        tiles[i].color = RandomColor();
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        //DrawRectangle(0, 0, 60, 40, RED);
        for (size_t i = 0; i < tiles.size(); i++)
        {
            DrawRectangleV(tiles[i].position, { TILE_WIDTH, TILE_HEIGHT }, tiles[i].color);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
