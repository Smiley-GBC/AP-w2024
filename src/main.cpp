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

void NumberList()
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

int main()
{
	//NumberList();

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
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		Node<Vector2>* current = &r0;
		while (current != nullptr)
		{
			DrawCircleV(current->data, r, RED);
			current = current->next;
		}
		//DrawCircleV(p0, r, RED);
		//DrawCircleV(p1, r, RED);
		//DrawCircleV(p2, r, RED);
		//DrawCircleV(p3, r, RED);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
