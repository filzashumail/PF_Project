// FILZA SHUMAIL 25I-0627 SECTION B
// SUBHAN AHMED  25I-0522 SECTION C

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cstring>
using namespace std;

#include "module1.h"
#include "module2.h"
#include "module3.h"
#include "module4.h"
#include "module5.h"
#include "module6.h"

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
	char choice;
        bool md3work = false;

	if (!readfile("config.txt", numDepts, numFloors, numRooms))
	{
		cout << "config.txt not found. Please enter configuration values:" << endl;

		numDepts  = campusCheck("  Number of Departments:      ");
		numFloors = campusCheck("  Number of Floors per Dept:  ");
		numRooms  = campusCheck("  Number of Rooms per Floor:  ");

		writefile("config.txt", numDepts, numFloors, numRooms);
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

	CampusGrid = initCampus(numDepts, numFloors, numRooms);

	cout << "Campus grid allocated and initialised. Total rooms: " << (numDepts * numFloors * numRooms) << endl;
    
	loadDatabase(CampusGrid, names, ids, gpas, statuses, numStudents, numDepts, numFloors, numRooms);

         drawDashboard(CampusGrid, names, ids, gpas, statuses, numStudents, numDepts, numFloors, numRooms, currentDept, currentFloor, step); 

	do 
	{
	        md3work=false;
		cin.get(choice);
		if (choice != '\n')         
		{ 
			cin.ignore(1000, '\n'); 
		}
		system("clear"); 
		if (choice == 'E' || choice == 'e')
			enrollStudent(CampusGrid, names, ids, gpas, statuses, numStudents, numDepts, numFloors, numRooms);
		else if (choice == 'X' || choice == 'x')
		{ 
			cout << "\nExiting UniVault" << endl; break; 
		}
		else if (choice == '\n')
		{
			unsigned char flags = timeStep(CampusGrid, names, ids, gpas, statuses, numStudents, step, numDepts, numFloors, numRooms);
		         drawDashboard(CampusGrid, names, ids, gpas, statuses, numStudents, numDepts, numFloors, numRooms, currentDept, currentFloor, step); md3work=true;
		         
		     
                 if (flags & 0x04)
                 {
                   for (int i = 0; i < numStudents; i++)
                   {
                 if (statuses[i] == 2)
                 {
                   for (int l = 0; l < numDepts; l++)
                    for (int m = 0; m < numFloors; m++)
                     for (int n = 0; n < numRooms; n++)
                       if (*(*(*(CampusGrid+l)+m)+n) == ids[i])
                                *(*(*(CampusGrid+l)+m)+n) = 0;

                delete[] names[i];

                for (int j = i; j < numStudents - 1; j++)
                {
                    names[j]    = names[j+1];
                    ids[j]      = ids[j+1];
                    gpas[j]     = gpas[j+1];
                    statuses[j] = statuses[j+1];
                }

                char** newNames = new char*[numStudents-1];
                for (int j = 0; j < numStudents-1; j++) newNames[j] = names[j];
                delete[] names; names = newNames;

                int* newIds = new int[numStudents-1];
                for (int j = 0; j < numStudents-1; j++) newIds[j] = ids[j];
                delete[] ids; ids = newIds;

                float* newGpas = new float[numStudents-1];
                for (int j = 0; j < numStudents-1; j++) newGpas[j] = gpas[j];
                delete[] gpas; gpas = newGpas;

                int* newStatuses = new int[numStudents-1];
                for (int j = 0; j < numStudents-1; j++) newStatuses[j] = statuses[j];
                delete[] statuses; statuses = newStatuses;

                numStudents--;
                i--;
                }
                }
                }
                	
			 
		}
		else if (choice == 'S' || choice == 's')
		{
			saveDatabase(CampusGrid, names, ids, gpas, statuses, numStudents, numDepts, numFloors, numRooms);
		}
		else if (choice == 'F' || choice == 'f')
		{
			find(CampusGrid, names, ids, gpas, statuses, numStudents, numDepts, numFloors, numRooms);
			cout << "\nPress Enter to continue...";
    		cin.get(); // wait for input b4 redraw
			
		}
		else if (choice == 'J' || choice == 'j')
		{
			jump(&currentDept, &currentFloor, numDepts, numFloors);
		}
		else
        { 
            cout << "Invalid option" << endl; 
        }
         if(!md3work)
         {
            drawDashboard(CampusGrid, names, ids, gpas, statuses, numStudents, numDepts, numFloors, numRooms, currentDept, currentFloor, step); 
         }
        
	} while (true);


	// deallocating memory
	for (int i = 0; i < numStudents; i++)
	{
		delete[] names[i];
	}
	delete[] names;
	delete[] ids;
	delete[] gpas;
	delete[] statuses;

	emptyCampus(CampusGrid, numDepts, numFloors);
	CampusGrid = nullptr;

	return 0;
}
