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

template<typename T>
class Array
{
public:
    void Add(T value)
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
            T* newData = new T[(count + 1) * 2];
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

    T Get(int index)
    {
        return GetHelper(index);
    }

    T operator[](int index)
    {
        return GetHelper(index);
    }

    int Count() { return count; }

private:
    T* data = nullptr;
    int count = 0;      // number of elements in array
    int capacity = 0;   // space for available elements

    T GetHelper(int index)
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
    Array<int> intArray;
    intArray.Add(1);
    intArray.Add(2);
    intArray.Add(3);
    intArray.Add(4);

    Array<float> floatArray;
    floatArray.Add(4.4f);
    floatArray.Add(3.3f);
    floatArray.Add(2.2f);
    floatArray.Add(1.1f);

    for (int i = 0; i < intArray.Count(); i++)
    {
        cout << intArray[i] << endl;
        cout << floatArray[i] << endl;
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