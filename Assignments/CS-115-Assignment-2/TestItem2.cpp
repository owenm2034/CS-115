//
//  TestItem2.cpp
//
//  A test program for the Item module.
//
//  This program is to be used with Assignment 2: Part A for
//    CS115, 202210.
//
//  Do not modify this file.
//
//  2022-01-27: Now more tolerant of spaces in itemDebugPrint
//

#include "Item.h"
#include "Item.h"  // repeated to test for #include errors

#include <cassert>
#include <string>
#include <iostream>
#include <iomanip>
#include <typeinfo>  // for typeid
#include <sstream>
#include <vector>

#include "TestHelper.h"

using namespace std;

const unsigned int TEST_LOCATION_COUNT = 5;
const unsigned int TEST_LOCATION_NONE  = TEST_LOCATION_COUNT;

struct TestResult
{
	bool is_get_id_correct;
	bool is_in_inventory_correct;
	bool is_at_location_correct[TEST_LOCATION_COUNT];
	bool is_get_player_points_correct;
	bool is_description_printed_correct;
};

int main ();

double testDebugPrint (const string& printed,
                       char correct_id_char,
                       int correct_start_row,
                       int correct_start_column,
                       int correct_current_row,
                       int correct_current_column,
                       bool correct_is_in_inventory,
                       int correct_points,
                       const string& correct_world_description,
                       const string& correct_inventory_description);
string trimSpaces (const string& str);
bool isPrintedBoolCorrect   (const string& printed, bool correct,
                             unsigned int line);
bool isPrintedCharCorrect   (const string& printed, char correct,
                             unsigned int line);
bool isPrintedIntCorrect    (const string& printed, int correct,
                             unsigned int line);
bool isPrintedStringCorrect (const string& printed, const string& correct,
                             unsigned int line);

TestResult testItem (const Item& item,
                     char correct_id_char,
                     unsigned int correct_location_index,
                     bool correct_is_in_inventory,
                     int correct_player_points,
                     const string& correct_description);
unsigned int markResults (const TestResult& result);
bool isAllLocationResultsCorrect (const TestResult& result);
TestResult combineResults (const TestResult& result1, const TestResult& result2);

const int COMPILE_AND_START_MARKS     = 9;
const int DID_NOT_CRASH_RUNNING_MARKS = 11;
const int COMPILE_AND_NOT_CRASH_MARKS = COMPILE_AND_START_MARKS + DID_NOT_CRASH_RUNNING_MARKS;
const int COMBINED_TEST_MARKS         = 35;
const int TOTAL_MARKS                 = COMPILE_AND_NOT_CRASH_MARKS + COMBINED_TEST_MARKS;

const char ID_NOT_INITIALIZED_CORRECT = '\0';

const unsigned int OUTPUT_LINE_COUNT_CORRECT = 9;

const int TEST_LOCATION_ROW   [TEST_LOCATION_COUNT] =
{	0,	4,	6,	1,	9,	};
const int TEST_LOCATION_COLUMN[TEST_LOCATION_COUNT] =
{	0,	2,	3,	7,	0,	};

const unsigned int RESULT_MAX_MARK = 5;

const char   APPLE_ID_CHAR               = 'a';
const int    APPLE_START_ROW             = TEST_LOCATION_ROW   [1];
const int    APPLE_START_COLUMN          = TEST_LOCATION_COLUMN[1];
const int    APPLE_POINTS                = 5;
const string APPLE_WORLD_DESCRIPTION     = "There is an apple (a) here.";
const string APPLE_INVENTORY_DESCRIPTION = "You are carrying an apple (a).";

const char   BOAT_ID_CHAR               = 'b';
const int    BOAT_START_ROW             = TEST_LOCATION_ROW   [2];
const int    BOAT_START_COLUMN          = TEST_LOCATION_COLUMN[2];
const int    BOAT_POINTS                = -10;
const string BOAT_WORLD_DESCRIPTION     = "There is a boat (b) here.";
const string BOAT_INVENTORY_DESCRIPTION = "You are in a boat (b).";



