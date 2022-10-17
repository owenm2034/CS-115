// Name: Owen Monus
// Student Number: 200482797
// Date: Oct 17, 2022x

// Filename: main.cpp
// Purpose: To practice using overloaded functions and operators

#include "Date.h"
#include <iostream>
using namespace std;

int main()
{
	Date date1;
	int month, day, year;
	
	cout << "Date is: " << date1.getMonth() << "/"
       << date1.getDay() << "/" 
	     << date1.getYear() << endl;

	cout << "Please enter integer Year, Day and Month separated by spaces: ";
	cin >> year >> day >> month;
	date1.setMonth(month);
	date1.setDay(day);
	date1.setYear(year);
	
	cout << "Please enter integer Year, Day and Month separated by spaces: ";
	cin >> year >> day >> month;

	//Calling constructor with three arguments
	Date date2(month, day, year);
	
	/*----------------------------------------------------------*/
	/*-PART 1 Change this code to the comments indicated beside-*/
	/*----------------------------------------------------------*/
  cout << date1 << date2;

  if (date1 == date2)
		cout << "The days are the same." << endl; //same dates
	else
		cout << "The days are different." << endl; //different dates

	++date1;
	++date2;
	cout << "After incrementing" << endl;
	cout << date1 << date2;

	/*----------------------------------------------------------*/
	/*---------------PART 2  Uncomment these lines--------------*/
	/*----------------------------------------------------------*/
/*
	Date date4, date3;
	date3 = date1 + 82;
	date4 = 6 + date2;

	cout << "After addition" << endl;
	cout << date1 << date2 << date3 << date4;
*/

	return 0;
}

