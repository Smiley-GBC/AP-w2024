//#include "raylib.h"
#include "Math.h"
#include <iostream>
using namespace std;

struct Circle1
{
public:
    float GetRadius() { return radius; }
    float SetRadius(float r) { radius = r; }

private:
    float radius;
};

struct Circle2
{
    float radius;
};

int main()
{
    int numbers[] = { 1, 2, 3, 4, 5 };
    cout << numbers[0] << endl;
    cout << numbers[1] << endl;
    cout << numbers[2] << endl;
    cout << numbers[3] << endl;
    cout << numbers[4] << endl << endl;

    // [] ("subscript operator") is shorthand to do pointer arithmetic and dereference
    // The offset is a muliple of the datatype. ie n * sizeof(int)
    // numbers + 0 means numbers + 0 * sizeof(int)
    // numbers + 1 means numbers + 1 * sizeof(int)
    // numbers + 2 means numbers + 2 * sizeof(int)
    // numbers + 3 means numbers + 3 * sizeof(int)
    // numbers + 4 means numbers + 4 * sizeof(int)
    cout << *(numbers + 0) << endl;
    cout << *(numbers + 1) << endl;
    cout << *(numbers + 2) << endl;
    cout << *(numbers + 3) << endl;
    cout << *(numbers + 4) << endl << endl;

    // We can prove this pointer arithmetic by doing the long-form:
    int offset = sizeof(int);
    cout << offset << endl << endl;

    // Here we're saying "go to offset + 0 times size of integer"
    char* start = reinterpret_cast<char*>(numbers);
    cout << (int)*(start + 0 * offset) << endl;
    cout << (int)*(start + 1 * offset) << endl;
    cout << (int)*(start + 2 * offset) << endl;
    cout << (int)*(start + 3 * offset) << endl;
    cout << (int)*(start + 4 * offset) << endl;

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
    return 0;
}