int main ()
{
	testHelperStartup("TestItem2", COMPILE_AND_START_MARKS, TOTAL_MARKS);


	//
	//  Test ID_NOT_INITIALIZED constant
	//

	cout << "Testing ID_NOT_INITIALIZED" << endl;
	bool correct_id_not_initialized = testHelperConstant(ID_NOT_INITIALIZED, ID_NOT_INITIALIZED_CORRECT, "ID_NOT_INITIALIZED");
	cout << endl;


	//
	//  Test Item struct
	//

	cout << "Checking Item size in bytes" << endl;
	size_t item_bytes              = sizeof(Item);
	size_t item_bytes_position     = sizeof(int)    * 4;
	size_t item_bytes_descriptions = sizeof(string) * 2;
	size_t item_bytes_correct      = sizeof(char) + sizeof(int) * 5 + sizeof(bool) + sizeof(string) * 2;
	bool correct_item_bytes = false;
	if(item_bytes < item_bytes_position)
		cout << "* Incorrect: Item should contain starting and current positions" << endl;
	else if(item_bytes < item_bytes_descriptions)
		cout << "* Incorrect: Item should contain ground and inventory descriptions" << endl;
	else if(item_bytes >= item_bytes_correct * 2)
		cout << "* Incorrect: Item contains far too much data" << endl;
	else
	{
		cout << "* Correct" << endl;
		correct_item_bytes = true;
	}
	cout << endl;

	cout << "Creating Item" << endl;
	Item* p_item = new Item;
	cout << "* Completed without crashing" << endl;
	cout << endl;

	cout << "Destroyed Item" << endl;
	delete p_item;
	cout << "* Completed without crashing" << endl;
	cout << endl;


	//
	//  Test itemInit and itemDebugPrint functions
	//

	cout << "Creating and initializing an apple ('a') Item" << endl;
	Item apple;
	cout << "* Created without crashing" << endl;
	itemInit(apple, APPLE_ID_CHAR,
	         APPLE_START_ROW, APPLE_START_COLUMN,
	         APPLE_POINTS,
	         APPLE_WORLD_DESCRIPTION, APPLE_INVENTORY_DESCRIPTION);
	cout << "* Initialized without crashing" << endl;
	cout << endl;

	cout << "Printing apple" << endl;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	itemDebugPrint(apple);
	string captured_apple1 = testHelperEndCapture();
	cout << "----------------------------------------------------------------" << endl;
	double print_apple_fraction_correct_1 = testDebugPrint(captured_apple1,
	                                                       APPLE_ID_CHAR,
	                                                       APPLE_START_ROW, APPLE_START_COLUMN,
	                                                       APPLE_START_ROW, APPLE_START_COLUMN,
	                                                       false, APPLE_POINTS,
	                                                       APPLE_WORLD_DESCRIPTION, APPLE_INVENTORY_DESCRIPTION);
	cout << endl;


	//
	//  Test manipulating apple
	//

	static const unsigned int TEST_APPLE_COUNT = 6;
	TestResult result_apple[TEST_APPLE_COUNT];

	cout << "Checking apple state" << endl;
	result_apple[0] = testItem(apple, APPLE_ID_CHAR,
	                           1, false, 0,
	                           APPLE_WORLD_DESCRIPTION);
	cout << endl;

	cout << "Moving apple to inventory" << endl;
	itemMoveToInventory(apple);
	result_apple[1] = testItem(apple, APPLE_ID_CHAR,
	                           TEST_LOCATION_NONE, true, APPLE_POINTS,
	                           APPLE_INVENTORY_DESCRIPTION);
	cout << endl;

	cout << "Moving apple to (" << TEST_LOCATION_ROW[3] << ", " << TEST_LOCATION_COLUMN[3] << ")" << endl;
	itemMoveToLocation(apple, TEST_LOCATION_ROW[3], TEST_LOCATION_COLUMN[3]);
	result_apple[2] = testItem(apple, APPLE_ID_CHAR,
	                           3, false, 0,
	                           APPLE_WORLD_DESCRIPTION);
	cout << endl;

	cout << "Printing apple" << endl;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	itemDebugPrint(apple);
	string captured_apple2 = testHelperEndCapture();
	cout << "----------------------------------------------------------------" << endl;
	double print_apple_fraction_correct_2 = testDebugPrint(captured_apple2,
	                                                       APPLE_ID_CHAR,
	                                                       APPLE_START_ROW, APPLE_START_COLUMN,
	                                                       TEST_LOCATION_ROW[3], TEST_LOCATION_COLUMN[3],
	                                                       false, APPLE_POINTS,
	                                                       APPLE_WORLD_DESCRIPTION, APPLE_INVENTORY_DESCRIPTION);
	cout << endl;

	cout << "Moving apple to (" << TEST_LOCATION_ROW[4] << ", " << TEST_LOCATION_COLUMN[4] << ")" << endl;
	itemMoveToLocation(apple, TEST_LOCATION_ROW[4], TEST_LOCATION_COLUMN[4]);
	result_apple[3] = testItem(apple, APPLE_ID_CHAR,
	                           4, false, 0,
	                           APPLE_WORLD_DESCRIPTION);
	cout << endl;

	cout << "Moving apple to inventory" << endl;
	itemMoveToInventory(apple);
	result_apple[4] = testItem(apple, APPLE_ID_CHAR,
	                           TEST_LOCATION_NONE, true, APPLE_POINTS,
	                           APPLE_INVENTORY_DESCRIPTION);
	cout << endl;

	cout << "Printing apple" << endl;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	itemDebugPrint(apple);
	string captured_apple3 = testHelperEndCapture();
	cout << "----------------------------------------------------------------" << endl;
	double print_apple_fraction_correct_3 = testDebugPrint(captured_apple3,
	                                                       APPLE_ID_CHAR,
	                                                       APPLE_START_ROW, APPLE_START_COLUMN,
	                                                       TEST_LOCATION_ROW[4], TEST_LOCATION_COLUMN[4],
	                                                       true, APPLE_POINTS,
	                                                       APPLE_WORLD_DESCRIPTION, APPLE_INVENTORY_DESCRIPTION);
	cout << endl;

	cout << "Reseting apple to starting location" << endl;
	itemReset(apple);
	result_apple[5] = testItem(apple, APPLE_ID_CHAR,
	                           1, false, 0,
	                           APPLE_WORLD_DESCRIPTION);
	cout << endl;


	//
	//  Test 2 items at once
	//

	cout << "Creating and initializing a boat ('b') Item" << endl;
	Item boat;
	cout << "* Created without crashing" << endl;
	itemInit(boat, BOAT_ID_CHAR,
	         BOAT_START_ROW, BOAT_START_COLUMN,
	         BOAT_POINTS,
	         BOAT_WORLD_DESCRIPTION, BOAT_INVENTORY_DESCRIPTION);
	cout << "* Initialized without crashing" << endl;
	cout << endl;

	cout << "Printing boat" << endl;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	itemDebugPrint(boat);
	string captured_boat1 = testHelperEndCapture();
	cout << "----------------------------------------------------------------" << endl;
	double print_boat_fraction_correct = testDebugPrint(captured_boat1,
	                                                    BOAT_ID_CHAR,
	                                                    BOAT_START_ROW, BOAT_START_COLUMN,
	                                                    BOAT_START_ROW, BOAT_START_COLUMN,
	                                                    false, BOAT_POINTS,
	                                                    BOAT_WORLD_DESCRIPTION, BOAT_INVENTORY_DESCRIPTION);
	cout << endl;


	static const unsigned int TEST_BOTH_COUNT = 3;
	TestResult result_both_apple[TEST_BOTH_COUNT];
	TestResult result_both_boat [TEST_BOTH_COUNT];

	cout << "Checking current states" << endl;
	result_both_boat[0] = testItem(boat, BOAT_ID_CHAR,
	                               2, false, 0,
	                               BOAT_WORLD_DESCRIPTION);
	cout << "Checking apple" << endl;
	result_both_apple[0] = testItem(apple, APPLE_ID_CHAR,
	                                1, false, 0,
	                                APPLE_WORLD_DESCRIPTION);
	cout << endl;

	cout << "Moving boat to (" << TEST_LOCATION_ROW[0] << ", " << TEST_LOCATION_COLUMN[0] << ")" << endl;
	itemMoveToLocation(boat, TEST_LOCATION_ROW[0], TEST_LOCATION_COLUMN[0]);
	result_both_boat[1] = testItem(boat, BOAT_ID_CHAR,
	                               0, false, 0,
	                               BOAT_WORLD_DESCRIPTION);
	cout << "Checking apple" << endl;
	result_both_apple[1] = testItem(apple, APPLE_ID_CHAR,
	                                1, false, 0,
	                                APPLE_WORLD_DESCRIPTION);
	cout << endl;

	cout << "Moving boat to inventory" << endl;
	itemMoveToInventory(boat);
	result_both_boat[2] = testItem(boat, BOAT_ID_CHAR,
	                               TEST_LOCATION_NONE, true, BOAT_POINTS,
	                               BOAT_INVENTORY_DESCRIPTION);
	cout << "Checking apple" << endl;
	result_both_apple[2] = testItem(apple, APPLE_ID_CHAR,
	                                1, false, 0,
	                                APPLE_WORLD_DESCRIPTION);
	cout << endl;


	//
	//  Print results
	//

	double debug_print_highest = print_apple_fraction_correct_1;
	if(debug_print_highest < print_apple_fraction_correct_2)
		debug_print_highest = print_apple_fraction_correct_2;
	if(debug_print_highest < print_apple_fraction_correct_3)
		debug_print_highest = print_apple_fraction_correct_3;
	if(debug_print_highest < print_boat_fraction_correct)
		debug_print_highest = print_boat_fraction_correct;

	unsigned int apple_result_mark[TEST_APPLE_COUNT];
	for(unsigned int i = 0; i < TEST_APPLE_COUNT; i++)
		apple_result_mark[i] = markResults(result_apple[i]);

	TestResult result_both[TEST_BOTH_COUNT];
	unsigned int both_result_mark[TEST_BOTH_COUNT];
	for(unsigned int i = 0; i < TEST_BOTH_COUNT; i++)
	{
		result_both     [i] = combineResults(result_both_apple[i], result_both_boat[i]);
		both_result_mark[i] = markResults(result_both[i]);
	}

	TestResult results_worst = result_apple[0];
	for(unsigned int i = 1; i < TEST_APPLE_COUNT; i++)
		results_worst = combineResults(results_worst, result_apple[i]);
	for(unsigned int i = 0; i < TEST_BOTH_COUNT; i++)
		results_worst = combineResults(results_worst, result_both[i]);

	testHelperPrintSummaryHeader(24, 1, DID_NOT_CRASH_RUNNING_MARKS);
	testHelperPrintSummaryLine("ID_NOT_INITIALIZED",    correct_id_not_initialized);
	testHelperPrintSummaryLine("Item declaration",      correct_item_bytes);
	testHelperPrintSummaryLine("Print apple (1)",       print_apple_fraction_correct_1);
	testHelperPrintSummaryLine("Print apple (2)",       print_apple_fraction_correct_2);
	testHelperPrintSummaryLine("Print apple (3)",       print_apple_fraction_correct_3);
	testHelperPrintSummaryLine("Test apple (at start)", apple_result_mark[0], RESULT_MAX_MARK);
	testHelperPrintSummaryLine("Test apple (1st take)", apple_result_mark[1], RESULT_MAX_MARK);
	testHelperPrintSummaryLine("Test apple (1st move)", apple_result_mark[2], RESULT_MAX_MARK);
	testHelperPrintSummaryLine("Test apple (2nd move)", apple_result_mark[3], RESULT_MAX_MARK);
	testHelperPrintSummaryLine("Test apple (2nd take)", apple_result_mark[4], RESULT_MAX_MARK);
	testHelperPrintSummaryLine("Test apple (reset)",    apple_result_mark[5], RESULT_MAX_MARK);
	testHelperPrintSummaryLine("Print boat",            print_boat_fraction_correct);
	testHelperPrintSummaryLine("Test both (add boat)",  both_result_mark[0], RESULT_MAX_MARK);
	testHelperPrintSummaryLine("Test both (move boat)", both_result_mark[1], RESULT_MAX_MARK);
	testHelperPrintSummaryLine("Test both (take boat)", both_result_mark[2], RESULT_MAX_MARK);

	unsigned int mark = COMPILE_AND_NOT_CRASH_MARKS;

	if(correct_id_not_initialized)
		mark += 1;
	if(correct_item_bytes)
		mark += 3;

	mark += (int)(debug_print_highest * 4);
	mark += (int)(print_apple_fraction_correct_1 * 2);
	mark += (int)(print_apple_fraction_correct_2 * 2);
	mark += (int)(print_apple_fraction_correct_2 * 2);
	mark += (int)(print_boat_fraction_correct    * 2);

	mark += apple_result_mark[0];
	for(unsigned int i = 1; i < TEST_APPLE_COUNT; i++)
		if(apple_result_mark[i] == RESULT_MAX_MARK)
			mark += 1;
	for(unsigned int i = 0; i < TEST_BOTH_COUNT; i++)
		if(both_result_mark[i] == RESULT_MAX_MARK)
			mark += 1;
	if(results_worst.is_get_id_correct)
		mark += 1;
	if(isAllLocationResultsCorrect(results_worst))
		mark += 2;
	if(results_worst.is_in_inventory_correct)
		mark += 1;
	if(results_worst.is_get_player_points_correct)
		mark += 1;
	if(results_worst.is_description_printed_correct)
		mark += 1;

	assert(mark <= TOTAL_MARKS);
	testHelperPrintMark(mark, TOTAL_MARKS);

	testHelperWaitForEnter();
	return 0;
}



