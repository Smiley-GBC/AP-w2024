#include "raylib.h"
#include "Math.h"

#include "Stack.h"	// Custom LIFO
#include "Queue.h"	// Custom FIFO

#include <stack>	// Built-in "STL" LIFO
#include <queue>	// Built-in "STL" FIFO

#include <iostream>
using namespace std;

void StackTest();
void QueueTest();
void StackSTL();
void QueueSTL();

int main()
{
	cout << "Custom stack test:" << endl;
	StackTest();

	cout << endl << "Custom queue test:" << endl;
	QueueTest();

	cout << endl << "STL stack test:" << endl;
	StackSTL();

	cout << endl << "STL queue test:" << endl;
	QueueSTL();

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
	Queue<int, 8> queue;
	queue.Enqueue(3);
	queue.Enqueue(6);
	queue.Enqueue(9);
	queue.Enqueue(12);

	for (int i = 0; i < 4; i++)
	{
		queue.Enqueue(i);
	}
	// 8 elements in queue --> back == [7], front = 0 (because nothing's been removed)

	for (int i = 0; i < 3; i++)
	{
		queue.Dequeue();
	}
	// 5 elements in queue --> back == [7], front = 3 

	queue.Print();

	cout << "Queue wrap:" << endl;
	for (int i = 0; i < 3; i++)
	{
		queue.Enqueue(i * 3);
	}

	queue.Print();
	//cout << "Expecting 3, 6, 9:" << endl;
	//queue.Print();
	//
	//cout << "Expecting 6, 9:" << endl;
	//queue.Dequeue();
	//queue.Print();
	//
	//cout << "Expecting 9:" << endl;
	//queue.Dequeue();
	//queue.Print();
	//
	//cout << "Expecting nothing!" << endl;
	//queue.Dequeue();
	//queue.Print();
}

void StackSTL()
{
	stack<int> stack;
	stack.push(1);
	stack.push(2);
	stack.push(3);

	while (!stack.empty())
	{
		// Get most recently added
		cout << stack.top() << endl;

		// Remove most recently added
		stack.pop();
	}
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
