#include <raylib.h>
#include <Math.h>
#include <iostream>

using namespace std;

//Pointer to a function that returns void and takes no arguments
using DrawShape = void(*)();

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

void DrawManually()
{
	DrawShape drawShape = nullptr;

	drawShape = DrawCircle;
	drawShape();

	drawShape = DrawRectangle;
	drawShape();

	drawShape = DrawTriangle;
	drawShape();
}

void DrawAutomatically()
{
	DrawShape shapes[] = { DrawCircle, DrawRectangle, DrawTriangle };

	for (int i = 0; i < 3; i++) {
		shapes[i]();
	}
}

int main()
{
	cout << "Drawing manually. " << endl;
	DrawManually();


	cout << "Drawing Automatically" << endl;
	DrawAutomatically();
	return 0;
}