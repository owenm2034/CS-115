// Name: Owen Monus
// Student Number: 200482797
// Date: Sept 10, 2022

#include "myFunction.h"

/* Function:  readArray
   Purpose:   To read values from a file into an array.
   Parameters: Base address of an array.
   Returns:   void
-----------------------------------------------------------*/
void readArray(int twoDArray[][COLUMN_SIZE], string inFile)
{

  ifstream inpF;
  int i, j;

  inpF.open(inFile);

  for (i = 0; i < ROW_SIZE; i++)    
  {
    for (j = 0; j < COLUMN_SIZE; j++) 
    {
	    inpF >> twoDArray[i][j];    
    }
  }  

  inpF.close();

} // end readArray function

/* Function:  printArray
   Purpose:   To print values from a file into an array.
   Parameters: Base address of an array.
   Returns:   void
-----------------------------------------------------------*/
void printArray(int twoDArray[][COLUMN_SIZE]) {
  for (unsigned int i = 0; i < ROW_SIZE; i++)    
  {
    for (unsigned int j = 0; j < COLUMN_SIZE; j++) 
    {
	    cout << twoDArray[i][j] << " ";    
    }
    cout << endl;
  }  
} //end printArray function

/* Function:  sumArray
   Purpose:   To sum values from a file into an array.
   Parameters: Two arrays to be added together, an array to record the sums.
   Returns:   void
-----------------------------------------------------------*/
void sumArray(int twoDArrayOne[][COLUMN_SIZE], int twoDArrayTwo[][COLUMN_SIZE], int sumArray[][COLUMN_SIZE]) {
  for (unsigned int i = 0; i < ROW_SIZE; i++)    
  {
    for (unsigned int j = 0; j < COLUMN_SIZE; j++) 
    {
	    sumArray[i][j] = (twoDArrayOne[i][j] + twoDArrayTwo[i][j]);    
    }
  }  
} //end sumArray function
