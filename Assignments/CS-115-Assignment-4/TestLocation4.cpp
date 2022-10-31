//
//  TestLocation4.cpp
//
//  A test program for the Location module.
//
//  This program is based on TestLocation3.cpp, although it has
//    been significantly changed.  It now tests node-index-based
//    locations instead of row-and-column-based ones.
//
//  This program is to be used with Assignment 4: Part D for
//    CS115, 202210.
//
//  Do not modify this file.
//
//  2022-03-14: Changed marking scheme: 10 => 5
//
#include "Location.h"
#include "Location.h"  // repeated to test for #include errors

#include <cassert>
#include <cctype>
#include <cstring>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <typeinfo>  // for typeid

#include "TestHelper.h"

using namespace std;



int main ();
void overwriteField (Location& location, unsigned int value);
unsigned int extractField (const Location& location);
bool checkLocation (const Location& location,
                    int correct_node_index,
                    bool is_print_incorrect);
bool checkPrinted (const string& printed,
                   int correct_node_index,
                   bool is_print_incorrect);

// fallback template equality test operator
//   -> will only be called if "const"s in Location::operator== are incorrect
bool is_fallback_equality_test_called = false;
template <typename T>
bool operator== (const T& lhs, const T& rhs)
{
	is_fallback_equality_test_called = true;
	return false;
}

const int COMPILE_AND_START_MARKS     = 1;
const int DID_NOT_CRASH_RUNNING_MARKS = 1;
const int COMPILE_AND_NOT_CRASH_MARKS = COMPILE_AND_START_MARKS + DID_NOT_CRASH_RUNNING_MARKS;
const int COMBINED_TEST_MARKS         = 3;
const int TOTAL_MARKS                 = COMPILE_AND_NOT_CRASH_MARKS + COMBINED_TEST_MARKS;

const unsigned int UNSET_NODE_INDEX           = 999;
const unsigned int DEFAULT_NODE_INDEX_CORRECT =   0;
const unsigned int INACCESSIBLE_NODE_INDEX    =   0;
const string       INACCESSIBLE_PRINT_CORRECT = "INACCESSIBLE";

const unsigned int TEST_COUNT = 10;
const int A_TEST_NODE_INDEXES[TEST_COUNT] =
{	0,	1,	6,	7,	0,	11,	10000,	5,	0,	86,	};

const unsigned int   EQUAL_COUNT_MAX = TEST_COUNT;
const unsigned int UNEQUAL_COUNT_MAX = TEST_COUNT * TEST_COUNT - TEST_COUNT;



