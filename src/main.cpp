//#include "raylib.h"
#include "Math.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

//int Add(int a, int b)
//{
//    return a + b;
//}
//
//float Add(float a, float b)
//{
//    return a + b;
//}

template<typename T>
T Add(T a, T b)
{
    cout << "Generic add: " << a + b << endl;
    return a + b;
}

class Array
{
public:
    void Add(int value)
    {
        if (count < capacity)
        {
            // Append value and increment count if enough space
            data[count] = value;
            count++;
        }
        else
        {
            // Otherwise, double the space, copy old values and delete old storage
            int* newData = new int[(count + 1) * 2];
            for (int i = 0; i < count; i++)
            {
                newData[i] = data[i];
            }
            newData[count] = value;
            capacity = (count + 1) * 2;
            count++;

            delete[] data;
            data = newData;
        }
    }

    int Get(int index)
    {
        return GetHelper(index);
    }

    int operator[](int index)
    {
        return GetHelper(index);
    }

    int Count() { return count; }

private:
    int* data = nullptr;
    int count = 0;      // number of elements in array
    int capacity = 0;   // space for available elements

    int GetHelper(int index)
    {
        // Ensure positive & less than number of elements in our array
        assert(index >= 0 && index < count);

        // Ensure we have more than 0 elements in our array!
        assert(count > 0);

        return data[index];
    }
};

int main()
{
    Array arr;
    arr.Add(1);
    arr.Add(2);
    arr.Add(3);
    arr.Add(4);

    for (int i = 0; i < arr.Count(); i++)
    {
        cout << arr[i] << endl;
    }

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