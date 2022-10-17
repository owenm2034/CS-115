// Name: Owen Monus
// Student Number: 200482797
// Date: Sept 26, 2022

#pragma once
#include <string>
#include "Location.h"
#include <cassert>
 
using namespace std;

int const ROW_COUNT = 10; // 2D array row size
int const COLUMN_COUNT = 10; // 2D array column size
unsigned int const MAX_DESCRIPTION_COUNT = 1000;
Location const NO_SUCH_VALUE = Location(-1, -1);

typedef unsigned int NodeValue;

const NodeValue INACCESSIBLE = 0; 
const NodeValue START_MESSAGE = 1; 
const NodeValue END_MESSAGE = 2;
const NodeValue DEATH_NODE = 3;
const NodeValue START_NODE = 4;
const NodeValue VICTORY_NODE = 5;

class World {
    private:
        unsigned int description_count;
        string descriptions[MAX_DESCRIPTION_COUNT];
        NodeValue nodes[ROW_COUNT][COLUMN_COUNT];

        void loadNodes(string filename);
        void loadDescriptions(string filename);
        bool isInvariantTrue () const;
    public:
        //
        //  World
        //  constructor
        //
        //  Purpose: Initialize an instance of World with a node map
        //           & a description set
        //  Parameter(s):
        //    <1> game_name: The title of the text files for the
        //                   node map & descriptions to be initialized 
        //                   with
        //  Precondition(s):
        //    <1> game_name_grid.txt & game_name_text.txt exist
        //  Returns: N/A
        //  Side Effect: N/A
        //  Postcondition(s):
        //    <1> Every member variable is initialized
        //
        World(const string& game_name);
        void debugPrint() const;
        bool isValid (const Location& location) const;
        bool isDeath (const Location& location) const;
        bool isVictory (const Location& location) const;
        bool canGoNorth (const Location& location) const;
        bool canGoSouth (const Location& location) const;
        bool canGoEast (const Location& location) const;
        bool canGoWest (const Location& location) const;
        
        //
        //  getNorth
        //
        //  Purpose: Move a Worlds location one step north
        //  Parameter(s):
        //    <1> location: the location to alter
        //  Precondition(s):
        //    <1> the world is invaritant:
        //      <a> description_count is less than MAX_DESCRIPTION_COUNT
        //      <b> there are no blank descriptions in descriptions[]
        //      <c> no nodes in nodes[][] have a value greater than or equal to description_count
        //    <2> the passed location is valid:
        //      <a> the row position of location is less than ROW_COUNT and greater than -1
        //      <b> the column position of location is greater than -1 and less than COLUMN_COUNT
        //    <3> the passeed location can go north:
        //      <a> the location row position isn't 0
        //      <b> the world's node one row up (row - 1) does not equal INACCESSIBLE
        //  Returns: an instance of location north of the specified location
        //  Side Effect: N/A
        //  Postcondition(s):
        //    <1> an instance of location is returned 
        //
        Location getNorth (const Location& location) const;
        Location getSouth (const Location& location) const;
        Location getEast (const Location& location) const;
        Location getWest (const Location& location) const;
        Location getStart () const;
        void printStartMessage () const;
        void printEndMessage () const;
        void printDescription (const Location& location) const;
};