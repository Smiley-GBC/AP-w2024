//#include "raylib.h"
#include "Math.h"
#include <iostream>
using namespace std;

void PointerArithmetic();

// Unless getters & setters do something meaningful, they shouldn't exist
struct Circle1
{
    float GetRadius() { return radius; }
    float SetRadius(float r) { radius = r; }

private:
    float radius;
};

// This is a more "correct" version of the above code
struct Circle2
{
    float radius;
};

// Sometimes, its advantageous to make our code "immutable".
// Meaning once our object has been created, it cannot be changed.
// To achieve this, we set the radius ONCE on creation,
// and make a getter but not a setter.
struct Circle3
{
    Circle3(float r) { radius = r; }
    float GetRadius() { return radius; }

private:
    float radius;
};

int Add(int a, int b)
{
    return a + b;
}

float Add(float a, float b)
{
    return a + b;
}

// Classes are the same as structs,
// but they're private by default (whereas structs are public)
class Test
{
public:
    // This is a "constructor function". It runs *automatically* when an object is created
    // If the constructor has no arguments, it is said to be the "default constructor"
    // If the user doesn't overload the default constructor, the compiler will create one.
    Test()
    {
        cout << "Test default constructor. . ." << endl;
    }

    // Here is an "overloaded constructor" that takes an integer argument.
    // Just like functions, we can overload constructors!
    Test(int integer)
    {
        cout << "Test overloaded int constructor " << integer << endl;
    }

    Test(float decimal)
    {
        cout << "Test overloaded float constructor " << decimal << endl;
    }

private:

};

int main()
{
    // Pointer math examples ranging from automatic to manual
    //PointerArithmetic();

    // Function overloading example (same name and argument count, different behaviour)
    cout << "Integer add: " << Add((int)1.75f, (int)2.5f) << endl;
    cout << "Decimal add: " << Add(1.75f, 2.5f) << endl;

    // We can overload constructors just like functions.
    // "Just because we *can* doesn't mean we *should*".
    Test test1(1);   // Outputs "Test overloaded int constructor 1"
    Test test2(1.5f);// Outputs "Test overloaded float constructor 1.5"

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

void PointerArithmetic()
{
    int numbers[] = { 1, 2, 3, 4, 5 };
    cout << numbers[0] << endl;
    cout << numbers[1] << endl;
    cout << numbers[2] << endl;
    cout << numbers[3] << endl;
    cout << numbers[4] << endl << endl;

    // [] ("subscript operator") is shorthand to do pointer arithmetic and dereference
    // The offset is a muliple of the datatype. ie n * sizeof(int)
    // numbers + 0 means numbers + 0 * sizeof(int)
    // numbers + 1 means numbers + 1 * sizeof(int)
    // numbers + 2 means numbers + 2 * sizeof(int)
    // numbers + 3 means numbers + 3 * sizeof(int)
    // numbers + 4 means numbers + 4 * sizeof(int)
    cout << *(numbers + 0) << endl;
    cout << *(numbers + 1) << endl;
    cout << *(numbers + 2) << endl;
    cout << *(numbers + 3) << endl;
    cout << *(numbers + 4) << endl << endl;

    // We can prove this pointer arithmetic by doing the long-form:
    int offset = sizeof(int);
    cout << offset << endl << endl;

    // Here we're saying "go to offset + 0 times size of integer"
    char* start = reinterpret_cast<char*>(numbers);
    cout << (int)*(start + 0 * offset) << endl;
    cout << (int)*(start + 1 * offset) << endl;
    cout << (int)*(start + 2 * offset) << endl;
    cout << (int)*(start + 3 * offset) << endl;
    cout << (int)*(start + 4 * offset) << endl;

    // Again, we can use pointer arithmetic to iterate through an array!
    // Points to numbers[0] (since numbers is just a pointer)
    int* numberPtr = numbers;
    cout << *numberPtr++ << endl;
    cout << *numberPtr++ << endl;
    cout << *numberPtr++ << endl;
    cout << *numberPtr++ << endl;
    cout << *numberPtr++ << endl;
}