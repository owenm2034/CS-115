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

void itemInit (Item& item, char id1, 
               int row1, int column1, 
               int points1,
               const string& world_description1,
               const string& inventory_description1);
void itemDebugPrint (const Item& item);
char itemGetId (const Item& item);
bool itemIsInInventory (const Item& item);
bool itemIsAtLocation (const Item& item,
                       int row, int column);
int itemGetPlayerPoints (const Item& item);
void itemPrintDescription (const Item& item);
void itemReset (Item& item);
void itemMoveToInventory (Item& item);
void itemMoveToLocation (Item& item,
