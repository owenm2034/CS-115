// Name: Owen Monus
// Student Number: 200482797
// Date: Sept 26th

// Filename: main.cpp
// Purpose: Write code from scratch for main.cpp by 
// following along with the video demonstrations.

#include <iostream>
#include "Date.h"
using namespace std;

int main() {
  int tempMonth;
  int tempDay;
  int tempYear;
  
  // instantiate one date object (date1) using the default constructor
  Date date1;
  
  // use the getters to display the month, day, and year of date1 (should print 
  // the default values) 
  cout << "Testing the default constructor and the getters" << endl 
    << "The initialized date is (M-D-Y): ";
  cout << date1.getMonth() << "-";
  cout << date1.getDay() << "-";
  cout << date1.getYear() << endl;

  // read keyboard input from the user for a month, day and year 
  cout << endl << "Please enter a date:(Month Day Year): ";
  cin >> tempMonth >> tempDay >> tempYear;
  
  // use the setters to set the values of date1 to the values that came from the 
  // user 
  date1.setMonth(tempMonth);
  date1.setDay(tempDay);
  date1.setYear(tempYear);

  // read keyboard input from the user for a second date 
  cout << "Please enter a date:(Month Day Year): ";
  cin >> tempMonth >> tempDay >> tempYear;
  
  // use the constructor with three arguments to instantiate date2 to the second 
  // date input from the user
  Date date2(tempMonth, tempDay, tempYear);

  // print both objects using printDate
  cout << endl << "Printing the two days: " << endl;
  date1.printDate();
  date2.printDate();
  
  // print a message to say if the two days are the same (testing the sameDay 
  // function)
  if(date1.sameDay(date2)) {
    cout << "The two days are the same" << endl;
  }
  else 
    cout << "The two days are different" << endl;
}