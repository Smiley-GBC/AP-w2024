//#include "raylib.h"
#include "Math.h"
#include <iostream>
using namespace std;

struct Enemy
{
    float health;

    // base health "declaration" --> tells the compiler "hey, base health is a thing"
    static float baseHealth;
};

// base health "definition" --> tells the compiler specific information about base health
// (without *specific information* you will get linker errors!!!)
// :: is the "scope-resolution" operator. It resolves between different names
float Enemy::baseHealth = 100.0f;

struct Player
{
    Player()
    {
        health = baseHealth;
    }

    float health;
    static float baseHealth;
};

float Player::baseHealth;

int main()
{
    // Why :: is useful:
    // We know we can't have duplicate variables because the compiler can't tell the difference.
    //float baseHealth = 1.0f;
    //float baseHealth = 2.0f;

    // We use :: to "resolve the scope" of object-specific variables so that compiler knows who's who!
    // (We need to tell the compiler which object baseHealth belongs to)
    Player::baseHealth = 100.0f;
    Enemy::baseHealth = 50.0f;

    Player player1;
    cout << "Player 1 health: " << player1.health << endl;

    // Changes health for *ALL* players
    cout << endl << "Changing base health to 200:" << endl;
    Player::baseHealth = 200.0f;
    Player player2;
    Player player3;
    cout << "Player 1 health: " << player1.health << endl;
    cout << "Player 2 health: " << player2.health << endl;
    cout << "Player 3 health: " << player3.health << endl;

    // Changes health for specific player
    // (if we change baseHealth AFTER player1 is created, player1 is unaffected)

    cout << endl << "Multiplying player1's health by 5:" << endl;
    player1.health *= 5.0f;
    cout << "Player 1 health: " << player1.health << endl;

    // All new players will now have a base health of 1000 (200 * 5)
    cout << endl << "Changing base health to 1000:" << endl;
    Player::baseHealth *= 5.0f;
    Player player4;
    cout << "Player 1 health: " << player1.health << endl;
    cout << "Player 2 health: " << player2.health << endl;
    cout << "Player 3 health: " << player3.health << endl;
    cout << "Player 4 health: " << player4.health << endl;

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
