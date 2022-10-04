//
//  TestLocation3.cpp
//
//  A test program for the Location module.
//
//  This program is to be used with Assignment 3: Part A for
//    CS115, 202210.
//
//  Do not modify this file.
//

#include "Location.h"
#include "Location.h"  // repeated to test for #include errors

#include <cassert>
#include <cctype>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <typeinfo>  // for typeid

#include "TestHelper.h"

using namespace std;
namespace
{
	struct Result
	{
		bool is_row_correct;
		bool is_column_correct;
	};

}



int main ();
Result checkLocation (const Location& location,
                      int correct_row, int correct_column,
                      bool is_print_incorrect);
bool checkPrinted (const string& printed,
                   int correct_row, int correct_column,
                   bool is_print_incorrect);

const int COMPILE_AND_START_MARKS     = 3;
const int DID_NOT_CRASH_RUNNING_MARKS = 2;
const int COMPILE_AND_NOT_CRASH_MARKS = COMPILE_AND_START_MARKS + DID_NOT_CRASH_RUNNING_MARKS;
const int COMBINED_TEST_MARKS         = 10;
const int TOTAL_MARKS                 = COMPILE_AND_NOT_CRASH_MARKS + COMBINED_TEST_MARKS;

const int UNSET_ROW    = 999;
const int UNSET_COLUMN = 999;

const int DEFAULT_ROW_CORRECT    = 0;
const int DEFAULT_COLUMN_CORRECT = 0;

const unsigned int TEST_COUNT = 10;
const int A_TEST_ROWS[TEST_COUNT] =
{	0,	1,	6,	7,	0,	11,	-1,	5,	0,	-68,	};
const int A_TEST_COLUMNS[TEST_COUNT] =
{	0,	2,	3,	0,	8,	47,	4,	-1,	-9,	-86,	};



