//
//  TestWorld1B.cpp
//
//  A test program for the World module.
//
//  This program is to be used with Assignment 1: Part B for
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
#include <sstream>
#include <vector>

#include "TestHelper.h"

using namespace std;



int main ();

typedef bool (*pfCanGoDirectionFunction)(const World, int, int);
bool testCanGoDirection (const World& world, unsigned int array_offset,
                         pfCanGoDirectionFunction pf_function);
void fillWorld (World& r_world, unsigned int node_value);
double getWorldFractionInaccessible (const World& world);
double getWorldFractionMatchingBlizzard (const World& world);
bool testFindNode (const World& world,
                   unsigned int node_value, const string& node_name,
                   int desired_row, int desired_column);
double testDebugPrint (const string& printed);

const int COMPILE_AND_START_MARKS     =  6;
const int DID_NOT_CRASH_RUNNING_MARKS =  6;
const int COMPILE_AND_NOT_CRASH_MARKS = COMPILE_AND_START_MARKS + DID_NOT_CRASH_RUNNING_MARKS;
const int COMBINED_TEST_MARKS         = 23;
const int TOTAL_MARKS                 = COMPILE_AND_NOT_CRASH_MARKS + COMBINED_TEST_MARKS;

const int ROW_COUNT_CORRECT    = 6;
const int COLUMN_COUNT_CORRECT = 9;
const int NODE_COUNT_CORRECT   = ROW_COUNT_CORRECT * COLUMN_COUNT_CORRECT;
const unsigned int AA_BLIZARD_CORRECT[ROW_COUNT_CORRECT][COLUMN_COUNT_CORRECT] =
{
	{	0,	9,	9,	10,	11,	12,	13,	13,	3,	},
	{	9,	9,	9,	0,	15,	14,	3,	3,	0,	},
	{	9,	9,	0,	3,	16,	3,	0,	0,	0,	},
	{	0,	7,	8,	3,	17,	18,	0,	25,	5,	},
	{	6,	4,	3,	0,	0,	19,	0,	19,	0,	},
	{	3,	3,	0,	0,	21,	20,	22,	23,	24,	},
};

const unsigned int INACCESSIBLE_CORRECT  = 0;
const unsigned int START_MESSAGE_CORRECT = 1;
const unsigned int END_MESSAGE_CORRECT   = 2;
const unsigned int DEATH_NODE_CORRECT    = 3;
const unsigned int START_NODE_CORRECT    = 4;
const unsigned int VICTORY_NODE_CORRECT  = 5;
const unsigned int FIRST_ORDINARY_NODE   = 6;

const int VALID_CHECK_SPACING = 3;
const int VALID_START         = VALID_CHECK_SPACING - 1;
const int VALID_CELL_COUNT    = (ROW_COUNT_CORRECT    / VALID_CHECK_SPACING) *
                                (COLUMN_COUNT_CORRECT / VALID_CHECK_SPACING);
const int INVALID_CHECK_BORDER = 2;
const int INVALID_START        = VALID_START - VALID_CHECK_SPACING * 2;
const int INVALID_ROW_END      = ROW_COUNT_CORRECT    + VALID_CHECK_SPACING * 2;
const int INVALID_COLUMN_END   = COLUMN_COUNT_CORRECT + VALID_CHECK_SPACING * 2;
const int INVALID_CELL_COUNT   = ((ROW_COUNT_CORRECT    / VALID_CHECK_SPACING + INVALID_CHECK_BORDER * 2) *
                                  (COLUMN_COUNT_CORRECT / VALID_CHECK_SPACING + INVALID_CHECK_BORDER * 2)) -
                                 VALID_CELL_COUNT;

const unsigned int TEST_DIRECTION_NODE_COUNT = 4;
const unsigned int A_TEST_DIRECTION_NODE_ROW[TEST_DIRECTION_NODE_COUNT] =
{
	0,
	ROW_COUNT_CORRECT / 2,
	ROW_COUNT_CORRECT - 1,
	ROW_COUNT_CORRECT / 2,
};
const unsigned int A_TEST_DIRECTION_NODE_COLUMN[TEST_DIRECTION_NODE_COUNT] =
{
	COLUMN_COUNT_CORRECT / 2,
	0,
	COLUMN_COUNT_CORRECT / 2,
	COLUMN_COUNT_CORRECT - 1,
};

