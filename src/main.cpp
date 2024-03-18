#include "raylib.h"
#include "Math.h"
#include <iostream>
#include <string>
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

void InfiniteLoop()
{
	printf("RUN FOR YOUR LIFE IF YOU VALUE YOUR STACK POINTER!!!\n");
	InfiniteLoop();
}

void NoMoreMemory()
{
	printf("Error 404: your PC can't run Cyrsis\n");
}

void MemoryGoofiness()
{
	// 1 byte (char) * 1024 = 1kb
		// 1kb * 1024 = 1mb
		// Our stack is less than 1mb (stack overflow if you run this)!
	char data[1024 * 1024];

	// Heap memory is essentially how much RAM you have (much larger than the stack)
	// Allocate 1mb every iteration (may or may not crash your PC)
	while (true)
	{
		char* memoryleak = new char[1024 * 1024];
	}

	int count = 0;
	//std::set_new_handler(NoMoreMemory);
	try {
		int* pBigDataArray = new int[1000000000L];
	}
	catch (const std::bad_alloc&) {
		NoMoreMemory();
	}
	for (int i = 0; i < 16; i++)
	{
		count = i + 1;
		new char[1024 * 1024 * 1024];
	}
}

int CharacterCount(char check, string text, int position)
{
	// Base case: we've reached the end of the string
	if (position == text.length())
		return 0;

	// Recursive case 1: the current character is a match
	if (text[position] == check)
		return 1 + CharacterCount(check, text, position + 1);
	else
	// Recursive case 2: the current character is not a match
		return CharacterCount(check, text, position + 1);
}

int Factorial(int n)
{
	if (n == 0)
		return 1;
	else
		return n * Factorial(n - 1);
	
	// Short-hand for above. Returns 1 if true, otherwise factorial if false
	//return n == 0 ? 1 : n * Factorial(n - 1);
}

int Fibonacci(int n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return Fibonacci(n - 1) + Fibonacci(n - 2);
}

void RecursiveNumbers()
{
	printf("%i\n", Factorial(6));
	printf("%i\n", Fibonacci(0));	// 0
	printf("%i\n", Fibonacci(1));	// 1
	printf("%i\n", Fibonacci(2));	// 1
	printf("%i\n", Fibonacci(3));	// 2
	printf("%i\n", Fibonacci(4));	// 3
	printf("%i\n", Fibonacci(5));	// 5
	printf("%i\n", Fibonacci(6));	// 8
}

int main()
{
	//InfiniteLoop();
	//MemoryGoofiness();
	//printf("%i\n", CharacterCount('r',"Connor", 0));
	//RecursiveNumbers();

	//NumberNodes();
	//NumberList();
	//PathFollowing();
	//printf("Iterative count:\n");
	//for (int i = 0; i < 5; i++)
	//{
	//	printf("%i\n", i + 1);
	//}
	//
	//printf("\nRecursive count:\n");
	//Count(5);
	
	return 0;
}
