// Name: Owen Monus
// Student Number: 200482797
// Date: Sept 10, 2022

#pragma once
#include <string>

using namespace std;

int const ROW_COUNT = 6; // 2D array row size
int const COLUMN_COUNT = 9; // 2D array column size
unsigned int const DESCRIPTION_COUNT = 26;

typedef unsigned int NodeValue;
typedef NodeValue World[ROW_COUNT][COLUMN_COUNT]; 

const NodeValue INACCESSIBLE = 0; 
const NodeValue START_MESSAGE = 1; 
const NodeValue END_MESSAGE = 2;
const NodeValue DEATH_NODE = 3;
const NodeValue START_NODE = 4;
const NodeValue VICTORY_NODE = 5; 

/****************************FUNCTION PROTOTYPES*****************************/
//
//  worldClear
//
//  Purpose: Sets every element in World to INACCESSIBLE
//  Parameter(s):
//    <1> world: The world to clear
//    <2> 
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: Every element in world becomes INACCESSIBLE
//
void worldClear (World world);

//
//  worldLoadAll
//
//  Purpose: Loads the node map and text descriptions into the world
//  Parameter(s):
//    <1> world: The world to load into
//    <2> game_name: A string with the games chosen name
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: the given world is loaded with the [game_name]_text.txt descriptions
//               and [game_name]_grid.txt node map
//
void worldLoadAll (World world, string game_name);

//
//  worldLoadNodes
//
//  Purpose: Loads the nodes from a text file. If the nodes cannot be loaded, it prints out an
//           error message
//  Parameter(s):
//    <1> world: The world to load into
//    <2> filename: the file to load the nodes from
//  Precondition(s): 
//    <1>  filename references an existing file within the current directory 
//  Returns: N/A
//  Side Effect: if possible, the given world is loaded with the filename node map. If not 
//               possible, an error message is printed
//
void worldLoadNodes (World world, string filename);

//
//  worldDebugPrint
//
//  Purpose: Prints out all node values in the world in a grid seperated by tabs
//  Parameter(s):
//    <1> world: The world to debug
//    <2> filename: A string with the games chosen name
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: the given world's node map is printed out
//
void worldDebugPrint (const World world);

//
//  worldIsValid
//
//  Purpose: Checks if the location, or row and coloumn position, is non-negative and less 
//           than the world's row and column sizes
//  Parameter(s):
//    <1> world: The world to validate
//    <2> row: An integer holding the worlds row position
//    <3> column: An integer holding the worlds column position
//  Precondition(s): N/A
//  Returns: A boolean representing whether the world is valid or not.
//           True: valid 
//           False: invalid
//  Side Effect: N/A
//
bool worldIsValid (const World world, int row, int column);

//
//  worldCanGoNorth
//
//  Purpose: Checks if the location of the world is able to move north. This function checks to ensure
//  no out of bounds exceptions will occur, it also checks if the position north is marked as
//  INACCESSIBLE, and if so, you cannot move north
//  Parameter(s):
//    <1> world: The world to check if moving north is possible
//    <2> row: An integer holding the worlds row position
//    <3> column: An integer holding the worlds column position
//  Precondition(s): N/A
//  Returns: A boolean representing whether the world can move north or not.
//           True: can move north 
//           False: cant move north
//  Side Effect: N/A
//
bool worldCanGoNorth (const World world, int row, int column);

//
//  worldCanGoSouth
//
//  Purpose: Checks if the location of the world is able to move south. This function checks to ensure
//  no out of bounds exceptions will occur, it also checks if the position south is marked as
//  INACCESSIBLE, and if so, you cannot move south
//  Parameter(s):
//    <1> world: The world to check if moving south is possible
//    <2> row: An integer holding the worlds row position
//    <3> column: An integer holding the worlds column position
//  Precondition(s): N/A
//  Returns: A boolean representing whether the world can move south or not.
//           True: can move south 
//           False: cant move south
//  Side Effect: N/A
//
bool worldCanGoSouth (const World world, int row, int column);

