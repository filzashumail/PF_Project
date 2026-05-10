// FILZA SHUMAIL 25I-0627 SECTION B
// SUBHAN AHMED  25I-0522 SECTION C

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cstring>
using namespace std;

// MODULE 1

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

//MODULE 2

bool findFreeRoom(int*** grid, int nd, int nf, int nr, int &d, int &f, int &r, int &scount) {
	//saving original collision position
	int startD = d, startF = f, startR = r;

	for (int i = d; i < nd; i++) 
    {
		int startFloor;
		//if still in collision department, continue from collision floor
		if (i == d)
        { 
            startFloor = f; 
        }
		else 
        { 
            startFloor = 0; 
        }
		for (int j = startFloor; j < nf; j++) 
        {
			int startRoom;
			//if still on exact collision floor, continue from next room
			if (i == d && j == f)
            { 
                startRoom = r + 1; 
            }
			else 
            { 
                startRoom = 0; 
            }
			for (int k = startRoom; k < nr; k++) 
            {
				scount++;
				// free room found
				if (*(*(*(grid + i) + j) + k) == 0) 
                { 
                    d = i; f = j; r = k; return true; 
                }
			}
		}
	}

	//If no room available after the randomly generated one, we loop around
	for (int i = 0; i <= startD; i++) 
    {
		int endFloor;
		// stop at original floor in last department
		if (i == startD) 
        { 
            endFloor = startF + 1; 
        }
		else 
        { 
            endFloor = nf; 
        }
		for (int j = 0; j < endFloor; j++) 
        {
			int endRoom;
			// stop at original room in collision floor
			if (i == startD && j == startF) 
            { 
                endRoom = startR; 
            }
			else 
            { 
                endRoom = nr; 
            }
			for (int k = 0; k < endRoom; k++) 
            {
				scount++;
				// free room found
				if (*(*(*(grid + i) + j) + k) == 0) 
                {
					d = i; f = j; r = k; 
                    return true;
				}
			}
		}
	}
	//no free room anywhere
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
		bool findr = findFreeRoom(grid, nd, nf, nr, d, f, r, scount); //function to find a free room
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

// MODULE 3

void runTimeStep(int*** grid, char** &names, int* &ids, float* &gpas, int* &statuses, int &numStudents, int &step, int nd, int nf, int nr)
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
        const char* statusStr;
        //here we setting the event of the student
        if      
            (statuses[i] == 0) statusStr = "STUDYING";
        else if (statuses[i] == 1) 
            statusStr = "WARNING";
        else                       
            statusStr = "GRADUATING";

        // nd here we taking action on that lil nga
        // progressing
        if (roll >= 1 && roll <= 5)
        {
            gpas[i] += 0.1f;
            if (gpas[i] > 4.00f) 
                gpas[i] = 4.00f;

            flags |= 0x01; // set progress bit

            cout << "  " << names[i] << " (" << ids[i] << ")"<< " -> Progress  | GPA: " << fixed << setprecision(2) << gpas[i]<< " | " << statusStr << endl;
        }
        // steady
        else if (roll >= 6 && roll <= 8)
        {
            // no change to GPA or status
            cout << "  " << names[i] << " (" << ids[i] << ")" << " -> Steady    | GPA: " << fixed << setprecision(2) << gpas[i] << " | " << statusStr << endl;
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
            // students don't store coordinates so a full scan is required
            // pointer arithmetic mandatory — bracket indexing on grid is forbidden
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

            // compact all four arrays by shifting every element after i one position left
            for (int j = i; j < numStudents - 1; j++)
            {
                names[j] = names[j + 1];
                ids[j] = ids[j + 1];
                gpas[j] = gpas[j + 1];
                statuses[j] = statuses[j + 1];
            }

            // shrink names to numstdnts-1
            char** newNames = new char*[numStudents - 1];

            for (int j = 0; j < numStudents - 1; j++)
                newNames[j] = names[j];

            delete[] names;
            names = newNames;

            // shrink ids 
            int* newIds = new int[numStudents - 1];

            for (int j = 0; j < numStudents - 1; j++)
                newIds[j] = ids[j];

            delete[] ids;
            ids = newIds;

            // shrink gpas
            float* newGpas = new float[numStudents - 1];

            for (int j = 0; j < numStudents - 1; j++)
                newGpas[j] = gpas[j];

            delete[] gpas;
            gpas = newGpas;

            // shrink statuses
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

    // graduation report is gated behind bitwise check 

    if (flags & 0x04)
        cout << "\n  \u2605 One or more students graduated this step." << endl;

    cout << "\n--- Step " << step << " Summary ---" << endl;
    cout << "Active students now: " << numStudents << endl;
}

//MODULE 4
void drawDashboard(int*** grid, char** names, int* ids, float* gpas, int* statuses, int numStudents, int nd, int nf, int nr, int currentDept, int currentFloor, int step){
 //clearing the screen

int search, temID;

//formatting
cout<<"\n========================================================================================================\n"; 
cout<<"                              UniVault  .  LIVE RESOURCE DASHBOARD                                               \n";
cout<<"========================================================================================================\n";
cout<<"\n[DEPT: " << right << setfill('0') << setw(2) << (currentDept+1) << " - CS]         [FLOORS: "<< setw(2) << nf << "]         [ROOMS: "<< setw(2) << nr << "]         [STEP: "<< setw(3) << step << "]\n";

cout << setfill(' ');//to reset

cout<<"\n--------------------------------------------------------------------------------------------------------\n";
cout<< left;
cout<< setw(24) << "ROOM ADDR" << setw(15) << "ID" << setw(24) << "NAME" << setw(15) << "GPA" << "STATUS";
cout<<"\n--------------------------------------------------------------------------------------------------------\n";

for(int i=0 ; i<nr ; i++){


//for room adress (pointer notation in code)(void*)(&grid[currentDept][currentFloor][i])
//ID = grid[currentDept][currentFloor][i];

temID = *(*(*(grid + currentDept) + currentFloor) + i) ;


//finding the index for names, gpa and status
for(int j=0 ; j<numStudents ; j++){
if(ids[j]==temID) { search = j; break; }}

if (temID == 0) { 

cout<< setw(24) << ( (void*)(*(*(grid + currentDept) + currentFloor) + i) ) << setw(15) << "----" << setw(24) << "---------------" << setw(15) << "0.00" << "EMPTY" << endl; }

else {

if(statuses[search]==0) {
cout<< setw(24) << ( (void*)(*(*(grid + currentDept) + currentFloor) + i) ) << setw(15) << ( temID ) << setw(24) << ( *(names + search) ) << setw(15) << fixed << setprecision(2) << (*(gpas + search) ) << "STUDYING" << endl;}

else if (statuses[search]==1) {
cout<< setw(24) << ( (void*)(*(*(grid + currentDept) + currentFloor) + i) ) << setw(15) << ( temID ) << setw(24) << ( *(names + search) ) << setw(15) << fixed << setprecision(2) << (*(gpas + search) ) << "WARNING \u26A0" << endl;}

else if (statuses[search]==2) {
cout<< setw(24) << ( (void*)(*(*(grid + currentDept) + currentFloor) + i) ) << setw(15) << ( temID ) << setw(24) << ( *(names + search) ) << setw(15) << fixed << setprecision(2) << (*(gpas + search) ) << "GRADUATING \u2605" << endl;}
}}
cout<<"\n--------------------------------------------------------------------------------------------------------\n";
cout<< "COMMANDS: [ENTER] Step  |  [E] Enroll  |  [J] Jump  |  [F] Find  |  [S] Save  |  [X] Exit\n";
cout<<"\n========================================================================================================\n";

}

// MODULE 5


// MAIN
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

    CampusGrid = initCampus(numDepts, numFloors, numRooms);

    cout << "Campus grid allocated and initialised. Total rooms: " << (numDepts * numFloors * numRooms) << endl;


do {
    
    drawDashboard(CampusGrid, names, ids, gpas, statuses, numStudents, numDepts, numFloors, numRooms, currentDept, currentFloor, step); 

cin.get(choice);
if (choice != '\n')         
    { cin.ignore(1000, '\n'); }
system("clear"); 
if (choice == 'E' || choice == 'e')
enrollStudent(CampusGrid, names, ids, gpas, statuses, numStudents, numDepts, numFloors, numRooms);
else if (choice == 'X' || choice == 'x')
{ cout << "\nExiting UniVault" << endl; break; }
 else if (choice == '\n')
        {
            runTimeStep(CampusGrid, names, ids, gpas, statuses, numStudents, step, numDepts, numFloors, numRooms);
        }
else if (choice == 'J' || choice == 'j')
{
cout << "Enter Department (1 to " << numDepts << "): ";
cin >> currentDept;
cin.ignore(1000, '\n');
currentDept--;
cout << "Enter Floor (1 to " << numFloors << "): ";
cin >> currentFloor;
cin.ignore(1000, '\n');
currentFloor--;
//validation
while (currentDept < 0 || currentDept >= numDepts) { cout<<"\nInvalid Department, Enter again: "; cin >> currentDept; }
while (currentFloor < 0 || currentFloor >= numFloors) { cout<<"\nInvalid Floor, Enter again: "; cin >> currentFloor; }
}
else { cout << "Invalid option" << endl; }
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

    freeCampus(CampusGrid, numDepts, numFloors);
    CampusGrid = nullptr;

    return 0;
}


//Rozzy chill rozzy chill rozzy chill rozzy chill rozzy chill rozzy chill rozzy chill rozzy chill rozzy chill
// EVERYONE GET IN THE CAR WHAT THE IMPOSSIBLE THIS ISNT THE CAR NOOOOOOOOOOOO JOJO

