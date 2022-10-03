// Name: Owen Monus
// Student Number: 200482797
// Date: Oct 2nd, 2022

#ifndef __CAT_H__
#define __CAT_H__
#include <string>
using namespace std;

const int NUM_COL = 5; // constant for the number of colours

class Cat {
private:
	double length;
	double height;
	double tailLength;
	string eyeColour;
	string furClassification; // none, short, medium, long
	string furColours[5];

public:
	// constructors
	Cat();
	Cat(double, double, double, string, string, const string[]);
	
  // getters and setters

	// other functions
  void readCat();
	void printCat() const;
	bool isCalico() const;
	bool isTaller(const Cat &) const;
};

#endif
