//#include "raylib.h"
#include "Math.h"
#include <iostream> // input-output stream (console stuff)
#include <array>    // standard static array
#include <vector>   // standard dynamic array (C# List<T>)
#include <string>   // standard string (text)
#include <cassert>  // stardard assertions (crash if false)
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

// We can also say template<class T>
// Its like class vs struct -- class T and typename T are exactly the same!
template<typename T>
T Add(T a, T b)
{
    cout << "Generic add: " << a + b << endl;
    return a + b;
}

// Dynamic array (can add & remove) --> Practice exercise: implement a Remove(int index) method!
template<typename T>
class DynamicArray
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

// Static (fixed-size) array
template<typename T, int capacity>
class Array
{
public:
    void Add(T value)
    {
        // If the array is full, don't add!
        assert(count < capacity, "Cannot add, array is full!");
        data[count] = value;
        count++;
    }

    // Swaps the last element with the element at index, then removes the last element
    void Remove(int index)
    {
        // Ensure index is valid (non-negative and within range)
        assert(index >= 0 && index < count);

        // Store the last element in our array
        T temp = data[count - 1];

        // Overwrite value at index to be removed with value at last index
        data[index] = temp;

        // Decrement count to effectively "remove" the value
        count--;
    }

    T operator[](int index)
    {
        assert(index >= 0 && index < count);
        assert(count > 0);
        return data[index];
    }

    int Count() { return count; }

private:
    T data[capacity];
    int count = 0;
};

int main()
{
    // Standard static array of 4 decimal numbers
    std::array<float, 4> stlArray;
    
    // Standard dynamic array of integers
    std::vector<int> stlDynamicArray;

    Array<int, 3> arr;
    arr.Add(4);
    arr.Add(5);
    arr.Add(6);
    arr.Remove(0);

    for (int i = 0; i < arr.Count(); i++)
    {
        cout << arr[i] << endl;
    }

    DynamicArray<int> intArray;
    intArray.Add(1);
    intArray.Add(2);
    intArray.Add(3);
    intArray.Add(4);

    DynamicArray<float> floatArray;
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