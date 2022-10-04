// Author: Owen Monus
// Student ID: 200482797   
// Date: September 29th 2022
// Class: CS115 _ University of Regina


// includes
#include "Item.h"
#include "World.h"
#include <iostream> 
using namespace std;

// helper functionn declarations
void printItemDescription(int rowToSearch, int colToSearch, Item items[], const unsigned int numOfItems);
void checkGameState(World &world, unsigned int playerRow, unsigned int playerCol, bool &worldIsValid);
void hanldePlayerInput(const string &userInput, bool &worldIsValid, World &world, int &playerRow, int &playerCol);
void handlePlayerInput(const string &userInput, bool &worldIsValid, World &world, int &playerRow, int &playerCol, Item items[], const unsigned int ITEM_COUNT);
void printPlayerScore(const Item items[], const unsigned int numOfItems);

int main () {
    // data declarations
    // a constant int holding the amount of items in the world
    const unsigned int ITEM_COUNT = 5;
    World world;
    // tracks the players row posistion
    int playerRow;
    // tracks the players col posistion
    int playerCol; 
    // tracks if the game should continue
    bool worldIsValid = true; 
    // a string to hold user input in
    string userInput;
    // an array of 5 items
    Item items[ITEM_COUNT] = {
        { // Alice
            'a',
            0,
            6,
            0,
            6,
            false,
            1,
            "You see Alice (a) here, trying to read a very small compass.",
            "Somewhere nearby, you hear Alice (a) jabbering about directions."       
        },
        
        { // Charlie
            'c',
            0,
            6,
            0,
            6,
            false,
            1,
            "You see Charlie (c) lying half-buried in the drifting snow here.",
            "Behind you, Charlie (c) is dragging himself through the snow."
        },

        { // Emma
            'e',
            3,
            5,
            3,
            5,
            false,
            1,
            "Young Emma (e) is crouched down here, out of the wind.",
            "Young Emma (e) is trying to use you to block the wind."
        },

        { // David
            'd',
            4,
            1,
            4,
            1,
            false,
            1,
            "David (d) is using a stick to write in the snow here.",
            "David (d) is dashing this way and that, despite the weather."
        },

        { // Benny & Bobby
            'b',
            5,
            8,
            5,
            8,
            false,
            2,
            "The twins, Benny and Bobby (b), are huddled together here.",
            "The twins, Benny and Bobby (b), are huddled behind you."
        }
    };

    // load nodes from a file
    worldLoadAll(world, "blizzard"); 
    worldPrintStartMessage(world);
    
    // blank line between start message & 1st description
    cout << '\n';
    // move to the starting node
    worldFindValue(world, playerRow, playerCol, START_NODE); 
    worldPrintDescription(world, playerRow, playerCol);
    printItemDescription(playerRow, playerCol, items, ITEM_COUNT);
    // blank line between 1st description & user prompt (next?) 
    cout << '\n'; 
    
    while(worldIsValid) {
         // prompt user for input
         cout << "Next? ";
         // read in the users input
         getline(cin, userInput);
         // respond appropriately to the users input
         handlePlayerInput(userInput, worldIsValid, world, playerRow, playerCol, items, ITEM_COUNT);
    } // end while

    // print the end message and score
    worldPrintEndMessage(world);
    printPlayerScore(items, ITEM_COUNT);

    return 0;
}


/*********************************FUNCTIONS***********************************/
// 
//  printItemDescriptions
//
//  Purpose: Print the descriptions of all items in an array that are at a specific location
//  Parameter(s):
//    <1> rowToSearch: the index of the row to check for items
//    <2> colToSearch: the index of the column to check for items
//    <3> items[]: an array of items to check 
//    <4> numOfItems: the size of items[]
//  Precondition(s):
//    <1>  items[] has been initialized with numOfItems items
//  Returns: N/A
//  Side Effect: N/A
//  Postcondition(s):
//    <1> If there is an item in items[] that is at the provided row/column location, its description
//        will be printed out
//
void printItemDescription(int rowToSearch, int colToSearch, Item items[], const unsigned int numOfItems) {
    for (int i = 0; i < numOfItems; i++) {
        // if the item is in the row & column to search
        if (items[i].currentRow == rowToSearch && items[i].currentCol == colToSearch) {
            // print the item's description
            itemPrintDescription(items[i]);
        } // end if
    } // end for
} // end printItemDescription