const unsigned int UNINITIALIZED_NODE_VALUE = 999;

const int START_ROW_CORRECT    = 4;
const int START_COLUMN_CORRECT = 1;

const int NODE_14_ROW_CORRECT    = 1;
const int NODE_14_COLUMN_CORRECT = 5;



int main ()
{
	testHelperStartup("TestWorld1B", COMPILE_AND_START_MARKS, TOTAL_MARKS);

	World world;


	//
	//  Test isValid function
	//

	cout << "Testing if nodes inside the world are valid" << endl;
	unsigned int valid_inside_correct = 0;
	bool is_first_invalid = true;
	for(int r = VALID_CHECK_SPACING - 1; r < ROW_COUNT_CORRECT; r += VALID_CHECK_SPACING)
		for(int c = VALID_CHECK_SPACING - 1; c < COLUMN_COUNT_CORRECT; c += VALID_CHECK_SPACING)
		{
			bool is_valid = worldIsValid(world, r, c);
			if(is_valid)
				valid_inside_correct++;
			else if(is_first_invalid)
			{
				cout << "* Incorrect: Cell (" << r << ", " << c << ") not is valid but should be" << endl;
				is_first_invalid = false;
			}
		}
	if(valid_inside_correct == VALID_CELL_COUNT)
		cout << "* Correct" << endl;
	cout << endl;

	cout << "Testing if nodes outside the world are invalid" << endl;
	unsigned int valid_outside_correct = 0;
	bool is_first_valid = true;
	for(int r = INVALID_START; r < INVALID_ROW_END; r += VALID_CHECK_SPACING)
		for(int c = INVALID_START; c < INVALID_COLUMN_END; c += VALID_CHECK_SPACING)
		{
			if(r >= 0 && r < ROW_COUNT_CORRECT)
				if(c >= 0 && c < COLUMN_COUNT_CORRECT)
					continue;  // already checked above

			bool is_valid = worldIsValid(world, r, c);
			if(!is_valid)
				valid_outside_correct++;
			else if(is_first_valid)
			{
				cout << "* Incorrect: Cell (" << r << ", " << c << ") is valid but should not be" << endl;
				is_first_valid = false;
			}
		}
	if(valid_outside_correct == INVALID_CELL_COUNT)
		cout << "* Correct" << endl;
	cout << endl;


	//
	//  Test single-node queries
	//

	assert(2 <  ROW_COUNT_CORRECT);
	assert(7 <= COLUMN_COUNT_CORRECT);
	for(int c = 0; c < 7; c++)
		world[2][c] = c;

	cout << "Testing worldIsDeath" << endl;
	bool is_death_correct   = true;
	for(int c = 0; c < 7; c++)
	{
		bool should_be_death = c == DEATH_NODE_CORRECT;
		if(worldIsDeath(world, 2, c) != should_be_death)
		{
			if(is_death_correct)  // first time obly
			{
				if(should_be_death)
					cout << "* Incorrect: Node value " << c << " reported as death node, shouldn't be" << endl;
				else
					cout << "* Incorrect: Node value " << c << " not reported as death node, should be" << endl;
			}
			is_death_correct = false;
		}
	}
	if(is_death_correct)
		cout << "* Correct" << endl;
	cout << endl;

	cout << "Testing worldIsVictory" << endl;
	bool is_victory_correct = true;
	for(int c = 0; c < 7; c++)
	{
		bool should_be_victory = c == VICTORY_NODE_CORRECT;
		if(worldIsVictory(world, 2, c) != should_be_victory)
		{
			if(is_victory_correct)  // first time obly
			{
				if(should_be_victory)
					cout << "* Incorrect: Node value " << c << " reported as victory node, shouldn't be" << endl;
				else
					cout << "* Incorrect: Node value " << c << " not reported as victory node, should be" << endl;
			}
			is_victory_correct = false;
		}
	}
	if(is_victory_correct)
		cout << "* Correct" << endl;
	cout << endl;


	//
	//  Test direction queries
	//

	for(int i = 0; i < TEST_DIRECTION_NODE_COUNT; i++)
	{
		// add open node to test
		int node_r = A_TEST_DIRECTION_NODE_ROW   [i];
		int node_c = A_TEST_DIRECTION_NODE_COLUMN[i];
		world[node_r][node_c] = FIRST_ORDINARY_NODE + i;

		// set neighbours, 1 skipped (off map), 1 open
		if(i != 0)
			world[node_r - 1][node_c] = (i == 2) ? FIRST_ORDINARY_NODE + 4 : INACCESSIBLE_CORRECT;
		if(i != 1)
			world[node_r][node_c - 1] = (i == 3) ? FIRST_ORDINARY_NODE + 5 : INACCESSIBLE_CORRECT;
		if(i != 2)
			world[node_r + 1][node_c] = (i == 0) ? FIRST_ORDINARY_NODE + 6 : INACCESSIBLE_CORRECT;
		if(i != 3)
			world[node_r][node_c + 1] = (i == 1) ? FIRST_ORDINARY_NODE + 7 : INACCESSIBLE_CORRECT;
	}

	cout << "Testing worldCanGoNorth" << endl;
	bool is_north_correct = testCanGoDirection(world, 0, &worldCanGoNorth);
	cout << endl;

	cout << "Testing worldCanGoSouth" << endl;
	bool is_south_correct = testCanGoDirection(world, 2, &worldCanGoSouth);
	cout << endl;

	cout << "Testing worldCanGoEast" << endl;
	bool is_east_correct = testCanGoDirection(world, 3, &worldCanGoEast);
	cout << endl;

	cout << "Testing worldCanGoWest" << endl;
	bool is_west_correct = testCanGoDirection(world, 1, &worldCanGoWest);
	cout << endl;


	//
	//  Test whole-world operations
	//

	cout << "Testing worldClear" << endl;
	fillWorld(world, UNINITIALIZED_NODE_VALUE);
	worldClear(world);
	cout << "* Completed without crashing" << endl;
	double clear_fraction_correct = getWorldFractionInaccessible(world);
	cout << endl;

	cout << "Testing worldLoadNodes" << endl;
	fillWorld(world, UNINITIALIZED_NODE_VALUE);
	worldLoadNodes(world, "blizzard_grid.txt");
	cout << "* Completed without crashing" << endl;
	double load_nodes_fraction_correct = getWorldFractionMatchingBlizzard(world);
	cout << endl;

	cout << "Testing worldLoadAll" << endl;
	fillWorld(world, UNINITIALIZED_NODE_VALUE);
	worldLoadAll(world, "blizzard");
	cout << "* Completed without crashing" << endl;
	double load_all_fraction_correct = getWorldFractionMatchingBlizzard(world);
	cout << endl;

	cout << "Testing worldFindValue (1)" << endl;
	bool find_start_correct = testFindNode(world, START_NODE_CORRECT, "Start node",
	                                       START_ROW_CORRECT, START_COLUMN_CORRECT);
	cout << endl;

	cout << "Testing worldFindValue (2)" << endl;
	bool find_node_14_correct = testFindNode(world, 14, "Node 14",
	                                         NODE_14_ROW_CORRECT, NODE_14_COLUMN_CORRECT);
	cout << endl;


	//
	//  Test display
	//

	cout << "Printing world" << endl;
	cout << "------------------------------------------------------------------" << endl;
	testHelperStartCapture();
	worldDebugPrint(world);
	string captured = testHelperEndCapture();
	cout << "------------------------------------------------------------------" << endl;
	double debug_print_fraction_correct = testDebugPrint(captured);
	cout << endl;


	//
	//  Print results
	//

	double valid_inside_fraction_correct  = (double)(valid_inside_correct ) / (double)(  VALID_CELL_COUNT);
	double valid_outside_fraction_correct = (double)(valid_outside_correct) / (double)(INVALID_CELL_COUNT);

	testHelperPrintSummaryHeader(24, 1, DID_NOT_CRASH_RUNNING_MARKS);
	testHelperPrintSummaryLine("worldIsValid (inside)",  valid_inside_fraction_correct);
	testHelperPrintSummaryLine("worldIsValid (outside)", valid_outside_fraction_correct);
	testHelperPrintSummaryLine("worldIsDeath",           is_death_correct);
	testHelperPrintSummaryLine("worldIsVictory",         is_victory_correct);
	testHelperPrintSummaryLine("worldCanGoNorth",        is_north_correct);
	testHelperPrintSummaryLine("worldCanGoSouth",        is_south_correct);
	testHelperPrintSummaryLine("worldCanGoEast",         is_east_correct);
	testHelperPrintSummaryLine("worldCanGoWest",         is_west_correct);
	testHelperPrintSummaryLine("worldClear",             clear_fraction_correct);
	testHelperPrintSummaryLine("worldLoadNodes",         load_nodes_fraction_correct);
	testHelperPrintSummaryLine("worldLoadAll",           load_all_fraction_correct);
	testHelperPrintSummaryLine("worldFindValue (1)",     find_start_correct);
	testHelperPrintSummaryLine("worldFindValue (2)",     find_node_14_correct);
	testHelperPrintSummaryLine("worldDebugPrint",        debug_print_fraction_correct);

	unsigned int mark = COMPILE_AND_NOT_CRASH_MARKS;

	mark += (int)(valid_inside_fraction_correct * valid_outside_fraction_correct * 2);
	if(is_death_correct && is_victory_correct)
		mark += 1;
	if(is_north_correct)
		mark += 1;
	if(is_south_correct)
		mark += 1;
	if(is_east_correct)
		mark += 1;
	if(is_west_correct)
		mark += 1;
	mark += (int)(clear_fraction_correct * 2);
	if(load_nodes_fraction_correct > 0.0)
		mark += 3;
	mark += (int)(load_nodes_fraction_correct * 6);
	if(load_all_fraction_correct == 1.0)
		mark += 1;
	if(find_start_correct && find_node_14_correct)
		mark += 2;
	mark += (int)(debug_print_fraction_correct * 2);

	assert(mark <= TOTAL_MARKS);
	testHelperPrintMark(mark, TOTAL_MARKS);

	testHelperWaitForEnter();
	return 0;
}

