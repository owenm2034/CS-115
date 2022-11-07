// Name: Owen Monus
// Student Number: 200482797   
// Date: October 22, 2022

#pragma once
#include "iostream"
using namespace std;

class Location  {
    public:
        unsigned int nodeIndex;
        
        /// @brief default constructor; sets node index to 0;
        Location();
        
        /// @brief Initializes an instance of location with a passed node index
        /// @param node_index row position
        Location(unsigned int node_index);
        
        /// @brief compares two locations to see if their row & column values are equivalent
        /// @param other the location to compare coordinates with
        /// @return \b True: if the row & column values of each location are the same &
        /// @return \b False: if the row & column values of each location is different
        bool operator== (const Location& other) const;

        bool isInaccessible () const;
};

/**
 * @brief prints the row and column position of a location
 *       in the form (row = 2, column = 4)
 * 
 * @param out the type of cout
 * @param location location to print info for
 * 
 * @return ostream& cout 
 */
ostream& operator<< (ostream& out, const Location& location);