int main ()
{
	testHelperStartup("TestLocation4", COMPILE_AND_START_MARKS, TOTAL_MARKS);

	//
	//  Test Location class
	//

	cout << "Checking Location size in bytes" << endl;
	size_t location_bytes         = sizeof(Location);
	size_t location_bytes_correct = sizeof(unsigned int);
	bool correct_location_bytes = false;
	if(location_bytes  == 0)
		cout << "* Incorrect: Location must contain member data" << endl;
	else if(location_bytes < location_bytes_correct)
		cout << "* Incorrect: Location should contain a node index (unsigned int)" << endl;
	else if(location_bytes > location_bytes_correct)
		cout << "* Incorrect: Location contains unnecessary data" << endl;
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

	cout << "Destroying Location" << endl;
	delete p_location;
	p_location = NULL;
	cout << "* Completed without crashing" << endl;
	cout << endl;


	//
	//  Test constructors
	//

	cout << "Testing default constructor" << endl;
	Location location_default;
	overwriteField(location_default, UNSET_NODE_INDEX);
	location_default = Location();
	bool correct_default = checkLocation(location_default, DEFAULT_NODE_INDEX_CORRECT, true);
	if(correct_default)
		cout << "* Correct" << endl;
	cout << endl;

	cout << "Testing initializing constructor" << endl;
	Location location_init[TEST_COUNT];
	bool     correct_init [TEST_COUNT];
	unsigned int init_incorrect_count = 0;
	for(unsigned int i = 0; i < TEST_COUNT; i++)
	{
		overwriteField(location_init[i], UNSET_NODE_INDEX);
		location_init[i] = Location(A_TEST_NODE_INDEXES[i]);

		bool is_print_incorrect = init_incorrect_count == 0;
		correct_init[i] = checkLocation(location_init[i], A_TEST_NODE_INDEXES[i], is_print_incorrect);
		if(!correct_init)
			init_incorrect_count++;
	}
	if(init_incorrect_count == 0)
		cout << "* Correct" << endl;
	else if(init_incorrect_count > 1)
		cout << "* " << (init_incorrect_count - 1) << " more initialized incorrectly" << endl;
	cout << endl;


	//
	//  Test operator==
	//

	cout << "Testing equality test operator (operator==)" << endl;
	bool correct_consts_on_equality_test = true;
	unsigned int   equal_incorrect_count = 0;
	unsigned int unequal_incorrect_count = 0;
	(const Location)(location_init[0]) == (const Location)(location_init[0]);
	if(is_fallback_equality_test_called)
	{
		cout << "* Incorrect: Missing \"const\"s on Location::operator==" << endl;
		correct_consts_on_equality_test = false;
		  equal_incorrect_count =   EQUAL_COUNT_MAX;
		unequal_incorrect_count = UNEQUAL_COUNT_MAX;
	}
	else
	{
		for(unsigned int i = 0; i < TEST_COUNT; i++)
			for(unsigned int j = 0; j < TEST_COUNT; j++)
			{
				if(location_init[i] == location_init[j])
				{
					if(A_TEST_NODE_INDEXES[i] != A_TEST_NODE_INDEXES[j])
					{
						if(unequal_incorrect_count == 0)
						{
							cout << "* Incorrect: Node indexes " << A_TEST_NODE_INDEXES[i] << " and "
								 << A_TEST_NODE_INDEXES[j] << " report as equal but aren't" << endl;
						}
						unequal_incorrect_count++;
					}
				}
				else
				{
					if(A_TEST_NODE_INDEXES[i] == A_TEST_NODE_INDEXES[j])
					{
						if(equal_incorrect_count == 0)
						{
							cout << "* Incorrect: Node indexes " << A_TEST_NODE_INDEXES[i] << " and "
								 << A_TEST_NODE_INDEXES[j] << " should report as equal" << endl;
						}
						equal_incorrect_count++;
					}
				}
			}
		if(unequal_incorrect_count > 1)
		{
			cout << "* " << setw(2) << (unequal_incorrect_count - 1) << " more (of "
			     << setw(2) << UNEQUAL_COUNT_MAX << ") should report as unequal" << endl;
		}
		if(equal_incorrect_count > 1)
		{
			cout << "* " << setw(2) << (equal_incorrect_count - 1) << " more (of "
			     << setw(2) << EQUAL_COUNT_MAX << ") should report as equal" << endl;
		}
	}
	if(unequal_incorrect_count == 0 &&
	   equal_incorrect_count   == 0 &&
	   correct_consts_on_equality_test)
	{
		cout << "* Correct" << endl;
	}
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
		if(A_TEST_NODE_INDEXES[i] == 0)
			ss << "(node = " << INACCESSIBLE_PRINT_CORRECT << ")";
		else
			ss << "(node = " << A_TEST_NODE_INDEXES[i] << ")";
		cout << "    " << setw(28) << left << ss.str();
		testHelperStartCapture();
		cout << location_init[i];
		string captured = testHelperEndCapture();
		cout << endl;

		bool is_all_good_so_far = correct_print == i;
		if(checkPrinted(captured, A_TEST_NODE_INDEXES[i], is_all_good_so_far))
			correct_print++;
	}
	if(correct_print == TEST_COUNT)
		cout << "* Correct" << endl;
	else if(correct_print < TEST_COUNT - 1)
	{
		cout << "* " << setw(2) << (TEST_COUNT - 1 - correct_print) << " more (of "
		     << setw(2) << TEST_COUNT << ") printed incorrectly" << endl;
	}
	cout << endl;


	//
	//  Print results
	//

	unsigned int init_correct = 0;
	for(unsigned int i = 0; i < TEST_COUNT; i++)
		if(correct_init[i])
			init_correct++;
	double correct_init_fraction = (double)(init_correct) / (TEST_COUNT);

	double correct_equal_fraction   = (double)(  EQUAL_COUNT_MAX -   equal_incorrect_count) /   EQUAL_COUNT_MAX;
	double correct_unequal_fraction = (double)(UNEQUAL_COUNT_MAX - unequal_incorrect_count) / UNEQUAL_COUNT_MAX;
	double correct_print_fraction   = (double)(correct_print) / TEST_COUNT;

	testHelperPrintSummaryHeader(26, 2, DID_NOT_CRASH_RUNNING_MARKS);
	testHelperPrintSummaryLine("Location declaration",     correct_location_bytes);
	testHelperPrintSummaryLine("Default constructor",      correct_default);
	testHelperPrintSummaryLine("Initalizing constructor",  init_correct,    TEST_COUNT);
	testHelperPrintSummaryLine("Equality test \"const\"s", correct_consts_on_equality_test);
	testHelperPrintSummaryLine("Equality test (true)",     correct_equal_fraction);
	testHelperPrintSummaryLine("Equality test (false)",    correct_unequal_fraction);
	testHelperPrintSummaryLine("Stream output (<<)",       correct_print_fraction);

	unsigned int mark = COMPILE_AND_NOT_CRASH_MARKS;

	if(correct_location_bytes &&
	   correct_default        &&
	   correct_init_fraction == 1.0)
	{
		mark += 1;
	}
	if(correct_consts_on_equality_test &&
	   correct_equal_fraction   == 1.0 &&
	   correct_unequal_fraction == 1.0)
	{
		mark += 1;
	}
	if(correct_print_fraction == 1.0)
		mark += 1;

	assert(mark <= TOTAL_MARKS);
	testHelperPrintMark(mark, TOTAL_MARKS);

	testHelperWaitForEnter();
	return 0;
}

