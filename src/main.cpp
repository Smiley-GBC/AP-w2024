#include "raylib.h"
#include "Math.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	const char* filePath = "File Test.txt";

	// Two types of c++ file streams -- ifstream (input), and ofstream (output)
	ofstream outFile;
	outFile.open(filePath);
	outFile << "Top secret information" << endl;
	outFile.close();
	//remove("File Test.txt");

	ifstream inFile;
	inFile.open(filePath);
	string fileContents;

	// Stream extraction operator stops whenever it encounters a "delimiter"
	//inFile >> fileContents;

	// We have to use getline if we'd like to read a file line-by-line!
	getline(inFile, fileContents);

	inFile.close();
	cout << fileContents;

	return 0;
}
