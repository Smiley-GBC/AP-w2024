//#include "raylib.h"
#include "Math.h"
#include <iostream> // input-output stream (console stuff)
#include <array>    // standard static array
#include <vector>   // standard dynamic array (C# List<T>)
#include <string>   // standard string (text)
#include <cassert>  // stardard assertions (crash if false)
using namespace std;

struct IntSingleton
{
public:
    static int& Instance()
    {
        static int instance;
        return instance;
    }

private:
    IntSingleton() {}
};

struct DecimalSingleton
{
public:
    static float& Instance()
    {
        static float instance;
        return instance;
    }

private:
    DecimalSingleton() {}
};

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

void Counter()
{
    // "function-static" variables persist between calls
    static int count = 1;
    cout << "Counting: x" << count << endl;
    count++;
}

// TODO -- have a lesson on global variables (singleton vs static vs extern)
// Use something cool like sounds or textures to demo it!
struct Test
{
    int value;
};

struct Vec2
{
    float x;
    float y;

    // Unary (1 argument) operator overload example
    // Unary operators can only be "member-wise"
    // (+=, -=, *=, /=, %= are all unary operators because they take 1 argument)
    // (+, -, *, /, %, ==, != are all binary operators because they take 2 arguments)
    Vec2& operator+=(Vec2 v)
    {
        cout << "Values before unary add [x: " << x << ", y: " << y << "]." << endl;
        // Identical to above. "this" is just a pointer to the current object (Vec2*)
        //cout << "Values before unary add [x: " << this->x << ", y: " << this->y << "]." << endl;
        x += v.x;
        y += v.y;
        cout << "Values after unary add [x: " << x << ", y: " << y << "]." << endl;
        return *this;
    }

    // Member-wise binary add
    // (binary operators can be global OR member-wise whereas unary operators can only be member-wise)
    Vec2 operator+(Vec2 b)
    {
        return { x + b.x, y + b.y };
    }
};

struct Vec2Int
{
    int x;
    int y;
};

// Cannot exist at the same time as the member-wise binary add (line 87)
//Vec2 operator+(Vec2 a, Vec2 b)
//{
//    return { a.x + b.x, a.y + b.y };
//}

Vec2Int operator+(Vec2Int a, Vec2Int b)
{
    return { a.x + b.x, a.y + b.y };
}

template<typename T>
struct vec2
{
    T x;
    T y;
};

template<typename T>
vec2<T> operator+(vec2<T> a, vec2<T> b)
{
    return { a.x + b.x, a.y + b.y };
}

template<typename T>
struct Node
{
    T value = 0;
    Node* next = nullptr;
};

void List()
{
    Node<float> n1;
    n1.value = 1.1f;

    Node<float> n2;
    n2.value = 2.2f;

    Node<float> n3;
    n3.value = 3.3f;

    Node<float> n4;
    n4.value = 4.4f;

    Node<float> n5;
    n5.value = 5.5f;

    n1.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
    n4.next = &n5;

    Node<float>* current = &n1;
    while (current != nullptr)
    {
        cout << "Node value: " << current->value << endl;
        current = current->next;
    }
}

void TypeAdd()
{
    Vec2 a{ 1.5f, 2.5f };
    Vec2 b{ 3.5f, 4.5f };
    Vec2 c = a + b;
    c += a;
    cout << c.x << ' ' << c.y << endl;
    
    Vec2Int x{ 1.0f, 2.0f };
    Vec2Int y{ 3.0f, 4.0f };
    Vec2Int z = x + y;
    cout << z.x << ' ' << z.y << endl;
}

void TemplateAdd()
{
    // Compiler error because vec2 needs x & y members but Test only has a value member
    //vec2<Test> t1;
    //vec2<Test> t2;
    //vec2<Test> t3 = t1 + t2;

    vec2<float> a{ 1.5f, 2.5f };
    vec2<float> b{ 3.5f, 4.5f };
    vec2<float> c = a + b;
    cout << c.x << ' ' << c.y << endl;

    vec2<int> x{ 1, 2 };
    vec2<int> y{ 3, 4 };
    vec2<int> z = x + y;
    cout << z.x << ' ' << z.y << endl;
}

int main()
{
    TypeAdd();

    // Single global instance of int
    //Singleton<int>::Instance()++;
    //Singleton<int>::Instance()++;
    //Singleton<int>::Instance()++;
    //cout << Singleton<int>::Instance() << endl;

    // Single global instance of Test
    //Singleton<Test>::Instance().value++;
    //Singleton<Test>::Instance().value++;
    //Singleton<Test>::Instance().value++;
    //Singleton<Test>::Instance().value++;
    //cout << Singleton<Test>::Instance().value << endl;

    return 0;
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