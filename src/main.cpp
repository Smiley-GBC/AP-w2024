#include "raylib.h"
#include "Math.h"
#include "AudioManager.h"
using namespace std;

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Resource Manager");
    InitAudioDevice();
    SetTargetFPS(60);

    AudioManager audioManager;

    bool musicPlaying = false;
    Music music = LoadMusicStream("./assets/audio/ncs_time_leap_aero_chord.mp3");

    Sound headshot = audioManager.LoadSound("./assets/audio/headshot.mp3");
    audioManager.LoadSound("./assets/audio/headshot.mp3");
    audioManager.LoadSound("./assets/audio/headshot.mp3");
    // Test our sound caching by stepping through the program to see which branch it takes!

    Sound ownage = audioManager.LoadSound("./assets/audio/ownage.mp3");
    Sound doublekill = audioManager.LoadSound("./assets/audio/doublekill.mp3");
    SetSoundVolume(ownage, 0.5f);
    SetSoundVolume(doublekill, 0.25f);

    Texture enterprise = LoadTexture("./assets/textures/enterprise.png");
    Texture d7 = LoadTexture("./assets/textures/d7.png");

    bool isD7 = false;
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_ONE))
            PlaySound(headshot);

        if (IsKeyPressed(KEY_TWO))
            PlaySound(ownage);

        if (IsKeyPressed(KEY_THREE))
            PlaySound(doublekill);

        if (IsKeyPressed(KEY_TAB))
            isD7 = !isD7;

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
        DrawTexture(isD7 ? d7 : enterprise, 10, 10, WHITE);
        EndDrawing();
    }
    
    UnloadTexture(d7);
    UnloadTexture(enterprise);
    UnloadSound(doublekill);
    UnloadSound(ownage);
    UnloadSound(headshot);

    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();
}
