// FILZA SHUMAIL 25I-0627 SECTION B
// SUBHAN AHMED  25I-0522 SECTION C

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;


// MODULE 3

unsigned char timeStep(int*** grid, char** &names, int* &ids, float* &gpas, int* &statuses, int &numStudents, int &step, int nd, int nf, int nr)
{
	if (numStudents == 0)
	{
		cout << "No students enrolled. Enroll students before simulating." << endl;
		return 0;
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
		}	
                }
		
	if (flags & 0x04)
		cout << "\n\u2605One or more students graduated this step." << endl;

	cout << "\n--- Step " << step << " Summary ---" << endl;
	cout << "Active students now: " << numStudents << endl;
	 return flags;
}
