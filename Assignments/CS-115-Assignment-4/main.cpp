// Author: Owen Monus
// Student ID: 200482797   
// Date: October 22nd 2022

#include "Game.h"
#include <iostream>

using namespace std;

// helper function declarations
void handlePlayerInput(string &userInput, bool &gameIsValid, Game &game);

int main() {
    // initialize variables
    string userInput;
    bool gameIsValid = true;
    Game game = Game("ghostwood");

    // begin game
    game.printStartMessage();
    cout << '\n';
    game.printDescription();
    cout << '\n';

    // run game
    while (!game.isOver() && gameIsValid) {
        cout << "Next? ";
        getline(cin, userInput);
        handlePlayerInput(userInput, gameIsValid, game);
    } // end while

    // print the end message and score
    game.printEndMessage();
    game.printScore();

    return 0;
}


/*********************************FUNCTIONS***********************************/

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
void handlePlayerInput(string &userInput, bool &gameIsValid, Game &game) {
    switch (userInput[0]) {
        case '#': { //if a comment is entered
            break; //do nothing
        }
        case 'q': { //if the player wants to quit
            cout << "Are you sure you want to quit? ";
            getline(cin, userInput);
            if (userInput[0] == 'y') {
                gameIsValid = false;
                break;
            } else if (userInput[0] == 'n') {
                break;
            } else {
                cout << "Invalid command!" << endl;
            }
            break;
        }
        case 'n': { //if the player wants to move north
            game.moveNorth();
            break;
        }
        case 's': { //if the player wants to move south
            game.moveSouth();
            break;
        }
        case 'e': { //if the player wants to move east
            game.moveEast();
            break;
        }
        case 'w': { //if the player wants to move west
            game.moveWest();
            break;
        }
        case 't': { // if the player wants to pick up an item
            string itemToGrab;
            cout << "Take what? ";
            getline(cin, itemToGrab); // read in input
            game.takeItem(itemToGrab[0]);
            break;
        }
        case 'l': { // if the player wants to leave an item
            string itemToLeave; // a tempoary variable to hold the id of the item a player wants to pickup
            cout << "Leave what? ";
            getline(cin, itemToLeave); // read in input
            game.leaveItem(itemToLeave[0]);
            break;
        }
        case 'i': { // if the player wants to see their inventory
            game.printInventory();
            break;
        }
        case 'r': {
            cout << "Are you sure you want to restart? ";
            getline(cin, userInput);
            if (userInput[0] == 'y') {
                game.reset();
                cout << '\n';
                game.printStartMessage();
                cout << '\n';
                game.printDescription();
                cout << '\n';
                break;
            } else if (userInput[0] == 'n') {
                break;
            } else {
                cout << "Invalid command!" << endl;
            }
            break;
        }
        default: {
            cout << "Invalid command!" << endl;
        }
    }

    cout << endl;
} // end handlePlayerInput
