// Name: Owen Monus 
// Student Number: 200482797
// Date:  Sep 16, 2022

#include <iostream>
#include <string>
using namespace std;

const unsigned int NUM_OF_EMPLOYEES = 5;

struct Employee
{
  string name;
  int id;
  double salary;
};

//print the values of the Employee structure (each record on one line)
void printEmployee(const Employee& c);

//ask the user for input and return the Employee structure
Employee readEmployee();

//----Add findEmployee prototype for Step 2----
int findEmployee(const Employee array[],int tId,int num);