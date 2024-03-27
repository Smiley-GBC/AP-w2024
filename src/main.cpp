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
const float SCREEN_SIZE = 800.0f;
const float TILE_COUNT = 10.0f;
const float TILE_SIZE = SCREEN_SIZE / TILE_COUNT;

struct Cell
{
    int row;    // y
    int col;    // x
};

int main()
{
    InitWindow(SCREEN_SIZE, SCREEN_SIZE, "Tile Map");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Render tiles
        for (size_t row = 0; row < TILE_COUNT; row++)
        {
            for (size_t col = 0; col < TILE_COUNT; col++)
            {
                Vector2 position = Vector2{ col * TILE_SIZE, row * TILE_SIZE };
                //Color color = tileColors[grid[row][col]];
                DrawRectangleV(position, { TILE_SIZE, TILE_SIZE }, RED);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

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