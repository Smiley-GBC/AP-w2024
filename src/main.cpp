//#include <raylib.h>
#include <Math.h>
#include <iostream>
using namespace std;

// structs are "coppied" by default in C#
//struct

// classes are "referenced" by default in C#
//class

struct Test
{
	int data;
};

// Passed by pointer
// If we do this we can change our memory address which causes problems...
// Hence, its generally more safe to pass by reference!
//(*test).data; // same as "->"
//void Change1(Test* test)
//{
//	test++;
//	cout << test->data << endl;
//}

// Passed by reference
// References work as "automatically dereferenced pointers" internally
//void Change2(Test& test)
//{
//	cout << test.data << endl;
//}

// Adding "const" AFTER the pointer makes its address constant
//void Change3(Test* const test)
//{
//	// Doesn't compile
//	test++;
//}

// Adding "const" BEFORE the pointer makes its value constant
//void Change4(const Test* test)
//{
//	// Doesn't compile
//	test->data++;
//}

void Change5(const Test* const test)
{
	cout << test->data << endl;
}

void Change6(const Test& test)
{
	cout << test.data << endl;
}

//Pointer to a function that returns void and takes no arguments
using DrawShape = void(*)();

struct Shape
{
	virtual void Draw() = 0;

	unsigned int vertexCount;
	float area;
	float length;
};

struct Circle : public Shape
{
	void Draw() final
	{
		cout << " #####" << endl;
		cout << "#     #" << endl;
		cout << "#     #" << endl;
		cout << "#     #" << endl;
		cout << " ##### " << endl;
	}
};

struct Rectangle : public Shape
{
	void Draw() final
	{
		cout << "########" << endl;
		cout << "#      #" << endl;
		cout << "#      #" << endl;
		cout << "#      #" << endl;
		cout << "########" << endl;
	}
};

struct Triangle : public Shape
{
	void Draw() final
	{
		cout << "    #   " << endl;
		cout << "  #  #  " << endl;
		cout << "#      #" << endl;
		cout << "########" << endl;
	}
};

void DrawManuallyOOP()
{
	Shape* shape = nullptr;

	shape = new Circle;
	shape->Draw();
	//(*shape).Draw(); //The same as shape->Draw()

	shape = new Rectangle;
	shape->Draw();

	shape = new Triangle;
	shape->Draw();
}

void DrawAutomaticallyOOP()
{
	Shape* shape[] = { new Circle, new Rectangle, new Triangle };

	for (int i = 0; i < 3; i++)
	{
		shape[i]->Draw();
		delete shape[i];
	}
}

void DrawCircle()
{
	cout << " #####" << endl;
	cout << "#     #" << endl;
	cout << "#     #" << endl;
	cout << "#     #" << endl;
	cout << " ##### " << endl;
}

void DrawRectangle()
{
	cout << "########" << endl;
	cout << "#      #" << endl;
	cout << "#      #" << endl;
	cout << "#      #" << endl;
	cout << "########" << endl;
}

void DrawTriangle()
{
	cout << "    #   " << endl;
	cout << "  #  #  " << endl;
	cout << "#      #" << endl;
	cout << "########" << endl;
}

void DrawManuallyFP()
{
	DrawShape drawShape = nullptr;

	drawShape = DrawCircle;
	drawShape();

	drawShape = DrawRectangle;
	drawShape();

	drawShape = DrawTriangle;
	drawShape();
}

void DrawAutomaticallyFP()
{
	DrawShape shapes[] = { DrawCircle, DrawRectangle, DrawTriangle };

	for (int i = 0; i < 3; i++) {
		shapes[i]();
	}
}

using DecimalMath = float(*)(float, float);
// Integer version of the above
//using IntegerMath = int(*)(int, int);

float Add(float a, float b) {
	return a + b;
}

float Sub(float a, float b) {
	return a - b;
}

float Mul(float a, float b) {
	return a * b;
}

float Div(float a, float b) {
	return a / b;
}

int main()
{
	float a = 1.0f;
	float b = 2.0f;

	// Pointer to a function, so if we don't want any function, we can use nullptr!
	DecimalMath dm = nullptr;

	dm = Add;
	cout << dm(a, b) << endl;

	dm = Sub;
	cout << dm(a, b) << endl;

	dm = Mul;
	cout << dm(a, b) << endl;

	dm = Div;
	cout << dm(a, b) << endl;

	cout << "Drawing manually. " << endl;
	DrawManuallyFP();
	
	cout << "Drawing Automatically" << endl;
	DrawAutomaticallyFP();

	return 0;
}