#include "raylib.h"
#include "Math.h"

#include "Stack.h"	// Custom LIFO
#include "Queue.h"	// Custom FIFO

#include <stack>	// Built-in "STL" LIFO
#include <queue>	// Built-in "STL" FIFO

#include <iostream>
using namespace std;

template<typename T>
struct Node
{
	T data;
	Node<T>* next = nullptr;
};

// "NodeFunc is a pointer to a function that returns void and accepts 1 integer argument"
using NodeFunc = void(*)(int&);

class List
{
public:

	// Destroy list by walking it and deleting each element
	~List()
	{
		Clear();
	}

	void Clear()
	{
		Node<int>* current = head;
		while (current != nullptr)
		{
			Node<int>* temp = current;
			current = current->next;
			delete temp;
		}
		head = nullptr;
	}

	void Add(int number)
	{
		if (head == nullptr)
		{
			// Initialize our list if there's nothing in it
			head = new Node<int>;
			head->data = number;
		}
		else
		{
			// Loop until we find the last element
			Node<int>* current = head;
			while (current->next != nullptr)
			{
				current = current->next;
			}

			// Update the last element to point to the new node
			Node<int>* node = new Node<int>;
			current->next = node;
			node->data = number;
		}
	}

	// TODO 1 -- create a Get function
	// TODO 2 -- modify the Remove method to output the removed value
	void Remove(int number)
	{
		// Case 1: nothing in the list
		if (head == nullptr)
			return;

		// Case 2: first element in list (head) is the element we want to remove
		if (head->data == number)
		{
			Node<int>* next = head->next;
			delete head;
			head = next;
		}

		// Case 3: need to make previous element point to element after the one we want to remove
		Node<int>* current = head;
		Node<int>* previous = nullptr;
		
		// Loop until we've reached the end or found our number
		while (current != nullptr && current->data != number)
		{
			previous = current;
			current = current->next;
		}

		// Once our loop exits, if current is non-null, we've found the number!
		// (Otherwise if current is null we've searched the entire list without luck)
		if (current != nullptr)
		{
			previous->next = current->next;
			delete current;
		}
	}

	void ForEach(NodeFunc each)
	{
		Node<int>* current = head;
		while (current != nullptr)
		{
			each(current->data);
			// Instead of printing, we can call our generic node function!
			//cout << current->data << endl;
			current = current->next;
		}
	}

	void PrintRecursive(Node<int>* current)
	{
		// Base case: we've reached the end (node is nullptr)
		if (current == nullptr)
			return;

		// Recursive case: print and advance
		printf("Current node value: %i\n", current->data);
		PrintRecursive(current->next);
	}

	// Print every number in our list by walking it and outputting the data of each node
	void Print()
	{
		Node<int>* current = head;
		while (current != nullptr)
		{
			cout << current->data << endl;
			current = current->next;
		}
	}

	//private:
	Node<int>* head = nullptr;
};

void StackTest();
void QueueTest();
void StackSTL();
void QueueSTL();

int main()
{
	List list;
	list.Add(1);
	list.Add(2);
	list.Add(3);
	list.Print();

	list.Remove(2);
	list.Print();

	//cout << "Custom stack test:" << endl;
	//StackTest();
	//
	//cout << endl << "Custom queue test:" << endl;
	//QueueTest();
	//
	//cout << endl << "STL stack test:" << endl;
	//StackSTL();
	//
	//cout << endl << "STL queue test:" << endl;
	//QueueSTL();

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
