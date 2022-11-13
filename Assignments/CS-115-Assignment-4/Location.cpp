// Name: Owen Monus
// Student Number: 200482797
// Date: Nov 10, 2022

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

