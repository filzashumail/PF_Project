// FILZA SHUMAIL 25I-0627 SECTION B
// SUBHAN AHMED  25I-0522 SECTION C

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

// read config.txt and returns true if successful, false if file missing
bool readConfig(const char* filename, int& numDepts, int& numFloors, int& numRooms)
{
    ifstream file(filename);
    if (!file.is_open())
        return false;

    file >> numDepts >> numFloors >> numRooms;
    file.close();
    return true;
}

// writing config.txt with user provided values
void writeConfig(const char* filename, int numDepts, int numFloors, int numRooms)
{
    ofstream file(filename);
    file << numDepts << endl << numFloors << endl << numRooms  << endl;
    file.close();
}

// allocate 3D campus grid and initialise every room to 0
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

// deallocate the entire 3d campus grid frm heap
void freeCampus(int*** grid, int numDepts, int numFloors)
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
int getPositiveInt(const char* prompt)
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

int main()
{
    srand(time(0));

    int*** CampusGrid = nullptr;
    int numDepts = 0, numFloors = 0, numRooms = 0;
    int numStudents = 0, step = 0, currentFloor = 0, currentDept = 0;

    char** names    = nullptr;
    int*   ids      = nullptr;
    float* gpas     = nullptr;
    int*   statuses = nullptr;

    if (!readConfig("config.txt", numDepts, numFloors, numRooms))
    {
        cout << "config.txt not found. Please enter configuration values:" << endl;

        numDepts  = getPositiveInt("  Number of Departments:      ");
        numFloors = getPositiveInt("  Number of Floors per Dept:  ");
        numRooms  = getPositiveInt("  Number of Rooms per Floor:  ");

        writeConfig("config.txt", numDepts, numFloors, numRooms);
        cout << "  config.txt created successfully." << endl;
    }
    else
    {
        // chk if values read from file are sensible
        if (numDepts <= 0 || numFloors <= 0 || numRooms <= 0)
        {
            cout << "Error: config.txt contains invalid values. Please fix and restart." << endl;
            return 0;
        }
    }

    cout << "\nConfiguration loaded: "<< numDepts  << " dept(s), " << numFloors << " floor(s), "<< numRooms  << " room(s) per floor." << endl;

    // the campus will be initialised here
    CampusGrid = initCampus(numDepts, numFloors, numRooms);

    cout << "Campus grid allocated and initialised. Total rooms: " << (numDepts * numFloors * numRooms) << endl;

    // idhar se apna m2 ya smth krna

    




    // deallocating memory
    freeCampus(CampusGrid, numDepts, numFloors);
    CampusGrid = nullptr;

    return 0;
}