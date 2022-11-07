//
// Created by Owen Monus on 2022-11-07.
//

#ifndef CS_115_ASSIGNMENT_4_NODE_H
#define CS_115_ASSIGNMENT_4_NODE_H

#include "Location.h"

class Node {
private:
    unsigned int description;
    unsigned int north;
    unsigned int south;
    unsigned int east;
    unsigned int west;
    bool is_death;

public:
    /**
     * @brief Initialize the descriptions and node indexes to 0. is_death is set to false
     */
    Node();

    /**
     * @brief Initializes every value of a node
     * @param description1 unsigned int the nodes description
     * @param north1 unsigned int of the node to the north
     * @param south1 unsigned int of the node to the south
     * @param east1 unsigned int of the node to the east
     * @param west1 unsigned int of the node to the west
     * @param is_death1 boolean containing whether or not this node is a death node
     */
    Node(unsigned int description1,
         unsigned int north1,
         unsigned int south1,
         unsigned int east1,
         unsigned int west1,
         bool is_death1);

    /**
     * @brief Prints the values for the Node in the same format as the node data file,
     *        ending with a newline
     */
    void debugPrint() const;

    unsigned int getDescription () const;

    Location getNorth() const;

    Location getSouth() const;

    Location getEast() const;

    Location getWest() const;

    bool isDeath() const;

};


#endif //CS_115_ASSIGNMENT_4_NODE_H
