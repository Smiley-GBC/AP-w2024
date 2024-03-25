#include "raylib.h"
#include "Math.h"
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <cassert>
using namespace std;

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 800;

constexpr int STACK_MAX = 8;

//template<typename T>
class Stack
{
public:
	void Push(int value)
	{
		// Ensure we have room in our stack
		assert(count < Capacity());
		data[count] = value;
		count++;
	}

	// Most recently added value in our stack (LIFO)
	int Top()
	{
		// Ensure there's at least one value in our stack!
		assert(count > 0);
		return data[count - 1];
	}

	int Pop()
	{
		int top = Top();
		count--;
		return top;
	}

	bool Empty()
	{
		return Count() == 0;
	}

	bool Full()
	{
		return Count() >= Capacity();
	}

	// Number of elements in our stack
	int Count()
	{
		return count;
	}

	// Maximum number of elements our stack can hold
	int Capacity()
	{
		return STACK_MAX;
	}

	void Print()
	{
		for (int i = 0; i < count; i++)
			cout << data[i] << endl;
	}

private:
	int data[STACK_MAX];
	int count = 0;
};

int main()
{
	Stack numbers;
	cout << "Stack push" << endl;
	for (int i = 0; i < 8; i++)
		numbers.Push(i);
	numbers.Print();

	cout << "Stack pop" << endl;
	for (int i = 0; i < 8; i++)
		cout << numbers.Pop() << endl;

	if (numbers.Empty())
	{
		cout << "No more numbers :(" << endl;
	}

	// Don't exceed the capacity of our stack!
	if (!numbers.Full())
	{
		numbers.Push(69);
	}
	numbers.Print();
	
	return 0;
}
