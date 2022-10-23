// Name: Owen Monus
// Student Number: 200482797
// Date: October 22, 2022

#include <string>
#include <iostream>
#include <fstream>
#include "World.h"
using namespace std;

//
// Phil's helper function -> it checks if a string has content
bool stringHasContent(string toCheck)
{
    if(toCheck.empty()){
        return false;
    }

    for(int i = 0; i < toCheck.length(); i++){
        if(toCheck.at(i) != ' ' || toCheck.at(i) != '\n' || toCheck.at(i) != '\0'){
            return true;
        }
    }
    return false;
}

void World::loadNodes(string filename)
{
    ifstream fin;
    fin.open(filename);
    for (int r = 0; r < ROW_COUNT; r++) {
        for (int c = 0; c < COLUMN_COUNT; c++) {
            fin >> nodes[r][c];
        } //end column for
    } //end row for
    fin.close();
}

void World::loadDescriptions(string filename) 
{
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
    while(flag < numLines) {
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
        /* the value of tempString doesnt matter, as long as it isnt "" – the following getline 
        call changes it's value */
        tempString = "someValue"; 
        while (stringHasContent(tempString)) { //stringHasContent(tempString)
            getline(fin, tempString, '\n');            
            descriptions[i] = descriptions[i] + tempString + "\n";
        } //end while

        //remove the excess \n from the end of the string
        descriptions[i] = descriptions[i].substr(0, (descriptions[i].length() - 1)); 

    } //end for
}

bool World::isInvariantTrue () const 
{
    if (!(description_count <= MAX_DESCRIPTION_COUNT)) {
        return false;
        cout << "!(description_count <= MAX_DESCRIPTION_COUNT): true" << endl;
    }
    
    for (int i = 0; i < description_count; i++) {
        if (!(descriptions[i] != "")) {
            cout << "descriptions at " << i << " is \"\"" << endl; 
            return false;
        }
    }
    
    for (int r = 0; r < ROW_COUNT; r++) {
        for (int c = 0; c < COLUMN_COUNT; c++) {
            if (!(nodes[r][c] < description_count)) {
                cout << "nodes[" << r << "][" << c << "] >= description_count : true" << endl;
                return false;
            }
        }
    }
    
    return true;
}

World::World(const string& game_name) 
{
    string nodeDataFile = game_name + "_grid.txt";
    string textDataFile = game_name + "_text.txt";

    loadDescriptions(textDataFile);
    loadNodes(nodeDataFile);
    
    // assert(isInvariantTrue());
}

void World::debugPrint() const 
{
    for (int r = 0; r < ROW_COUNT; r++) {
        for (int c = 0; c < COLUMN_COUNT; c++) {
            cout << nodes[r][c] << '\t';
        } //end column for
        cout << endl; 
    } //end row for

    cout << "\nDescription Count: " << description_count << endl;
    for (int i = 0; i < description_count; i++) {
        cout << descriptions[i] << endl;
    }
}

bool World::isValid(const Location& location) const
{
    assert(isInvariantTrue());
    if((location.row >= 0 && location.row < ROW_COUNT) && (location.column >= 0 && location.column < COLUMN_COUNT)) {
        return true;
    }
    else
        return false;
}

bool World::isDeath(const Location& location) const 
{
    assert(isInvariantTrue());
    assert(isValid(location)); 
    if(nodes[location.row][location.column] == DEATH_NODE) {
        return true;
    }
    else
        return false;
}

bool World::isVictory (const Location& location) const
{
    assert(isInvariantTrue());
    assert(isValid(location));
    if(nodes[location.row][location.column] == VICTORY_NODE) {
        return true;
    }
    else
        return false;
}

bool World::canGoNorth (const Location& location) const 
{
    assert(isInvariantTrue());
    assert(isValid(location));
    if(( location.row != 0) && (nodes[location.row - 1][location.column] != INACCESSIBLE)) {
        return true;
    }
    else
        return false;
}

bool World::canGoSouth (const Location& location) const 
{    
    assert(isInvariantTrue());
    assert(isValid(location));
    if(( location.row != ( ROW_COUNT - 1 )) && (nodes[location.row + 1][location.column] != INACCESSIBLE)) {
        return true;
    }
    else
        return false;
}

bool World::canGoEast (const Location& location) const
{
    assert(isInvariantTrue());
    assert(isValid(location));
    if(( location.column != ( COLUMN_COUNT - 1 )) && 
    (nodes[location.row][location.column + 1] != INACCESSIBLE)) {
        return true;
    }
    else
        return false;
}

bool World::canGoWest (const Location& location) const
{
    assert(isInvariantTrue());
    assert(isValid(location));
    if((location.column != 0) && (nodes[location.row][location.column - 1] != INACCESSIBLE)) {
        return true;
    }
    else
        return false;
}

Location World::getNorth (const Location& location) const 
{
    assert(isInvariantTrue());
    assert(canGoNorth(location));
    return Location(location.row - 1, location.column);
}

Location World::getSouth (const Location& location) const 
{
    assert(isInvariantTrue());
    assert(canGoSouth(location));
    return Location(location.row + 1, location.column);
}

Location World::getEast (const Location& location) const 
{
    assert(isInvariantTrue());
    assert(canGoEast(location));
    return Location(location.row, location.column + 1);
}

Location World::getWest (const Location& location) const 
{   
    assert(isInvariantTrue());
    assert(canGoWest(location));
    return Location(location.row, location.column - 1);
}

Location World::getStart() const 
{
    assert(isInvariantTrue());
    for (int r = 0; r < ROW_COUNT; r++) {
        for (int c = 0; c < COLUMN_COUNT; c++) {
            if (nodes[r][c] == START_NODE) {
                return Location(r, c);
            } // end if
        } // end column for
    } // end row for
    return NO_SUCH_VALUE;
} // end getStart

void World::printStartMessage () const 
{
    assert(isInvariantTrue());
    cout << descriptions[START_MESSAGE];
}

void World::printEndMessage () const 
{
    assert(isInvariantTrue());
    cout << descriptions[END_MESSAGE];
}

void World::printDescription (const Location& location) const 
{
    assert(isInvariantTrue());
    assert(isValid(location));
    cout << descriptions[nodes[location.row][location.column]];
}