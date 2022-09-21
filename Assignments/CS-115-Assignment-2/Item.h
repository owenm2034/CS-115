/*
*   Author: Owen Monus
*   Student ID: 200482797   
*   Date: September 21st 2022
*   Class: CS115 _ University of Regina
*   Purpose: Provide prototypes and constant declarations for Item
*/

#pragma once
#include <string>
using namespace std;

const char ID_NOT_INITIALIZED = '\0';

struct Item { 
    char itemId;
    int startingRow;
    int startingCol;
    bool inPLayerInventory;
    int points;
    string itemDescription;
};

//
//  itemInit
//
//  Purpose: PUT TEXT HERE
//  Parameter(s):
//    <1> item: 
//    <2> id1:
//    <3> row1:
//    <4> column1:
//    <5> points1:
//    <6> world_description1:
//    <7> inventory_description1:
//  Precondition(s): PUT TEXT HERE
//  Returns: N/A
//  Side Effect: PUT TEXT HERE
//
void itemInit (Item& item, char id1, 
               int row1, int column1, 
               int points1,
               const string& world_description1,
               const string& inventory_description1);

//
//  itemDebugPrint
//
//  Purpose: PUT TEXT HERE
//  Parameter(s):
//    <1> item: 
//  Precondition(s): PUT TEXT HERE
//  Returns: N/A
//  Side Effect: PUT TEXT HERE
//
void itemDebugPrint (const Item& item);

//
//  itemGetId
//
//  Purpose: PUT TEXT HERE
//  Parameter(s):
//    <1> item: 
//  Precondition(s): PUT TEXT HERE
//  Returns: A char containing PUT TEXT HERE
//  Side Effect: PUT TEXT HERE
//
char itemGetId (const Item& item);

//
//  itemIsInInventory
//
//  Purpose: PUT TEXT HERE
//  Parameter(s):
//    <1> item: 
//  Precondition(s): PUT TEXT HERE
//  Returns: A boolean 
//  Side Effect: PUT TEXT HERE
//
bool itemIsInInventory (const Item& item);

//
//  itemIsAtLocation
//
//  Purpose: PUT TEXT HERE
//  Parameter(s):
//    <1> item: 
//    <2> row:
//    <3> column:
//  Precondition(s): PUT TEXT HERE
//  Returns: A boolean detailing
//  Side Effect: PUT TEXT HERE
//
bool itemIsAtLocation (const Item& item,
                       int row, int column);

//
//  itemGetPlayerPoints
//
//  Purpose: PUT TEXT HERE
//  Parameter(s):
//    <1> item: 
//  Precondition(s): PUT TEXT HERE
//  Returns: An int 
//  Side Effect: PUT TEXT HERE
//                     
int itemGetPlayerPoints (const Item& item);

//
//  itemPrintDescription
//
//  Purpose: PUT TEXT HERE
//  Parameter(s):
//    <1> item: 
//  Precondition(s): PUT TEXT HERE
//  Returns: N/A
//  Side Effect: PUT TEXT HERE
//
void itemPrintDescription (const Item& item);

//
//  itemReset
//
//  Purpose: PUT TEXT HERE
//  Parameter(s):
//    <1> item: 
//  Precondition(s): PUT TEXT HERE
//  Returns: N/A
//  Side Effect: PUT TEXT HERE
//
void itemReset (Item& item);

//
//  itemMoveToInventory
//
//  Purpose: PUT TEXT HERE
//  Parameter(s):
//    <1> item: 
//  Precondition(s): PUT TEXT HERE
//  Returns: N/A
//  Side Effect: PUT TEXT HERE
//
void itemMoveToInventory (Item& item);

//
//  itemMoveLocation
//
//  Purpose: PUT TEXT HERE
//  Parameter(s):
//    <1> item: 
//    <2> row:
//    <3> column:
//  Precondition(s): PUT TEXT HERE
//  Returns: N/A
//  Side Effect: PUT TEXT HERE
//
void itemMoveToLocation (Item& item, int row, int column);
