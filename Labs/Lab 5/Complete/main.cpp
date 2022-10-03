// Name: Owen Monus
// Student Number: 200482797
// Date: Oct 2nd, 2022

/* Filename: main.cpp
   Purpose: To convert the structure into a class implementation. */

#include "Cat.h"
#include <iostream>
using namespace std;

int main()
{
  Cat myCat;

  string colours[5];
  colours[0] = "white";
  colours[1] = "";
  Cat averageCat (44, 24, 28, "blue", "medium", colours);

  myCat.readCat();

  cout << "The average cat's first colour is " << averageCat.getFirstFurColour() << endl;

  cout << "-------------------------------------------------------"<< endl;
  cout << "This is myCat:" << endl;
  myCat.printCat();
  if (myCat.isTaller(averageCat))
  {
	  cout << "My cat is taller than the average cat\n";
  }
  else
  {
	  cout << "My cat is shorter than the average cat\n";
  }
  if (myCat.isCalico())
  {
	  cout << "My cat is a calico\n";
  }
  
  return 0;
}
