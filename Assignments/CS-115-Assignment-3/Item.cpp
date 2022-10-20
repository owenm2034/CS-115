//Author: Owen Monus
//Student ID: 200482797   
//Date: September 29th 2022
//Class: CS115 _ University of Regina
//Purpose: Provide function declarations for Item


#include <cassert>
#include <iostream>
#include "Item.h"
using namespace std;

bool Item::isInvariantTrue() const
{
    if(world_description == "" || inventory_description == "") 
    {
        cout << "one of world_description or inventory_description contain a blank string" << endl;
        return false;
    }
    return true;
}

Item::Item()
    :id(ID_NOT_INITIALIZED),
    start_location(Location()),
    current_location(Location()),
    in_player_inventory(false),
    points(0),
    world_description("[Item not initialized]"),
    inventory_description("[Item not initialized]")
{}

Item::Item (char id1,
           const Location& location,
           int points1,
           const string& world_description1,
           const string& inventory_description1) 
    : id (id1),
    start_location (location),
    current_location (location),
    in_player_inventory (false),
    points (points1),
    world_description (world_description1),
    inventory_description (inventory_description1)
{ 
    assert(isInvariantTrue());
}

void Item::debugPrint() const 
{
    cout << "id:" << '\t' << '\''<< id << '\'' << endl;
    cout << "start_location:" << '\t' << start_location << endl;
    cout << "current_location:" << '\t' << current_location << endl;
    cout << "is_in_inventory:" << '\t' << in_player_inventory << endl;
    cout << "points:" << '\t' << points << endl;
    cout << "world_description:" << '\t' << '\"'<< world_description << '\"' << endl;
    cout << "inventory_description:" << '\t' << '\"'<< inventory_description << '\"' << endl;
}

bool Item::isInitialized() const 
{
    assert(isInvariantTrue());
    return (id != ID_NOT_INITIALIZED);
} 

char Item::getId () const 
{
    assert(isInvariantTrue());
    return id;
}

bool Item::isInInventory () const 
{
    assert(isInvariantTrue());
    return in_player_inventory;
}

bool Item::isAtLocation (const Location& location) const
{
    assert(isInvariantTrue());
    return (location == current_location);
}

int Item::getPlayerPoints () const
{
    assert(isInvariantTrue());
    if(in_player_inventory) {
        return points;
    }
    return 0;
}

void Item::printDescription () const
{
    assert(isInvariantTrue());
    if (in_player_inventory) 
    {
        cout << inventory_description << endl;
    }
    else
    {
       cout << world_description << endl;
    }
}

bool Item::operator< (const Item& other) const
{
    assert(isInvariantTrue());
    return (id < other.id);
}

void Item::reset () 
{
    assert(isInvariantTrue());
    current_location = start_location;
    in_player_inventory = false;
    assert(isInvariantTrue());
}

void Item::moveToInventory ()
{
    assert(isInvariantTrue());
    in_player_inventory = true;
    assert(isInvariantTrue());
}

void Item::moveToLocation (const Location& location) 
{
    assert(isInvariantTrue());
    current_location = location;
    in_player_inventory = false;
    assert(isInvariantTrue());
}