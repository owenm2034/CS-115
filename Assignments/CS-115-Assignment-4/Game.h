//
// Created by Owen Monus on 2022-11-03.
//

#ifndef CS_115_ASSIGNMENT_4_GAME_H
#define CS_115_ASSIGNMENT_4_GAME_H

#include "World.h"
#include "ItemManager.h"
#include "Location.h"

/**
 * @invariant something
 */
class Game {
private:
    ItemManager itemManager;
    World world;
    Location playerLocation;

    /**
     * @brief The class invariant requires that the player location is valid
     * according to the isValid function of the World class.
     * @return \True if the player location is valid
     *         \False otherwise
     */
    bool isInvariantTrue() const;

public:
    /**
     * @brief Initializes the World and the ItemManager with the game name
     * and sets the player Location to the start location for the World.
     * @param game_name The game name which is the following part of the *.txt files:
     * ***THIS PART***_someComponent.txt
     */
    Game(const string &game_name);

    /**
     * @brief Returns whether the game is over
     * @return true if the player is at a victory or death node
     */
    bool isOver() const;

    /**
     * @brief prints the worlds start message
     */
    void printStartMessage() const;

    /**
     * @brief prints the worlds end message
     */
    void printEndMessage() const;

    /**
     * @brief prints the description of the player's current location and then
     * prints the descriptions of any items at that node.
     */
    void printDescription() const;

    /**
     * @brief prints the Items in a player's inventory
     */
    void printInventory() const;

    /**
     * @brief prints a sentence with the players total score.
     */
    void printScore() const;

    /**
     * @brief Moves the player back to the start location
     * and resets all items.
     */
    void reset();

    /**
     * @brief Moves the player north if possible. If not, it prints a message saying the player
     * cannot move in that direction
     */
    void moveNorth();

    /**
     * @brief Moves the player south if possible. If not, it prints a message saying the player
     * cannot move in that direction
     */
    void moveSouth();

    /**
     * @brief Moves the player east if possible. If not, it prints a message saying the player
     * cannot move in that direction
     */
    void moveEast();

    /**
     * @brief Moves the player west if possible. If not, it prints a message saying the player
     * cannot move in that direction
     */
    void moveWest();

    /**
     * @brief Attempts to leave the item with the provided id
     * @param id the id(char) of the item to leave
     */
    void takeItem(char id);

    /**
     * @brief Attempts to take the item with the provided id
     * @param id the id(char) of the item to take
     */
    void leaveItem(char id);
};


#endif //CS_115_ASSIGNMENT_4_GAME_H
