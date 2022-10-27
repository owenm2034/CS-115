// Author: Owen Monus
// Student ID: 200482797   
// Date: October 4th 2022
// Class: CS115 _ University of Regina

#include "iostream"
#include "Location.h"
using namespace std;

Location::Location() {
    row = 0;
    column = 0;
}

Location::Location(int row1, int column1) {
    row = row1;
    column = column1;
}

bool Location::operator== (const Location& other) const {
    return ((row == other.row) && (column == other.column));
}

ostream& operator<< (ostream& out, const Location& location) {
    out << "(row = " << location.row << ", column = " << location.column << ')';
    return out;
}