#include "raylib.h"
#include "Math.h"
#include <array>
#include <queue>
#include <vector>
using namespace std;

const float TILE_WIDTH = 80.0f;
const float TILE_HEIGHT = 80.0f;
const size_t TILE_COUNT = 10;

struct Tile
{
    Vector2 position;
};

struct Cell
{
    int row;    // y
    int col;    // x
};

enum TileType
{
    GRASS,
    WATER,
    MUD,
    STONE,
    COUNT
};

vector<Cell> Neighbours(Cell cell, int rows, int cols)
{
    bool left = cell.col - 1 >= 0;
    bool right = cell.col + 1 < cols;
    bool top = cell.row - 1 >= 0;
    bool bot = cell.row + 1 < rows;

    vector<Cell> neighbours;
    if (left) neighbours.push_back({ cell.row, cell.col - 1 });
    if (right) neighbours.push_back({ cell.row, cell.col + 1 });
    if (top) neighbours.push_back({ cell.row - 1, cell.col });
    if (bot) neighbours.push_back({ cell.row + 1, cell.col });
    return neighbours;
}

vector<Cell> FloodFill(Cell start, int rows, int cols)
{
    vector<Cell> cells;
    //for (int row = 0; row < rows; row++)
    //{
    //    for (int col = 0; col < cols; col++)
    //    {
    //
    //    }
    //}
    return cells;
}

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

        vector<Cell> neighbours = Neighbours({ 4, 4 }, TILE_COUNT, TILE_COUNT);
        for (size_t i = 0; i < neighbours.size(); i++)
        {
            Cell neighbour = neighbours[i];
            Vector2 position = Vector2{ neighbour.col * TILE_WIDTH, neighbour.row * TILE_HEIGHT };
            DrawRectangleV(position, { TILE_WIDTH, TILE_HEIGHT }, PURPLE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