bool testCanGoDirection (const World& world, unsigned int array_offset,
                         pfCanGoDirectionFunction pf_function)
{
	bool is_correct = true;

	for(unsigned int i = 0; i < TEST_DIRECTION_NODE_COUNT; i++)
	{
		unsigned int i2 = (i + array_offset) % TEST_DIRECTION_NODE_COUNT;
		int node_r = A_TEST_DIRECTION_NODE_ROW   [i2];
		int node_c = A_TEST_DIRECTION_NODE_COLUMN[i2];

		bool should_be_open = i == 2;
		if(pf_function(world, node_r, node_c) != should_be_open)
		{
			if(is_correct)  // first time obly
			{
				if(i == 0)
					cout << "* Incorrect: Returns true for going off map edge" << endl;
				else if(i == 2)
					cout << "* Incorrect: Returns false for entering open node" << endl;
				else
					cout << "* Incorrect: Returns true for going to inaccessible node" << endl;
			}
			is_correct = false;
		}
	}
	if(is_correct)
		cout << "* Correct" << endl;

	return is_correct;
}

void fillWorld (World& r_world, unsigned int node_value)
{
	for(int r = 0; r < ROW_COUNT_CORRECT; r++)
		for(int c = 0; c < COLUMN_COUNT_CORRECT; c++)
			r_world[r][c] = node_value;
}

