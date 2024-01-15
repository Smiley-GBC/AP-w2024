//#include "raylib.h"
#include "Math.h"
#include <iostream>

// Increments a copy of n
void ByValue(int n)
{
    n++;
}

// Increments n (& = ref in c#)
void ByReference(int& n)
{
    n++;
}

// Review of passing by value vs passing by reference
void Review()
{
    int x = 0;
    int y = 0;
    ByValue(x);
    ByReference(y);
    std::cout << "By value: " << x << std::endl << "By reference: " << y << std::endl;
}

struct Texture
{
    int width;
    int height;
    char data[];
};

struct Renderer
{
    Texture* steve;
};

struct ShapeShifter
{
    Texture* steve;
};

struct GoofyHelmet
{
    Texture* steve;
};

// Theoretical memory sharing example
void MemorySharing()
{
    Texture steve;
    Renderer renderer;
    ShapeShifter shapeShifter;
    GoofyHelmet helmet;

    // "&" means "address". Pointers simply store addresses.
    // So, we effectively share memory by pointing to the same address!
    renderer.steve = &steve;
    shapeShifter.steve = &steve;
    helmet.steve = &steve;
}

// This means I'm "using the standard namespace", so I don't have to type std:: every time.
using namespace std;


// Practical pointers example
void PointersPractice()
{
    float* numberPtr = nullptr;
    float number = 0.0f;
    numberPtr = &number;
    float x = 1.1f;
    float y = 2.2f;
    float z = 3.3f;

    // An example of outputting 3 numbers to the console
    cout
        << "X: " << x << endl
        << "Y: " << y << endl
        << "Z: " << z << endl;

    // What if we wanted to store the current number and output it?
    number = x;
    cout << "Number as x: " << number << endl;

    number = y;
    cout << "Number as y: " << number << endl;

    number = z;
    cout << "Number as z: " << number << endl;

    numberPtr = &x;
    cout << "Number pointer as x: " << *numberPtr << endl;

    numberPtr = &y;
    cout << "Number pointer as y: " << *numberPtr << endl;

    numberPtr = &z;
    cout << "Number pointer as z: " << *numberPtr << endl;
}

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
    PointersPractice();

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