double testDebugPrint (const string& printed,
                       char correct_id_char,
                       int correct_start_row,
                       int correct_start_column,
                       int correct_current_row,
                       int correct_current_column,
                       bool correct_is_in_inventory,
                       int correct_points,
                       const string& correct_world_description,
                       const string& correct_inventory_description)
{
	vector<string> lines = testHelperSplitWithoutEmpty(printed, '\n');
	if(lines.size() != OUTPUT_LINE_COUNT_CORRECT)
	{
		cout << "* Incorrect: Printed " << lines.size() << " lines, should be " << OUTPUT_LINE_COUNT_CORRECT << endl;
		return 0.0;
	}

	unsigned int print_correct_count = 0;
	for(unsigned int i = 0; i < OUTPUT_LINE_COUNT_CORRECT; i++)
	{
		vector<string> tokens = testHelperSplitWithoutEmpty(lines[i], '\t');
		if(tokens.size() != 2)
		{
			if(tokens.size() < 2)
				cout << "* Incorrect: Line " << i << " has no tab ('\t')" << endl;
			else
				cout << "* Incorrect: Line " << i << " has multiple tabs ('\t')" << endl;
		}
		else
		{
			tokens[0] = trimSpaces(tokens[0]);

			bool is_field_name_correct = false;
			if(tokens[0].empty())
				cout << "* Incorrect: Line " << i << " has no value name" << endl;
			else if(tokens[0].back() != ':')
				cout << "* Incorrect: Line " << i << " has no colon after the value name" << endl;
			else
				is_field_name_correct = true;

			bool is_field_value_correct = false;
			if(tokens[1].empty())
				cout << "* Incorrect: Line " << i << " has nothing for the field value" << endl;
			else
			{
				tokens[1] = trimSpaces(tokens[1]);

				switch(i)
				{
				case 0:
					is_field_value_correct = isPrintedCharCorrect(tokens[1], correct_id_char, i);
					break;
				case 1:
					is_field_value_correct = isPrintedIntCorrect(tokens[1], correct_start_row, i);
					break;
				case 2:
					is_field_value_correct = isPrintedIntCorrect(tokens[1], correct_start_column, i);
					break;
				case 3:
					if(correct_is_in_inventory)
						is_field_value_correct = true;  // any position is OK if item is in inventory
					else
						is_field_value_correct = isPrintedIntCorrect(tokens[1], correct_current_row, i);
					break;
				case 4:
					if(correct_is_in_inventory)
						is_field_value_correct = true;  // any position is OK if item is in inventory
					else
						is_field_value_correct = isPrintedIntCorrect(tokens[1], correct_current_column, i);
					break;
				case 5:
					is_field_value_correct = isPrintedBoolCorrect(tokens[1], correct_is_in_inventory, i);
					break;
				case 6:
					is_field_value_correct = isPrintedIntCorrect(tokens[1], correct_points, i);
					break;
				case 7:
					is_field_value_correct = isPrintedStringCorrect(tokens[1], correct_world_description, i);
					break;
				case 8:
					is_field_value_correct = isPrintedStringCorrect(tokens[1], correct_inventory_description, i);
					break;
				}
				assert(OUTPUT_LINE_COUNT_CORRECT == 9);
			}

			if(is_field_name_correct && is_field_value_correct)
				print_correct_count++;
		}
	}

	if(print_correct_count == OUTPUT_LINE_COUNT_CORRECT)
		cout << "* Correct" << endl;

	return (double)(print_correct_count) / (double)(OUTPUT_LINE_COUNT_CORRECT);
}

