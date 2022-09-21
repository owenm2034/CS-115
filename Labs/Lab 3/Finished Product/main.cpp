// Name: Owen Monus
// Student Number: 200482797
// Date:  Sep 16, 2022

// Filename: main.cpp
// Purpose: Implement functions to read in and print an Employee struct
//          and write another function that passes in an array of Employees and
//          returns the index of the found id
//          (the functions will be stored in Employee.cpp)

#include "Employee.h"
#include <iomanip>
#include <iostream>
using namespace std;

int main() {
	// declare an array of Employees
	Employee employeeArray[NUM_OF_EMPLOYEES];
	// declare a variable to store index of Employees array where the id was
	// found
	int employeeIndex;
	// declare a variable to store the Employee id to search for in array
	int employeeId;

	cout << fixed << showpoint << setprecision(2);

	// read in data for each employee
	for (int i = 0; i < NUM_OF_EMPLOYEES; i++) {
		employeeArray[i] = readEmployee();
		cin.ignore(256, '\n');
	}
	cout << endl;
	// print out data for each employee
	for (int i = 0; i < NUM_OF_EMPLOYEES; i++) {
		printEmployee(employeeArray[i]);
	}

	//----Add code below for Step2----
	// prompt the user for an id
	cout << "Enter an id to look for: ";
	cin >> employeeId;
	// call the findEmployee function
	employeeIndex = findEmployee(employeeArray, employeeId, NUM_OF_EMPLOYEES);
	// if found, display the name of the employee that goes with the id
	if (employeeIndex != -1) {
		cout << "Found Employee: " << employeeArray[employeeIndex].name << endl;
	} else
		cout << "Did not find an Employee with that Id!";
}
