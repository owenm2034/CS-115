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
  int array2[ROW_SIZE][COLUMN_SIZE];
  int arrayOfSums[ROW_SIZE][COLUMN_SIZE];
  string fileName;

  // prompt user for input
  cout << "Please enter the name of the file containing data for Array 1: ";
  cin >> fileName;
     
  // read user provided file into array1
  readArray(array1,fileName);

  // prompt user for input
  cout << "Please enter the name of the file containing data for Array 2: ";
  cin >> fileName;

  // read user provided file into array2
  readArray(array2, fileName);

  // sum the values of array1 and array2 into arrayOfSums
  sumArray(array1, array2, arrayOfSums);

  // print the contents of arrayOfSums index by index
  cout << "The Sum is:" << endl;
  printArray(arrayOfSums);

  return 0;
}

