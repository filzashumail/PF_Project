// FILZA SHUMAIL 25I-0627 SECTION B
// SUBHAN AHMED  25I-0522 SECTION C

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

//MODULE 6
void loadDatabase(int*** grid, char** &names, int* &ids, float* &gpas, int* &statuses, int &numStudents, int nd, int nf, int nr)
{
	char temp[100];
	int d, f, r, temID;

	ifstream file("database.txt");
	if (!file.is_open()) 
    { 
        return; 
    }
	file >> numStudents;
	names    = new char*[numStudents];
	ids      = new int[numStudents];
	gpas     = new float[numStudents];
	statuses = new int[numStudents];

	for (int i = 0; i < numStudents; i++) 
    {
		file >> ids[i];
		file.ignore(); //skip space after id
		file.getline(temp, 100, '.'); //read name until .
		file >> gpas[i] >> statuses[i] >> d >> f >> r;
		file.ignore(); //skip newline

		//name 
		names[i] = new char[strlen(temp) + 1];
		for (int j = 0; j <= (int)strlen(temp); j++) 
        {
			names[i][j] = temp[j]; 
        }
	}

	while (file >> d >> f >> r >> temID)
    {
		*(*(*(grid + d) + f) + r) = temID;
    }

	file.close();
}    

void saveDatabase(int*** grid, char** names, int* ids, float* gpas, int* statuses, int numStudents, int nd, int nf, int nr){

	int sdep, sfloor, sroom;

	ofstream file("database.txt");
	file << numStudents << "\n";

	//finding dep, floor and room for each student 
	for (int i = 0; i < numStudents; i++)
    {
		sdep=-67, sfloor=-67, sroom=-67;
		for (int l = 0; l < nd; l++)
        {
			for (int m = 0; m < nf; m++)
            {
				for (int n = 0; n < nr; n++)
                {
					if (*(*(*(grid + l) + m) + n) == ids[i]) 
					{ 
                        sdep = l; sfloor = m; sroom = n; 
                    }
                }
            }
        }
		if (sdep != -67 && sfloor != -67 && sroom != -67) 
        {

			file << ids[i] << " " << names[i] << ". " << fixed << setprecision(2) << gpas[i] << " " << statuses[i] << " " << sdep << " " << sfloor << " " << sroom << endl; 
		}
	}

	//Grid occupancy 
	for (int i = 0; i < numStudents; i++)
    { 
		for (int l = 0; l < nd; l++)
        {
			for (int m = 0; m < nf; m++)
            {
				for (int n = 0; n < nr; n++)
                {
					if (*(*(*(grid + l) + m) + n) == ids[i])
                    { 
						sdep = l; sfloor = m; sroom = n; 
                    }
                }
                
            }
            
        }

		if (sdep != -67 && sfloor != -67 && sroom != -67) 
        {
			file << sdep << " " << sfloor << " " << sroom << " " << ids[i] << endl; 
		}
	}
	file.close();

} 
