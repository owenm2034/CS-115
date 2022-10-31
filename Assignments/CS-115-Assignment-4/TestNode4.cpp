//
//  TestNode4.cpp
//
//  A test program for the Node module.
//
//  This program is to be used with Assignment 4: Part E for
//    CS115, 202210.
//
//  Do not modify this file.
//
//  2022-03-04: Added #include for <cstring> (needed for memcpy)
//  2022-03-14: Changed marking scheme: 15 => 8
//

#include "Node.h"
#include "Node.h"  // repeated to test for #include errors

#include <cassert>
#include <climits>
#include <cstring>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <typeinfo>  // for typeid

#include "TestHelper.h"

#include "Location.h"

using namespace std;
namespace
{
	struct CheckResult
	{
		bool is_description_correct;
		bool is_north_correct;
		bool is_south_correct;
		bool is_east_correct;
		bool is_west_correct;
		bool is_death_correct;
	};

	struct PrintResult
	{
		bool is_anything;
		bool is_newline_correct;
		bool is_token_count_correct;
		bool is_node_type_correct;
		bool is_description_correct;
		bool is_north_correct;
		bool is_south_correct;
		bool is_east_correct;
		bool is_west_correct;
	};

}  // end on anonymous namespace



int main ();

unsigned int extractField (const Location& location);
CheckResult checkNode (const Node& node,
                       int correct_description,
                       int correct_north,
                       int correct_south,
                       int correct_east,
                       int correct_west,
                       bool correct_is_death);
unsigned int countCheckResult (const CheckResult& result);
double scoreCheckResult (const CheckResult& result);

void debugPrintCorrect (unsigned int correct_description,
                        unsigned int correct_north,
                        unsigned int correct_south,
                        unsigned int correct_east,
                        unsigned int correct_west,
                        bool correct_is_death);
PrintResult checkPrinted (const string& printed,
                          int correct_description,
                          int correct_north,
                          int correct_south,
                          int correct_east,
                          int correct_west,
                          bool correct_is_death);
char getCorrectNodeType (bool correct_is_death);
string tabsToSpaces (const string& str);
unsigned int countInString (const string& str, char search_for);
unsigned int countPrintResult (const PrintResult& result);
double scorePrintResult (const PrintResult& result);

const int COMPILE_AND_START_MARKS     = 1;
const int DID_NOT_CRASH_RUNNING_MARKS = 1;
const int COMPILE_AND_NOT_CRASH_MARKS = COMPILE_AND_START_MARKS + DID_NOT_CRASH_RUNNING_MARKS;
const int COMBINED_TEST_MARKS         = 6;
const int TOTAL_MARKS                 = COMPILE_AND_NOT_CRASH_MARKS + COMBINED_TEST_MARKS;

const unsigned int PRINT_TOKEN_COUNT_CORRECT = 6;

const unsigned int COUNT_CHECK_RESULT_MAX = 6;
const unsigned int COUNT_PRINT_RESULT_MAX = 9;

const unsigned int TEST_DESCRIPTION_DEFAULT = 0;
const unsigned int TEST_NORTH_DEFAULT       = 0;
const unsigned int TEST_SOUTH_DEFAULT       = 0;
const unsigned int TEST_EAST_DEFAULT        = 0;
const unsigned int TEST_WEST_DEFAULT        = 0;
const bool         TEST_IS_DEATH_DEFAULT    = false;

const unsigned int TEST_DESCRIPTION_1 = 1;
const unsigned int TEST_NORTH_1       = 2;
const unsigned int TEST_SOUTH_1       = 3;
const unsigned int TEST_EAST_1        = 4;
const unsigned int TEST_WEST_1        = 5;
const bool         TEST_IS_DEATH_1    = false;

const unsigned int TEST_DESCRIPTION_2 = 100;
const unsigned int TEST_NORTH_2       = 86;
const unsigned int TEST_SOUTH_2       = 73;
const unsigned int TEST_EAST_2        = 61;
const unsigned int TEST_WEST_2        = 50;
const bool         TEST_IS_DEATH_2    = true;



