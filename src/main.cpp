//#include "raylib.h"
#include "Math.h"
#include <iostream> // input-output stream (console stuff)
#include <array>    // standard static array
#include <vector>   // standard dynamic array (C# List<T>)
#include <string>   // standard string (text)
#include <cassert>  // stardard assertions (crash if false)
using namespace std;

struct Singleton
{
public:
    static int& Instance()
    {
        static int instance;
        return instance;
    }

private:
    Singleton() {}
};

void Counter()
{
    // "function-static" variables persist between calls
    static int count = 1;
    cout << "Counting: x" << count << endl;
    count++;
}

int main()
{
    Singleton::Instance()++;
    Singleton::Instance()++;
    Singleton::Instance()++;
    cout << Singleton::Instance() << endl;
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