#include "raylib.h"
#include "Math.h"
#include <iostream>
#include <array>
#include <queue>
#include <vector>
#include <functional>
#include <algorithm>
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

struct Node
{
    Cell cell;      // current
    Cell parent;    // previous
};

Cell Invalid()
{
    return { -1, -1 };
}

bool operator==(const Cell& a, const Cell& b)
{
    return a.row == b.row && a.col == b.col;
}

float Manhattan(Cell a, Cell b)
{
    return abs(a.row - b.row) + abs(a.col - b.col);
}

class CompareObject
{
public:
    // C++ defaults to *highest* priority *first*
    // We want *lowest* priority *first*
    // Hence, use > instead of < to flip the order!
    bool operator() (const Cell& a, const Cell& b) const
    {
        return Manhattan(a, goal) > Manhattan(b, goal);
    }

    Cell goal;
};

// Prioritize based on distance to goal!
using dist_queue = priority_queue<Cell, vector<Cell>, CompareObject>;

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

vector<Cell> FloodFill(Cell start, Cell goal, int tiles[TILE_COUNT][TILE_COUNT], int stepCount)
{
    vector<Cell> cells;
    CompareObject co;
    co.goal = goal;
    dist_queue frontier(co);
    bool visited[TILE_COUNT][TILE_COUNT]; // "closed list"
    frontier.push(start);

    Node nodes[TILE_COUNT][TILE_COUNT];
    for (int row = 0; row < TILE_COUNT; row++)
    {
        for (int col = 0; col < TILE_COUNT; col++)
        {
            // Allowed to explore if not stone
            visited[row][col] = tiles[row][col] == STONE;
            nodes[row][col].cell = { row, col };
            nodes[row][col].parent = Invalid();
        }
    }

    bool found = false;
    for (int i = 0; i < stepCount; i++)
    {
        // Exit if there's nothing left to explore
        if (frontier.empty()) break;

        Cell current = frontier.top();    // Get next in line
        frontier.pop();                     // Remove from line

        if (current == goal)
        {
            found = true;
            break;
        }

        visited[current.row][current.col] = true;   // Mark as visited
        cells.push_back(current);

        // "Range-based for-loop" -- identical to "foreach" in C#
        // Basically does this Cell neighbour = neighbours[i]; automatically
        for (Cell neighbour : Neighbours(current, TILE_COUNT, TILE_COUNT))
        {
            if (!visited[neighbour.row][neighbour.col])
            {
                frontier.push(neighbour);
                nodes[neighbour.row][neighbour.col].parent = current;
            }
        }
    }

    // Retrace our steps if we've found a path
    if (found)
    {
        vector<Cell> path;
        Cell current = goal;
        Cell next = nodes[current.row][current.col].parent;

        // Retrace our steps until there's nowhere left to backtrack (parent is invalid)
        while (next.row != -1 && next.col != -1)
        {
            path.push_back(current);
            current = next;
            next = nodes[current.row][current.col].parent;
        }
        reverse(path.begin(), path.end());
        return path;
    }
    
    // Otherwise return all cells in flood-fill for visualization
    return cells;
}

int main()
{
    //C++ data structures can be sorted
    //By default, std::sort sorts ascending least to greatest like so:
    //sort(vec.begin(), vec.end());
    //If we instead want to sort ascending greatest to least, we can add a comparison object:
    //sort(vec.begin(), vec.end(), greater<int>());
    //We can also add a less comparison if need be
    //sort(vec.begin(), vec.end(), less<int>());

    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    sort(vec.begin(), vec.end(), greater<int>());
    printf("Printing stack greatest to least:\n");
    for (int v : vec)
        cout << v << endl;

    sort(vec.begin(), vec.end(), less<int>());
    printf("\nPrinting stack least to greatest:\n");
    for (int v : vec)
        cout << v << endl;

    const int screenWidth = 800;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Tile Map");
    SetTargetFPS(60);

    Color tileColors[COUNT]{ GREEN, BLUE, BROWN, DARKGRAY };
    int grid[TILE_COUNT][TILE_COUNT]
    {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 3, 3, 3, 3, 3, 3, 3, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 3, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 3, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 3, 2, 0 },
        { 0, 0, 0, 0, 0, 1, 0, 3, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 3, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 3, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    };

    Cell start, end;
    start.row = 6; start.col = 5;
    end.row = 5; end.col = 9;
    int stepCount = 0;
    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_SPACE)) ++stepCount;

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

        vector<Cell> cells = FloodFill(start, end, grid, stepCount);
        for (size_t i = 0; i < cells.size(); i++)
        {
            Cell neighbour = cells[i];
            Vector2 position = Vector2{ neighbour.col * TILE_WIDTH, neighbour.row * TILE_HEIGHT };
            DrawRectangleV(position, { TILE_WIDTH, TILE_HEIGHT }, PURPLE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
