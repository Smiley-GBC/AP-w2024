#include "Math.h" // <-- ignore this, its just so the rendering framework (raylib) can compile
#include <iostream>
using namespace std;

class Test
{
// Accessible anywhere (even outside the class)
public:
	int a = 3;

	// Default (parameter-less) constructor.
	// All objects must have a default constructor. If not created, the compiler creates it.
	Test()
	{
		cout << "Test created" << endl;
	}

	// Same goes for destructor.
	~Test()
	{
		cout << "Test destroyed" << endl;
	}

// Accessible in this class and derived classes
protected:
	int b = 2;

// Accessible only within this class
private:
	int c = 1;
};

class SuperTest : Test
{
	void Print()
	{
		cout << a << endl;
		cout << b << endl;
		//cout << c << endl; <-- inaccessible (private, only visible within Test)
	}
};

struct PowerUp
{
	PowerUp(float speed)
	{
		this->speed = baseSpeed + speed;
	}

	float speed;
	static float baseSpeed;
};

float PowerUp::baseSpeed = 100.0f;

// 3 types of polymorphism:
// 1. Old school (switch statements)
// 2. Behaviour only (function pointers)
// 3. Object-oriented (data + behaviour) <-- tested on this one in the exam
struct Shape
{
	// "Pure virtual method" (virtual method with no implementation, hence the = 0)
	virtual float Area() = 0;
};

struct Circle : Shape
{
	// could also use "override", difference is final means we cannot override anymore
	// ie we can't make an Oval class that overrides Circle's Area if we use final 
	float Area() final
	{
		return PI * 2.0f * radius;
	}

	float radius;
};

struct Rectangle : Shape
{
	float Area() final
	{
		return width * height;
	}

	float width;
	float height;
};

struct Triangle : Shape
{
	float Area() final
	{
		return width * height * 0.5f;
	}

	float width;
	float height;
};

int main()
{
	Test* t2 = new Test; // <-- allocated on the heap. "Whatever we create, we must destroy".
	delete t2;
	Test t; // <-- allocated on the stack. "Compiler does out babysitting"
	t.a;
	//t.b; <-- inaccessible (protected, only visible within Test & SuperTest)
	//t.c; <-- inaccessible (private, only visible within Test)

	PowerUp a(50.0f);
	PowerUp::baseSpeed += 50.0f;
	PowerUp b(50.0f);
	//PowerUp c; <-- Error because no default constructor is defined. Only parameterized constructors available!

	Circle circle;
	circle.radius = 10.0f;

	Rectangle rectangle;
	rectangle.width = 20.0f;
	rectangle.height = 10.0f;

	Triangle triangle;
	triangle.width = 20.0f;
	triangle.height = 10.0f;

	Shape* shapes[] = { &circle, &rectangle, &triangle };
	for (Shape* shape : shapes)
		cout << shape->Area() << endl;
	
	// And always remember... friends can see each other's privates!
	return 0;
}
