//Author: Owen Monus
//Student ID: 200482797   
//Date: September 29th 2022
//Class: CS115 _ University of Regina
//Purpose: Provide function declarations for Item


#include <cassert>
#include <iostream>
#include "Item.h"
using namespace std;

void itemInit (Item& item, char id1, 
               int row1, int column1, 
               int points1,
               const string& world_description1,
               const string& inventory_description1) 
{
    assert(id1 != ID_NOT_INITIALIZED);
    assert(world_description1 != "");
    assert(inventory_description1 != "");
    
    item.itemId = id1;
    item.startingRow = row1;
    item.startingCol = column1;
    item.currentRow = item.startingRow;
    item.currentCol = item.startingCol;
    item.inPlayerInventory = false;
    item.points = points1;
    item.itemWorldDescription = world_description1;
    item.itemInventoryDescription = inventory_description1;
}

void itemDebugPrint (const Item& item) 
{
    cout << "id:" << '\t' << '\''<< item.itemId << '\'' << endl;
    cout << "start_row:" << '\t' << item.startingRow << endl;
    cout << "start_column:" << '\t' << item.startingCol << endl;
    cout << "current_row:" << '\t' << item.currentRow << endl;
    cout << "current_column:" << '\t' << item.currentCol << endl;
    cout << "is_in_inventory:" << '\t' << item.inPlayerInventory << endl;
    cout << "points:" << '\t' << item.points << endl;
    cout << "world_description:" << '\t' << '\"'<< item.itemWorldDescription << '\"' << endl;
    cout << "inventory_description:" << '\t' << '\"'<< item.itemInventoryDescription << '\"' << endl;
}

char itemGetId (const Item& item) 
{
    return item.itemId;
}

bool itemIsInInventory (const Item& item) 
{
    return item.inPlayerInventory;
}

bool itemIsAtLocation (const Item& item, int row, int column) 
{
    if (item.inPlayerInventory) {
        return false;
    }
    else if (item.currentRow == row && item.currentCol == column) {
        return true;
    }
    return false;
}

int itemGetPlayerPoints (const Item& item) 
{
    if (item.inPlayerInventory) {
        return item.points;
    }
    return 0;
}

void itemPrintDescription (const Item& item) 
{
    if (item.inPlayerInventory) {
        cout << item.itemInventoryDescription << endl;
    }
    else
        cout << item.itemWorldDescription << endl;
}

void itemReset (Item& item) 
{
    item.currentRow = item.startingRow;
    item.currentCol = item.startingCol;
    item.inPlayerInventory = false;
}

void itemMoveToInventory (Item& item) 
{
    item.inPlayerInventory = true;
}

void itemMoveToLocation (Item& item, int row, int column) 
{
    item.currentRow = row;
    item.currentCol = column;
    item.inPlayerInventory = false;
}