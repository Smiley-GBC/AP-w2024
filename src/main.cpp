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
struct Item
{
    // We don't need any more arrays since this is the inner layer
    // Just add whatever data an item should have here
    string name = "Candy";
    float price = 2.00f;
};

// Middle layer
struct Store
{
    // See Corporation's explanation
    int itemCount = 0;
    Item* items = nullptr;
    int latitude = 1, longitude = 2;
};

// Outer layer
struct Corporation
{
    // We don't know how many stores the corporation has.
    // Hence, we must make it a dynamic array so we determine
    // the number of stores when our program runs!
    int storeCount = 0;
    Store* stores = nullptr;
    string address = "Test address";
};

void CreateItem(Item& item)
{
    float price = 0.0f;
    cout << "What is the price of your item?" << endl;
    cin >> price;
    item.price = price;
}

void CreateStore(Store& store)
{
    cout << "How many items do you have?" << endl;
    cin >> store.itemCount;
    store.items = new Item[store.itemCount];

    for (int i = 0; i < store.itemCount; i++)
    {
        CreateItem(store.items[i]);
    }
}

void CreateCorporation(Corporation& corp)
{
    cout << "How many stores do you own?" << endl;
    cin >> corp.storeCount;
    corp.stores = new Store[corp.storeCount];

    for (int i = 0; i < corp.storeCount; i++)
    {
        CreateStore(corp.stores[i]);
    }
}

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;
    Table woodTable;
    woodTable.topColor = GRAY;
    woodTable.legsColor = BROWN;
    woodTable.height = 60.0f;
    woodTable.width = 200.0f;
    woodTable.x = screenWidth * 0.5f - woodTable.width * 0.5f;
    woodTable.y = screenHeight * 0.75 - woodTable.height;
    woodTable.legWidth = 10.0f;
    woodTable.legHeight = woodTable.height * 3.0f;
    woodTable.legs[0] = woodTable.x;
    woodTable.legs[1] = woodTable.x + woodTable.legWidth * 3.0f;

    woodTable.legs[2] = woodTable.x + woodTable.width - woodTable.legWidth * 3.0f;
    woodTable.legs[3] = woodTable.x + woodTable.width - woodTable.legWidth;

    // Integer array allocated on the "stack" (constant size)
    int staticIntegers[10]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    //for (int i = 0; i < 10; i++)
    //{
    //    cout << staticIntegers[i] << endl;
    //}

    // Integer array allocated on the "heap" (variable size)
    // The "new" keyword means "allocated on the heap"
    int* dynamicIntegers = new int[10];
    //for (int i = 0; i < 10; i++)
    //{
    //    // We cannot initialize heap-arrays with curly braces,
    //    // So we'll populate it with a for-loop!
    //    dynamicIntegers[i] = i + 1;
    //    cout << "Address of index " << i << ": " << &dynamicIntegers[i] << endl;
    //    cout << "Value of index " << i << ": " << dynamicIntegers[i] << endl;
    //}

    //for (int i = 0; i < 10; i++)
    //{
    //    OutputAddress(staticIntegers, i, 10);
    //}

    //for (int i = 0; i < 10; i++)
    //{
    //    OutputAddress(dynamicIntegers, i, 10);
    //}

    // Pointers doulbe as arrays.
    // We can do "pointer arithmetic" to output individual values of an array by offsetting from the address of the first element
    cout << *(staticIntegers + 0) << endl;
    cout << *(staticIntegers + 1) << endl;
    cout << *(staticIntegers + 2) << endl;
    cout << *(staticIntegers + 3) << endl;
    cout << *(staticIntegers + 4) << endl;
    cout << *(staticIntegers + 5) << endl;
    cout << *(staticIntegers + 6) << endl;
    cout << *(staticIntegers + 7) << endl;
    cout << *(staticIntegers + 8) << endl;
    cout << *(staticIntegers + 9) << endl;

    // Characters are 1 byte wide
    // We're not adding 0 through 9 bytes to the 0th element. We're adding n * sizeof datatype
    char characters[10]{ 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };
    cout << *(characters + 0) << endl;
    cout << *(characters + 1) << endl;
    cout << *(characters + 2) << endl;
    cout << *(characters + 3) << endl;
    cout << *(characters + 4) << endl;
    cout << *(characters + 5) << endl;
    cout << *(characters + 6) << endl;
    cout << *(characters + 7) << endl;
    cout << *(characters + 8) << endl;
    cout << *(characters + 9) << endl;

    cout << "Pointer arithmetic test:" << endl;

    // Offsetting by these two amounts of bytes gives us the last element of our array
    int integer9Offset = sizeof(int) * 9;
    int character9Offset = sizeof(char) * 9;

    // To test, we should see the same value twice in our console!
    cout << *(characters + 9) << endl;
    cout << *(characters + character9Offset) << endl;

    // The integer test is harder to get working because we calculated our offset in bytes,
    // but pointer arithmetic uses the width of the data type so 4 bytes per int + index 9 is a 36 byte offset (4 * 9 = 36)
    //cout << *(staticIntegers + 9) << endl;
    //cout << *(((char*)staticIntegers) + integer9Offset) << endl;

    Corporation corp;
    CreateCorporation(corp);

    for (int i = 0; i < corp.storeCount; i++)
    {
        cout << corp.address << endl;
        for (int j = 0; j < corp.storeCount; j++)
        {
            cout << corp.stores[j].longitude << corp.stores[j].longitude << endl;
            for (int k = 0; k < corp.stores[j].itemCount; k++)
            {
                cout << corp.stores[j].items[k].name << endl;
                cout << corp.stores[j].items[k].price << endl;
            }
        }
    }

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        woodTable.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