int main ()
{
	testHelperStartup("TestLocation3", COMPILE_AND_START_MARKS, TOTAL_MARKS);

	//
	//  Test Location class
	//

	cout << "Checking Location size in bytes" << endl;
	size_t location_bytes         = sizeof(Location);
	size_t location_bytes_correct = sizeof(int) * 2;
	bool correct_location_bytes = false;
	if(location_bytes < location_bytes_correct)
		cout << "* Incorrect: Location should contain a row and a column" << endl;
	else if(location_bytes > location_bytes_correct)
		cout << "* Incorrect: Location contains unnecessary data data" << endl;
	else
	{
		cout << "* Correct" << endl;
		correct_location_bytes = true;
	}
	cout << endl;

	cout << "Creating Location" << endl;
	Location* p_location = new Location;
	cout << "* Completed without crashing" << endl;
	cout << endl;

	cout << "Destroyed Location" << endl;
	delete p_location;
	cout << "* Completed without crashing" << endl;
	cout << endl;


	//
	//  Test constructors
	//

	cout << "Testing default constructor" << endl;
	Location location_default;
	location_default.row    = UNSET_ROW;
	location_default.column = UNSET_COLUMN;
	location_default = Location();
	Result result_default = checkLocation(location_default, DEFAULT_ROW_CORRECT, DEFAULT_COLUMN_CORRECT, true);
	if(result_default.is_row_correct &&
	   result_default.is_column_correct)
	{
		cout << "* Correct" << endl;
	}
	cout << endl;

	cout << "Testing initializing constructor" << endl;
	Location location_init[TEST_COUNT];
	Result   result_init  [TEST_COUNT];
	unsigned int init_incorrect_count = 0;
	for(unsigned int i = 0; i < TEST_COUNT; i++)
	{
		location_init[i].row    = UNSET_ROW;
		location_init[i].column = UNSET_COLUMN;
		location_init[i] = Location(A_TEST_ROWS[i], A_TEST_COLUMNS[i]);

		bool is_print_incorrect = init_incorrect_count == 0;
		result_init[i] = checkLocation(location_init[i], A_TEST_ROWS[i], A_TEST_COLUMNS[i], is_print_incorrect);
		if(!result_init[i].is_row_correct ||
		   !result_init[i].is_column_correct)
		{
			init_incorrect_count++;
		}
	}
	if(init_incorrect_count == 0)
		cout << "* Correct" << endl;
	else if(init_incorrect_count > 0)
		cout << "* " << (init_incorrect_count - 1) << " more initialized incorrectly" << endl;
	cout << endl;


	//
	//  Test operator==
	//

	cout << "Testing that equality test operator (operator==)" << endl;
	unsigned int   equal_incorrect_count = 0;
	unsigned int unequal_incorrect_count = 0;
	for(unsigned int i = 0; i < TEST_COUNT; i++)
		for(unsigned int j = 0; j < TEST_COUNT; j++)
		{
			if(location_init[i] == location_init[j])
			{
				if(i != j)
				{
					if(unequal_incorrect_count == 0)
					{
						bool is_row_equal    = location_init[i].row    == location_init[j].row;
						bool is_column_equal = location_init[i].column == location_init[j].column;
						if(!is_row_equal)
						{
							cout << "* Incorrect: Rows " << location_init[i].row << " and "
								 << location_init[j].row << " report as equal but aren't" << endl;
						}
						else
						{
							assert(!is_column_equal);
							cout << "* Incorrect: Columns " << location_init[i].column << " and "
								 << location_init[j].column << " report as equal but aren't" << endl;
						}
					}
					unequal_incorrect_count++;
				}
			}
			else
			{
				if(i == j)
				{
					if(equal_incorrect_count == 0)
					{
						cout << "* Incorrect: Locations ("
						     << location_init[i].row    << ", "
						     << location_init[i].column << ") and ("
						     << location_init[j].row    << ", "
						     << location_init[j].column << ") should report as equal" << endl;
					}
					equal_incorrect_count++;
				}
			}
		}
	if(unequal_incorrect_count == 0 && equal_incorrect_count == 0)
		cout << "* Correct" << endl;
	if(unequal_incorrect_count > 1)
		cout << "* " << (unequal_incorrect_count - 1) << " more incorrectly reported as equal" << endl;
	if(equal_incorrect_count > 1)
		cout << "* " << (equal_incorrect_count - 1) << " more incorrectly reported as unequal" << endl;
	cout << endl;


	//
	//  Test printing
	//

	cout << "Testing stream insertion operator (operator<<)" << endl;
	cout << "    " << setw(28) << left << "Correct Output" << "Printed Output" << endl;
	cout << "    " << setw(28) << left << "--------------" << "--------------" << endl;
	unsigned int correct_print = 0;
	for(unsigned int i = 0; i < TEST_COUNT; i++)
	{
		stringstream ss;
		ss << "(row = " << A_TEST_ROWS[i] << ", column = " << A_TEST_COLUMNS[i] << ")";
		cout << "    " << setw(28) << left << ss.str();
		testHelperStartCapture();
		cout << location_init[i];
		string captured = testHelperEndCapture();
		cout << endl;

		bool is_all_good_so_far = correct_print == i;
		if(checkPrinted(captured, A_TEST_ROWS[i], A_TEST_COLUMNS[i], is_all_good_so_far))
			correct_print++;
	}
	if(correct_print == TEST_COUNT)
		cout << "* Correct" << endl;
	else if(correct_print < TEST_COUNT - 1)
		cout << "* " << (TEST_COUNT - 1 - correct_print) << " more printed incorrectly" << endl;
	cout << endl;


	//
	//  Print results
	//

	unsigned int default_correct = (result_default.is_row_correct    ? 1 : 0) +
	                               (result_default.is_column_correct ? 1 : 0);

	unsigned int init_correct = 0;
	for(unsigned int i = 0; i < TEST_COUNT; i++)
	{
		if(result_init[i].is_row_correct)
			init_correct++;
		if(result_init[i].is_column_correct)
			init_correct++;
	}
	double correct_init_fraction = (double)(init_correct) / (TEST_COUNT * 2);

	unsigned int   equal_count = TEST_COUNT;
	unsigned int unequal_count = TEST_COUNT * TEST_COUNT - TEST_COUNT;
	double correct_equal_fraction   = (double)(  equal_count -   equal_incorrect_count) / equal_count;
	double correct_unequal_fraction = (double)(unequal_count - unequal_incorrect_count) / unequal_count;
	double correct_print_fraction   = (double)(correct_print) / TEST_COUNT;

	testHelperPrintSummaryHeader(26, 2, DID_NOT_CRASH_RUNNING_MARKS);
	testHelperPrintSummaryLine("Location declaration",    correct_location_bytes);
	testHelperPrintSummaryLine("Default constructor",     default_correct,              2);
	testHelperPrintSummaryLine("Initalizing constructor", init_correct,    TEST_COUNT * 2);
	testHelperPrintSummaryLine("Equality test (true)",    correct_equal_fraction);
	testHelperPrintSummaryLine("Equality test (false)",   correct_unequal_fraction);
	testHelperPrintSummaryLine("Stream output (<<)",      correct_print_fraction);

	unsigned int mark = COMPILE_AND_NOT_CRASH_MARKS;

	if(correct_location_bytes)
		mark += 1;
	if(default_correct == 2)
		mark += 1;
	mark += (int)(correct_init_fraction * 3);
	if(correct_equal_fraction == 1.0)
		mark += 1;
	if(correct_unequal_fraction == 1.0)
		mark += 1;
	mark += (int)(correct_print_fraction * 3);

	assert(mark <= TOTAL_MARKS);
	testHelperPrintMark(mark, TOTAL_MARKS);

	testHelperWaitForEnter();
	return 0;
}