double getWorldFractionInaccessible (const World& world)
{
	unsigned int inaccessible_count = 0;
	bool is_no_errors = true;

	for(int r = 0; r < ROW_COUNT_CORRECT; r++)
		for(int c = 0; c < COLUMN_COUNT_CORRECT; c++)
		{
			if(world[r][c] == INACCESSIBLE_CORRECT)
				inaccessible_count++;
			else if(is_no_errors)
			{
				cout << "* Incorrect: Cell (" << r << ", " << c << ") was not set to INACCESSIBLE" << endl;
				is_no_errors = false;
			}
		}
	if(is_no_errors)
		cout << "* Correct" << endl;

	return (double)(inaccessible_count) / (double)(ROW_COUNT_CORRECT * COLUMN_COUNT_CORRECT);
}

double getWorldFractionMatchingBlizzard (const World& world)
{
	unsigned int inaccessible_count = 0;
	bool is_no_errors = true;

	for(int r = 0; r < ROW_COUNT_CORRECT; r++)
		for(int c = 0; c < COLUMN_COUNT_CORRECT; c++)
		{
			if(world[r][c] == AA_BLIZARD_CORRECT[r][c])
				inaccessible_count++;
			else if(is_no_errors)
			{
				cout << "* Incorrect: Cell (" << r << ", " << c << ") had value " << world[r][c];
				if(world[r][c] == UNINITIALIZED_NODE_VALUE)
					cout << " (\"not loaded\")";
				cout << ", should be " << AA_BLIZARD_CORRECT[r][c] << endl;
				is_no_errors = false;
			}
		}
	if(is_no_errors)
		cout << "* Correct" << endl;

	return (double)(inaccessible_count) / (double)(ROW_COUNT_CORRECT * COLUMN_COUNT_CORRECT);
}

