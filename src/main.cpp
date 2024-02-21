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

    bool musicPlaying = false;
    Music music = LoadMusicStream("./assets/audio/ncs_time_leap_aero_chord.mp3");
    
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_SPACE))
        {
            // TODO -- stop track from restarting every time
            // Add pause & resume functionality
            musicPlaying = !musicPlaying;
            if (musicPlaying)
                PlayMusicStream(music);
            else
                StopMusicStream(music);
        }
        UpdateMusicStream(music);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        EndDrawing();
    }
    
    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();
}