//
//  worldCanGoEast
//
//  Purpose: Checks if the location of the world is able to move east. This function checks to ensure
//  no out of bounds exceptions will occur, it also checks if the position east is marked as
//  INACCESSIBLE, and if so, you cannot move east
//  Parameter(s):
//    <1> world: The world to check if moving east is possible
//    <2> row: An integer holding the worlds row position
//    <3> column: An integer holding the worlds column position
//  Precondition(s): N/A
//  Returns: A boolean representing whether the world can move east or not.
//           True: can move east 
//           False: cant move east
//  Side Effect: N/A
//
bool worldCanGoEast (const World world, int row, int column);

//
//  worldCanGoWest
//
//  Purpose: Checks if the location of the world is able to move west. This function checks to ensure
//  no out of bounds exceptions will occur, it also checks if the position west is marked as
//  INACCESSIBLE, and if so, you cannot move west
//  Parameter(s):
//    <1> world: The world to check if moving west is possible
//    <2> row: An integer holding the worlds row position
//    <3> column: An integer holding the worlds column position
//  Precondition(s): N/A
//  Returns: A boolean representing whether the world can move west or not.
//           True: can move west 
//           False: cant move west
//  Side Effect: N/A
//
bool worldCanGoWest (const World world, int row, int column);

//
//  worldIsDeath
//
//  Purpose: Determine if the world location is in a death node
//  Parameter(s):
//    <1> world: The world to check for death
//    <2> row: An integer holding the worlds row position
//    <3> column: An integer holding the worlds column position
//  Precondition(s): N/A
//  Returns: A boolean representing whether the world is in a death node.
//           True: in a death node 
//           False: not in a death node
//  Side Effect: N/A
//
bool worldIsDeath (const World world, int row, int column);

//
//  worldIsVictory
//
//  Purpose: Determine if the world location is in a victory node
//  Parameter(s):
//    <1> world: The world to check for victory
//    <2> row: An integer holding the worlds row position
//    <3> column: An integer holding the worlds column position
//  Precondition(s): N/A
//  Returns: A boolean representing whether the world is in a victory node.
//           True: in a victory node 
//           False: not in a victory node
//  Side Effect: N/A
//
bool worldIsVictory (const World world, int row, int column);

//
//  worldFindValue
//
//  Purpose: Changes the world position to a requested node type
//  Parameter(s): 
//    <1> world: The world to find a value in
//    <2> result_row: The world's row position
//    <3> result_column: The world's column position
//    <4> value_to_find: The node type to find
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: The given world's row and column values will be changed to
//               the index ([row][column]) of a node containing the value of 
//               value_to_find 
//
void worldFindValue (const World world, int& result_row, int& result_column, NodeValue value_to_find);

//
//  worldLoadDescriptions
//
//  Purpose: Loads text descriptions of the world from a provided file. 
//  Parameter(s):
//    <1> world: The world to load descripotions into
//    <2> filename: the file to load the descriptions from
//  Precondition(s): 
//    <1>  filename references an existing file within the current directory
//    <2>  That file contains lines of text, or text chunks (multi-line paragraphs), each seperated by a blank line
//  Returns: N/A
//  Side Effect: Each text chunk gets loaded into an array of descriptions as a long string.
//
void worldLoadDescriptions (World world, string filename);

//
//  worldPrintDescription
//
//  Purpose: Determines the world's current node and prints out the description at that node
//  Parameter(s):
//    <1> world: The world to print a descriptions from
//    <2> row: An integer holding the worlds row position
//    <3> column: An integer holding the worlds column position
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: The world's current location description is printed out
//
void worldPrintDescription (const World world, int row, int column);

//
//  worldPrintStartMessage
//
//  Purpose: Print the start of game message
//  Parameter(s):  
//  <1> world: The world to print a message from
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: The world's start message is printed out
//
void worldPrintStartMessage (const World world);

//
//  worldPrintEndMessage
//
//  Purpose: Print the end of game message
//  Parameter(s):  
//  <1> world: The world to print a message from
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: The world's end message is printed out
//
void worldPrintEndMessage (const World world);
