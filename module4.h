// FILZA SHUMAIL 25I-0627 SECTION B
// SUBHAN AHMED  25I-0522 SECTION C

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

//MODULE 4

void drawDashboard(int*** grid, char** names, int* ids, float* gpas, int* statuses, int numStudents, int nd, int nf, int nr, int currentDept, int currentFloor, int step){
	//clearing the screen

	int search , temID;

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


		//ID = grid[currentDept][currentFloor][i];
		search=-67;
		temID = *(*(*(grid + currentDept) + currentFloor) + i) ;


		//finding the index for names, gpa and status
		for(int j=0 ; j<numStudents ; j++){
			if(ids[j]==temID) { search = j; break; }}

		if (temID == 0) { 

			cout<< setw(24) << ( (void*)(*(*(grid + currentDept) + currentFloor) + i) ) << setw(15) << "----" << setw(24) << "---------------" << setw(15) << "0.00" << "EMPTY" << endl; }

		else {

			if(search!=-67){

				if(statuses[search]==0) {
					cout<< setw(24) << ( (void*)(*(*(grid + currentDept) + currentFloor) + i) ) << setw(15) << ( temID ) << setw(24) << ( *(names + search) ) << setw(15) << fixed << setprecision(2) << (*(gpas + search) ) << "STUDYING" << endl;}

				else if (statuses[search]==1) {
					cout<< setw(24) << ( (void*)(*(*(grid + currentDept) + currentFloor) + i) ) << setw(15) << ( temID ) << setw(24) << ( *(names + search) ) << setw(15) << fixed << setprecision(2) << (*(gpas + search) ) << "WARNING \u26A0" << endl;}

				else if (statuses[search]==2) {
					cout<< setw(24) << ( (void*)(*(*(grid + currentDept) + currentFloor) + i) ) << setw(15) << ( temID ) << setw(24) << ( *(names + search) ) << setw(15) << fixed << setprecision(2) << (*(gpas + search) ) << "GRADUATING \u2605" << endl;}
			}
		}
	}
	cout<<"\n--------------------------------------------------------------------------------------------------------\n";
	cout<< "COMMANDS: [ENTER] Step  |  [E] Enroll  |  [J] Jump  |  [F] Find  |  [S] Save  |  [X] Exit\n";
	cout<<"\n========================================================================================================\n";

}
