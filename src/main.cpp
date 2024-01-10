#include "raylib.h"
#include "Math.h"

class Table
{
public:
    float x, y;
    float width, height;
    float legWidth, legHeight;
    float weight;
    int legs;
    Color legsColor;
    Color topColor;

    // Convert from function to method by removing the table parameter and refering to properties
    void Draw()
    {
        float spacing = width / legs;
        float legX = x;
        for (int i = 0; i < legs; i++)
        {
            DrawRectangle(legX, y, legWidth, legHeight, legsColor);
            legX += spacing;
        }
        DrawRectangle(x, y, width, height, topColor);
    }
};

// Regular function
//void Draw(Table table)
//{
//    DrawRectangle(table.x, table.y, table.width, table.height, table.color);
//}

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
    woodTable.legs = 4;
    woodTable.legWidth = 10.0f;
    woodTable.legHeight = woodTable.height * 3.0f;
    
    const char* sentence = "asdkjashdkjh";

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText(sentence, screenWidth * 0.5f, screenHeight * 0.5f, 20, YELLOW);
        woodTable.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
