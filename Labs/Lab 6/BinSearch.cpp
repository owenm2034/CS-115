// Name: Owen Monus 
// Student Number: 200482797
// Date: Oct 9

// File name: BinSearch.cpp
// Purpose    implementatin of BinSearch.h

#include "BinSearch.h"
#include <iostream>
using namespace std;


////////////////////////////////////////////////////////////////////////////
// Function: void generateArray(IntArrayType intArray, int count)
// Purpose:    Generate an array of random integers in ascending order
// Parameters: intArray: Array of integers in acending order
//             count :   The number of integers in the array 
// Return:     None
////////////////////////////////////////////////////////////////////////////
void generateArray(IntArrayType intArray, int count)
{
  int j;

  srand((unsigned) time(NULL)); // seed the rand() function

  intArray[0] = rand()%10; // pick a random number as the first value
  for (j = 1; j < count; j++)
    // make sure the array is in ascending order
    intArray[j] = intArray[j - 1] + rand()%10 + 2;
}

////////////////////////////////////////////////////////////////////////////
// Function: void printArray(IntArrayType intArray, int count)
// Purpose:    printing the array 
// Parameters: intArray: Array of integers in acending order
//             count :   The number of integers in the array 
// Return:     None
////////////////////////////////////////////////////////////////////////////
void printArray(IntArrayType intArray, int count)
{
  int p;

  //Print header
  cout << "Ones ->";
  for (p = 0; p <= 9; p++)
  {
    cout << setw(4) << p << " |";
  }
  cout << endl;
  cout << "Tens ||" << setw(60) << setfill('=')<< '|' << endl << setfill(' ');
   
  for (p = 0; p < count; p++)
  {
    //Label new rows
    if (p % 10 == 0)
      cout << setw(4) << p/10 << " ||";
      
    //Print the array value
    cout << setw(4) << intArray[p] << " |";

    //End rows
    if (p % 10 == 9)
      cout << endl;   
  }

  cout << endl;
}



////////////////////////////////////////////////////////////////////////////
// Function: 
//     int binarySearch(IntArrayType intArray, int low, int high, int target)
// Purpose:    search for "target" in an ordered integer array
// Parameters: intArray: Array of integers in acending order
//             low:      The starting index
//             high:     The ending index
//             target:   The integer value to search
// Return:     The index of the value if found
//             -1 if not found
////////////////////////////////////////////////////////////////////////////
int binarySearch(IntArrayType intArray, int low, int high, int target)
{
  int mid, difference;
  //  int loopCtr = 1;

  while (low <= high)
  {
    mid = (low + high) / 2;
    difference = intArray[mid] - target;
    //---Compare section step one: cout Statements Here----
  
    
    if (difference == 0)         // if intArray[mid] equals target
      return mid;
    else if (difference < 0)     // if intArray[mid] is less than target
      low = mid + 1;
    else
      high = mid - 1;
  }

  return -1;   // If reach here, target was not found.
}



