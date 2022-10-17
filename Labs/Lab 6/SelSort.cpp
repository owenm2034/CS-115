// Name: Owen Monus
// Student Number: 200482797
// Date:

//File name: SelSort.cpp
// Purpose:  Implementation of Selection Sort

#include "SelSort.h"

using namespace std;


////////////////////////////////////////////////////////////////////
// Function: SelSort(IntArrayType IntArray, int Count)
// Purpose:  Given an integer array with "Count" number of elements,
//           sort the elements in ascending order
// Parameters: IntArray: an integer array to hold MAXINDEX elements
//             Count:    number of elements
// Return:     None
////////////////////////////////////////////////////////////////////
void selSort(IntArrayType intArray, int size)
{
  int searchIndex, indexOfMin, tempValue;

  for (int currentIndex = 0; currentIndex < size; currentIndex++)
  {
    indexOfMin = currentIndex;

    // Find index of smallest element in unsorted section of elements
    for(searchIndex = currentIndex + 1; searchIndex < size; searchIndex++)
	   if(intArray[indexOfMin] > intArray[searchIndex])
        indexOfMin = searchIndex;
        
    // Exchange items at position indexOfMin and currentIndex
    if (indexOfMin > currentIndex)
    {
	    tempValue = intArray[indexOfMin];
	    intArray[indexOfMin] = intArray[currentIndex];
	    intArray[currentIndex] = tempValue;
    }
  }
}

//////////////////////////////////////////////////////////////////////
// Function: void GenerateArray(IntArrayType IntArray, int Count);
// Purpose:  Given "Count", generate "Count" number of random integers
//           and put them in IntArray
// Parameters: IntArray: an integer array to hold MAXINDEX elements
//             Count:    number of elements in the array
// Return:     None
//////////////////////////////////////////////////////////////////////
void generateArray(IntArrayType intArray, int count)
{
  int k;

  srand((unsigned) time(NULL));  // seed the random number generator

  for (k = 0; k < count; k++)
    intArray[k] = rand() % 1000;
}

////////////////////////////////////////////////////////////////////////////
// Function: void PrintArray(IntArrayType IntArray, int Count);
// Purpose:  Print out the content of "IntArray"
// Parameters: IntArray: an integer array to hold MAXINDEX elements
//             Count:    number of elements in the array
// Return:     None
////////////////////////////////////////////////////////////////////////////
void printArray(IntArrayType intArray, int count)
{
  int j;

  for (j = 0; j < count; j++)
  {
    cout << setw(5) << intArray[j];
    if (j % 10 == 9)   // check the remainder after division by 10
      cout << endl;
  }

  cout << endl;
}
