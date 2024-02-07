//#include <raylib.h>
#include <Math.h>
#include <iostream>
#include <string>
using namespace std;

// "Old-school" polymorphism
enum MathType
{
	ADD,
	SUB,
	MUL,
	DIV
};

float MathOperation(float a, float b, MathType type)
{
	switch (type)
	{
	case ADD:
		return a + b;

	case SUB:
		return a - b;

	case MUL:
		return a * b;

	case DIV:
		return a / b;
	}
}

// Function pointers (or "delegates" in C#)
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

struct Character
{
	virtual string Name() = 0;
};

struct Edwin : public Character
{
	string Name() final
	{
		return "Edwin";
	}
};

// Virtual methods (method overriding, object-oriented style)
struct MathOp
{
	// = 0 means "pure-virtual" function. *Forces* the derived class to override said method!
	virtual float Operation(float a, float b) = 0;
};

struct AddOp : public MathOp
{
	float Operation(float a, float b) final
	{
		return a + b;
	}
};

struct SubOp : public MathOp
{
	float Operation(float a, float b) final
	{
		return a - b;
	}
};

struct MulOp : public MathOp
{
	float Operation(float a, float b) final
	{
		return a * b;
	}
};

struct DivOp : public MathOp
{
	float Operation(float a, float b) final
	{
		return a / b;
	}
};

int main()
{
	Character* edwin = new Edwin;

	float a = 1.0f;
	float b = 2.0f;

	// Method 1 -- old school
	MathType mathType;

	mathType = ADD;
	cout << MathOperation(a, b, mathType) << endl;

	mathType = SUB;
	cout << MathOperation(a, b, mathType) << endl;

	mathType = MUL;
	cout << MathOperation(a, b, mathType) << endl;

	mathType = DIV;
	cout << MathOperation(a, b, mathType) << endl;

	// Method 2 -- function pointers
	DecimalMath dm = nullptr;

	dm = Add;
	cout << endl << dm(a, b) << endl;

	dm = Sub;
	cout << dm(a, b) << endl;

	dm = Mul;
	cout << dm(a, b) << endl;

	dm = Div;
	cout << dm(a, b) << endl;

	// Method 3 -- virtual methods (OOP)
	MathOp* op = nullptr;

	op = new AddOp;
	cout << endl << op->Operation(a, b) << endl;

	op = new SubOp;
	cout << op->Operation(a, b) << endl;

	op = new MulOp;
	cout << op->Operation(a, b) << endl;

	op = new DivOp;
	cout << op->Operation(a, b) << endl;

	return 0;
}