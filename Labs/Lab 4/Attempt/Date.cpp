// Name: Owen Monus
// Student Number: 200482797
// Date: Sept 26th

// Filename: Date.cpp
// Purpose: Write code from scratch for Date.cpp by 
// following along with the video demonstrations.

#include "Date.h"

Date::Date() {
  month = 1;
  day = 1;
  year = 1;
}

Date::Date(int m, int d, int y) {
  assert(m >= 1 && m <= 12);
  month = m;
  assert(d >= 1 && d <= 31);
  day = d;
  assert(y >= 0);
  year = y;
}

//Accessors
int Date::getMonth() const {
  return month;
}

int Date::getDay() const {
  return day;
}

int Date::getYear() const {
  return year;
}

//Mutators
void Date::setMonth(int m) {
  assert(m >= 1 && m <= 12);
  month = m;  
}

void Date::setDay (int d) {
  assert(d >= 1 && d <= 31);
  day = d;
}

void Date::setYear(int y) {
  assert( y > 0);
  year = y;
}

void Date::printDate() const {
  cout << "The date is (M-D-Y): " << month << "-" << day << "-" << year << endl;
}

//implement same day function
bool Date::sameDay(const Date &d) const {
  if (getDay() == d.getDay()) {
    return true;
  }
  else
    return false;
}