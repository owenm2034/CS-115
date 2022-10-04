// Author: Owen Monus
// Student ID: 200482797   
// Date: October 4th 2022
// Class: CS115 _ University of Regina

#pragma once
#include "iostream"
using namespace std;

class Location  {
    private:
    
    public:
        int row;
        int column;
        
        Location();
        Location(int row1, int column1);
        bool operator== (const Location& other) const;
};

//
//  itemInit
//
//  Purpose: initializes an Item.
//  Parameter(s):
//    <1> item: the item to initialize
//    <2> id1: the id to access the item with
//    <3> row1: the starting row position of the item
//    <4> column1: the starting column position of the item
//    <5> points1: represents the amount of points this item is worth
//    <6> world_description1: description of the item when its in the world
//    <7> inventory_description1: description of the item when its in the players inventory
//  Precondition(s):
//    <1>  the item id (id1) parameter is not ID_NOT_INITIALIZED
//    <2>  the world description (world_description) is not a blank string ("")
//    <3>  the inventory description (inventory_description) is not a blank string ("")
//  Returns: N/A
//  Side Effect: 
//    <1> the items currentRow value is initialized as startingRow
//    <2> the items currentCol value is initialized as startingCol
//  Postcondition(s):
//    <1> The given item will be initialized with the provided data
//
ostream& operator<< (ostream& out, const Location& location);


