// Name: Owen Monus
// Student Number: 200482797
// Date: Nov 10, 2022

#ifndef CS_115_ASSIGNMENT_4_NODE_H
#define CS_115_ASSIGNMENT_4_NODE_H

#include "Location.h"

const Location NO_SUCH_LOCATION(-1);

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
     * @brief Initialize a node
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

    /**
     *
     * @return the node description
     */
    unsigned int getDescription() const;

    /**
     *
     * @return the location to the north of the node
     */
    Location getNorth() const;

    /**
     *
     * @return @return the location to the south of the node
     */
    Location getSouth() const;

    /**
     *
     * @return the location to the east of the node
     */
    Location getEast() const;

    /**
     *
     * @return the location to the west of the node
     */
    Location getWest() const;

    /**
     *
     * @return whether or not a node is a death node
     */
    bool isDeath() const;

};


#endif //CS_115_ASSIGNMENT_4_NODE_H
