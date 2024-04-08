#include <iostream>
using namespace std;

class Test
{
// Accessible anywhere (even outside the class)
public:
	int a = 3;

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
		cout << b << endl;
		//cout << c << endl; <-- inaccessible (private, only visible within Test)
	}
};

int main()
{
	Test t;
	t.a;
	//t.b; <-- inaccessible (protected, only visible within Test & SuperTest)
	//t.c; <-- inaccessible (private, only visible within Test)
	return 0;
}
