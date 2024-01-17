#include "raylib.h"
#include "Math.h"
#include <iostream>
using namespace std;

const int LEGS_COUNT = 4;

class Table
{
public:
    float x, y;
    float width, height;
    float legWidth, legHeight;
    float weight;
    float legs[LEGS_COUNT];
    Color legsColor;
    Color topColor;

    // Convert from function to method by removing the table parameter and refering to properties
    void Draw()
    {
        for (int i = 0; i < LEGS_COUNT; i++)
        {
            DrawRectangle(legs[i], y, legWidth, legHeight, legsColor);
        }
        DrawRectangle(x, y, width, height, topColor);
    }
};

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;
    Table woodTable;
    woodTable.topColor = GRAY;
    woodTable.legsColor = BROWN;
    woodTable.height = 60.0f;
    woodTable.width = 200.0f;
    woodTable.x = screenWidth * 0.5f - woodTable.width * 0.5f;
    woodTable.y = screenHeight * 0.75 - woodTable.height;
    woodTable.legWidth = 10.0f;
    woodTable.legHeight = woodTable.height * 3.0f;
    woodTable.legs[0] = woodTable.x;
    woodTable.legs[1] = woodTable.x + woodTable.legWidth * 3.0f;

    woodTable.legs[2] = woodTable.x + woodTable.width - woodTable.legWidth * 3.0f;
    woodTable.legs[3] = woodTable.x + woodTable.width - woodTable.legWidth;

    // Integer array allocated on the "stack" (constant size)
    int staticIntegers[10]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    for (int i = 0; i < 10; i++)
    {
        cout << staticIntegers[i] << endl;
    }

    // Integer array allocated on the "heap" (variable size)
    // The "new" keyword means "allocated on the heap"
    int* dynamicIntegers = new int[10];
    for (int i = 0; i < 10; i++)
    {
        // We cannot initialize heap-arrays with curly braces,
        // So we'll populate it with a for-loop!
        cout << "Added of index " << i << ": " << &dynamicIntegers[i] << endl;
        cout << "Value of index " << i << ": " << dynamicIntegers[i] << endl;
    }
    
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        woodTable.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
