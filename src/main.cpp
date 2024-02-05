//#include "raylib.h"
#include "Math.h"
#include <iostream>
#include <string>
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

// "Forward-declaration" (just like static variables, we can have function declarations, and definitions)
void StaticExamples();


struct Insect
{
    // Common variables for all insects
    int legs;
    int wings;
    float weight;
    float exoskeleton;
    string name;
    string type;

    // Common functions for all insects
    void Name()
    {
        cout << "Hello I'm " << name << " the " << type << endl;
    }
};

// ':' means "inherits from"
// Bee IS an Insect (has legs, wings, weight and exoskeleton)
struct Bee : public Insect
{
    float stingPower;
    int honeyCount;
    int pollunCount;
    bool hasSpicyPersonality;
    string hiveName;
};

// Grasshopper IS an Insect (has legs, wings, weight and exoskeleton)
struct Grasshopper : public Insect
{
    float jumpHeight;
    float jumpDistance;
    string sound;
    bool dismembersBugs;
    bool eatsMate;
    int killCount;
};

void Inhertiance();

// Method 1: "Old-School" polymorphism -- if you want different behaviours, just manually check your type!
// Use if you like the syntax, OR if your code is performance-critical (best performance)
enum SoundType
{
    DOG,
    CAT,
    COW,
    FOX
};

string MakeSound(SoundType type)
{
    switch (type)
    {
    case DOG:
        return "Woof!";

    case CAT:
        return "Meow!";

    case COW:
        return "MOOOOOOOOOOOOOOOOOOOOO";

    case FOX:
        return "Yip yip!";
    }
}

// Method 2: function pointers
// We read this as "SoundFunction is a pointer to a function that returns a string and takes no arguments"
// (See bottom of file for more examples)
// Use when you have strictly behaviour (medium performance)
using SoundFunction = string(*)();

string Bark()
{
    return "Woof!";
}

string Meow()
{
    return "Meow!";
}

string Moo()
{
    return "MOOOOOOOOOOOOOOOOOOOOO!";
}

string Yip()
{
    return "Yip yip!";
}

// Method 3 -- "Object-Oriented" polymorphism
// Use when you NEED to bundle data AND behaviour (slow performance)
struct Animal
{
    // Not sure what sound our animals make by default...
    virtual string Sound()    // "virtual" means derived classes can *override* said method
    {
        return "Generic animal noises";
    }
};

struct Dog : public Animal
{
    virtual string Sound() override
    {
        return "Woof!";
    }
};

struct Cat : public Animal
{
    virtual string Sound() override
    {
        return "Meow!";
    }
};

struct Cow : public Animal
{
    virtual string Sound() override
    {
        return "MOOOOOOOOOOOOOOOOOOOOO";
    }
};

struct Fox : public Animal
{
    virtual string Sound() override
    {
        return "Yip yip!";
    }
};

void Polymorphism()
{
    // Method 1
    cout << "Method 1:" << endl;
    SoundType soundType;

    soundType = DOG;
    cout << MakeSound(soundType) << endl;
    soundType = CAT;
    cout << MakeSound(soundType) << endl;
    soundType = COW;
    cout << MakeSound(soundType) << endl;
    soundType = FOX;
    cout << MakeSound(soundType) << endl;

    // Method 2
    cout << endl << "Method 2:" << endl;
    SoundFunction soundFunction = nullptr;

    soundFunction = Bark;
    cout << soundFunction() << endl;
    soundFunction = Meow;
    cout << soundFunction() << endl;
    soundFunction = Moo;
    cout << soundFunction() << endl;
    soundFunction = Yip;
    cout << soundFunction() << endl;

    cout << endl << "Method 3:" << endl;
    Animal* animal = nullptr;

    animal = new Dog;
    cout << animal->Sound() << endl;
    animal = new Cat;
    cout << animal->Sound() << endl;
    animal = new Cow;
    cout << animal->Sound() << endl;
    animal = new Fox;
    cout << animal->Sound() << endl;

    cout << endl << "Automation examples:" << endl;
    SoundType types[] = { DOG, CAT, COW, FOX };
    SoundFunction functions[] = { Bark, Meow, Moo, Yip };
    Animal* animals[] = { new Dog, new Cat, new Cow, new Fox };
    for (int i = 0; i < 4; i++)
    {
        cout << MakeSound(types[i]) << endl;    // Look up sound based on type
        cout << functions[i]() << endl;         // Just an array of functions, so simply invoke the current function!
        cout << animals[i]->Sound() << endl;    // Invoke animal-specific sound
    }
}

int main()
{
    //StaticExamples();
    //Inhertiance();
    Polymorphism();

    return 0;
}

void Inhertiance()
{
    Grasshopper gary;
    gary.name = "Gary";
    gary.type = "Grasshopper";

    Bee barry;
    barry.name = "Barry";
    barry.type = "Bee";

    gary.Name();
    barry.Name();
}

// Function definition
void StaticExamples()
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
}

// Additional function pointer examples:
using Ex1 = void(*)();  // Ex1 is a pointer to a function that returns void and takes no arguments
using Ex2 = int(*)();   // Ex2 is a pointer to a function that returns int and takes no arguments
using Ex3 = float(*)(); // Ex3 is a pointer to a function that returns float and takes no arguments
using Ex4 = void(*)(int, float);
// Ex4 is a pointer to a function that returns void and takes an int followed by a float as arguments

void Example4(int a, float b)
{
    cout << a << b << "<-- output from function pointer example 4!" << endl;
}

void FunctionPointerExample()
{
    // This is a "delegate" in C#
    Ex4 exampleFunctionPtr = Example4;

    // We can store a function like any other variable, and then invoke it at our convenience!
    exampleFunctionPtr(1, 1.f);
}

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