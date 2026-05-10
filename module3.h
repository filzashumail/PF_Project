// FILZA SHUMAIL 25I-0627 SECTION B
// SUBHAN AHMED  25I-0522 SECTION C

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;


// MODULE 3

void timeStep(int*** grid, char** &names, int* &ids, float* &gpas, int* &statuses, int &numStudents, int &step, int nd, int nf, int nr)
{
	if (numStudents == 0)
	{
		cout << "No students enrolled. Enroll students before simulating." << endl;
		return;
	}
	step++;

	cout << "\n=== Time Step " << step << " ===" << endl;

	// flags tracks which events fired across saray students this step
	// declared outside the loop so sath sath bits info rakhay 
	unsigned char flags = 0;

	for (int i = 0; i < numStudents; i++)
	{
		int roll = (rand() % 10) + 1;
		const char* status;
		//here we setting the event of the student
		if      
			(statuses[i] == 0) status = "STUDYING";
		else if (statuses[i] == 1) 
			status = "WARNING";
		else                       
			status = "GRADUATING";

		// nd here we taking action on that lil nga
		// progressing
		if (roll >= 1 && roll <= 5)
		{
			gpas[i] += 0.1;
			if (gpas[i] > 4.00) 
				gpas[i] = 4.00;

			flags |= 0x01; // set progress bit

			cout << "  " << names[i] << " (" << ids[i] << ")"<< " -> Progress  | GPA: " << fixed << setprecision(2) << gpas[i]<< " | " << status << endl;
		}
		// steady
		else if (roll >= 6 && roll <= 8)
		{
			// no change to GPA or status
			cout << "  " << names[i] << " (" << ids[i] << ")" << " -> Steady    | GPA: " << fixed << setprecision(2) << gpas[i] << " | " << status << endl;
		}

		// warning(me)
		else if (roll == 9)
		{
			statuses[i] = 1;
			gpas[i] -= 0.2;

			if (gpas[i] < 0.0) 
				gpas[i] = 0.0;

			flags |= 0x02; 

			cout << "  " << names[i] << " (" << ids[i] << ")" << " -> Warning   | GPA: " << fixed << setprecision(2) << gpas[i]<< " | WARNING" << endl;
		}

		// graduation(not me)
		else if (roll == 10)
		{
			statuses[i] = 2;
			flags |= 0x04; // set graduation bit

			cout << "  " << names[i] << " (" << ids[i] << ")" << " -> Graduated | Removed from registry. Room cleared." << endl;

			// scan entire grid to find and clear this student's room
			for (int l = 0; l < nd; l++)
			{
				for (int m = 0; m < nf; m++)
				{
					for (int n = 0; n < nr; n++)
					{
						if (*(*(*(grid + l) + m) + n) == ids[i])
						{
							*(*(*(grid + l) + m) + n) = 0;
						}
					}
				}
			}

			// free heap memory for this student's name before shifting
			delete[] names[i];

			// compact all four arrays by shifting every element after i one position to the left
			for (int j = i; j < numStudents - 1; j++)
			{
				names[j] = names[j + 1];
				ids[j] = ids[j + 1];
				gpas[j] = gpas[j + 1];
				statuses[j] = statuses[j + 1];
			}

			// shrink everything to numstdnts-1
			char** newNames = new char*[numStudents - 1];

			for (int j = 0; j < numStudents - 1; j++)
				newNames[j] = names[j];

			delete[] names;
			names = newNames;

			int* newIds = new int[numStudents - 1];

			for (int j = 0; j < numStudents - 1; j++)
				newIds[j] = ids[j];

			delete[] ids;
			ids = newIds;

			float* newGpas = new float[numStudents - 1];

			for (int j = 0; j < numStudents - 1; j++)
				newGpas[j] = gpas[j];

			delete[] gpas;
			gpas = newGpas;

			int* newStatuses = new int[numStudents - 1];

			for (int j = 0; j < numStudents - 1; j++)
				newStatuses[j] = statuses[j];

			delete[] statuses;
			statuses = newStatuses;

			numStudents--;
			// decrement i so the shifted student at this index is not skipped
			i--;
		}
	}

	if (flags & 0x04)
		cout << "\n\u2605One or more students graduated this step." << endl;

	cout << "\n--- Step " << step << " Summary ---" << endl;
	cout << "Active students now: " << numStudents << endl;
}
