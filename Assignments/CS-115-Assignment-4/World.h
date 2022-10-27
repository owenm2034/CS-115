// Name: Owen Monus
// Student Number: 200482797
// Date: Oct 22, 2022

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

        ///
        /// @brief loads the nodes from {filename}_nodes.txt into the nodes array
        /// @param filename the name of the game in the text (.txt) files
        /// @post nodes[][] is filled with the data from {filename}_nodes.txt
        void loadNodes(string filename);
        
        /// 
        ///@brief finds the number of descriptions in {filename}_descriptions.txt and loads that amount
        ///        of descriptions into descriptions[]
        /// @param filename the name of the game in the text (.txt) files
        /// @post descriptions[] is filled with the amount of descriptions in {filename}_descriptions.txt
        /// @remark description_count is changed to the number of descriptions in {filename}_descriptions.txt
        void loadDescriptions(string filename);
        
        ///
        /// @brief Checks if the game is in a valid state. A valid state is true when description_count <= MAX_DESCRIPTION_COUNT &
        /// descriptions[d] is not an empty string for all of descriptions & nodes[r][c] < description count for all rows
        /// (r) and columns(c)
        /// @cond description_count <= MAX_DESCRIPTION_COUNT
        /// @cond descriptions[d] is not an empty string for all of descriptions
        /// @cond nodes[r][c] < description count for all rows(r) and columns(c)
        /// @return True if \b all test cases are true, and false if any are false 
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
        
        /** 
         * @brief Prints the values in the nodes array in a grid. Then it should print the description 
         * count and then the descriptions themselves, separated by blank lines.
         * 
         */
        void debugPrint() const;
        
        ///
        /// @brief Checks if a location is non-negative and less 
        ///        than the world's row and column sizes
        /// @param location the location to check
        /// @pre isInvariantTrue()
        /// @return True if the specified location is inside the bounds of the nodes array and false otherwise.
        bool isValid (const Location& location) const;
        
        ///
        /// @brief  Determines if a location is at a death node
        /// @pre isInvariantTrue()
        /// @pre isValid(location)
        /// @param location location to check
        /// @return True if the specified location is in a death node and false otherwise
        bool isDeath (const Location& location) const;
        
        /**
         * @brief Determines if a location is at a victory node
         * 
         * @param location location to check 
         * @pre isInvariantTrue()
         * @pre isValid(location)
         * @return true if the specified location is at a victory node
         * @return false if the specified location is not at a victory node
         */
        bool isVictory (const Location& location) const;
        
        /** 
         * @brief determines if a world can move north from a passed location 
         * 
         * @param location location to check north of
         * 
         * @pre isInvariantTrue()
         * @pre isValid(location)
         * 
         * @return true if the world can go north (i.e. the node north is not INACCESSIBLE).
         * @return false if the world can't go north (i.e. the node north is INACCESSIBLE)
         */
        bool canGoNorth (const Location& location) const;
        
        /**
         * @brief determines if a world can move south from a passed location 
         * 
         * @param location location to check south of
         * 
         * @pre isInvariantTrue()
         * @pre isValid(location)
         * 
         * @return true if the world can go south (i.e. the node south is not INACCESSIBLE).
         * @return false if the world can't go south (i.e. the node south is INACCESSIBLE)
         */
        bool canGoSouth (const Location& location) const;
        
        /**
         * @brief 
         * 
         * @param location 
         * 
         * @pre isInvariantTrue()
         * @pre isValid(location)
         * 
         * @return true 
         * @return false 
         */
        bool canGoEast (const Location& location) const;
        
        /** 
         * @brief 
         * 
         * @param location 
         * 
         * @pre isInvariantTrue()
         * @pre isValid(location)
         * 
         * @return true 
         * @return false 
         */
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
        
        /** 
         * @brief Move a location one step south
         * 
         * @param location the location to modify
         * 
         * @pre isInvariantTrue()
         * @pre canGoSouth(location)
         * 
         * @return a changed Location 
         */
        Location getSouth (const Location& location) const;
        
        /** 
         * @brief Move a location one step East 
         * 
         * @param location the location to modify 
         * 
         * @pre isInvariantTrue()
         * @pre canGoEast(location)
         * 
         * @return a changed Location 
         */
        Location getEast (const Location& location) const;
        
        /** 
         * @brief Move a location one step west
         * 
         * @param location the location to modify 
         * 
         * @pre isInvariantTrue()
         * @pre canGoWest(location)
         * 
         * @return a changed location
         */
        Location getWest (const Location& location) const;
        
        /** 
         * @brief Print the games start message
         * 
         * @pre isInvariantTrue()
         * 
         * @return a location with the coordinates of START_NODE
         */
        Location getStart () const;
        
        /**
         * @brief prints out the worlds starting message
         * 
         * @pre isInvariantTrue()
         */
        void printStartMessage () const;
        
        /**
         * @brief Print the game end message
         * 
         * @pre isInvariantTrue()
         */
        void printEndMessage () const;
        
        /**
         * @brief prints the description at a location
         * 
         * @param location location to print description at
         * @return *void
         */
        void printDescription (const Location& location) const;
};