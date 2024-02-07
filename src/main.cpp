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
public:
	virtual void Draw() = 0;

	unsigned int vertexCount;
	float length;
	float area;
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

// Cannot override Draw any further since its declared "final" (last override) in circle
//struct Oval : public Circle
//{
//	void Draw() override
//	{
//
//	}
//};

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
	delete shape;

	shape = new Rectangle;
	shape->Draw();
	delete shape;

	shape = new Triangle;
	shape->Draw();
	delete shape;
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

int main()
{
	cout << "Drawing manually. " << endl;
	//DrawManuallyFP();
	DrawManuallyOOP();
	
	cout << "Drawing Automatically" << endl;
	//DrawAutomaticallyFP();
	DrawAutomaticallyOOP();

	return 0;
}