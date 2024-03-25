#pragma once
#include <cassert>
#include <iostream>
using std::cout;
using std::endl;

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

	void Clear()
	{
		count = 0;
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