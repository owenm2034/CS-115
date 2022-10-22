// Name: Owen Monus
// Student Number: 200482797   
// Date: October 22, 2022

#pragma once
#include "iostream"
using namespace std;

class Location  {
    public:
        int row;
        int column;
        
        /// @brief default constructor; sets row to 0 & column to 0
        Location();
        
        /// @brief Initializes an instance of location with a passed row & column
        /// @param row1 row position
        /// @param column1 column position
        Location(int row1, int column1);
        
        /// @brief compares two locations to see if their row & column values are equivalent
        /// @param other the location to compare coordinates with
        /// @return \b True: if the row & column values of each location are the same &
        /// @return \b False: if the row & column values of each location is different
        bool operator== (const Location& other) const;
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


