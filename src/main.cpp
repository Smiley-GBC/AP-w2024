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

    float g = 0.0f, h = 0.0f;
    float F() { return g + h; }
};

Node nodes[TILE_COUNT][TILE_COUNT];

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

    // Made global for visualization
    //Node nodes[TILE_COUNT][TILE_COUNT];
    for (int row = 0; row < TILE_COUNT; row++)
    {
        for (int col = 0; col < TILE_COUNT; col++)
        {
            // Allowed to explore if not stone
            visited[row][col] = tiles[row][col] == STONE;
            nodes[row][col].cell = { row, col };
            nodes[row][col].parent = Invalid();
            nodes[row][col].g = 0.0f;
            nodes[row][col].h = 0.0f;
        }
    }

    bool found = false;
    for (int i = 0; i < stepCount; i++)
    {
        // Exit if there's nothing left to explore
        if (frontier.empty()) break;

        Cell current = frontier.top();      // Get next in line
        frontier.pop();                     // Remove from line

        if (current == goal)
        {
            found = true;
            break;
        }

        visited[current.row][current.col] = true;   // Mark as visited
        cells.push_back(current);

        float gNew, hNew;
        for (Cell neighbour : Neighbours(current, TILE_COUNT, TILE_COUNT))
        {
            // Don't re-explore neighbours (otherwise infinite loop)
            if (visited[neighbour.row][neighbour.col])
                continue;
            
            // Compute neighbour's f-score; f(n) = g(n) + h(n)
            Node node = nodes[neighbour.row][neighbour.col];
            //gNew = node.g;
            //gNew += Manhattan(current, neighbour);
            gNew = Manhattan(start, current);
            hNew = Manhattan(neighbour, goal);
            // TODO -- add terrain cost to heuristic

            // If the neighbour is unexplored or has the best score so far:
            if (node.F() <= FLT_EPSILON || node.F() > (gNew + hNew))
            {
                // Update graph connections
                node.g = gNew;
                node.h = hNew;
                node.parent = current;
                nodes[neighbour.row][neighbour.col] = node;

                frontier.push(neighbour);
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

    Cell test1{ 9, 9 };
    Cell test2{ 10, 10 };

    Cell start, end;
    start.row = 6; start.col = 5;
    end.row = 5; end.col = 9;

    float d1 = Manhattan(test1, end);
    float d2 = Manhattan(test2, end);

    int stepCount = 0;
    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_SPACE)) ++stepCount;
        vector<Cell> cells = FloodFill(start, end, grid, stepCount);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Render tiles
        for (size_t row = 0; row < TILE_COUNT; row++)
        {
            for (size_t col = 0; col < TILE_COUNT; col++)
            {
                Vector2 position = Vector2{ col * TILE_WIDTH, row * TILE_HEIGHT };
                Color color = tileColors[grid[row][col]];
                DrawRectangleV(position, { TILE_WIDTH, TILE_HEIGHT }, color);
            }
        }

        // Render path
        for (size_t i = 0; i < cells.size(); i++)
        {
            Cell neighbour = cells[i];
            Vector2 position = Vector2{ neighbour.col * TILE_WIDTH, neighbour.row * TILE_HEIGHT };
            DrawRectangleV(position, { TILE_WIDTH, TILE_HEIGHT }, PURPLE);
        }

        // Render scores (must render on top of path)
        for (size_t row = 0; row < TILE_COUNT; row++)
        {
            for (size_t col = 0; col < TILE_COUNT; col++)
            {
                Vector2 position = Vector2{ col * TILE_WIDTH, row * TILE_HEIGHT };
                Node& node = nodes[row][col];
                DrawText(TextFormat("f: %.2f", node.F()), position.x + 5, position.y + 5, 10, RED);
                DrawText(TextFormat("h: %.2f", node.h), position.x + 5, position.y + 15, 10, ORANGE);
                DrawText(TextFormat("g: %.2f", node.g), position.x + 5, position.y + 25, 10, GOLD);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

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