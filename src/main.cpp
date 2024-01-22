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
        value = integer;
        cout << "Test overloaded int constructor " << integer << endl;
    }

    Test(float decimal)
    {
        value = decimal;
        cout << "Test overloaded float constructor " << decimal << endl;
    }

    // This is called the "destructor" (indicated by '~').
    // It runs when an object is destroyed!
    ~Test()
    {
        cout << "Test " << value << " destroyed." << endl;
    }

    float value;
};

// Case 1: objects are destroyed because they've gone out of scope
// This is because they're created on the "stack".
// The stack is memory alloacted before the program runs by the compiler.
// It is generally preferable because the compiler automatically deallocates the memory.
// The downside is it is fixed-size, so we must know the amount of memory needed.
// "The stack means the compiler does our baby-sitting for us :)"
void StackConstructorDestructor()
{
    // Function overloading example (same name and argument count, different behaviour)
    //cout << "Integer add: " << Add((int)1.75f, (int)2.5f) << endl;
    //cout << "Decimal add: " << Add(1.75f, 2.5f) << endl;

    // We can overload constructors just like functions.
    // "Just because we *can* doesn't mean we *should*".
    Test test1(1);   // Outputs "Test overloaded int constructor 1"
    Test test2(1.5f);// Outputs "Test overloaded float constructor 1.5"

    // Outputs "Test 1.5 destroyed."
    // Outputs "Test 1 destroyed."
    // This is because objects are destroyed in the opposite order they were created.
    // (Has to do with the way they're allocated on the stack).
}

void HeapConstructorDestructor()
{
    // Initialize pointers to nullptr (address 0) for safety
    Test* test1 = nullptr;
    Test* test2 = nullptr;

    // Dereferencing a null-pointer is allowed
    //*test1;

    // Reading from or writing to a null pointer is FORBIDDEN!!! (Crashes the program)
    //cout << test2->value << endl;

    // When allocating an object on the "heap" (basically somewhere in your ram),
    // we use the "new" operator. This returns us a pointer to the object's memory.
    test1 = new Test(1);
    test2 = new Test(1.5f);

    // "->" means "*(object.value)" aka same as '.' but automatically dereferenced
    cout << test1->value << endl;
    cout << test2->value << endl;

    // When allocating with new, we must deallocate with delete.
    // (We're the babysitter instead of the compiler).
    delete test1;
    delete test2;

    // After deleting pointers, we want to invalidate them by assigning to nullptr.
    // This will result in our program crashing instead of outputting garbage!

    // Version 1 (bad):
    //cout << test1->value << endl;
    //cout << test2->value << endl;
    //test1 = nullptr;
    //test2 = nullptr;

    // Version 2 (good):
    //test1 = nullptr;
    //test2 = nullptr;
    //cout << test1->value << endl; // crash x1
    //cout << test2->value << endl; // crash x2
}

int main()
{
    // Pointer math examples ranging from automatic to manual
    PointerArithmetic();

    StackConstructorDestructor();
    HeapConstructorDestructor();

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