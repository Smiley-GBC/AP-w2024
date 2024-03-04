#include "raylib.h"
#include "Math.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void SimpleFileIO()
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
}

struct Weapon
{
	string description;
	int damage;
	int type;
	float range;
	float weight;
};

int main()
{
	Weapon outWeapon, inWeapon;
	outWeapon.description = "The mighty excalibur";
	outWeapon.damage = 9999;
	outWeapon.type = 420;
	outWeapon.range = 10.0f;
	outWeapon.weight = 25.0f;

	const char* filePath = "Weapons.txt";
	ofstream outFile;
	outFile.open(filePath);
	outFile
		<< outWeapon.type << ' '
		<< outWeapon.damage << ' '
		<< outWeapon.range << ' '
		<< outWeapon.weight << ' '
		<< outWeapon.description << endl;
	outFile.close();

	ifstream inFile;
	inFile.open(filePath);
	inFile >> inWeapon.type >> inWeapon.damage >> inWeapon.range >> inWeapon.weight;
	getline(inFile, inWeapon.description);
	inFile.close();

	return 0;
}
