#pragma once
#include <cassert>
#include <iostream>
using std::cout;
using std::endl;

template<typename T, int QUEUE_MAX>
class Queue
{
public:
	// Add a value to the back of our queue
	void Enqueue(T value)
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
	T Dequeue()
	{
		assert(!Empty());

		// Save the first item
		T temp = data[front];

		// Move front
		++front %= Capacity();

		// Decrement number of elements
		count--;

		// Output copy of the previously first item
		return temp;
	}

	// "First in line"
	T Front()
	{
		return data[front];
	}

	// "Last in line"
	T Back()
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

	void Clear()
	{
		front = back = count = 0;
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