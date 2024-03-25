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

template<typename T, int STACK_MAX>
class Stack
{
public:
	void Push(T value)
	{
		// Ensure we have room in our stack
		assert(count < Capacity());
		data[count] = value;
		count++;
	}

	// Most recently added value in our stack (LIFO)
	T Top()
	{
		// Ensure there's at least one value in our stack!
		assert(count > 0);
		return data[count - 1];
	}

	T Pop()
	{
		T top = Top();
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
	T data[STACK_MAX];
	int count = 0;
};

int main()
{
	Stack<int, 8> integers;
	cout << "Stack push" << endl;
	for (int i = 0; i < 8; i++)
		integers.Push(i);
	integers.Print();

	cout << "Stack pop" << endl;
	for (int i = 0; i < 8; i++)
		cout << integers.Pop() << endl;

	if (integers.Empty())
	{
		cout << "No more numbers :(" << endl;
	}

	// Don't exceed the capacity of our stack!
	if (!integers.Full())
	{
		integers.Push(69);
	}
	integers.Print();

	Stack<float, 4> decimals;
	decimals.Push(Random(-1.0f, 1.0f));
	decimals.Push(Random(-1.0f, 1.0f));
	decimals.Push(Random(-1.0f, 1.0f));
	decimals.Push(Random(-1.0f, 1.0f));
	decimals.Print();
	
	return 0;
}
