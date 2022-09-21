// Name: Owen Monus
// Student Number: 200482797
// Date: Sept 10, 2022

// Filename: main.cpp
// Purpose: Implement a C++ program to add two 4 by 5 matrices 
//          and then output the results to the screen
//          as outlined in the exercise description.

#include "myFunction.h"

int main()
{
  int array1[ROW_SIZE][COLUMN_SIZE];
  string fileName;

  // prompt user for input
  cout << "Please enter the name of the file containing data for Array 1: ";
  cin >> fileName;
     
  readArray(array1,fileName);
  printArray(array1);

  return 0;
}

