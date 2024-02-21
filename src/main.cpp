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

    Sound headshot = LoadSound("./assets/audio/headshot.mp3");
    Sound ownage = LoadSound("./assets/audio/ownage.mp3");
    Sound doublekill = LoadSound("./assets/audio/doublekill.mp3");
    
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_ONE))
            PlaySound(headshot);

        if (IsKeyPressed(KEY_TWO))
            PlaySound(ownage);

        if (IsKeyPressed(KEY_THREE))
            PlaySound(doublekill);

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
    
    UnloadSound(doublekill);
    UnloadSound(ownage);
    UnloadSound(headshot);

    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();
}