void overwriteField (Location& location, unsigned int value)
{
	unsigned int size = sizeof(Location);
	if(size == 0)  // doesn't seem to happen on my computer, always at least 1
		return;

	assert(size > 0);
	if(size > sizeof(unsigned int))
		size = sizeof(unsigned int);

	const unsigned char*    value_as_chars = reinterpret_cast<const unsigned char*>(&value);
	      unsigned char* location_as_chars = reinterpret_cast<      unsigned char*>(&location);
	memcpy(location_as_chars, value_as_chars, size);
}

unsigned int extractField (const Location& location)
{
	unsigned int size = sizeof(Location);
	if(size == 0)  // doesn't seem to happen on my computer, always at least 1
		return 0;

	assert(size > 0);
	if(size > sizeof(unsigned int))
		size = sizeof(unsigned int);

	unsigned int result = 0;
	const unsigned char* location_as_chars = reinterpret_cast<const unsigned char*>(&location);
	      unsigned char*   result_as_chars = reinterpret_cast<      unsigned char*>(&result);
	memcpy(result_as_chars, location_as_chars, size);
	return result;
}

bool checkLocation (const Location& location,
                    int correct_node_index,
                    bool is_print_incorrect)
{
	unsigned int node_index = extractField(location);

	if(is_print_incorrect)
	{
		if(node_index == UNSET_NODE_INDEX)
			cout << "* Incorrect: Member field was not set (value " << UNSET_NODE_INDEX << ")" << endl;
		else if(node_index != correct_node_index)
			cout << "* Incorrect: Member field was set to " << node_index << ", should be " << correct_node_index << endl;
	}

	return node_index == correct_node_index;
}

