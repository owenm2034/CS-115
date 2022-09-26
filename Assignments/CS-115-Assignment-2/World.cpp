// Name: Owen Monus
// Student Number: 200482797
// Date: Sept 26, 2022

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

#include "World.h"

//an array of length DESCRIPTION_COUNT that contains the world text descriptions
string descriptions[DESCRIPTION_COUNT]; 

void worldClear (World world) {
    for (int r = 0; r < ROW_COUNT; r++) {
        for (int c = 0; c < COLUMN_COUNT; c++) {
            world[r][c] = INACCESSIBLE;
        } //end column for
    } //end row for
} //end worldClear

void worldLoadAll (World world, string game_name) {
    string nodeDataFile = game_name + "_grid.txt";
    string textDataFile = game_name + "_text.txt";

    worldLoadNodes(world, nodeDataFile);
    worldLoadDescriptions(world, textDataFile);
} //end worldLoadAll

void worldLoadNodes (World world, string filename) {
    ifstream fin;

    fin.open(filename);
    
    for (int r = 0; r < ROW_COUNT; r++) {
        for (int c = 0; c < COLUMN_COUNT; c++) {
            fin >> world[r][c];
        } //end column for
    } //end row for

    fin.close();
} //end worldLoadNodes

void worldDebugPrint (const World world) {
    for (int r = 0; r < ROW_COUNT; r++) {
        for (int c = 0; c < COLUMN_COUNT; c++) {
            cout << world[r][c] << '\t';
        } //end column for
        cout << endl; 
    } //end row for
} //end worldDebugPrint

bool worldIsValid (const World world, int row, int column) {
    if((row >= 0 && row < ROW_COUNT) && (column >= 0 && column < COLUMN_COUNT)) {
        return true;
    }
    else
        return false;
} // end worldIsValid

bool worldCanGoNorth (const World world, int row, int column) {
    if(( row != 0 ) && ( world[row -1][column] != INACCESSIBLE)) {
        return true;
    }
    else
        return false;
} //end worldCanGoNorth

bool worldCanGoSouth (const World world, int row, int column) {
    if(( row != ( ROW_COUNT -1 ) ) && ( world[row + 1][column] != INACCESSIBLE)) {
        return true;
    }
    else
        return false;
} //end worldCanGoSouth

bool worldCanGoEast (const World world, int row, int column) {
    if(( column != ( COLUMN_COUNT -1 ) ) && ( world[row][column +1] != INACCESSIBLE)) {
        return true;
    }
    else
        return false;
} //end worldCanGoEast

bool worldCanGoWest (const World world, int row, int column) {
    if(( column != 0 ) && ( world[row][column -1] != INACCESSIBLE)) {
        return true;
    }
    else
        return false;
} //end worldCanGoWest

bool worldIsDeath (const World world, int row, int column) {
    if(world[row][column] == DEATH_NODE) {
        return true;
    }
    else
        return false;
} //end worldIsDeath

bool worldIsVictory (const World world, int row, int column) {
    if(world[row][column] == VICTORY_NODE) {
        return true;
    }
    else
        return false;
} //end worldIsVictory

void worldFindValue (const World world, int& result_row, int& result_column, NodeValue value_to_find) {
    result_row = -1;
    result_column = -1;
    
    for (int r = 0; r < ROW_COUNT; r++) {
        for (int c = 0; c < COLUMN_COUNT; c++) {
            if (world[r][c] == value_to_find) {
                result_row = r;
                result_column = c;
            } //end if
        } //end column for
    } //end row for
} //end worldFindValue

void worldLoadDescriptions (World world, string filename) {
    fstream fin;
    string tempString; // string to hold the values fstream reads in

    fin.open(filename);
    getline(fin, tempString, '\n'); 
    getline(fin, tempString, '\n');

    //Adds a chunk of text from filename into a string at i in descriptions
    for (int i = 0; i < DESCRIPTION_COUNT; i++) {
        /* the value of tempString doesnt matter, as long as it isnt "" – the following getline 
        call changes it's value */
        tempString = " "; 
        while (tempString != "") {
            getline(fin, tempString, '\n');            
            descriptions[i] = descriptions[i] + tempString + "\n";
        } //end while

        //remove the excess \n from the end of the string
        descriptions[i] = descriptions[i].substr(0, (descriptions[i].length() - 1)); 

    } //end for
} //end worldLoadDescriptions

void worldPrintDescription (const World world, int row, int column) {
    unsigned int descriptionIndex = world[row][column];
    cout << descriptions[descriptionIndex];
} //end worldPrintDescription

void worldPrintStartMessage (const World world) {
    cout << descriptions[START_MESSAGE];
} //end worldPrintStrartMessage

void worldPrintEndMessage (const World world) {
    cout << descriptions[END_MESSAGE];
} //end worldPrintStartMessage