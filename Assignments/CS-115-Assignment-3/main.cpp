// Author: Owen Monus
// Student ID: 200482797   
// Date: October 22nd 2022

#include "Item.h"
#include "World.h"
#include "Location.h"
#include <iostream> 
using namespace std;

// helper functionn declarations
void printItemDescription(Location location, Item items[], const unsigned int numOfItems);
void checkGameState(World &world, Location location, bool &worldIsValid);
void handlePlayerInput(const string &userInput, bool &worldIsValid, World &world, Location &location, Item items[], const unsigned int ITEM_COUNT);
void printPlayerScore(const Item items[], const unsigned int numOfItems);

int main () {
    // initialize variables
    const unsigned int ITEM_COUNT = 9;
    string userInput;

    bool worldIsValid = true; 
    World world = World("ghostwood");
    Item items[ITEM_COUNT] = {
        { // scarab beetle
        's',   
        Location(0,3),
        -5,
        "There is a black scarab beetle (s) here.",
        "A black scarab beetle (s) is crawling up your arm."       
        },
        { // candle stick
            'c',
            Location(1, 1),
            9,
            "There is a silver candlestick (c) here.",
            "You are carrying a silver candlestick (c)."
        },
        { // key
            'k',
            Location(2, 0),
            3,
            "There is an old iron key (k) here.",
            "You have an old iron key (k) in your pocket."
        },
        { // tarantula
            't',
           Location(2, 9),
            -8,
            "There is a tarantula (t) here.",
            "There is a tarantula (t) hanging on your shirt."
        },
        { // book
            'b',
            Location(3, 4),
            4,
            "There is a book (b) here with an eye drawn on the cover.",
            "You have a book (b) under your arm with an eye drawn on the cover."
        },
        { // moth
            'm',
            Location(5,5),
            -2,
            "There is a giant moth (m) sleeping here.",
            "A giant moth (m) is perched on your shoulder."
        },
        { //amulet
            'p',
            Location(7, 9),
            7,
            "There is a golden pendant (p) here.",
            "You are wearing a golden pendant (p)."
        },
        { // dagger
            'd',
            Location(8,0),
            1,
            "There is an rune-carved dagger (d) here.",
            "You have an rune-carved dagger (d) stuck in your belt."
        },
        { // ring
            'r',
            Location(9,6),
            10,
            "There is a diamond ring (r) here.",
            "You are wearing a diamond ring (r)."
        }
    };

    // initialize world 
    Location playerLocation = world.getStart();
    
    // begin game
    world.printStartMessage();
    cout << '\n';
    world.printDescription(playerLocation);
    printItemDescription(playerLocation, items, ITEM_COUNT);
    cout << '\n'; 
    
    // run game
    while(worldIsValid) {
         cout << "Next? ";
         getline(cin, userInput);
         handlePlayerInput(userInput, worldIsValid, world, playerLocation, items, ITEM_COUNT);
    } // end while

    // print the end message and score
    world.printEndMessage();
    printPlayerScore(items, ITEM_COUNT);

    return 0;
}


/*********************************FUNCTIONS***********************************/
// 
//  printItemDescriptions
//
//  Purpose: Print the descriptions of all items in an array that are at a specific location
//  Parameter(s):
//    <1> location: the worlds current location to compare to the items location
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
void printItemDescription(Location location, Item items[], const unsigned int numOfItems) {
    for (int i = 0; i < numOfItems; i++) {
        // if the item is in the row & column to search
        if (items[i].isAtLocation(location)) {
            // print the item's description
            items[i].printDescription();
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
void checkGameState(World &world, Location location, bool &worldIsValid) {
    if(world.isDeath(location) || world.isVictory(location)) {
        worldIsValid = false;
    }//end if
} // end checkGameState

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
void handlePlayerInput(const string &userInput, bool &worldIsValid, World &world, Location &location, Item items[], const unsigned int ITEM_COUNT) {
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
                if (world.canGoNorth(location)) { 
                    location = world.getNorth(location);
                    world.printDescription(location);
                    printItemDescription(location, items, ITEM_COUNT);
                }
                else
                    cout << "There is no way to go in that direction" << endl;
                break;
            } // end n case
            case 's': { //if the player wants to move south
                if (world.canGoSouth(location)) {
                    location = world.getSouth(location);
                    world.printDescription(location);
                    printItemDescription(location, items, ITEM_COUNT);
                } 
                else
                    cout << "There is no way to go in that direction" << endl;
                break;
            } // end s case
            case 'e': { //if the player wants to move east
                if (world.canGoEast(location)) {
                    location = world.getEast(location);
                    world.printDescription(location);
                    printItemDescription(location, items, ITEM_COUNT);
                } 
                else
                    cout << "There is no way to go in that direction" << endl;
                break;
            } // end e case
            case 'w': { //if the player wants to move west  
                if (world.canGoWest(location)) {
                    location = world.getWest(location);
                    world.printDescription(location);
                    printItemDescription(location, items, ITEM_COUNT);
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
                    if (items[i].isAtLocation(location)) { // and if the column of the player is the same as the column of the item
                        validInput = true;
                        items[i].moveToInventory();
                    } // end if
                } // end for
                if ( !validInput) {
                    cout << "Invalid item" << endl;
                } // end if
                break;
            } // end t case
            case 'l': { // if the player wants to leave an item
                string itemToLeave; // a tempoary variable to hold the id of the item a player wants to pickup
                bool validInput = false;
                cout << "Leave what? "; 
                getline(cin, itemToLeave); // read in input
                for (int i = 0; i < ITEM_COUNT; i++) { // checking all items in the item array
                    // if the user provided id matches the item id & if the item is in the player's invenotry 
                    if (itemToLeave[0] == items[i].getId() && items[i].isInInventory()) { 
                        validInput = true;
                        items[i].reset();
                        items[i].moveToLocation(location);
                    } // end if
                } // end for
                if ( !validInput) {
                    cout << "Invalid item" << endl;
                } // end if
                break;
            }
            case 'i': { // if the player wants to see their inventory
                for(int i = 0; i < ITEM_COUNT; i++) {
                    if (items[i].isInInventory()) {
                        items[i].printDescription();
                    }
                }
                break;
            }
            case '~': { // debugging case
                cout << "CurrentRow: " << location.row << endl << "CurrentCol: " << location.column << endl;
                printItemDescription(location, items, ITEM_COUNT);
                break;
            }
            default: { //if the input isnt recognized
                cout << "Invlaid command!" << endl;
            } // end default case
    } //end switch
    
    //prints a new line between Next?'s
    cout << endl;
    // ensures the game isnt located at a death or victory node
    checkGameState(world, location, worldIsValid);
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
        score += items[i].getPlayerPoints(); //tally players score
    } // end for
    cout << "In this game you scored " << score << " points." << endl;
} // end printPlayerScore`````````