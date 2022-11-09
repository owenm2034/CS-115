//
// Created by Owen Monus on 2022-11-07.
//

#include "Node.h"

Node::Node() : description(0), north(0), south(0), east(0), west(0), is_death(false) {}

Node::Node(unsigned int description1, unsigned int north1, unsigned int south1, unsigned int east1,
           unsigned int west1, bool is_death1) : description(description1), north(north1), south(south1), east(east1),
                                                 west(west1), is_death(is_death1) {}

void Node::debugPrint() const {
    if (is_death) {
        cout << "D";
    }
    else {
        cout << "N";
    }
    cout << " " << description << " " << north << " " << south << " " << east << " " << west << endl;
}

unsigned int Node::getDescription() const {
    return description;
}

bool Node::isDeath() const {
    return is_death;
}

Location Node::getNorth() const {
    return Location(north);
}

Location Node::getSouth() const {
    return Location(south);
}

Location Node::getEast() const {
    return Location(east);
}

Location Node::getWest() const {
    return Location(west);
}