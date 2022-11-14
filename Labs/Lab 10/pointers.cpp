// Name: Owen Monus
// Student Number: 200482797
// Date: Nov 14th, 2022

// Filename: pointers.cpp
// Purpose: To work with pointers and dynamically allocate
//           an array for the marks of a student as outlined
//           in the exercise description.

#include <string>
#include <iostream>
using namespace std;


struct Student
{
  string name;
  int id;
  int* mark;
  ~Student() {delete [] mark; mark = nullptr;}
};

void inputStudent(Student* stuPtr, int markCount);   // function prototype for inputting
void printStudent(Student* stuPtr, int markCount);  // function prototype for printing

//*********************** Main Function ************************//
int main ()
{
  Student stu;		             // instantiating a Student object
  Student* studentPtr = &stu;  // defining a pointer for the Student object

  int size;
  cout << "How many marks are there? ";
  cin >> size;

  // NOTE: you could send studentPtr OR &stu, both refer to the same address!
  // inputting from the keyboard into the instance
  // printing the object
  inputStudent(studentPtr, size);	
  printStudent(studentPtr, size);
  
  return 0;
} // end of main

//************************* Start of functions ************************// 

// Part 1:
void inputStudent(Student* stuPtr, int markCount) {
  stuPtr -> mark = new int[markCount];
  cout << "Please enter a name: "; 
  cin >> stuPtr -> name;
  cout << "Please enter an id: ";
  cin >> stuPtr -> id; 
  for (int i = 0; i < markCount; i++) {
    cout << "Please enter a mark: ";
    cin >> stuPtr -> mark[i];
    }
}

void printStudent(Student* stuPtr, int markCount) {
  cout << "Student Info:" << endl;
  cout << "Name: " << stuPtr-> name << endl;
  cout << "Id: " << stuPtr -> id << endl;
  for (int i = 0; i < markCount; i++) {
    cout << "Mark " << i << ": " << stuPtr -> mark[i] << endl;
  }
}