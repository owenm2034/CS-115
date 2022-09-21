/*
*   Author: Philip Pitura   
*   Date: September 14th 2022
*   Class: CS115 _ University of Regina
*   Purpose: Provide definitions and implementations of World Functions
*/



#include <iostream>
#include <string>
#include <fstream>
#include "World.h"
using namespace std;

string descriptions[DESCRIPTION_COUNT];

//Sets each node to INACCESSIBLE
void worldClear(World world){
    for(int i = 0; i < ROW_COUNT; i++){
        for(int j = 0; j < COLUMN_COUNT; j++){
            world[i][j] = INACCESSIBLE;
        }// end column loop
    }//end row loop
}


void worldLoadAll(World world, string game_name){
    string data_file_name = game_name + "_grid.txt";
    string text_data_file = game_name + "_text.txt";

    worldLoadDescriptions(world, text_data_file);
    worldLoadNodes(world, data_file_name);
}


//Load nodes from file.
void worldLoadNodes(World world, string filename){
    ifstream fin;
    fin.open(filename.c_str());

    if(!fin){
        cout << "ERROR Opening file.\n";
    }

    for(int i = 0; i < ROW_COUNT; i++){
        for(int j = 0; j < COLUMN_COUNT; j++){
            fin >> world[i][j];
        }
    }

    fin.close();
}

void worldDebugPrint(const World world){
    for(int i = 0; i < ROW_COUNT; i++){
        for(int j = 0; j < COLUMN_COUNT; j++){
            cout << world[i][j] << "\t";
        }// end column loop
        cout << endl;
    }//end row loop
}

//return true if the world location is valid (has a non-negative row and column that are less than their count constants)
bool worldIsValid(const World world, int row, int column){
    
    if(row >= 0 && row < ROW_COUNT)
        if(column >= 0 && column < COLUMN_COUNT)
            return true;
    
    
    return false;
}


//The next four functions work the same. The only difference is the direction we check.
//This is indicated by number changes to the checkRow and checkColumn

bool worldCanGoNorth(const World world, int row, int column){
    int checkRow = row - 1;
    int checkColumn = column;


    //we check in this order to first ensure we are not breaking the bounds of the array
    //then we access the array to see if it's inaccessible. If you do these checks the other way
    //or at the same time you could have a out of bounds exception.
    if(worldIsValid(world, checkRow, checkColumn))
        if(world[checkRow][checkColumn] != INACCESSIBLE)
            return true;


    return false;
}
bool worldCanGoSouth(const World world, int row, int column){
    int checkRow = row + 1;
    int checkColumn = column;


    //we check in this order to first ensure we are not breaking the bounds of the array
    //then we access the array to see if it's inaccessible. If you do these checks the other way
    //or at the same time you could have a out of bounds exception.
    if(worldIsValid(world, checkRow, checkColumn))
        if(world[checkRow][checkColumn] != INACCESSIBLE)
            return true;


    return false;
}
bool worldCanGoEast(const World world, int row, int column){
    int checkRow = row;
    int checkColumn = column + 1;


    //we check in this order to first ensure we are not breaking the bounds of the array
    //then we access the array to see if it's inaccessible. If you do these checks the other way
    //or at the same time you could have a out of bounds exception.
    if(worldIsValid(world, checkRow, checkColumn))
        if(world[checkRow][checkColumn] != INACCESSIBLE)
            return true;


    return false;
}
bool worldCanGoWest(const World world, int row, int column){
    int checkRow = row;
    int checkColumn = column - 1;


    //we check in this order to first ensure we are not breaking the bounds of the array
    //then we access the array to see if it's inaccessible. If you do these checks the other way
    //or at the same time you could have a out of bounds exception.
    if(worldIsValid(world, checkRow, checkColumn))
        if(world[checkRow][checkColumn] != INACCESSIBLE)
            return true;


    return false;
}

//return true if the indicated node is a death node
bool worldIsDeath(const World world, int row, int column){
    return (world[row][column] == DEATH_NODE);
}

//return true if the indicated node is a victory node
bool worldIsVictory(const World world, int row, int column){
    return (world[row][column] == VICTORY_NODE);
}



void worldFindValue(const World world, int& result_row, int& result_column, NodeValue value_to_find){
    result_row = -1;
    result_column = -1;

    for(int i = 0; i < ROW_COUNT; i++){
        for(int j = 0; j < COLUMN_COUNT; j++){
            if(world[i][j] == value_to_find){
                result_row = i;
                result_column = j;
            }
        }// end column loop
    }//end row loop
}

bool stringHasContent(string toCheck){
    if(toCheck.empty()){
        return false;
    }

    for(int i = 0; i < toCheck.length(); i++){
        if(toCheck.at(i) != ' ' || toCheck.at(i) != '\n'){
            return true;
        }
    }
    return false;
}

void worldLoadDescriptions (World world, string filename){ 
    ifstream fin;
    fin.open(filename.c_str());

    string inText;
    string toStore = "";
    getline(fin, inText);
    descriptions[0] = inText;
    getline(fin, inText);

    for(int i = 0; i < DESCRIPTION_COUNT;){
        getline(fin, inText);        

        // cout << "inText is: " << int(inText.at(0));
        if(stringHasContent(inText)){
            toStore += inText + '\n';
        }
        else{
            descriptions[i] = toStore;
            i++;
            toStore = "";
        }
    }

    // This code was for debugging
    // for(int i = 0; i < DESCRIPTION_COUNT; i++){
    //     cout << i << ": " << descriptions[i] << endl;
    // }


}

void worldPrintDescription (const World world, int row, int column){
    cout << descriptions[world[row][column]];
}


void worldPrintStartMessage (const World world){
    cout << descriptions[START_MESSAGE];
}


void worldPrintEndMessage (const World world){
    cout << descriptions[END_MESSAGE];
}