// an adapted form exists in TestItem3
bool checkPrinted (const string& printed,
                   int correct_node_index,
                   bool is_print_incorrect)
{
	if(printed.empty())
	{
		if(is_print_incorrect)
			cout << "* Incorrect: Printed nothing" << endl;
		return false;
	}

	if(printed.find('\n') != string::npos)
	{
		if(is_print_incorrect)
			cout << "* Incorrect: Should not print a newline" << endl;
		return false;
	}

	assert(printed.size() >= 1);
	bool opening_parenthesis = printed[0                 ] == '(';
	bool closing_parenthesis = printed[printed.size() - 1] == ')';
	if(!opening_parenthesis || !closing_parenthesis)
	{
		if(is_print_incorrect)
		{
			bool is_any_opening = printed.find('(') != string::npos;
			bool is_any_closing = printed.find(')') != string::npos;

			if(!opening_parenthesis && !closing_parenthesis)
			{
				if(is_any_opening && is_any_closing)
					cout << "* Incorrect: Parentheses should be printed around everything else" << endl;
				else
					cout << "* Incorrect: Should print parentheses around location" << endl;
			}
			else if(!opening_parenthesis)
			{
				if(is_any_opening)
					cout << "* Incorrect: Opening parenthesis should be printed first" << endl;
				else
					cout << "* Incorrect: Missing opening parenthesis" << endl;
			}
			else if(!closing_parenthesis)
			{
				if(is_any_opening)
					cout << "* Incorrect: Closing parenthesis should be printed last" << endl;
				else
					cout << "* Incorrect: Missing closing parenthesis" << endl;
			}
		}
		return false;
	}

	assert(printed.length() >= 2);
	string without_parentheses = printed.substr(1, printed.length() - 2);
	vector<string> tokens = testHelperSplitWithoutEmpty(without_parentheses, ' ');
	switch(tokens.size())
	{
	case 0:
		if(is_print_incorrect)
			cout << "* Incorrect: Nothing between parentheses" << endl;
		return false;
	case 1:
		if(is_print_incorrect)
			cout << "* Incorrect: No spaces between parentheses" << endl;
		return false;
	case 2:
		if(is_print_incorrect)
			cout << "* Incorrect: Should be spaces on either side of '='" << endl;
		return false;
	case 3:
		// everything is good so far
		break;
	default:
		if(is_print_incorrect)
			cout << "* Incorrect: Too many spaces between parentheses" << endl;
		return false;
	}
	assert(tokens.size() == 3);

	string lowercase = tokens[0];
	for(unsigned int i = 0; i < lowercase.size(); i++)
		lowercase[i] = tolower(lowercase[i]);

	if(lowercase != "node")
	{
		if(is_print_incorrect)
			cout << "* Incorrect: Should start with \"node = \"" << endl;
		return false;
	}

	if(tokens[1] != "=")
	{
		if(is_print_incorrect)
			cout << "* Incorrect: Missing \"=\"" << endl;
		return false;
	}

	if(correct_node_index == INACCESSIBLE_NODE_INDEX)
	{
		if(tokens[2] != INACCESSIBLE_PRINT_CORRECT)
		{
			if(is_print_incorrect)
				cout << "* Incorrect: Should print \"" << INACCESSIBLE_PRINT_CORRECT << "\" for impassable nodes" << endl;
			return false;
		}
	}
	else
	{
		stringstream ss_node_index(tokens[2]);
		int printed_node_index;
		ss_node_index >> printed_node_index;

		if(ss_node_index.fail())
		{
			if(is_print_incorrect)
				cout << "* Incorrect: Node index was not printed as an integer" << endl;
			return false;
		}
		else if(printed_node_index != correct_node_index)
		{
			if(is_print_incorrect)
				cout << "* Incorrect: Printed node index as " << printed_node_index << ", should be " << correct_node_index << endl;
			return false;
		}
	}

	return true;
}
