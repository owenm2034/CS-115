// Name: Owen Monus
// Student Number: 200482797
// Date: Nov 10, 2022

#pragma once

#include <string>
#include "Location.h"

using namespace std;

const char ID_NOT_INITIALIZED = '\0';

class Item {
private:
    char id;
    Location start_location;
    Location current_location;
    bool in_player_inventory;
    int points;
    string world_description;
    string inventory_description;

    /**
     * @brief Checks if an item is in a valid state. A valid state is when
     *        world_description is not an empty string and inventory_description
     *        is not an empty string
     *
     * @cond world_description is not an empty string
     * @cond inventory_description is not an empty string
     *
     * @return true
     * @return false
     */
    bool isInvariantTrue() const;

public:
    /**
     * @brief Construct a new Item object. Sets ID to ID_NOT_INITIALIZED
     * @pre isInvariantTrue()
     */
    Item(); // new in A3

    /**
     * @brief Construct a new Item object
     *
     * @param id1 item id
     * @param location starting location of Item
     * @param points1 points of item
     * @param world_description1 the in world description of the item
     * @param inventory_description1 the in inventory description of the item
     *
     * @pre isInvariantTrue()
     */
    Item(char id1,
         const Location &location,
         int points1,
         const string &world_description1,
         const string &inventory_description1);

    /**
     * @brief Prints all fields of the item
     *
     */
    void debugPrint() const;

    /**
     * @brief ensures an item has been initialized
     *
     * @pre isInvariantTrue()
     *
     * @return false if the id field is ID_NOT_INITIALIZED and true otherwise.
     */
    bool isInitialized() const; // new in A3

    /**
     * @brief Get the Id of item
     *
     * @pre isInvariantTrue()
     *
     * @return char id
     */
    char getId() const;

    /**
     * @brief checks if an item is in inventory
     *
     * @pre isInvariantTrue()
     *
     * @return in_player_inventory
     */
    bool isInInventory() const;

    /**
     * @brief checks if an item is at a passed location
     *
     * @param location location to check for item at
     *
     * @pre isInvariantTrue()
     *
     * @return true if the items current_location has the same coordinates
     *         as the passed location.
     * @return false if in_player_inventory OR items current_location
     *         is different from the passed location
     */
    bool isAtLocation(const Location &location) const;

    /**
     * @brief Gets the points value of an item.
     *
     * @pre isInvariantTrue()
     *
     * @return 0 if its not in_player_inventory, and the point value of
     *         the item if it is in_player_inventory
     */
    int getPlayerPoints() const;

    /**
     * @brief If item is in_player_inventory, it prints inventory_description.
     *        Otherwise it prints world_description
     *
     * @pre isInvariantTrue()
     */
    void printDescription() const;

    /**
     * @brief The operator will return whether the id for this current Item
     *        is strictly less than the id for the other parameter Item
     *
     * @param other item to compare with
     *
     * @pre isInvariantTrue()
     *
     * @return true if id < other.getId().
     * @return false if id >=  other.getId()
     */
    bool operator<(const Item &other) const; // new in A3

    /**
     * @brief Resets an items current_location to starting_location. Sets
     *        in_player_inventory to false.
     * @pre isInvariantTrue()
     * @post isInvariantTrue()
     */
    void reset();

    /**
     * @brief Change an item's so its in an inventory. (i.e in_player_inventory
     * is set to true)
     *
     * @pre isInvariantTrue()
     */
    void moveToInventory();

    /**
     * @brief Moves an item from its current_location to a given one
     *
     * @param location location to move item to
     *
     * @pre isInvariantTrue()
     */
    void moveToLocation(const Location &location);
};