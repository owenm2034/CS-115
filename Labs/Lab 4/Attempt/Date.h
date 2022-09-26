// Name: Owen Monus
// Student Number: 200482797
// Date: Sept 26th

// Filename: Date.h
// Purpose: Write code from scratch for main.cpp by 
// following along with the video demonstrations.

#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <cassert>
using namespace std;

class Date {
  private:
    int month, day, year;
  public:
    // default constructor
    Date();

    Date(int m, int d, int y);
    
    int getMonth() const;
    int getDay() const;
    int getYear() const;
    
    void setMonth(int m);
    void setDay(int d);
    void setYear(int y);

    void printDate() const;
    
    bool sameDay(const Date &d) const;
    
};

#endif