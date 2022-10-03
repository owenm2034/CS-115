// Name: Owen Monus
// Student Number: 200482797
// Date: Oct 2nd, 2022

#include "Cat.h"
#include <iostream>
using namespace std;

Cat::Cat() {
  length = 0;
  height = 0;
  tailLength = 0;
  eyeColour = "";
  furClassification = ""; //none, short, medium, long
  for (int i = 0; i < NUM_COL; i ++) {
    furColours[i] = "";  
  }
}

Cat::Cat (double l, double h, double tL, string eC, string fCl, const string furCol[])
{
  int i = 0;
  length = l;
  height = h;
  tailLength = tL;
  eyeColour = eC;
  furClassification = fCl; //none, short, medium, long
  while (furCol[i] != "")
  {
    furColours[i] = furCol[i];
    i++;
  }
  furColours[i] = "";

}

void Cat::readCat ()
{
  int i = 0;
  cout << "Please describe the cat" << endl;
  cout << "Please enter a length: ";
  cin >> length;
  cout << "Please enter a height: ";
  cin >> height;
  cout << "Please enter a tail length: ";
  cin >> tailLength;
  cout << "Please enter an eye colour: ";
  cin >> eyeColour;
  cout << "Please enter a description of the fur (long, medium, short, none): ";
  cin >> furClassification;
  cout << "Please enter the colours of the fur (separated by a space or a newline character). ";
  cout << "Add \"done\" at the end: ";
  cin >> furColours[i]; 
  while (furColours[i] != "done")
  {
    i++;
    cin >> furColours[i]; 
  }
  furColours[i] = "";
}

void Cat::printCat () const
{
  int i = 0;
  cout << "Length: "<< length << "  Height: "<< height 
       << "  Tail Length: " << tailLength << endl;
  cout << "Eye Colour: " << eyeColour 
       << "  Fur Classification: " << furClassification << endl;
  cout << "Cat Colours: ";
  while (furColours[i] != "")
  {
    cout << furColours[i++] << " "; 
  }
  cout << endl;
}

bool Cat::isCalico () const
{
  if (furColours[3] != "")
    return false;
  for (int i=0; i< 3; i++)
  {
  	if (furColours[i] != "black" && 
      furColours[i] != "orange" && 
      furColours[i] != "white")
      return false;
  }
  return true;
}

bool Cat::isTaller (const Cat& cat2) const
{
  //TO DO: modify code below
  return (height > cat2.height);
}
