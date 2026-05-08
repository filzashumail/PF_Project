#include <iostream>
#include <fstream>
#include <cstdlib>   
#include <ctime>     
#include <iomanip>   

using namespace std;






int main (){

srand(time(0));
int*** CampusGrid = nullptr;
int numDepts=0, numFloors=0, numRooms=0, numStudents=0, step=0, currentFloor=0, currentDept=0;
char** names     = nullptr;
int*   ids       = nullptr;
float* gpas      = nullptr;
int*   statuses  = nullptr;
