//#include <raylib.h>
#include <Math.h>
#include <iostream>

using namespace std;

//Pointer to a function that returns void and takes no arguments
using DrawShape = void(*)();


//int Add(int i, int i2){
//	return i + i2;
//}
//
//int Add(float i, float i2) {
//	return i + i2;
//}

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

void DrawManually()
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

void DrawAutomatically()
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

//void DrawManually()
//{
//	DrawShape drawShape = nullptr;
//
//	drawShape = DrawCircle;
//	drawShape();
//
//	drawShape = DrawRectangle;
//	drawShape();
//
//	drawShape = DrawTriangle;
//	drawShape();
//}
//
//void DrawAutomatically()
//{
//	DrawShape shapes[] = { DrawCircle, DrawRectangle, DrawTriangle };
//
//	for (int i = 0; i < 3; i++) {
//		shapes[i]();
//	}
//}

int main()
{
	cout << "Drawing manually. " << endl;
	DrawManually();

	
	cout << "Drawing Automatically" << endl;
	DrawAutomatically();

	return 0;
}