string trimSpaces (const string& str)
{
	if(str.empty())
		return str;

	unsigned int keep_start = 0;
	while(keep_start < str.size() && str[keep_start] == ' ')
		keep_start++;

	unsigned int remove_start = str.size();
	while(remove_start > keep_start && str[remove_start - 1] == ' ')
		remove_start--;

	assert(keep_start <= remove_start);
	return str.substr(keep_start, remove_start - keep_start);
}

bool isPrintedBoolCorrect (const string& printed, bool correct,
                           unsigned int line)
{
	assert(!printed.empty());

	static const string TRUE_STRINGS[] =
	{
		"1",
		"true",
		"True",
		"TRUE",
		"yes",
		"Yes",
		"YES",
	};
	static const unsigned int TRUE_STRING_COUNT = sizeof(TRUE_STRINGS) / sizeof(string);

	static const string FALSE_STRINGS[] =
	{
		"0",
		"false",
		"False",
		"FALSE",
		"no",
		"No",
		"NO",
	};
	static const unsigned int FALSE_STRING_COUNT = sizeof(FALSE_STRINGS) / sizeof(string);

	if(correct == true)
	{
		for(unsigned int i = 0; i < TRUE_STRING_COUNT; i++)
			if(printed == TRUE_STRINGS[i])
				return true;
	}
	else
	{
		assert(correct == false);

		for(unsigned int i = 0; i < FALSE_STRING_COUNT; i++)
			if(printed == FALSE_STRINGS[i])
				return true;
	}
	return false;
}

