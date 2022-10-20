//Author: Owen Monus
//Student ID: 200482797   
//Date: September 29th 2022
//Class: CS115 _ University of Regina
//Purpose: Provide prototypes and constant declarations for Item

#pragma once
#include <string>
#include "Location.h"
using namespace std;

const char ID_NOT_INITIALIZED = '\0';

class Item
{
    private:
        char id;
        Location start_location;
        Location current_location;
        bool in_player_inventory;
        int points;
        string world_description;
        string inventory_description;
        bool isInvariantTrue() const;
    public:
        Item (); // new in A3
        Item (char id1,
           const Location& location,
           int points1,
           const string& world_description1,
           const string& inventory_description1);
        void debugPrint () const;
        bool isInitialized () const; // new in A3
        char getId () const;
        bool isInInventory () const;
        bool isAtLocation (const Location& location) const;
        int getPlayerPoints () const;
        void printDescription () const;
        bool operator< (const Item& other) const; // new in A3
        void reset ();
        void moveToInventory ();
        void moveToLocation (const Location& location);
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
void itemInit (Item& item, char id1, 
               int row1, int column1, 
               int points1,
               const string& world_description1,
               const string& inventory_description1);

//
//  itemDebugPrint
//
//  Purpose: Prints all fields of the item
//  Parameter(s):
//    <1> item: the item to debug
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: N/A
//  Postcondition(s): Prints all item data
//
void itemDebugPrint (const Item& item);

//
//  itemGetId
//
//  Purpose: Retrieves an items id
//  Parameter(s):
//    <1> item: item to retrieve id from
//  Precondition(s):
//    <1> item has an id
//  Returns: A char containing an items id
//  Side Effect: N/A
//  Postcondition(s):
//    <1> the given item's id is returned
//
char itemGetId (const Item& item);

//
//  itemIsInInventory
//
//  Purpose: return a boolean that tells if the item is in a players inventory
//  Parameter(s):
//    <1> item: item to check if its in an inventory
//  Precondition(s):
//    <1> item has been initialized
//  Returns: A boolean:
//    <T> true if the item is in the player's inventory
//    <F> false if the item isn't in the players inventory
//  Side Effect: N/A
//  Postcondition(s):
//    <1> Boolean returned indicating whether the item is in the player's inventory
//
bool itemIsInInventory (const Item& item);

//
//  itemIsAtLocation
//
//  Purpose: This function returns whether an item is at a given location
//  Parameter(s):
//    <1> item: The item to check the location of
//    <2> row: the row to check for item
//    <3> column: the column to check for item
//  Precondition(s): 
//    <1> item has been initialized with a position in the World
//  Returns: A boolean:
//    <T> true if item was at position [row,column]
//    <F> falseif item wasn't at position [row, column]
//  Side Effect: N/A
//  Postocndition(s):
//    <1> boolean is returned regarding item's location 
//
bool itemIsAtLocation (const Item& item,
                       int row, int column);

//
//  itemGetPlayerPoints
//
//  Purpose: Returns how many points the player currently has from a given item.
//           If the item is not in the player's inventory, the function should return 0.
//  Parameter(s):
//    <1> item: item to retrieve point value from
//  Precondition(s): 
//    <1> item has been initialized with a point value
//  Returns: An int containing the point value of item
//  Side Effect: N/A
//  Postcondition(s):
//    <1> The item's point value is returned                  
//   
int itemGetPlayerPoints (const Item& item);

//
//  itemPrintDescription
//
//  Purpose: If the item is in the player's inventory, the function will print the 
//           inventory description; otherwise it will print the world description.
//  Parameter(s):
//    <1> item: item to print description of
//  Precondition(s): 
//    <1> item has been initialized
//  Returns: N/A
//  Side Effect: N/A
//  Postcondition(s):
//    <1>  The item's description is printed based on its state (in world or in inventory)
//
void itemPrintDescription (const Item& item);

//
//  itemReset
//
//  Purpose: Moves the item to its starting location and set it to not be in the 
//           player’s inventory.
//  Parameter(s):
//    <1> item: the item to reset
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: N/A
//  Postcondition(s): 
//    <1> Item's position is set to [startingRow, startingCol] and inPlayerInventory is set
//        to false.
//
void itemReset (Item& item);

//
//  itemMoveToInventory
//
//  Purpose: Change an item's state so it is in a player's inventory
//  Parameter(s):
//    <1> item: item to move to player inventory
//  Precondition(s): 
//    <1> Item has been initialized
//  Returns: N/A
//  Side Effect: N/A
//  Postcondition(s):
//    <1> the item's inPlayerInventory boolean is set to true
//
void itemMoveToInventory (Item& item);

//
//  itemMoveLocation
//
//  Purpose: Moves an item from its current position to a given one
//  Parameter(s):
//    <1> item: the item to move
//    <2> row: the row to move it to
//    <3> column: the column to move it to
//  Precondition(s):
//  Returns: N/A
//  Side Effect: N/A
//  Postcondition(s):
//    <1> Item is moved to the given location
//    <2> Item is set to be not in the players inventory
//
void itemMoveToLocation (Item& item, int row, int column);
