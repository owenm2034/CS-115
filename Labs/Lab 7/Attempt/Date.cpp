// Name: Owen Monus
// Student Number: 200482797
// Date: Oct 17, 2022

#include "Date.h"

Date::Date()
{
  month = 0;
  day = 0;
  year = 0;
}

Date::Date(int m, int d, int y)
{
  month = m;
  day = d;
  year = y;
}

int Date::endOfMonth() const
{
  int concludingDay = 0;
  switch (month)
  {
    case 1:
      concludingDay = 31;
      break;
    case 2:
	    if ((year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0)))
        concludingDay = 29;
      else
        concludingDay = 28;
      break;
    case 3:
      concludingDay = 31;
      break;
    case 4:
      concludingDay = 30;
      break;
    case 5:
      concludingDay = 31;
      break;
    case 6:
      concludingDay = 30;
      break;
    case 7:
      concludingDay = 31;
      break;
    case 8:
      concludingDay = 31;
      break;
    case 9:
      concludingDay = 30;
      break;
    case 10:
      concludingDay = 31;
      break;
    case 11:
      concludingDay = 30;
      break;
    case 12:
      concludingDay = 31;
      break;
  }
  return concludingDay;
}

int Date::getMonth()const
{
  return month;
}

int Date::getDay()const
{
  return day;
}

int Date::getYear()const
{
  return year;
}

void Date::setMonth(int m)
{
  month = m;
}

void Date::setDay(int d)
{
  day = d;
}

void Date::setYear(int y)
{
  year = y;
}

void Date::printDate() const
{
  cout << "Date is: " << month << "/" << day << "/" << year << endl;
}

bool Date::operator==(const Date& myDate) const
{
  if (month == myDate.month && day == myDate.day && year == myDate.year)
    return true;
  else
    return false;
}

Date Date::operator++()
{
  if (day == endOfMonth())  //endOfMonth returns 28, 29, 30 or 31 depending on month 
  {
    if (month == 12)
    {
      year += 1;
      month = 1;
    }
    else
      month += 1;
    day = 1;
  }
  else
    day += 1;
  return *this;
}

ostream& operator<<(ostream& os, const Date& myDate) 
{
  os << "Date is: " << myDate.getMonth() 
     << "/" << myDate.getDay() 
     << "/" << myDate.getYear() << endl;
  return os;
}

/* This must be overloaded as a non-member function since the left hand
side will contain a type that is not Date ostream is a different type 
than date*/

//Implement the operator+ function here

// add a comment nect to the function that
// must be defined as a nin-member function and explain why