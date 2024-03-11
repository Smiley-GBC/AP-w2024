#include "raylib.h"
#include "Math.h"
#include <iostream>
using namespace std;

struct Node
{
	int data;
	Node* next = nullptr;
};

int main()
{
	Node head;
	Node number2, number3;
	head.data = 1;
	number2.data = 2;
	number3.data = 3;

	head.next = &number2;
	number2.next = &number3;

	// Walk the list by starting at the head and advancing till there's no more connections
	Node* current = &head;
	while (current != nullptr)
	{
		cout << current->data << endl;
		current = current->next;
	}

	return 0;
}
