// FILZA SHUMAIL 25I-0627 SECTION B
// SUBHAN AHMED  25I-0522 SECTION C

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

//MODULE 2

bool findFreeRoom(int*** grid, int nd, int nf, int nr, int &d, int &f, int &r, int &scount) {
	int j, k;  
	for (int i = d; i < nd; i++) 
    {
		if (i==d) 
        { 
            j=f; 
        }
		else 
        { 
            j=0;
        }
        
		for (; j < nf; j++) 
        {
			if (i == d && j == f) 
            { 
                k=r+1;
            }
			else 
            { 
                k=0; 
            }
			for (; k < nr; k++) 
            {
				if (*(*(*(grid + i) + j) + k) == 0) 
                {
					d = i; f = j; r = k; 
                    return true;
                }
				else 
                { 
                    scount++; 
                }
			}
		}
	}
	return false;
}

void enrollStudent(int*** grid, char** &names, int* &ids, float* &gpas, int* &statuses, int &numStudents, int nd, int nf, int nr)
{
	int d, f, r, scount = 0, newID; //scount = skip count
	char tname[100]; //temporary

	cout << "Enter student name: ";
	cin.getline(tname, 100);
	//validation
	if (strlen(tname) == 0) 
	{
		cout << "Invalid name" << endl;
		return;
	}

	//Before anything else check if there is room for another student
	//Generating a random dep, room and floor
	d = rand() % nd;
	f = rand() % nf;
	r = rand() % nr;

	//Checking if occupied (and finding next room)
	if (*(*(*(grid + d) + f) + r) != 0) //!=0 so someone is in there
	{ 
		bool findr = findFreeRoom(grid, nd, nf, nr, d, f, r, scount); 
		if (!findr) {
			cout << "All rooms are occupied!" << endl;
			return;
		}
	}

	//allocating name now
	char* name = new char[strlen(tname) + 1]; //strlen(name)+1 bytes for the name
	for (int i = 0; i <= (int)strlen(tname); i++)
	{
		name[i] = tname[i];
	}

	//giving sequential ID (using 1000 as staring point because it looks professional)
	newID = 1000 + numStudents + 1;

	//New array,copying, deleting old and updating pointer for Ids, names, gpa and statuses

	//IDS
	int* nIds = new int[numStudents + 1];
	for (int i = 0; i < numStudents; i++)
	{
		nIds[i] = ids[i];
	}
	nIds[numStudents] = newID; //the newest student at the end
	delete[] ids; //deleting the old array
	ids = nIds; //pointing to the new one

	//NAMES
	char** nnames = new char* [numStudents + 1];
	for (int i = 0; i < numStudents; i++)
	{
		nnames[i] = names[i];
	}
	nnames[numStudents] = name; //the newest student at the end
	delete[] names; //deleting the old array
	names = nnames; //pointing to the new one

	//GPA
	float* nGpas = new float[numStudents + 1]; //float cause GPA has decimals
	for (int i = 0; i < numStudents; i++)
	{
		nGpas[i] = gpas[i];
	}
	nGpas[numStudents] = 0.0f; //new student so GPA is 0
	delete[] gpas;
	gpas = nGpas;


	//STATUSES
	int* nStatus = new int[numStudents + 1];
	for (int i = 0; i < numStudents; i++)
	{
		nStatus[i] = statuses[i];
	}
	nStatus[numStudents] = 0; //we start at zero cause new student (studying)
	delete[] statuses;
	statuses = nStatus;

	//student count has now increased
	numStudents++;

	*(*(*(grid + d) + f) + r) = newID;

	//outputs
	cout << "\nStudent enrolled!" << endl;
	cout << "Assigned ID: " << newID << endl;
	cout << "Department: " << d+1 << endl;
	cout << "Floor: " << f+1 << endl;
	cout << "Room: " << r+1 << endl;
	cout << "Slots skipped: " << scount << endl;
}
