// Name: Owen Monus
// Student Number: 200482797
// Date: Sept 10, 2022

#ifndef MYFUNCTION_H
#define MYFUNCTION_H

#include <iostream>
#include <fstream>
using namespace std;

const unsigned int ROW_SIZE = 4;
const unsigned int COLUMN_SIZE = 5;

void readArray(int twoDArray[][COLUMN_SIZE], string inFile);  // function prototype
void printArray(int twoDArray[][COLUMN_SIZE]); //function prototype

#endif