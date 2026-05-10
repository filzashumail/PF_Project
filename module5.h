// FILZA SHUMAIL 25I-0627 SECTION B
// SUBHAN AHMED  25I-0522 SECTION C

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

// MODULE 5

void find(int*** grid, char** names, int* ids, float* gpas, int* statuses, int numStudents, int nd, int nf, int nr)
{
    int targetID;
    cout << "Enter Student ID to search: ";
    cin >> targetID;
    cin.ignore(1000, '\n');

    int indx = -1;

    for (int i = 0; i < numStudents; i++)
    {
        if (ids[i] == targetID)
        {
			indx = i;
            break;
        }
    }

    if (indx != -1)
    {
        const char* status;
        if (statuses[indx] == 0)
            status = "STUDYING";
        else if (statuses[indx] == 1)
            status = "WARNING";
        else
            status = "GRADUATING";

        cout << "\n  Student Found:" << endl;
        cout << "  Name    : " << names[indx] << endl;
        cout << "  ID      : " << ids[indx] << endl;
        cout << "  GPA     : " << fixed << setprecision(2) << gpas[indx] << endl;
        cout << "  Status  : " << status << endl;

        bool located = false;
        for (int i = 0; i < nd && !located; i++)
        {
            for (int j = 0; j < nf && !located; j++)
            {
                for (int k = 0; k < nr; k++)
                {
                    if (*(*(*(grid + i) + j) + k) == targetID)
                    {
                        cout << "  Location: Dept: " << (i + 1) << " | Floor: " << (j + 1) << " | Room: " << (k + 1) << endl;
                        located = true;
                        break;
                    }
                }
            }
        }
    }
    else
    {
        cout << "\n  Student with ID " << targetID << " not found." << endl;
    }
}

void jump(int* currentDept, int* currentFloor, int nd, int nf)
{
    do
    {
        cout << "Enter Department (1 to " << nd << "): ";
        cin >> *currentDept;
        cin.ignore(1000, '\n');
        (*currentDept)--;

        if (*currentDept < 0 || *currentDept >= nd)
        {
            cout << "  Invalid. ";
        }
    } while (*currentDept < 0 || *currentDept >= nd);

    do
    {
        cout << "Enter Floor (1 to " << nf << "): ";
        cin >> *currentFloor;
        cin.ignore(1000, '\n');
        (*currentFloor)--;

        if (*currentFloor < 0 || *currentFloor >= nf)
        {
            cout << "  Invalid. ";
        }
    } while (*currentFloor < 0 || *currentFloor >= nf);
}
