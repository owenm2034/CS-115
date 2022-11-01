// Name: Owen Monus 
// Student Number: 200482797
// Date: Oct 29

// Filename: maxTemplate.cpp
// Purpose: Demonstrate the use of function templates.

#include <iostream>
#include <string>
using namespace std;

// Make a template out of the prototype
template <typename T>
T myMax(T one, T two);

int main()
{
  int int_two = 5, int_one = 3;

  cout << "The max of " << int_one << " and " << int_two << " is "
        << myMax(int_one, int_two) << endl;

  // Test your template on double and string types
  double double_one = 5.6, double_two = 7.3;

   cout << "The max of " << double_one << " and " << double_two << " is "
        << myMax(double_one, double_two) << endl;


  string string_one = "donkey", string_two = "apple";

   cout << "The max of " << string_one << " and " << string_two << " is "
        << myMax(string_one, string_two) << endl;
  
  return 0;
}

// Make a template out of this function. Do not forget the return type.
template <typename T>
T myMax(T one, T two)
{
  T largest;
  if (one > two)
  {
    largest = one;
  }
  else
  {
    largest = two;
  }
  return largest;
} // end of myMax function
