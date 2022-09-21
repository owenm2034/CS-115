//
//  TestWorld1A.cpp
//
//  A test program for the World module.
//
//  This program is to be used with Assignment 1: Part A for
//    CS115, 202210.
//
//  Do not modify this file.
//

#include "World.h"
#include "World.h"  // repeated to test for #include errors

#include <cassert>
#include <string>
#include <iostream>
#include <iomanip>
#include <typeinfo>  // for typeid

#include "TestHelper.h"

using namespace std;

int main ();

const int COMPILE_AND_START_MARKS     = 3;
const int DID_NOT_CRASH_RUNNING_MARKS = 2;
const int COMPILE_AND_NOT_CRASH_MARKS = COMPILE_AND_START_MARKS + DID_NOT_CRASH_RUNNING_MARKS;
const int COMBINED_TEST_MARKS         = 10;
const int TOTAL_MARKS                 = COMPILE_AND_NOT_CRASH_MARKS + COMBINED_TEST_MARKS;

const int ROW_COUNT_CORRECT    = 6;
const int COLUMN_COUNT_CORRECT = 9;

const unsigned int INACCESSIBLE_CORRECT  = 0;
const unsigned int START_MESSAGE_CORRECT = 1;
const unsigned int END_MESSAGE_CORRECT   = 2;
const unsigned int DEATH_NODE_CORRECT    = 3;
const unsigned int START_NODE_CORRECT    = 4;
const unsigned int VICTORY_NODE_CORRECT  = 5;



int main ()
{
	testHelperStartup("TestWorld1A", COMPILE_AND_START_MARKS, TOTAL_MARKS);

	//
	//  Test size constants
	//

	cout << "Testing ROW_COUNT" << endl;
	bool correct_row_count = testHelperConstant(ROW_COUNT, ROW_COUNT_CORRECT, "ROW_COUNT");
	cout << endl;

	cout << "Testing COLUMN_COUNT" << endl;
	bool correct_column_count = testHelperConstant(COLUMN_COUNT, COLUMN_COUNT_CORRECT, "COLUMN_COUNT_COUNT");
	cout << endl;

	unsigned int correct_size = (correct_row_count    ? 1 : 0) +
	                            (correct_column_count ? 1 : 0);

	//
	//  Test node value constants
	//

	cout << "Testing INACCESSIBLE" << endl;
	bool correct_inaccessible = testHelperConstant(INACCESSIBLE, INACCESSIBLE_CORRECT, "INACCESSIBLE_COUNT");
	cout << endl;

	cout << "Testing START_MESSAGE" << endl;
	bool correct_start_message = testHelperConstant(START_MESSAGE, START_MESSAGE_CORRECT, "START_MESSAGE_COUNT");
	cout << endl;

	cout << "Testing END_MESSAGE" << endl;
	bool correct_end_message = testHelperConstant(END_MESSAGE, END_MESSAGE_CORRECT, "END_MESSAGE_COUNT");
	cout << endl;

	cout << "Testing DEATH_NODE" << endl;
	bool correct_death_node = testHelperConstant(DEATH_NODE, DEATH_NODE_CORRECT, "DEATH_NODE_COUNT");
	cout << endl;

	cout << "Testing START_NODE" << endl;
	bool correct_start_node = testHelperConstant(START_NODE, START_NODE_CORRECT, "START_NODE_COUNT");
	cout << endl;

	cout << "Testing VICTORY_NODE" << endl;
	bool correct_victory_node = testHelperConstant(VICTORY_NODE, VICTORY_NODE_CORRECT, "VICTORY_NODE_COUNT");
	cout << endl;

	unsigned int correct_node_constants = (correct_inaccessible  ? 1 : 0) +
	                                      (correct_start_message ? 1 : 0) +
	                                      (correct_end_message   ? 1 : 0) +
	                                      (correct_death_node    ? 1 : 0) +
	                                      (correct_start_node    ? 1 : 0) +
	                                      (correct_victory_node  ? 1 : 0);

	//
	//  Test typedefs
	//

	cout << "Testing NodeValue type" << endl;
	bool correct_node_value_type = typeid(NodeValue) == typeid(unsigned int);
	if(!correct_node_value_type)
		cout << "* Incorrect: NodeValue should be a typedef for unsigned int" << endl;
	else
		cout << "* Correct" << endl;
	cout << endl;

	cout << "Testing World type" << endl;
	bool correct_world_type = typeid(World) == typeid(NodeValue[ROW_COUNT][COLUMN_COUNT]);
	if(!correct_world_type)
	{
		if(typeid(World) == typeid(NodeValue[COLUMN_COUNT][ROW_COUNT]))
			cout << "* Incorrect: Row and column sizes for World are reversed" << endl;
		else
			cout << "* Incorrect: World should contain a 2D array of NodeValues" << endl;
	}
	else
		cout << "* Correct" << endl;
	cout << endl;

	unsigned int correct_typdefs = (correct_node_value_type ? 1 : 0) +
	                               (correct_world_type      ? 1 : 0);



	//
	//  Print results
	//

	testHelperPrintSummaryHeader(24, 1, DID_NOT_CRASH_RUNNING_MARKS);
	testHelperPrintSummaryLine("World size constants", correct_size,           2);
	testHelperPrintSummaryLine("Node value constants", correct_node_constants, 6);
	testHelperPrintSummaryLine("typedef declarations", correct_typdefs,        2);

	unsigned int mark = COMPILE_AND_NOT_CRASH_MARKS;

	mark += correct_size * 2;
	mark += (int)(correct_node_constants * 0.5);
	if(correct_node_value_type)
		mark += 1;
	if(correct_world_type)
		mark += 2;

	assert(mark <= TOTAL_MARKS);
	testHelperPrintMark(mark, TOTAL_MARKS);

	testHelperWaitForEnter();
	return 0;
}


