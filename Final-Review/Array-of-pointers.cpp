#include <iostream>
#include <sys/wait.h>
using namespace std;

int main () {
    // Create the array
    int length = 0;
    cout << "Enter the length of the array";
    cin >> length;
    int* arrayOfInts = new int[length];
    
    // fill the array
    for (int i = 0; i < length; i++) {
        int toAppend = 0;
        cout << "Please enter an integer: ";
        cin >> toAppend;
        arrayOfInts[i] = toAppend;
    }
    
    
    // display the array
    cout << endl;
    cout << "Your complete dynamically allocated array is: " << endl;
    for (int i = 0; i < length; i++ ) {
        cout << arrayOfInts[i] << '\t';
    }  
   
   //delte arra
   delete [] arrayOfInts;
   
    return 0;
}