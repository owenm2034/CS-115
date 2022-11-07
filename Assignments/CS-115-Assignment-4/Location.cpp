// Author: Owen Monus
// Student ID: 200482797   
// Date: October 4th 2022
// Class: CS115 _ University of Regina

#include "iostream"
#include "Location.h"

using namespace std;

Location::Location() {
    nodeIndex = 0;
}

Location::Location(unsigned int node_index) {
    nodeIndex = node_index;
}

bool Location::operator==(const Location &other) const {
    return (nodeIndex == other.nodeIndex);
}

bool Location::isInaccessible() const {
    return nodeIndex == 0;
}

ostream &operator<<(ostream &out, const Location &location) {
    if (location.isInaccessible()) {
        out << "(node = INACCESSIBLE)";
    } else {
        out << "(node = " << location.nodeIndex << ')';
    }
    return out;
}