Result checkLocation (const Location& location,
                      int correct_row, int correct_column,
                      bool is_print_incorrect)
{
	Result result;
	result.is_row_correct    = location.row    == correct_row;
	result.is_column_correct = location.column == correct_column;

	if(is_print_incorrect)
	{
		if(location.row    != location.column &&
		   location.row    == correct_column  &&
		   location.column == correct_row)
		{
			cout << "* Incorrect: row field was set to column value and vice versa" << endl;
			return result;
		}
		if(!result.is_row_correct)
		{
			if(location.row == correct_column)
				cout << "* Incorrect: row field was set to column value" << endl;
			else if(location.row == UNSET_ROW)
				cout << "* Incorrect: row field was not set (value " << UNSET_ROW << ")" << endl;
			else
				cout << "* Incorrect: row field was set to " << location.row << ", should be " << correct_row << endl;
		}
		if(!result.is_column_correct)
		{
			if(location.column == correct_row)
				cout << "* Incorrect: column field was set to row value" << endl;
			else if(location.column == UNSET_COLUMN)
				cout << "* Incorrect: column field was not set (value " << UNSET_COLUMN << ")" << endl;
			else
				cout << "* Incorrect: column field was set to " << location.column << ", should be " << correct_column << endl;
		}
	}

	return result;
}