bool isPrintedCharCorrect (const string& printed, char correct,
                           unsigned int line)
{
	assert(!printed.empty());

	if(printed.size() == 1 && printed[0] == correct)
		cout << "* Incorrect: Line " << line << " char should be surrounded by single quotes" << endl;
	else if(printed.size() < 3)
		cout << "* Incorrect: Line " << line << " needs to print more characters" << endl;
	else if(printed.size() > 3)
		cout << "* Incorrect: Line " << line << " needs to print fewer characters" << endl;
	else
	{
		assert(printed.size() == 3);

		if(printed[0] != '\'' || printed[2] != '\'')
			cout << "* Incorrect: Line " << line << " should be a char surrounded by single quotes" << endl;
		else if(printed[1] != correct)
		{
			cout << "* Incorrect: Line " << line << " prints the char '" << printed[1]
			     << "', should be '" << correct << "'" << endl;
		}
		else
			return true;  // correct char printed in correct format
	}

	return false;
}

bool isPrintedIntCorrect (const string& printed, int correct,
                          unsigned int line)
{
	assert(!printed.empty());

	int printed_as_int;
	stringstream ss(printed);
	ss >> printed_as_int;
	if(ss.bad())
	{
		cout << "* Incorrect: Line " << line << " should print an integer" << endl;
		return false;
	}

	if(printed_as_int != correct)
	{
		cout << "* Incorrect: Line " << line << " printed " << printed_as_int
		     << ", should be " << correct << endl;
		return false;
	}

	return true;
}

