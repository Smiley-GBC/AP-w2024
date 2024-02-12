//#include "raylib.h"
#include "Math.h"
#include <iostream>
#include <string>
using namespace std;

//int Add(int a, int b)
//{
//    return a + b;
//}
//
//float Add(float a, float b)
//{
//    return a + b;
//}

template<typename T>
T Add(T a, T b)
{
    cout << "Generic add: " << a + b << endl;
    return a + b;
}

int main()
{
    int a = 1;
    int b = 2;
    float c = 1.0f;
    float d = 2.0f;
    char x = 'x';
    char y = 'y';
    Add(x, y);
    Add(a, b);
    Add(c, d);

    return 0;
}

//const int screenWidth = 1280;
//const int screenHeight = 720;
//InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
//SetTargetFPS(60);
//
//while (!WindowShouldClose())
//{
//    BeginDrawing();
//    ClearBackground(RAYWHITE);
//    EndDrawing();
//}
//
//CloseWindow();