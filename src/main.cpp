#include "raylib.h"
#include "Math.h"
#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
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

	void Print()
	{
		cout
			<< description << ' '
			<< type << ' '
			<< damage << ' '
			<< range << ' '
			<< weight << endl;
	}
};

void SingleWeaponIO()
{
	Weapon outWeapon, inWeapon;
	outWeapon.description = "The mighty excalibur";
	outWeapon.damage = 9999;
	outWeapon.type = 420;
	outWeapon.range = 10.0f;
	outWeapon.weight = 25.0f;

	const char* filePath = "Weapon.txt";
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
}

void SaveWeapon(const Weapon& weapon, ofstream& outFile)
{
	outFile
		<< weapon.type << ' '
		<< weapon.damage << ' '
		<< weapon.range << ' '
		<< weapon.weight << ' '
		<< weapon.description << endl;
}

void LoadWeapon(Weapon& weapon, ifstream& inFile)
{
	inFile >> weapon.type >> weapon.damage >> weapon.range >> weapon.weight;
	getline(inFile, weapon.description);
}

void MultipleWeaponIO()
{
	array<Weapon, 3> outWeapons;
	outWeapons[0].description = "The mighty excalibur";
	outWeapons[0].damage = 9999;
	outWeapons[0].type = 420;
	outWeapons[0].range = 10.0f;
	outWeapons[0].weight = 25.0f;

	outWeapons[1].description = "The almost mighty excalipur";
	outWeapons[1].damage = 6666;
	outWeapons[1].type = 2;
	outWeapons[1].range = 100.0f;
	outWeapons[1].weight = 5.0f;

	outWeapons[2].description = "Magic Dave the epic stick";
	outWeapons[2].damage = 1234;
	outWeapons[2].type = 3;
	outWeapons[2].range = 1000.0f;
	outWeapons[2].weight = 250.0f;

	// ofstream files are truncated (erased) by default.
	// If you'd like to change this, pass the ios::app flag.
	// Its generally easier if you don't allow file appending as it makes logic more complex.
	const char* filePath = "Weapons.txt";
	ofstream outFile;
	outFile.open(filePath/*, ios::app*/);

	// Save the amount of weapons before we save the weapons themselves
	// (so we know how many weapons to load)
	outFile << outWeapons.size() << endl;
	for (int i = 0; i < outWeapons.size(); i++)
		SaveWeapon(outWeapons[i], outFile);
	outFile.close();

	int weaponCount = 0;
	vector<Weapon> inWeapons;
	ifstream inFile;
	inFile.open(filePath);
	inFile >> weaponCount;
	inWeapons.resize(weaponCount);
	for (int i = 0; i < weaponCount; i++)
	{
		LoadWeapon(inWeapons[i], inFile);
		inWeapons[i].Print();
	}
}

void SimpleBinaryIO()
{
	// Binary output
	int outNumbers[10]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	ofstream outFile;
	outFile.open("Numbers.bin", ios::binary | ios::out | ios::trunc);
	outFile.write((char*)outNumbers, 10 * sizeof(int));
	outFile.close();

	// Binary input
	int inNumbers[10];
	ifstream inFile;
	inFile.open("Numbers.bin", ios::binary | ios::in);
	inFile.read((char*)inNumbers, 10 * sizeof(int));
	inFile.close();

	// Sets the contents of inNumbers to be 0
	memset(inNumbers, 0, 10 * sizeof(int));

	// Text output
	outFile.open("Numbers.txt");
	for (int i = 0; i < 10; i++)
		outFile << outNumbers[i] << endl;
	outFile.close();

	// Text input
	inFile.open("Numbers.txt");
	for (int i = 0; i < 10; i++)
		inFile >> inNumbers[i];
	inFile.close();
}

// Binary files are convenient when data types are all primitive (int, float, bool, etc)
// but more involved when they contain *variable-length* information such strings
struct BinaryWeapon
{
	int damage;
	int type;
	float range;
	float weight;
};

void BinaryObjectIO()
{
	BinaryWeapon outWeapon, inWeapon;
	outWeapon.damage = 9999;
	outWeapon.type = 420;
	outWeapon.range = 10.0f;
	outWeapon.weight = 25.0f;

	// Binary output
	ofstream outFile;
	outFile.open("Weapon.bin", ios::binary | ios::out | ios::trunc);
	outFile.write((char*)&outWeapon, sizeof(Weapon));
	outFile.close();

	// Binary input
	ifstream inFile;
	inFile.open("Weapon.bin", ios::binary | ios::in);
	inFile.read((char*)&inWeapon, sizeof(Weapon));
	inFile.close();
}

int main()
{
	// Uncomment your file demo of choice!
	//SimpleFileIO();
	//SingleWeaponIO();
	//MultipleWeaponIO();
	//SimpleBinaryIO();
	//BinaryObjectIO();
	return 0;
}