bool isPrintedStringCorrect (const string& printed, const string& correct,
                             unsigned int line)
{
	assert(!printed.empty());

	if(printed[0] != '"')
	{
		cout << "* Incorrect: Line " << line << " should start with double quote" << endl;
		return false;
	}

	if(printed[printed.size() - 1] != '"')
	{
		cout << "* Incorrect: Line " << line << " should end with double quote" << endl;
		return false;
	}

	if(printed.size() == 1)
	{
		cout << "* Incorrect: Line " << line << " only prints a single double quote" << endl;
		return false;
	}

	if(printed.size() == 2)
	{
		cout << "* Incorrect: Line " << line << " prints a (quoted) empty string" << endl;
		return false;
	}

	unsigned int quote_count = 0;
	for(unsigned int i = 0; i < printed.size(); i++)
		if(printed[i] == '"')
			quote_count++;

	if(quote_count > 2)
	{
		cout << "* Incorrect: Line " << line << " prints more than 2 double quotes" << endl;
		return false;
	}

	string unquoted = printed.substr(1, printed.size() - 2);
	if(unquoted != correct)
	{
		cout << "* Incorrect: Line " << line << " is:" << endl;
		cout << "    \"" << unquoted << "\"" << endl;
		cout << "  It should be:" << endl;
		cout << "    \"" << correct << "\"" << endl;
		return false;
	}

	return true;
}



