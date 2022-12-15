#include <cstddef>
#include <iostream>
using namespace std;

int main () {
	//pointer to an array of pointers	
		int length;
		cout << "enter length: ";
		cin >> length; 
		int** p_array_of_p = new int*[length];
		//assign values
		for (int i = 0; i < length; i ++) {
			p_array_of_p[i] = new int;
			*p_array_of_p[i] = 5;
		}
		
		//delete
		for (int i = 0; i < length; i++) {
			delete p_array_of_p[i];
			p_array_of_p[i] = nullptr;
		}
		delete[] p_array_of_p;
		p_array_of_p = nullptr;
	
	// pointer to an array
		cout << "enter length: ";
		cin >> length; 
		int * ptr_Array = new int[length];
		for (int i = 0; i < length; i ++) {
			ptr_Array[i] = 8;
		}
		
		delete[] ptr_Array;
		ptr_Array = nullptr;
	
	// pointer to an int
		cout << "enter int: ";
		cin >> length; 
		int * p_to_int = new int;
		*p_to_int = length;
		delete p_to_int;
		p_to_int = nullptr;
	
	return 0;
}