bool testFindNode (const World& world,
                   unsigned int node_value, const string& node_name,
                   int desired_row, int desired_column)
{
	int row_found    = 999999;
	int column_found = 999999;
	worldFindValue(world, row_found, column_found, node_value);
	bool correct_row    = row_found    == desired_row;
	bool correct_column = column_found == desired_column;
	if(!correct_row)
	{
		if(!correct_column)
		{
			cout << "* Incorrect: " << node_name << " at (" << row_found << ", " << column_found
			     << "), should be (" << desired_row << ", " << desired_column << ")" << endl;
		}
		else
			cout << "* Incorrect: " << node_name << " found at row " << row_found << ", should be " << desired_row << endl;
	}
	else
	{
		if(!correct_column)
			cout << "* Incorrect: " << node_name << " found at column " << column_found << ", should be " << desired_column << endl;
		else
			cout << "* Correct" << endl;
	}

	return correct_row && correct_column;
}

double testDebugPrint (const string& printed)
{
	vector<string> lines = testHelperSplitWithoutEmpty(printed, '\n');
	if(lines.size() != ROW_COUNT_CORRECT)
	{
		cout << "* Incorrect: Printed " << lines.size() << " rows, should be " << ROW_COUNT_CORRECT << endl;
		return 0.0;
	}

	vector<vector<string> > node_as_strings;
	node_as_strings.resize(ROW_COUNT_CORRECT);
	for(int r = 0; r < ROW_COUNT_CORRECT; r++)
	{
		node_as_strings[r] = testHelperSplitWithoutEmpty(lines[r], '\t');
		if(node_as_strings[r].size() != COLUMN_COUNT_CORRECT)
		{
			cout << "* Incorrect: Printed " << node_as_strings[r].size()
			     << " values for row " << r << ", should be " << COLUMN_COUNT_CORRECT << endl;
			return 0.0;
		}
	}

	unsigned int cant_parse_count    = 0;
	unsigned int wrong_value_count   = 0;
	unsigned int print_correct_count = 0;

	vector<vector<unsigned int> > node_values;
	node_values.resize(ROW_COUNT_CORRECT);
	for(int r = 0; r < ROW_COUNT_CORRECT; r++)
		for(int c = 0; c < COLUMN_COUNT_CORRECT; c++)
		{
			node_values[r].resize(COLUMN_COUNT_CORRECT);
			stringstream ss(node_as_strings[r][c]);
			ss >> node_values[r][c];
			if(ss.bad())
			{
				if(cant_parse_count == 0)
				{
					cout << "* Incorrect: Printed \"" << node_as_strings[r][c] << "\" at ("
						 << r << ", " << c << "), which is not a node value" << endl;
				}
				cant_parse_count++;
			}
			else if(node_values[r][c] != AA_BLIZARD_CORRECT[r][c])
			{
				if(wrong_value_count == 0)
				{
					cout << "* Incorrect: Printed " << node_values[r][c] << " at ("
						 << r << ", " << c << "), should be " << AA_BLIZARD_CORRECT[r][c] << endl;
				}
				wrong_value_count++;
			}
			else
				print_correct_count++;
		}

	if(print_correct_count == NODE_COUNT_CORRECT)
		cout << "* Correct" << endl;
	else
	{
		if(cant_parse_count > 2)
			cout << "* " << (cant_parse_count - 1) << " more were not integers" << endl;
		if(cant_parse_count == 2)
			cout << "* " << (cant_parse_count - 1) << " more was not an integer" << endl;

		if(wrong_value_count > 2)
			cout << "* " << (wrong_value_count - 1) << " more incorrect node values" << endl;
		if(wrong_value_count == 2)
			cout << "* " << (wrong_value_count - 1) << " more incorrect node value" << endl;
	}

	return (double)(print_correct_count) / (double)(NODE_COUNT_CORRECT);
}