TestResult testItem (const Item& item,
                     char correct_id_char,
                     unsigned int correct_location_index,
                     bool correct_is_in_inventory,
                     int correct_player_points,
                     const string& correct_description)
{
	TestResult result;
	result.is_get_id_correct = true;
	for(unsigned int i = 0; i < TEST_LOCATION_COUNT; i++)
		result.is_at_location_correct[i] = true;
	result.is_in_inventory_correct        = true;
	result.is_get_player_points_correct   = true;
	result.is_description_printed_correct = true;

	bool is_all_correct = true;

	char id_char = itemGetId(item);
	if(id_char != correct_id_char)
	{
		cout << "* Incorrect: ID char is '" << id_char << "', should be '" << correct_id_char << "'" << endl;
		result.is_get_id_correct = false;
		is_all_correct = false;
	}

	for(unsigned int i = 0; i < TEST_LOCATION_COUNT; i++)
	{
		bool correct_is_at_location = i == correct_location_index;
		bool is_at_location = itemIsAtLocation(item, TEST_LOCATION_ROW[i], TEST_LOCATION_COLUMN[i]);

		if(is_at_location != correct_is_at_location)
		{
			if(correct_is_in_inventory == true)
			{
				cout << "* Incorrect: Is at location (" << TEST_LOCATION_ROW[i] << ", "
				     << TEST_LOCATION_COLUMN[i] << "), but should be in inventory" << endl;
			}
			else if(is_at_location)
			{
				cout << "* Incorrect: Is at location (" << TEST_LOCATION_ROW[i] << ", "
				     << TEST_LOCATION_COLUMN[i] << "), but shouldn't be" << endl;
			}
			else
			{
				cout << "* Incorrect: Is not at location (" << TEST_LOCATION_ROW[i] << ", "
				     << TEST_LOCATION_COLUMN[i] << "), but should be" << endl;
			}

			result.is_at_location_correct[i] = false;
			is_all_correct = false;
		}
	}

	bool is_in_inventory = itemIsInInventory(item);
	if(is_in_inventory != correct_is_in_inventory)
	{
		if(is_in_inventory)
			cout << "* Incorrect: Is in inventory, but shouldn't be" << endl;
		else
			cout << "* Incorrect: Is not in inventory, but should be" << endl;
		result.is_in_inventory_correct = false;
		is_all_correct = false;
	}

	int player_points = itemGetPlayerPoints(item);
	if(player_points != correct_player_points)
	{
		cout << "* Incorrect: Currently giving the player " << player_points
		     << " points, should be " << correct_player_points << endl;
		result.is_get_player_points_correct = false;
		is_all_correct = false;
	}

	testHelperStartCapture();
	itemPrintDescription(item);
	string captured = testHelperEndCapture(false);
	vector<string> captured_lines = testHelperSplitWithoutEmpty(captured, '\n');
	if(captured_lines.empty())
	{
		cout << "* Incorrect: No description printed" << endl;
		result.is_get_player_points_correct = false;
		is_all_correct = false;
	}
	else if(captured_lines.size() > 1)
	{
		cout << "* Incorrect: Multiple lines of description printed" << endl;
		result.is_get_player_points_correct = false;
		is_all_correct = false;
	}
	else if(captured_lines[0] != correct_description)
	{
		cout << "* Incorrect: Description printed was:" << endl;
		cout << "    \"" << captured_lines[0] << "\"" << endl;
		cout << "  It should be:" << endl;
		cout << "    \"" << correct_description << "\"" << endl;

		result.is_get_player_points_correct = false;
		is_all_correct = false;
	}

	if(is_all_correct)
		cout << "* Correct" << endl;

	return result;
}