// 
//  checkGameState
//
//  Purpose: Checks if the location of the world is a victory or death node; if so, the game is 
//           terminated
//  Parameter(s):
//    <1> world: the world to check the state of
//    <2> playerRow: the current row of the player
//    <3> playerCol: the current column of the player 
//    <4> worldIsValid: the boolean that states if the game will continue
//  Precondition(s):
//    <1>  world has been initialized with a node map
//  Returns: N/A
//  Side Effect: N/A
//  Postcondition(s):
//    <1> If the player is in a death or victory node, worldIsValid will be set to false
//
void checkGameState(World &world, unsigned int playerRow, unsigned int playerCol, bool &worldIsValid) {
    if(worldIsDeath(world, playerRow, playerCol) || worldIsVictory(world, playerRow, playerCol)) {
        worldIsValid = false;
    }//end if
} // end checkGameState

// 
//  handlePlayerInput
//
//  Purpose: Handle user input in a world without items
//  Parameter(s):
//    <1> userInput: the user command to resolve
//    <2> worldIsValid: the boolean that tracks wether or not to keep playing
//    <3> world: the world to check player input for
//    <4> playerRow: the players current row location
//    <5> playerCol: the players current column location
//  Precondition(s):
//    <1>  userInput has content
//    <2>  world has been loaded with all nodes and descriptions
//  Returns: N/A
//  Side Effect: N/A
//  Postcondition(s):
//    <1> If there is an item in items[] that is at the provided index, its description
//        will be printed out
//
void handlePlayerInput(const string &userInput, bool &worldIsValid, World &world, int &playerRow, int &playerCol) {
    switch (userInput[0]) { 
            case '#': { //if a comment is entered
                break; //do nothing
            } // end # case
            case 'q': { //if the player wants to quit
                cout << "Are you sure you want to quit? ";
                string toQuit = "";
                cin >> toQuit;
                if (toQuit[0] == 'y') {
                    worldIsValid = false;
                } //end if
                break;
            } // end q case
            case 'n': { //if the player wants to move north
                if (worldCanGoNorth(world, playerRow, playerCol)) { 
                    playerRow -= 1;
                    worldPrintDescription(world, playerRow, playerCol);
                }
                else
                    cout << "There is no way to go in that direction" << endl;
                break;
            } // end n case
            case 's': { //if the player wants to move south
                if (worldCanGoSouth(world, playerRow, playerCol)) {
                    playerRow += 1;
                    worldPrintDescription(world, playerRow, playerCol);
                } 
                else
                    cout << "There is no way to go in that direction" << endl;
                break;
            } // end s case
            case 'e': { //if the player wants to move east
                if (worldCanGoEast(world, playerRow, playerCol)) {
                    playerCol += 1;
                    worldPrintDescription(world, playerRow, playerCol);
                } 
                else
                    cout << "There is no way to go in that direction" << endl;
                break;
            } // end e case
            case 'w': { //if the player wants to move west
                if (worldCanGoWest(world, playerRow, playerCol)) {
                    playerCol -= 1;
                    worldPrintDescription(world, playerRow, playerCol);
                }
                else
                    cout << "There is no way to go in that direction" << endl;
                break;
            } // end w case
            default: { //if the input isnt recognized
                cout << "Invlaid command!" << endl;
            } // end default case
    } //end switch
    
    cout << endl; //prints a new line between Next?'s
    checkGameState(world, playerRow, playerCol, worldIsValid);
} // end handlePlayerInput

