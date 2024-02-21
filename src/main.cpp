#include "raylib.h"
#include "Math.h"
using namespace std;

template<typename T>
struct Singleton
{
public:
    static T& Instance()
    {
        static T instance;
        return instance;
    }

private:
    Singleton() {}
};

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Resource Manager");
    InitAudioDevice();
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    
    CloseAudioDevice();
    CloseWindow();
}
