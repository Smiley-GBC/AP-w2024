#include "raylib.h"
#include "Math.h"
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <cassert>
#include <queue>
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

// Dynamic stack - list implementation
class DynamicStack
{
	// "Nested class" -- StackNode is only visible within DynamicStack
private:
	class StackNode
	{
		friend class DynamicStack;
		int value;
		StackNode* next;

		// Constructor
		StackNode(int value, StackNode* next = nullptr)
		{
			this->value = value;
			this->next = next;
		}
	};

	StackNode* top;
public:
	DynamicStack()
	{
		top = nullptr;
	}

	void Push(int value)
	{
		top = new StackNode(value, top);
	}

	int Pop()
	{
		assert(!IsEmpty());
		int value = top->value;
		StackNode* temp = top;
		top = top->next;
		delete temp;
		return value;
	}

	bool IsEmpty() const
	{
		return (!top);
	}
};

constexpr int QUEUE_MAX = 8;


class Queue
{
public:
	// Add a value to the back of our queue
	void Enqueue(int value)
	{
		assert(!Full());

		// Insert the new item
		data[back] = value;

		// Move back
		++back %= Capacity();

		// Increment number of elements
		count++;
	}

	// Remove and return the front of our queue
	int Dequeue()
	{
		assert(!Empty());

		// Save the first item
		int temp = data[front];

		// Move front
		++front %= Capacity();

		// Decrement number of elements
		count--;

		// Output copy of the previously first item
		return temp;
	}

	// "First in line"
	int Front()
	{
		return data[front];
	}

	// "Last in line"
	int Back()
	{
		return data[back];
	}

	bool Empty()
	{
		return count == 0;
	}

	bool Full()
	{
		return Count() == Capacity();
	}

	int Count()
	{
		return count;
	}

	int Capacity()
	{
		return QUEUE_MAX;
	}

	void Print()
	{
		if (Empty()) return;
		int counter = 0;
		int i = front;
		while (counter < Count())
		{
			cout << data[i] << endl;
			++i %= Capacity();
			counter++;
		}
	}

private:
	int data[QUEUE_MAX];
	int front = 0;
	int back = 0;
	int count = 0;
};

void StackTest();
void QueueTest();
void StackSTL();
void QueueSTL();

int main()
{
	//StackTest();
	QueueTest();
	return 0;
}

void StackTest()
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
}

void QueueTest()
{
	Queue queue;
	queue.Enqueue(3);
	queue.Enqueue(6);
	queue.Enqueue(9);

	cout << "Expecting 3, 6, 9:" << endl;
	queue.Print();

	cout << "Expecting 6, 9:" << endl;
	queue.Dequeue();
	queue.Print();

	cout << "Expecting 9:" << endl;
	queue.Dequeue();
	queue.Print();

	cout << "Expecting nothing!" << endl;
	queue.Dequeue();
	queue.Print();
}

void StackSTL()
{

}

void QueueSTL()
{
	queue<int> queue;
	queue.push(1);
	queue.push(2);
	queue.push(3);

	while (!queue.empty())
	{
		// Get first in line
		cout << queue.front() << endl;

		// Remove first in line
		queue.pop();
	}
}
