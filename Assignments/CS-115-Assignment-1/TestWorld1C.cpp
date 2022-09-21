//
//  TestWorld1C.cpp
//
//  A test program for the World module.
//
//  This program is to be used with Assignment 1: Part C for
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
bool testMessagePrint (const string& printed, const string& correct);

const int COMPILE_AND_START_MARKS     = 3;
const int DID_NOT_CRASH_RUNNING_MARKS = 3;
const int COMPILE_AND_NOT_CRASH_MARKS = COMPILE_AND_START_MARKS + DID_NOT_CRASH_RUNNING_MARKS;
const int COMBINED_TEST_MARKS         = 14;
const int TOTAL_MARKS                 = COMPILE_AND_NOT_CRASH_MARKS + COMBINED_TEST_MARKS;

const unsigned int DESCRIPTION_COUNT_CORRECT = 26;

const string START_MESSAGE_CORRECT =
	"Welcome to Blizzard Valley!\n"
	"You and six children were hiking in the mountains when an\n"
	"unexpected blizzard blew up.  Find the children and get them all\n"
	"back to the hiking lodge on the other side of the river.\n";

const string END_MESSAGE_CORRECT =
	"Thank you for playing Blizzard Valley!\n";

const string MESSAGE_4_CORRECT =
	"You are at a bend on a steep mountain trail running along the\n"
	"top of a cliff.  The trail leads north and west from here. Icy\n"
	"cliffs to the east and south lead to a rushing river below.\n";

const string MESSAGE_25_CORRECT =
	"You are at the north end of a forest path.  To the east, you\n"
	"can see a large wooden building with light shining from the\n"
	"windows.\n";

const int START_ROW_CORRECT    = 4;
const int START_COLUMN_CORRECT = 1;

const int NODE_25_ROW_CORRECT    = 3;
const int NODE_25_COLUMN_CORRECT = 7;



int main ()
{
	testHelperStartup("TestWorld1C", COMPILE_AND_START_MARKS, TOTAL_MARKS);

	World world;


	//
	//  Test size constants
	//

	cout << "Testing DESCRIPTION_COUNT" << endl;
	bool correct_description_count = testHelperConstant(DESCRIPTION_COUNT, DESCRIPTION_COUNT_CORRECT, "DESCRIPTION_COUNT");
	cout << endl;

	//
	//  Testing loading
	//

	cout << "Testing loading descriptions (via worldLoadAll)" << endl;
	worldLoadAll(world, "blizzard");
	cout << "* Completed without crashing" << endl;
	cout << endl;

	//
	//  Testing printing messages
	//

	cout << "Testing worldPrintStartMessage" << endl;
	cout << "--------------------------------------------------------" << endl;
	testHelperStartCapture();
	worldPrintStartMessage(world);
	string start_message_captured = testHelperEndCapture();
	cout << "--------------------------------------------------------" << endl;
	bool print_start_message_correct = testMessagePrint(start_message_captured, START_MESSAGE_CORRECT);
	cout << endl;

	cout << "Testing worldPrintEndMessage" << endl;
	cout << "--------------------------------------------------------" << endl;
	testHelperStartCapture();
	worldPrintEndMessage(world);
	string end_message_captured = testHelperEndCapture();
	cout << "--------------------------------------------------------" << endl;
	bool print_end_message_correct = testMessagePrint(end_message_captured, END_MESSAGE_CORRECT);
	cout << endl;

	cout << "Testing message 4 (start node)" << endl;
	cout << "--------------------------------------------------------" << endl;
	testHelperStartCapture();
	worldPrintDescription(world, START_ROW_CORRECT, START_COLUMN_CORRECT);
	string message_4_captured = testHelperEndCapture();
	cout << "--------------------------------------------------------" << endl;
	bool print_message_4_correct = testMessagePrint(message_4_captured, MESSAGE_4_CORRECT);
	cout << endl;

	cout << "Testing message 25 (last in file)" << endl;
	cout << "--------------------------------------------------------" << endl;
	testHelperStartCapture();
	worldPrintDescription(world, NODE_25_ROW_CORRECT, NODE_25_COLUMN_CORRECT);
	string message_25_captured = testHelperEndCapture();
	cout << "--------------------------------------------------------" << endl;
	bool print_message_25_correct = testMessagePrint(message_25_captured, MESSAGE_25_CORRECT);
	cout << endl;


	//
	//  Print results
	//

	bool is_any_message_correct = print_start_message_correct ||
	                              print_end_message_correct   ||
	                              print_message_4_correct     ||
	                              print_message_25_correct;

	testHelperPrintSummaryHeader(30, 1, DID_NOT_CRASH_RUNNING_MARKS);
	testHelperPrintSummaryLine("Description count constant", correct_description_count);
	testHelperPrintSummaryLine("Print start game message",   print_start_message_correct);
	testHelperPrintSummaryLine("Print end game message",     print_end_message_correct);
	testHelperPrintSummaryLine("Print message 4",            print_message_4_correct);
	testHelperPrintSummaryLine("Print message 25",           print_message_25_correct);

	unsigned int mark = COMPILE_AND_NOT_CRASH_MARKS;

	if(correct_description_count)
		mark += 1;
	if(print_start_message_correct)
		mark += 2;
	if(print_end_message_correct)
		mark += 2;
	if(print_message_4_correct)
		mark += 1;
	if(print_message_25_correct)
		mark += 1;
	if(is_any_message_correct)
	{
		mark += 7;
		cout << endl;
		cout << "* At least one description was printed" << endl;
		cout << "    -7 marks if the text was in the .cpp file." << endl;
	}
	else
	{
		cout << endl;
		cout << "* No descriptions were printed:  -7 marks." << endl;
	}

	assert(mark <= TOTAL_MARKS);
	testHelperPrintMark(mark, TOTAL_MARKS);

	testHelperWaitForEnter();
	return 0;
}


bool testMessagePrint (const string& printed, const string& correct)
{
	vector<string> printed_lines = testHelperSplitWithoutEmpty(printed, '\n');
	vector<string> correct_lines = testHelperSplitWithoutEmpty(correct, '\n');
	if(printed_lines.size() != correct_lines.size())
	{
		cout << "* Incorrect: Printed " << printed_lines.size()
		     << " lines, should be " << correct_lines.size() << endl;
		return false;
	}

	for(unsigned int i = 0; i < printed_lines.size(); i++)
	{
		if(printed_lines[i] != correct_lines[i])
		{
			cout << "* Incorrect: Line " << i << " is:" << endl;
			cout << "    \"" << printed_lines[i] << "\"" << endl;
			cout << "  It should be:" << endl;
			cout << "    \"" << correct_lines[i] << "\"" << endl;
			return false;
		}
	}

	cout << "* Correct" << endl;
	return true;
}
