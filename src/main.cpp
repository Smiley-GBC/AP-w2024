#include "raylib.h"
#include "Math.h"

#include <stack>
#include <queue>

#include <iostream>
using namespace std;

const int SCREEN_SIZE = 800;
const int TILE_COUNT = 10;
const int TILE_SIZE = SCREEN_SIZE / TILE_COUNT;

struct Cell
{
    int row;    // y
    int col;    // x
};

// Abstract base class
class Command
{
public:
    virtual void Run() = 0;
    virtual void Undo() = 0;
};

class MoveCommand : public Command
{
public:
    MoveCommand(Cell& current, int dy, int dx) : mCell(current), mDy(dy), mDx(dx) {}

    void Run() final
    {
        Cell newCell = mCell;
        newCell.row += mDy;
        newCell.col += mDx;
        mCell = CanMove(newCell) ? newCell : mCell;
    }

    void Undo() final
    {
        mCell = { mCell.row - mDy, mCell.col - mDx };
    }

private:
    bool CanMove(Cell cell)
    {
        return cell.col >= 0 && cell.col < TILE_COUNT && cell.row >= 0 && cell.row < TILE_COUNT;
    }

    Cell& mCell;
    int mDx, mDy;
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

    stack<Command*> history;

    while (!WindowShouldClose())
    {
        Command* command = nullptr;
        //GetKeyPressed();
        if (IsKeyPressed(KEY_W))
            command = new MoveCommand(player, -1, 0);
        else if (IsKeyPressed(KEY_S))
            command = new MoveCommand(player, 1, 0);
        else if (IsKeyPressed(KEY_A))
            command = new MoveCommand(player, 0, -1);
        else if (IsKeyPressed(KEY_D))
            command = new MoveCommand(player, 0, 1);

        if (command != nullptr)
        {
            command->Run();
            history.push(command);
        }

        if (IsKeyPressed(KEY_Z) && !history.empty())
        {
            Command* recent = history.top();
            recent->Undo();
            delete recent;
            history.pop();
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTile(player, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