unsigned int markResults (const TestResult& result)
{
	unsigned int count = 0;

	if(result.is_get_id_correct)
		count++;
	if(isAllLocationResultsCorrect(result))
		count++;
	if(result.is_in_inventory_correct)
		count++;
	if(result.is_get_player_points_correct)
		count++;
	if(result.is_description_printed_correct)
		count++;
	
	return count;
}

bool isAllLocationResultsCorrect (const TestResult& result)
{
	for(unsigned int i = 0; i < TEST_LOCATION_COUNT; i++)
		if(!result.is_at_location_correct[i])
			return false;
	return true;
}

TestResult combineResults (const TestResult& result1, const TestResult& result2)
{
	TestResult combined;

	combined.is_get_id_correct = result1.is_get_id_correct &&
	                             result2.is_get_id_correct;
	for(unsigned int i = 0; i < TEST_LOCATION_COUNT; i++)
	{
		combined.is_at_location_correct[i] = result1.is_at_location_correct[i] &&
		                                     result2.is_at_location_correct[i];
	}
	combined.is_in_inventory_correct = result1.is_in_inventory_correct &&
	                                   result2.is_in_inventory_correct;
	combined.is_get_player_points_correct = result1.is_get_player_points_correct &&
	                                        result2.is_get_player_points_correct;
	combined.is_description_printed_correct = result1.is_description_printed_correct &&
	                                          result2.is_description_printed_correct;
	
	return combined;
}
