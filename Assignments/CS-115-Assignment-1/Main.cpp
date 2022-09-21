// Name: Owen Monus
// Student Number: 200482797
// Date: Sept 15, 2022

#include <iostream>
#include <string>
using namespace std;
#include "World.h"

/* 
main

Purpose: A simple, text-based exploration game. In the game, the player will
use text commands ('n', 's', 'e', and 'w') to explore a simulated 2D world. The game will 
print a suitable message and terminate when the player enters the quit ('q') command, or 
if the player reaches a special victory location or any of a number of death locations. 
For any other location, the player will be shown a description and then asked "Next? ". 
The process of receiving input from the player and responding will repeated until the 
game terminates. 

*/

int main() {
    World world;
    int playerRow; //tracks the players row posistion
    int playerCol; //tracks the players col posistion
    bool worldIsValid = true; //tracks if the game should continue
    string userInput;

    worldLoadAll(world, "blizzard"); //load nodes from a file
    worldPrintStartMessage(world);
    cout << '\n'; //blank line between start message & 1st description
    worldFindValue(world, playerRow, playerCol, START_NODE); //move to the starting node
    worldPrintDescription(world, playerRow, playerCol);
    cout << '\n'; //blank line between 1st description & next?
    
    while(worldIsValid) {
        cout << "Next? ";
        getline(cin, userInput);

        //The follwing switch statment handles player input according to the input
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

        cout << '\n'; //prints a new line between Next?'s

        /* Checks if the loaction of the world is a victory or death node; if so, the game is 
        terminated */
        if(worldIsDeath(world, playerRow, playerCol) || worldIsVictory(world, playerRow, playerCol)) {
            worldIsValid = false;
        }//end if
    } //end while

    worldPrintEndMessage(world);
   
    return 0;
} //end main
