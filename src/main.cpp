#include "raylib.h"
#include "Math.h"
#include <iostream>
#include <array>
#include <queue>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;

void QueueTest();
const int SCREEN_SIZE = 800;
const int TILE_COUNT = 10;
const int TILE_SIZE = SCREEN_SIZE / TILE_COUNT;

struct Cell
{
    int row;    // y
    int col;    // x
};

bool CanMove(Cell cell)
{
    return cell.col >= 0 && cell.col < TILE_COUNT && cell.row >= 0 && cell.row < TILE_COUNT;
}

// World-space to grid-space --> "Quantization"
// Grid-space to world-space --> "Localization"
void DrawTile(Cell cell, Color color)
{
    DrawRectangle(cell.col * TILE_SIZE, cell.row * TILE_SIZE, TILE_SIZE, TILE_SIZE, color);
}

int main()
{
    InitWindow(SCREEN_SIZE, SCREEN_SIZE, "Tile Map");
    SetTargetFPS(60);

    Cell player;
    player.row = TILE_COUNT / 2;
    player.col = TILE_COUNT / 2;

    while (!WindowShouldClose())
    {
        Cell newPlayer = player;
        if (IsKeyPressed(KEY_W))
        {
            newPlayer.row -= 1;
        }
        else if (IsKeyPressed(KEY_S))
        {
            newPlayer.row += 1;
        }
        else if (IsKeyPressed(KEY_A))
        {
            newPlayer.col -= 1;
        }
        else if (IsKeyPressed(KEY_D))
        {
            newPlayer.col += 1;
        }

        // "If we can move, assign the player to the new position.
        // Otherwise, keep the previous position."
        player = CanMove(newPlayer) ? newPlayer : player;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTile(player, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

// Render tiles (unnecessary cause we can just colour our background white)
//for (int row = 0; row < TILE_COUNT; row++)
//{
//    for (int col = 0; col < TILE_COUNT; col++)
//    {
//        DrawTile({ row, col }, WHITE);
//    }
//}

//vector<Cell> Neighbours(Cell cell, int rows, int cols)
//{
//    bool left = cell.col - 1 >= 0;
//    bool right = cell.col + 1 < cols;
//    bool top = cell.row - 1 >= 0;
//    bool bot = cell.row + 1 < rows;
//
//    vector<Cell> neighbours;
//    if (left) neighbours.push_back({ cell.row, cell.col - 1 });
//    if (right) neighbours.push_back({ cell.row, cell.col + 1 });
//    if (top) neighbours.push_back({ cell.row - 1, cell.col });
//    if (bot) neighbours.push_back({ cell.row + 1, cell.col });
//    return neighbours;
//}

//int grid[TILE_COUNT][TILE_COUNT]
//{
//    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 3, 3, 3, 3, 3, 3, 3, 0, 0 },
//    { 0, 0, 0, 0, 0, 0, 0, 3, 0, 0 },
//    { 0, 0, 0, 0, 0, 0, 0, 3, 0, 0 },
//    { 0, 0, 0, 0, 0, 0, 0, 3, 2, 0 },
//    { 0, 0, 0, 0, 0, 1, 0, 3, 0, 0 },
//    { 0, 0, 0, 0, 0, 0, 0, 3, 0, 0 },
//    { 0, 0, 0, 0, 0, 0, 0, 3, 0, 0 },
//    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
//};

void QueueTest()
{
    priority_queue<int, vector<int>, greater<int>> lt;
    lt.push(3);
    lt.push(2);
    lt.push(1);

    priority_queue<int, vector<int>, less<int>> gt;
    gt.push(1);
    gt.push(2);
    gt.push(3);

    // Added data to our queues in reverse-order so we can prove that the comparisons sort the data accordingly
    // Priority queues are sorted greatest to least by default (serve the customer with the highest priority)
    // In order to sort least to greatest, we have to pass the greater<> comparison
    // Think of it as "flipping an inequality"
    printf("Least to greatest:\n");
    while (!lt.empty())
    {
        cout << lt.top() << endl;
        lt.pop();
    }

    printf("\nGreatest to least:\n");
    while (!gt.empty())
    {
        cout << gt.top() << endl;
        gt.pop();
    }
}