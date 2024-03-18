#include "raylib.h"
#include "Math.h"
#include <iostream>
using namespace std;

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 800;

template<typename T>
struct Node
{
	T data;
	Node<T>* next = nullptr;
};

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

private:
	Node<int>* head = nullptr;
};

void NumberNodes()
{
	Node<int> head;
	Node<int> number2, number3;
	head.data = 1;
	number2.data = 2;
	number3.data = 3;

	head.next = &number2;
	number2.next = &number3;

	// Walk the list by starting at the head and advancing till there's no more connections
	Node<int>* current = &head;
	while (current != nullptr)
	{
		cout << current->data << endl;
		current = current->next;
	}
}

void NumberList()
{
	List list;
	list.Add(1);
	list.Add(2);
	list.Add(3);
	list.Print();
	list.Clear();
	list.Print();
	list.Print();
}

void PathFollowing()
{
	// p = "point", r = "render"
	Node< Vector2> p0, r0;
	Node< Vector2> p1, r1;
	Node< Vector2> p2, r2;
	Node< Vector2> p3, r3;
	p0.data = r0.data = { SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.2f };
	p1.data = r1.data = { SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.2f };
	p2.data = r2.data = { SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.8f };
	p3.data = r3.data = { SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.8f };

	// Path (p) end connects to start, whereas render (r) ends at 3
	p0.next = &p1; r0.next = &r1;
	p1.next = &p2; r1.next = &r2;
	p2.next = &p3; r2.next = &r3;
	p3.next = &p0;

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");
	SetTargetFPS(60);
	float r = 20.0f;

	float time = 0.0f;
	Node<Vector2>* a = &p0;	// a = start
	Node<Vector2>* b = &p1;	// b = end
	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();
		time += dt;
		Vector2 c = Lerp(a->data, b->data, time);

		// Change interval if close to the destination
		if (Distance(b->data, c) < 10.0f)
		{
			time = 0.0f;
			a = b;
			b = b->next;
		}

		BeginDrawing();
		ClearBackground(RAYWHITE);
		Node<Vector2>* current = &r0;
		while (current != nullptr)
		{
			DrawCircleV(current->data, r, RED);
			current = current->next;
		}
		DrawCircleV(c, r, BLUE);
		EndDrawing();
	}
	CloseWindow();
}

void Count(int number)
{
	// Recursive Case -- "condition for calling the function again"
	if (number > 0)
	{
		printf("%i\n", number);
		Count(number - 1);
	}
	else
	// Base Case -- "condition to exit recursion"
	{
		printf("*End recursion*");
	}
}

int main()
{
	//NumberNodes();
	//NumberList();
	//PathFollowing();
	printf("Iterative count:\n");
	for (int i = 0; i < 5; i++)
	{
		printf("%i\n", i + 1);
	}

	printf("\nRecursive count:\n");
	Count(5);
	
	return 0;
}
