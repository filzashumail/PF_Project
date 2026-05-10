// FILZA SHUMAIL 25I-0627 SECTION B
// SUBHAN AHMED  25I-0522 SECTION C

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

// MODULE 1

// read config.txt and returns true if successful, false if file missing
bool readfile(const char* filename, int& numDepts, int& numFloors, int& numRooms)
{
	ifstream file(filename);
	if (!file.is_open())
		return false;

	file >> numDepts >> numFloors >> numRooms;
	file.close();
	return true;
}

void writefile(const char* filename, int numDepts, int numFloors, int numRooms)
{
	ofstream file(filename);
	file << numDepts << endl << numFloors << endl << numRooms  << endl;
	file.close();
}

int*** initCampus(int numDepts, int numFloors, int numRooms)
{
	int*** CampusGrid = new int**[numDepts];

	for (int i = 0; i < numDepts; i++)
	{
		*(CampusGrid + i) = new int*[numFloors];

		for (int j = 0; j < numFloors; j++)
		{
			*(*(CampusGrid + i) + j) = new int[numRooms];

			for (int k = 0; k < numRooms; k++)
			{
				*(*(*(CampusGrid + i) + j) + k) = 0;
			}
		}
	}

	return CampusGrid;
}

void emptyCampus(int*** grid, int numDepts, int numFloors)
{
	for (int i = 0; i < numDepts; i++)
	{
		for (int j = 0; j < numFloors; j++)
		{
			delete[] *(*(grid + i) + j);
		}
		delete[] *(grid + i);
	}
	delete[] grid;
}

// reprompt shah jee for a positive int nd its gna loop til valid input given
int campusCheck(const char* prompt)
{
	int value = 0;
	do
	{
		cout << prompt;
		cin  >> value;
		if (value <= 0)
			cout << "  Invalid. Please enter a number greater than 0." << endl;
	}
	while (value <= 0);

	return value;
}
