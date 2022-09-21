/*
*   Author: Philip Pitura   
*   Date: September 14th 2022
*   Class: CS115 _ University of Regina
*   Purpose: Provide prototypes and constant declarations for World
*/


#pragma once
#include <string>
using namespace std;

const int ROW_COUNT = 6;
const int COLUMN_COUNT = 9;
const unsigned int DESCRIPTION_COUNT = 26;

typedef unsigned int NodeValue;
typedef NodeValue World[ROW_COUNT][COLUMN_COUNT];

const NodeValue INACCESSIBLE = 0;
const NodeValue START_MESSAGE = 1;
const NodeValue END_MESSAGE = 2;
const NodeValue DEATH_NODE = 3;
const NodeValue START_NODE = 4;
const NodeValue VICTORY_NODE = 5;

void worldClear(World world);
void worldLoadAll(World world, string game_name);
void worldLoadNodes(World world, string filename);
void worldLoadDescriptions (World world, string filename);
void worldDebugPrint(const World world);
bool worldIsValid(const World world, int row, int column);
bool worldCanGoNorth(const World world, int row, int column);
bool worldCanGoSouth(const World world, int row, int column);
bool worldCanGoEast(const World world, int row, int column);
bool worldCanGoWest(const World world, int row, int column);
bool worldIsDeath(const World world, int row, int column);
bool worldIsVictory(const World world, int row, int column);
void worldFindValue(const World world, int& result_row, int& result_column, NodeValue value_to_find);

void worldPrintDescription (const World world, int row, int column);
void worldPrintStartMessage (const World world);
void worldPrintEndMessage (const World world);


bool stingHasContent(string toCheck);