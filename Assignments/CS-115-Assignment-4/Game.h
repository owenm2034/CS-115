//
// Created by Owen Monus on 2022-11-03.
//

#ifndef CS_115_ASSIGNMENT_4_GAME_H
#define CS_115_ASSIGNMENT_4_GAME_H

#include "World.h"
#include "ItemManager.h"
#include "Location.h"

class Game {
private:


    /**
     *
     * @return
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
     *
     * @return
     */
    bool isOver() const;

    /**
     *
     */
    void printStartMessage() const;

    /**
     *
     */
    void printEndMessage() const;

    /**
     *
     */
    void printDescription() const;

    /**
     *
     */
    void printInventory() const;

    /**
     *
     */
    void printScore() const;

    /**
     *
     */
    void reset();

    /**
     *
     */
    void moveNorth();

    /**
     *
     */
    void moveSouth();

    /**
     *
     */
    void moveEast();

    /**
     *
     */
    void moveWest();

    /**
     *
     * @param id
     */
    void takeItem(char id);

    /**
     *
     * @param id
     */
    void leaveItem(char id);
};


#endif //CS_115_ASSIGNMENT_4_GAME_H
