#include "Templated-SS-algorithms.h"
#include <algorithm>
#include <iostream>
using namespace std;

template <typename toSS>
int binarySearch(int length, toSS toFind, toSS toSearch[]) {
	int min = 0;
	int max = length - 1;
	
	while (min <= max) {
		int mid = (min + max) /2;
		if ( toSearch[mid] == toFind ) {
			return mid;
		}
		else if (toSearch[mid] > toFind) {
			max = mid - 1;
		} else {
			min = mid + 1;
		}
	}
	return -1;
}

template <typename toSS>
int SearchSort<toSS>::sequentialSearch(int length, toSS toFind, toSS toSearch[]) {
	for (int i = 0; i < length; i++) {
		if (toSearch[i] == toFind) {
			return i;
		}
	}
	return -1;
}
 
template <typename toSS>
void insertionSort(int length, toSS toSearch[]) {
	// for all elements
	for (int i = 0; i < length; i ++) {
		//find insertion point
		int toInsert = toSearch[i];
		int insertPoint = i;
		for (int j = 0; j < i; j++) {
			if (toSearch[j] >= toInsert) {
				insertPoint = j;
			}
		}
		// shift elements
		
		for (int j = length; j > insertPoint; j--) {
			toSearch[j] = toSearch[j-1];
		}
		// insert
		toSearch[insertPoint] = toInsert;
		
	}
}

template <typename toSS>
void selectionSort(int length, toSS toSearch[]) {
	for (int i = 0; i < length; i ++) {
		int min = i;
		for (int j = i; j < length; j++) {
			if (toSearch[j] < toSearch[min]) {
				min = j;
			}
		}
		toSS store = toSearch[i];
		toSearch[i] = toSearch[min];
		toSearch[min] = store;
	}
}

template <typename toSS>
void printAgragate(int length, toSS toPrint[]) {
	for (int i = 0 ; i < length; i++) {
		cout << toPrint[i] << '\t';
	}
	cout << endl;
}

int main() {
	int integers[] = {4,5,6,1,2,3,7,8,9,10}; 
	printAgragate(9, integers);
	selectionSort(9, integers);
	cout << binarySearch<int>(9, 3,integers) << endl;
	printAgragate(9, integers);
	
	
	return 0;
}