// an adapted form exists in TestItem3
bool checkPrinted (const string& printed,
                   int correct_row, int correct_column,
                   bool is_print_incorrect)
{
	string lowercase = printed;
	for(unsigned int i = 0; i < lowercase.size(); i++)
		lowercase[i] = tolower(lowercase[i]);

	if(lowercase.empty())
	{
		if(is_print_incorrect)
			cout << "* Incorrect: Printed nothing" << endl;
		return false;
	}

	bool front_parenthesis = lowercase.front() == '(';
	bool  back_parenthesis = lowercase.back () == ')';
	if(!front_parenthesis && !back_parenthesis)
	{
		if(is_print_incorrect)
			cout << "* Incorrect: Should print parentheses around location" << endl;
		return false;
	}
	if(!front_parenthesis)
	{
		if(is_print_incorrect)
			cout << "* Incorrect: Missing opening parenthesis" << endl;
		return false;
	}
	if(!back_parenthesis)
	{
		if(is_print_incorrect)
			cout << "* Incorrect: Missing closing parenthesis" << endl;
		return false;
	}

	assert(lowercase.length() >= 2);
	string without_parentheses = lowercase.substr(1, lowercase.length() - 2);
	vector<string> split_around_comma = testHelperSplitWithoutEmpty(without_parentheses, ',');
	switch(split_around_comma.size())
	{
	case 0:
		if(is_print_incorrect)
			cout << "* Incorrect: Nothing between parentheses" << endl;
		return false;
	case 1:
		if(is_print_incorrect)
			cout << "* Incorrect: Missing a comma between parentheses" << endl;
		return false;
	case 2:
		// everything is good so far
		break;
	default:
		if(is_print_incorrect)
			cout << "* Incorrect: Too many commas between parentheses" << endl;
		return false;
	}
	assert(split_around_comma.size() == 2);

	vector<string> row_tokens = testHelperSplitWithoutEmpty(split_around_comma[0], ' ');
	switch(row_tokens.size())
	{
	case 0:
		if(is_print_incorrect)
			cout << "* Incorrect: Nothing for row term" << endl;
		return false;
	case 1:
		if(is_print_incorrect)
			cout << "* Incorrect: No spaces for row term" << endl;
		return false;
	case 2:
		if(is_print_incorrect)
			cout << "* Incorrect: Should be spaces on either side of '=' for row term" << endl;
		return false;
	case 3:
		// everything is good so far
		break;
	default:
		if(is_print_incorrect)
			cout << "* Incorrect: Too many spaces for row term" << endl;
		return false;
	}
	assert(row_tokens.size() == 3);

	if(row_tokens[0] != "row")
	{
		if(is_print_incorrect)
			cout << "* Incorrect: Row term should start with \"row = \"" << endl;
		return false;
	}

	if(row_tokens[1] != "=")
	{
		if(is_print_incorrect)
			cout << "* Incorrect: Missing \"=\" for row term" << endl;
		return false;
	}

	vector<string> column_tokens = testHelperSplitWithoutEmpty(split_around_comma[1], ' ');
	switch(column_tokens.size())
	{
	case 0:
		if(is_print_incorrect)
			cout << "* Incorrect: Nothing for column term" << endl;
		return false;
	case 1:
		if(is_print_incorrect)
			cout << "* Incorrect: No spaces for column term" << endl;
		return false;
	case 2:
		if(is_print_incorrect)
			cout << "* Incorrect: Should be spaces on either side of '=' for column term" << endl;
		return false;
	case 3:
		// everything is good so far
		break;
	default:
		if(is_print_incorrect)
			cout << "* Incorrect: Too many spaces for column term" << endl;
		return false;
	}
	assert(column_tokens.size() == 3);

	if(column_tokens[0] != "column")
	{
		if(is_print_incorrect)
			cout << "* Incorrect: Column term should start with \"column = \"" << endl;
		return false;
	}

	if(column_tokens[1] != "=")
	{
		if(is_print_incorrect)
			cout << "* Incorrect: Missing \"=\" for column term" << endl;
		return false;
	}

	stringstream ss_row(row_tokens[2]);
	int printed_row;
	ss_row >> printed_row;

	stringstream ss_column(column_tokens[2]);
	int printed_column;
	ss_column >> printed_column;

	if(printed_row != printed_column &&
	   printed_row == correct_column &&
	   correct_row == printed_column)
	{
		if(is_print_incorrect)
			cout << "* Incorrect: Printed row and column in reverse order" << endl;
		return false;
	}

	if(printed_row != correct_row)
	{
		if(is_print_incorrect)
			cout << "* Incorrect: Printed row as " << printed_row << ", should be " << correct_row << endl;
		return false;
	}
	if(printed_column != correct_column)
	{
		if(is_print_incorrect)
			cout << "* Incorrect: Printed column as " << printed_column << ", should be " << correct_column << endl;
		return false;
	}

	return true;
}
