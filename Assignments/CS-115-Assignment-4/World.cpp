// Name: Owen Monus
// Student Number: 200482797
// Date: Nov 10, 2022

#include <string>
#include <iostream>
#include <fstream>
#include "World.h"

using namespace std;

//
// Phil's helper function -> it checks if a string has content
bool stringHasContent(string toCheck) {
    if (toCheck.empty()) {
        return false;
    }

    for (int i = 0; i < toCheck.length(); i++) {
        if (toCheck.at(i) != ' ' || toCheck.at(i) != '\n' || toCheck.at(i) != '\0') {
            return true;
        }
    }
    return false;
}

void World::loadNodes(string filename) {
    ifstream fin;
    fin.open(filename);
    fin >> node_count;
    fin >> start_node >> victory_node >> start_game_desc_index >> end_game_desc_index;
    for (int i = 0; i < node_count; i++) {
        char type;
        unsigned int d;
        unsigned int n;
        unsigned int s;
        unsigned int e;
        unsigned int w;

        fin >> type >> d >> n >> s >> e >> w;
        if (type == 'D') {
            nodes[i] = Node(d, n, s, e, w, true);
        } else if (type == 'O') { //if an obstructed node, additional variables are read into dummy variables.
            char ob;
            unsigned int a;
            unsigned int b;
            fin >> ob >> a >> b;
            nodes[i] = Node(d, n, s, e, w, false);
        } else {
            nodes[i] = Node(d, n, s, e, w, false);
        }
    }
}

void World::loadDescriptions(string filename) {
    fstream fin;
    string tempString; // string to hold the values fstream reads in

    fin.open(filename);
    getline(fin, tempString);

    int numLines = 0;
    while (getline(fin, tempString)) {
        numLines++;
    }
    fin.clear();
    fin.seekg(0);

    int flag = 0;
    while (flag < numLines) {
        getline(fin, tempString);
        if (!stringHasContent(tempString)) {
            description_count += 1;
        } // end if
        flag++;
    } // end while

    fin.clear();
    fin.seekg(0);
    getline(fin, tempString, '\n');
    getline(fin, tempString, '\n');

    //Adds a chunk of text from filename into a string at i in descriptions
    for (int i = 0; i < description_count; i++) {
        /* the value of tempString doesn't matter, as long as it isn't "" – the following getline
        call changes its value */
        tempString = "someValue";
        while (stringHasContent(tempString)) { //stringHasContent(tempString)
            getline(fin, tempString, '\n');
            descriptions[i] = descriptions[i] + tempString + "\n";
        } //end while

        //remove the excess \n from the end of the string
        descriptions[i] = descriptions[i].substr(0, (descriptions[i].length() - 1));

    } //end for
}

bool World::isInvariantTrue() const {
    if (node_count > MAX_NODE_COUNT) {
        cout << "node_count > MAX_NODE_COUNT" << endl;
        return false;
    }

    if (start_node >= node_count) {
        cout << "Start_node: " << start_node << " >= node_count: " << node_count << endl;
        return false;
    }

    if (victory_node >= node_count) {
        cout << "Start_node >= node_count" << endl;
        return false;
    }

    if (start_game_desc_index >= description_count) {
        cout << "start_game_desc_index >= description_count" << endl;
        return false;
    }

    if (end_game_desc_index >= description_count) {
        cout << "end_game_desc_index >= description_count" << endl;
        return false;
    }

    for (int i = 0; i < node_count; i++) {
        if (!(descriptions[i] != "")) {
            cout << "descriptions at " << i << " is \"\"" << endl;
            return false;
        }
    }
    return true;
}

World::World(const string &game_name) {
    string nodeDataFile = game_name + "_nodes.txt";
    string textDataFile = game_name + "_text.txt";

    loadDescriptions(textDataFile);
    loadNodes(nodeDataFile);

    assert(isInvariantTrue());
}

void World::debugPrint() const {
    cout << "Number of Nodes: " << node_count << endl;
    cout << "Start Node: " << start_node << endl;
    cout << "Victory Node: " << victory_node << endl;
    for (int i = 0; i < node_count; i++) {
        nodes[i].debugPrint();
    }
    cout << endl;

    for (int i = 0; i < node_count; i++) {
        cout << descriptions[i] << endl;
    }
}

bool World::isValid(const Location &location) const {
    assert(isInvariantTrue());
    if (location.nodeIndex >= 0 && location.nodeIndex < node_count) {
        return true;
    } else
        return false;
}

bool World::isDeath(const Location &location) const {
    assert(isInvariantTrue());
    assert(isValid(location));
    if (nodes[location.nodeIndex].isDeath()) {
        return true;
    }
    return false;
}

bool World::isVictory(const Location &location) const {
    assert(isInvariantTrue());
    assert(isValid(location));
    return (location.nodeIndex == victory_node);
}

bool World::canGoNorth(const Location &location) const {
    assert(isInvariantTrue());
    assert(isValid(location));
    return !nodes[location.nodeIndex].getNorth().isInaccessible();

}

bool World::canGoSouth(const Location &location) const {
    assert(isInvariantTrue());
    assert(isValid(location));
    return !nodes[location.nodeIndex].getSouth().isInaccessible();
}

bool World::canGoEast(const Location &location) const {
    assert(isInvariantTrue());
    assert(isValid(location));
    return !nodes[location.nodeIndex].getEast().isInaccessible();
}

bool World::canGoWest(const Location &location) const {
    assert(isInvariantTrue());
    assert(isValid(location));
    return !nodes[location.nodeIndex].getWest().isInaccessible();
}

Location World::getNorth(const Location &location) const {
    assert(isInvariantTrue());
    assert(canGoNorth(location));
    return nodes[location.nodeIndex].getNorth();
}

Location World::getSouth(const Location &location) const {
    assert(isInvariantTrue());
    assert(canGoSouth(location));
    return nodes[location.nodeIndex].getSouth();
}

Location World::getEast(const Location &location) const {
    assert(isInvariantTrue());
    assert(canGoEast(location));
    return nodes[location.nodeIndex].getEast();
}

Location World::getWest(const Location &location) const {
    assert(isInvariantTrue());
    assert(canGoWest(location));
    return nodes[location.nodeIndex].getWest();
}

Location World::getStart() const {
    assert(isInvariantTrue());
    return Location(start_node);
} // end getStart

void World::printStartMessage() const {
    assert(isInvariantTrue());
    cout << descriptions[start_game_desc_index];
}

void World::printEndMessage() const {
    assert(isInvariantTrue());
    cout << descriptions[end_game_desc_index];
}

void World::printDescription(const Location &location) const {
    assert(isInvariantTrue());
    assert(isValid(location));
    cout << descriptions[nodes[location.nodeIndex].getDescription()];
}