// Name: Owen Monus
// Student Number: 200482797
// Date: September 6th, 2022

// Filename: lab1Grocery.cpp
// Purpose: To implement Uncle Bob's simple small-town store calculator
//           as described in the programming exercise description.

#include <iomanip>
#include <iostream>
using namespace std;

const int NUM = 5;

int main() {
	// This is for printing money in the proper format with two decimal places
	cout << setprecision(2) << fixed;

	// 1. Declare two arrays one for cost and one for tax
	double costArray[NUM];
	double taxArray[NUM] = {0};

	// 2. Declare additional variables such as letter input, totals for cost and
	// tax.
	char taxAppliedChoice;
	double totalCost = 0.0, totalTax = 0.0;

	// 3. Loop five times
	for (int i = 0; i < NUM; i++) 
  {
		// I. prompt the user for cost
		cout << "cost? ";

		// II. input the cost into the array
		cin >> costArray[i];

		// III. prompt for y and n
		cout << "tax? (y/n) ";

		// IV. input the y and n
		cin >> taxAppliedChoice;

		// V. if the letter is equal to y, then store the tax into the tax array
		if (taxAppliedChoice == 'y')
			taxArray[i] = costArray[i] * 0.1;
	}

	// 4. Print (cout) "For your review, here are your values:" with an endl.
	//   Then print some headers for the columns of Cost and Tax on a new line
  cout << "For your review, here are your values:" << endl;
  cout << setw(10) << "Cost" << setw(10) << "Tax" << endl;
  
	// 5. Loop five times
	// I. print the cost and the tax nicely in columns (Hint: try setw(10))
	// II. add the current element in the cost array to the "totalCost"
	// III. add the current element in the tax array to the "totalTax"
  for(int i = 0; i < NUM; i++) {
    cout << setw(10) << costArray[i] << setw(10) << taxArray[i] << endl;
    totalCost += costArray[i];
    totalTax += taxArray[i];
  }
  
	/*6. Print a line of dashes followed by an endl.
		 Then print the "totalCost" and "totalTax" nicely in columns */
  cout << "********************" << endl;
  cout << setw(10) << totalCost << setw(10) << totalTax << endl;
	
  // 7. Print a message "Your total bill is:" and the total bill amount
  cout << "Your total bill is: " << (totalTax + totalCost) << endl;

  return 0;
}