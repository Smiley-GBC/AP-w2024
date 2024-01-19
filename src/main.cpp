#include "raylib.h"
#include "Math.h"
#include <iostream>
#include <string>
using namespace std;

const int LEGS_COUNT = 4;

class Table
{
public:
    float x, y;
    float width, height;
    float legWidth, legHeight;
    float weight;
    float legs[LEGS_COUNT];
    Color legsColor;
    Color topColor;

    // Convert from function to method by removing the table parameter and refering to properties
    void Draw()
    {
        for (int i = 0; i < LEGS_COUNT; i++)
        {
            DrawRectangle(legs[i], y, legWidth, legHeight, legsColor);
        }
        DrawRectangle(x, y, width, height, topColor);
    }
};

void OutputAddress(int* ptr, int index, int count)
{
    //cout << "Address of index " << index << ": " << &ptr[index] << endl;
    cout << "Value of index " << index << ": " << ptr[index] << endl;
    cout << "Value of index " << index << ": " << *(ptr + index) << endl;
}

// Inner layer
struct Achievement
{
    // We don't need any more arrays since this is the inner layer
    // Just add whatever data an Achievement should have here
    string name = "First Blood";
    float Score_Value = 2.00f;
};

// Middle layer
struct Game
{
    // See Platform's explanation
    int AchievementCount = 0;
    Achievement* Achievements = nullptr;
    int latitude = 1, longitude = 2;
};

// Outer layer
struct Platform
{
    // We don't know how many Games the Platform has.
    // Hence, we must make it a dynamic array so we determine
    // the number of Games when our program runs!
    int GameCount = 0;
    Game* Games = nullptr;
    string address = "Test address";
};

void CreateAchievement(Achievement& Achievement)
{
    float Score_Value = 0.0f;
    cout << "What is the Score Value of Achievement #?" << endl;
    cin >> Score_Value;
    Achievement.Score_Value = Score_Value;
}

void CreateGame(Game& Game)
{
    cout << "How many Achievements do you have?" << endl;
    cin >> Game.AchievementCount;
    if (Game.AchievementCount < 5)
    {
        cout << "Min 5 Games, How many Achievements do you have?" << endl;
        Game.AchievementCount;
    }
    else
    {
        Game.Achievements = new Achievement[Game.AchievementCount];
    }

    for (int i = 0; i < Game.AchievementCount; i++)
    {
        CreateAchievement(Game.Achievements[i]);
    }
}

void CreatePlatform(Platform& platform)
{
    cout << "How many Games do you own?" << endl;
    cin >> platform.GameCount;
    if (platform.GameCount < 5)
    {
        cout << "Min 5 Games, How many Games do you own?" << endl;
        cin >> platform.GameCount;
    }
    else
    {
        platform.Games = new Game[platform.GameCount];
    }
    
    for (int i = 0; i < platform.GameCount; i++)
    {
        CreateGame(platform.Games[i]);
    }
}

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    Platform platform;
    CreatePlatform(platform);

    for (int i = 0; i < platform.GameCount; i++)
    {
        cout << platform.address << endl;
        for (int j = 0; j < platform.GameCount; j++)
        {
            cout << platform.Games[j].longitude << platform.Games[j].longitude << endl;
            for (int k = 0; k < platform.Games[j].AchievementCount; k++)
            {
                cout << platform.Games[j].Achievements[k].name << endl;
                cout << platform.Games[j].Achievements[k].Score_Value << endl;
            }
        }
    }

    //InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    /*while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }*/

    /*CloseWindow();
    return 0;*/
}
