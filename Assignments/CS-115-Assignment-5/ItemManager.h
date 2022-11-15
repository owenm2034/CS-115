// Name: Owen Monus
// Student Number: 200482797
// Date: Nov 10, 2022

#ifndef CS_115_ASSIGNMENT_4_ITEMMANAGER_H
#define CS_115_ASSIGNMENT_4_ITEMMANAGER_H


#include "Item.h"

const unsigned int NO_SUCH_ITEM = 999999999;

class ItemManager {
private:
    Item* item_ptr;
    int item_count;

    void load(const string &filename);

    /**
     * @brief If there is an item with the passed id, it should return that item's index. Otherwise, it should return
     * NO_SUCH_ITEM, a constant with value 999999999
     * @param id the id of the item to check
     * @return If the item is found, return the index of id. Otherwise, return 999999999
     */
    unsigned int find(char id) const;

    void sort();

    /**
     * @brief Checks if all items have been initialized with a World Description,
     * Inventory Description, and ID
     * @return \True: if all items have been initialized
     *         \False: if one of ID, WorldDescription, or InventoryDescription do not have a value
     */
    bool isInvariantTrue() const;

public:
    /**
     * @brief Sets item_count to zero, creates a dynamic array of size 0.
     */
    ItemManager();

    /**
     * @brief Create an instance of ItemManager with a given game name
     * @invariant isInvariantTrue is true
     * @param game_name A string containing the game name
     */
    ItemManager(const string &game_name);

    ItemManager(const ItemManager &to_copy);

    ~ItemManager();

    ItemManager &operator=(const ItemManager &to_copy);

    /**
     * @brief returns the amount of items in the itemManager
     * @return an int with the amount of items in itemManager
     */
    unsigned int getCount() const;

    /**
     * @return the total score of all items in a player's inventory
     */
    int getScore() const;

    /**
     * @brief print all the Items at a location
     * @param location Location to check
     */
    void printAtLocation(const Location &location) const;

    /**
     *  @brief Prints the Items in the player's inventory. Each Item
     *  will be printed on its own line.
     */
    void printInventory() const;

    /**
     * @brief check if an item is in the inventory by its id
     * @param id an id of an item to check if its in the inventory
     * @return Whether the item with that id is in the player's inventory
     */
    bool isInInventory(char id) const;

    /**
     * @brief Resets all item's location to their starting location. Also sets
     *        in_player_inventory to false.
     */
    void reset();

    /**
     * @brief Takes an item id and the player location as parameters and attempts to take that item.
     * If the player successfully took the item, return true. If the player failed to take it, print
     * "Invalid item." (with a newline) and return false.
     * @param id id of item to pick up
     * @param player_location current location of the player
     * @return True: if the player successfully picked up the item with the passed id
     * @return False: if the player did not pick up the item with the passed id
     */
    bool take(char id, const Location &player_location);

    /**
     * @brief attempts to drop an item from a players inventory
     * @param id the id of the item a player is attempting to drop
     * @param player_location the current location of the player
     * @return \True: if the item was left
     *         \False: if the item to leave was invalid
     */
    bool leave(char id, const Location &player_location);
};


#endif //CS_115_ASSIGNMENT_4_ITEMMANAGER_H
