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

    Music music = LoadMusicStream("./assets/audio/ncs_time_leap_aero_chord.mp3");
    PlayMusicStream(music);
    
    while (!WindowShouldClose())
    {
        UpdateMusicStream(music);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    
    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();
}
