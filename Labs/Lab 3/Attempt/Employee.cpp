// Name: Owen Monus
// Student Number: 200482797
// Date:  Sep 16, 2022

#include "Employee.h"

void printEmployee(const Employee &c) {
	cout << "The Employee info is: " << c.name << ", " << c.id << ", $"
		 << c.salary << endl;
}

Employee readEmployee() {
	Employee tempEmp;
	cout << "Emplyee Name?: ";
	getline(cin, tempEmp.name); // command to input a string
	cout << "Employee ID?: ";
	cin >> tempEmp.id;
	cout << "Employee Yearly Salary?: ";
	cin >> tempEmp.salary;

	return tempEmp;
}