// 
//  handlePlayerInput
//
//  Purpose: Handle user input in a world with items
//  Parameter(s):
//    <1> userInput: the user command to resolve
//    <2> worldIsValid: the boolean that tracks wether or not to keep playing
//    <3> world: the world to check player input for
//    <4> playerRow: the players current row location
//    <5> playerCol: the players current column location
//    <6> items[]: an array of items to consider within the world
//    <7> ITEM_COUNT: the size of items
//  Precondition(s):
//    <1>  userInput has content
//    <2>  world has been loaded with all nodes and descriptions
//  Returns: N/A
//  Side Effect: N/A
//  Postcondition(s):
//    <1> If there is an item in items[] that is at the provided index, its description
//        will be printed out
//
void handlePlayerInput(const string &userInput, bool &worldIsValid, World &world, int &playerRow, int &playerCol, Item items[], const unsigned int ITEM_COUNT) {
    switch (userInput[0]) { 
            case '#': { //if a comment is entered
                break; //do nothing
            } // end # case
            case 'q': { //if the player wants to quit
                cout << "Are you sure you want to quit? ";
                string toQuit = "";
                cin >> toQuit;
                if (toQuit[0] == 'y') {
                    worldIsValid = false;
                } //end if
                else if (toQuit[0] == 'n') {
                    break;
                }
                break;
            } // end q case
            case 'n': { //if the player wants to move north
                if (worldCanGoNorth(world, playerRow, playerCol)) { 
                    playerRow -= 1;
                    worldPrintDescription(world, playerRow, playerCol);
                    printItemDescription(playerRow, playerCol, items, ITEM_COUNT);
                }
                else
                    cout << "There is no way to go in that direction" << endl;
                break;
            } // end n case
            case 's': { //if the player wants to move south
                if (worldCanGoSouth(world, playerRow, playerCol)) {
                    playerRow += 1;
                    worldPrintDescription(world, playerRow, playerCol);
                    printItemDescription(playerRow, playerCol, items, ITEM_COUNT);
                } 
                else
                    cout << "There is no way to go in that direction" << endl;
                break;
            } // end s case
            case 'e': { //if the player wants to move east
                if (worldCanGoEast(world, playerRow, playerCol)) {
                    playerCol += 1;
                    worldPrintDescription(world, playerRow, playerCol);
                    printItemDescription(playerRow, playerCol, items, ITEM_COUNT);
                } 
                else
                    cout << "There is no way to go in that direction" << endl;
                break;
            } // end e case
            case 'w': { //if the player wants to move west  
                if (worldCanGoWest(world, playerRow, playerCol)) {
                    playerCol -= 1;
                    worldPrintDescription(world, playerRow, playerCol);
                    printItemDescription(playerRow, playerCol, items, ITEM_COUNT);
                }
                else
                    cout << "There is no way to go in that direction" << endl;
                break;
            } // end w case
            case 't': { // if the player wants to pick up an item
                string itemToGrab; // a tempoary variable to hold theid of the item a player wants to pickup
                bool validInput = false;
                cout << "Take what? "; 
                getline(cin, itemToGrab); // read in input
                for (int i = 0; i < ITEM_COUNT; i++) { // checking all items in the item array
                    if (itemToGrab[0] == items[i].itemId && // if the user provided id matches the item id 
                        playerRow == items[i].currentRow && // and if the row of the player is the same as the row of the item
                        playerCol == items[i].currentCol) { // and if the column of the player is the same as the column of the item
                        validInput = true;
                        items[i].inPlayerInventory = true;
                    } // end if
                } // end for
                if ( !validInput) {
                    cout << "Invalid item" << endl;
                } // end if
                break;
            } // end t case
            case 'l': { // if the player wants to leave an item
                string itemToLeave; // a tempoary variable to hold theid of the item a player wants to pickup
                bool validInput = false;
                cout << "Leave what? "; 
                getline(cin, itemToLeave); // read in input
                for (int i = 0; i < ITEM_COUNT; i++) { // checking all items in the item array
                    // if the user provided id matches the item id & if the item is in the player's invenotry 
                    if (itemToLeave[0] == items[i].itemId && items[i].inPlayerInventory) { 
                        validInput = true;
                        items[i].inPlayerInventory = false; // the item is no longer in the inventory
                        items[i].currentRow = playerRow; // row location is changed to the players row location
                        items[i].currentCol = playerCol; // column location is changed to the players column location
                    } // end if
                } // end for
                if ( !validInput) {
                    cout << "Invalid item" << endl;
                } // end if
                break;
            }
            case 'i': { // if the player wants to see their inventory
                for(int i = 0; i < ITEM_COUNT; i++) {
                    if (items[i].inPlayerInventory) {
                        itemPrintDescription(items[i]);
                    }
                }
                break;
            }
            case '~': { // debugging case
                cout << "CurrentRow: " << playerRow << endl << "CurrentCol: " << playerCol << endl;
                printItemDescription(playerRow, playerCol, items, ITEM_COUNT);
                break;
            } // end d case
            default: { //if the input isnt recognized
                cout << "Invlaid command!" << endl;
            } // end default case
    } //end switch
    
    cout << endl; //prints a new line between Next?'s
    checkGameState(world, playerRow, playerCol, worldIsValid);
} // end handlePlayerInput

// 
//  printPlayerScore
//
//  Purpose: Total up & print a players score based on the items in their inventory.
//          If the player has nothing in their inventory, 0 will be their score.
//  Parameter(s):
//    <1> items[]: an array of items within the world
//    <2> numOfItems: the size of items[]
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: N/A
//  Postcondition(s):
//    <1> A players score is printed out
//
void printPlayerScore(const Item items[], const unsigned int numOfItems) {
    int score = 0;
    for (int i = 0; i < numOfItems; i++) {
        score += itemGetPlayerPoints(items[i]);
    } // end for
    cout << "In this game you scored " << score << " points." << endl;
} // end printPlayerScore