int main ()
{
	testHelperStartup("TestNode4", COMPILE_AND_START_MARKS, TOTAL_MARKS);

	//
	//  Test Node class
	//

	cout << "Checking Node size in bytes" << endl;
	size_t node_bytes          = sizeof(Node);
	size_t node_bytes_correct1 = sizeof(unsigned int) * 5 + sizeof(bool);
	size_t node_bytes_correct2 = sizeof(Location)     * 5 + sizeof(bool);

	bool correct_node_bytes = false;
	if(node_bytes < node_bytes_correct1 && node_bytes < node_bytes_correct2)
		cout << "* Incorrect: Node should contain more data" << endl;
	else if(node_bytes > node_bytes_correct1 * 2 && node_bytes > node_bytes_correct2 * 2)
		cout << "* Incorrect: Node contains unnecessary data" << endl;
	else
	{
		cout << "* Correct" << endl;
		correct_node_bytes = true;
	}
	cout << endl;

	cout << "Creating Node" << endl;
	Node* p_node = new Node;
	cout << "* Completed without crashing" << endl;
	cout << endl;

	cout << "Destroying Node" << endl;
	delete p_node;
	p_node = NULL;
	cout << "* Completed without crashing" << endl;
	cout << endl;


	//
	//  Test default constructor
	//

	cout << "Testing default constructor" << endl;
	Node node_default;
	CheckResult result_default = checkNode(node_default, TEST_DESCRIPTION_DEFAULT,
	                                       TEST_NORTH_DEFAULT, TEST_SOUTH_DEFAULT, TEST_EAST_DEFAULT, TEST_WEST_DEFAULT,
	                                       TEST_IS_DEATH_DEFAULT);
	cout << endl;

	cout << "Testing debugPrint" << endl;
	debugPrintCorrect(TEST_DESCRIPTION_DEFAULT,
	                  TEST_NORTH_DEFAULT, TEST_SOUTH_DEFAULT, TEST_EAST_DEFAULT, TEST_WEST_DEFAULT,
	                  TEST_IS_DEATH_DEFAULT);
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	node_default.debugPrint();
	string captured = testHelperEndCapture();
	cout << "----------------------------------------------------------------" << endl;
	PrintResult print_result_default = checkPrinted(captured, TEST_DESCRIPTION_DEFAULT,
		                                            TEST_NORTH_DEFAULT, TEST_SOUTH_DEFAULT, TEST_EAST_DEFAULT, TEST_WEST_DEFAULT,
		                                            TEST_IS_DEATH_DEFAULT);
	cout << endl;


	//
	//  Test initializing constructor
	//

	cout << "Testing initializing constructor (#1)" << endl;
	Node node_init1(TEST_DESCRIPTION_1,
	                TEST_NORTH_1, TEST_SOUTH_1, TEST_EAST_1, TEST_WEST_1,
	                TEST_IS_DEATH_1);
	CheckResult result_init1 = checkNode(node_init1, TEST_DESCRIPTION_1,
	                                     TEST_NORTH_1, TEST_SOUTH_1, TEST_EAST_1, TEST_WEST_1,
	                                     TEST_IS_DEATH_1);
	cout << endl;

	cout << "Testing debugPrint" << endl;
	debugPrintCorrect(TEST_DESCRIPTION_1,
	                  TEST_NORTH_1, TEST_SOUTH_1, TEST_EAST_1, TEST_WEST_1,
	                  TEST_IS_DEATH_1);
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	node_init1.debugPrint();
	string captured_init1 = testHelperEndCapture();
	cout << "----------------------------------------------------------------" << endl;
	PrintResult print_result_init1 = checkPrinted(captured_init1, TEST_DESCRIPTION_1,
		                                          TEST_NORTH_1, TEST_SOUTH_1, TEST_EAST_1, TEST_WEST_1,
		                                          TEST_IS_DEATH_1);
	cout << endl;

	cout << "Testing initializing constructor (#2)" << endl;
	Node node_init2(TEST_DESCRIPTION_2,
	                TEST_NORTH_2, TEST_SOUTH_2, TEST_EAST_2, TEST_WEST_2,
	                TEST_IS_DEATH_2);
	CheckResult result_init2 = checkNode(node_init2, TEST_DESCRIPTION_2,
	                                     TEST_NORTH_2, TEST_SOUTH_2, TEST_EAST_2, TEST_WEST_2,
	                                     TEST_IS_DEATH_2);
	cout << endl;

	cout << "Testing debugPrint" << endl;
	debugPrintCorrect(TEST_DESCRIPTION_2,
	                  TEST_NORTH_2, TEST_SOUTH_2, TEST_EAST_2, TEST_WEST_2,
	                  TEST_IS_DEATH_2);
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	node_init2.debugPrint();
	string captured_init2 = testHelperEndCapture();
	cout << "----------------------------------------------------------------" << endl;
	PrintResult print_result_init2 = checkPrinted(captured_init2, TEST_DESCRIPTION_2,
		                                          TEST_NORTH_2, TEST_SOUTH_2, TEST_EAST_2, TEST_WEST_2,
		                                          TEST_IS_DEATH_2);
	cout << endl;


	//
	//  Print results
	//

	unsigned int default_result_count = countCheckResult(result_default);
	unsigned int init_result_count    = countCheckResult(result_init1) +
	                                    countCheckResult(result_init2);

	unsigned int construct_print_count = countPrintResult(print_result_default) +
	                                     countPrintResult(print_result_init1)   +
	                                     countPrintResult(print_result_init2);

	testHelperPrintSummaryHeader(24, 2, DID_NOT_CRASH_RUNNING_MARKS);
	testHelperPrintSummaryLine("Node declaration",     correct_node_bytes);
	testHelperPrintSummaryLine("Default constructor",  default_result_count,  COUNT_CHECK_RESULT_MAX);
	testHelperPrintSummaryLine("Init. constructor",    init_result_count,     COUNT_CHECK_RESULT_MAX * 2);
	testHelperPrintSummaryLine("debugPrint (default)", construct_print_count, COUNT_PRINT_RESULT_MAX * 3);

	unsigned int mark = COMPILE_AND_NOT_CRASH_MARKS;

	if(correct_node_bytes)
		mark += 1;
	mark += (int)(scoreCheckResult(result_default) +
	              scoreCheckResult(result_init1  ) +
	              scoreCheckResult(result_init2  ));
	mark += (int)(scorePrintResult(print_result_default)       +
	              scorePrintResult(print_result_init1  ) * 0.5 +
	              scorePrintResult(print_result_init2  ) * 0.5);

	assert(mark <= TOTAL_MARKS);
	testHelperPrintMark(mark, TOTAL_MARKS);

	testHelperWaitForEnter();
	return 0;
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

CheckResult checkNode (const Node& node,
                       int correct_description,
                       int correct_north,
                       int correct_south,
                       int correct_east,
                       int correct_west,
                       bool correct_is_death)
{
	CheckResult result;

	unsigned int description = node.getDescription();
	unsigned int north       = extractField(node.getNorth());
	unsigned int south       = extractField(node.getSouth());
	unsigned int east        = extractField(node.getEast ());
	unsigned int west        = extractField(node.getWest ());
	bool         is_death    = node.isDeath();

	result.is_description_correct = description == correct_description;
	result.is_north_correct       = north       == correct_north;
	result.is_south_correct       = south       == correct_south;
	result.is_east_correct        = east        == correct_east;
	result.is_west_correct        = west        == correct_west;
	result.is_death_correct       = is_death    == correct_is_death;

	if(!result.is_description_correct)
		cout << "* Incorrect: Description is " << description << ", but should be " << correct_description << endl;
	else if(!result.is_north_correct)
		cout << "* Incorrect: North node index is " << north << ", but should be " << correct_north << endl;
	else if(!result.is_south_correct)
		cout << "* Incorrect: South node index is " << south << ", but should be " << correct_south << endl;
	else if(!result.is_east_correct)
		cout << "* Incorrect: East node index is " << east << ", but should be " << correct_east << endl;
	else if(!result.is_west_correct)
		cout << "* Incorrect: West node index is " << west << ", but should be " << correct_west << endl;
	else if(!result.is_death_correct)
	{
		if(is_death)
			cout << "* Incorrect: This is a death node but it shouldn't be" << endl;
		else
			cout << "* Incorrect: This is not a death node but it should be" << endl;
	}
	else
		cout << "* Correct" << endl;

	return result;
}

unsigned int countCheckResult (const CheckResult& result)
{
	unsigned int total = 0;
	if(result.is_description_correct)
		total++;
	if(result.is_north_correct)
		total++;
	if(result.is_south_correct)
		total++;
	if(result.is_east_correct)
		total++;
	if(result.is_west_correct)
		total++;
	if(result.is_death_correct)
		total++;
	return total;
}

double scoreCheckResult (const CheckResult& result)
{
	unsigned int total = 0;
	if(result.is_description_correct)
		total += 2;
	if(result.is_north_correct)
		total += 1;
	if(result.is_south_correct)
		total += 1;
	if(result.is_east_correct)
		total += 1;
	if(result.is_west_correct)
		total += 1;
	if(result.is_death_correct)
		total += 2;
	return total / 8.0;
}



void debugPrintCorrect (unsigned int correct_description,
                        unsigned int correct_north,
                        unsigned int correct_south,
                        unsigned int correct_east,
                        unsigned int correct_west,
                        bool correct_is_death)
{
	cout << (correct_is_death ? 'D' : 'N') << "\t"
	     << correct_description << "\t"
	     << correct_north << "\t"
	     << correct_south << "\t"
	     << correct_east << "\t"
	     << correct_west << "\t// correct" << endl;
}

PrintResult checkPrinted (const string& printed,
                          int correct_description,
                          int correct_north,
                          int correct_south,
                          int correct_east,
                          int correct_west,
                          bool correct_is_death)
{
	PrintResult result;
	result.is_anything            = false;
	result.is_newline_correct     = false;
	result.is_token_count_correct = false;
	result.is_node_type_correct   = false;
	result.is_description_correct = false;
	result.is_north_correct       = false;
	result.is_south_correct       = false;
	result.is_east_correct        = false;
	result.is_west_correct        = false;

	//  Check overall line structure

	if(printed.empty())
	{
		cout << "* Incorrect: Printed nothing" << endl;
		return result;
	}
	result.is_anything = true;

	if(printed[printed.size() - 1] != '\n')
	{
		cout << "* Incorrect: Printed data is missing a newline at the end" << endl;
		return result;
	}
	if(countInString(printed,'\n') > 1)
	{
		cout << "* Incorrect: Printed multiple newlines" << endl;
		return result;
	}
	result.is_newline_correct = true;

	//  Split up line into tokens

	string without_newline = printed.substr(0, printed.length() - 1);
	vector<string> tokens = testHelperSplitWithoutEmpty(tabsToSpaces(without_newline), ' ');
	if(tokens.size() != PRINT_TOKEN_COUNT_CORRECT)
	{
		cout << "* Incorrect: Printed " << tokens.size() << " tokens, should be " << PRINT_TOKEN_COUNT_CORRECT << endl;
		return result;
	}
	result.is_token_count_correct = true;

	//  Check node type
	
	assert(!tokens[0].empty());
	if(tokens[0].size() != 1)
		cout << "* Incorrect: Node type \"" << tokens[0] << "\" should be a single character" << endl;
	else
	{
		char node_type = getCorrectNodeType(correct_is_death);
		if(tokens[0][0] != node_type)
			cout << "* Incorrect: Node type is '" << tokens[0] << "', but should be '" << node_type << "'" << endl;
		else
			result.is_node_type_correct = true;
	}

	//  Check description
	
	stringstream description_ss;
	description_ss << correct_description;
	string description_string = description_ss.str();
	if(tokens[1] != description_string)
		cout << "* Incorrect: Description printed as " << tokens[1] << ", but should be " << description_string << endl;
	else
		result.is_description_correct = true;

	//  Check links to other nodes
	
	stringstream north_ss;
	north_ss << correct_north;
	string north_string = north_ss.str();
	if(tokens[2] != north_string)
		cout << "* Incorrect: Node index to the north is " << tokens[2] << ", but should be " << north_string << endl;
	else
		result.is_north_correct = true;

	stringstream south_ss;
	south_ss << correct_south;
	string south_string = south_ss.str();
	if(tokens[3] != south_string)
		cout << "* Incorrect: Node index to the south is " << tokens[3] << ", but should be " << south_string << endl;
	else
		result.is_south_correct = true;

	stringstream east_ss;
	east_ss << correct_east;
	string east_string = east_ss.str();
	if(tokens[4] != east_string)
		cout << "* Incorrect: Node index to the east is " << tokens[4] << ", but should be " << east_string << endl;
	else
		result.is_east_correct = true;

	stringstream west_ss;
	west_ss << correct_west;
	string west_string = west_ss.str();
	if(tokens[5] != west_string)
		cout << "* Incorrect: Node index to the west is " << tokens[5] << ", but should be " << west_string << endl;
	else
		result.is_west_correct = true;

	//  Check if all correct
	
	if(result.is_node_type_correct   &&
	   result.is_description_correct &&
	   result.is_north_correct       &&
	   result.is_south_correct       &&
	   result.is_east_correct        &&
	   result.is_west_correct)
	{
		cout << "* Correct" << endl;
	}

	return result;
}

char getCorrectNodeType (bool correct_is_death)
{
	if(correct_is_death)
		return 'D';
	else
		return 'N';
}

string tabsToSpaces (const string& str)
{
	string result = str;
	for(unsigned int i = 0; i < str.size(); i++)
		if(result[i] == '\t')
			result[i] = ' ';
	return result;
}

unsigned int countInString (const string& str, char search_for)
{
	unsigned int count = 0;
	for(unsigned int i = 0; i < str.size(); i++)
		if(str[i] == search_for)
			count++;
	return count;
}

unsigned int countPrintResult (const PrintResult& result)
{
	if(!result.is_anything)
		return 0;
	if(!result.is_newline_correct)
		return 1;
	if(!result.is_token_count_correct)
		return 2;

	unsigned int total = 3;
	if(result.is_node_type_correct)
		total++;
	if(result.is_description_correct)
		total++;
	if(result.is_north_correct)
		total++;
	if(result.is_south_correct)
		total++;
	if(result.is_east_correct)
		total++;
	if(result.is_west_correct)
		total++;
	return total;
}

double scorePrintResult (const PrintResult& result)
{
	if(!result.is_anything)
		return 0.0;

	unsigned int total = 0;
	if(result.is_newline_correct)
		total += 1;
	if(result.is_token_count_correct)
		total += 2;
	if(result.is_node_type_correct)
		total += 2;
	if(result.is_description_correct)
		total += 1;
	if(result.is_north_correct)
		total += 1;
	if(result.is_south_correct)
		total += 1;
	if(result.is_east_correct)
		total += 1;
	if(result.is_west_correct)
		total += 1;
	return total / 10.0;
}

