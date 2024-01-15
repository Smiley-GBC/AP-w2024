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

// Practical pointers example
void PointersPractice()
{

}

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
