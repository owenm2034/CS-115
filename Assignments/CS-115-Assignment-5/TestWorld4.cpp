//
//  TestWorld4.cpp
//
//  A test program for the World module.
//
//  This program was based on TestWorld3.cpp.  It has been
//    adapted to use node-index-based Locations instead of
//    row-and-column-based ones.
//
//  This program is to be used with Assignment 4: Part F for
//    CS115, 202210.
//
//  Do not modify this file.
//
//  2022-03-14: Changed marking scheme: 25 => 12
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

#include "Location.h"

using namespace std;



int main ();

bool operator!= (const Location& location1, const Location& location2);
bool testGetStartNode (const World& world, const Location& desired);
bool testMessagePrint (const string& printed, const string& correct);

const int COMPILE_AND_START_MARKS     = 2;
const int DID_NOT_CRASH_RUNNING_MARKS = 2;
const int COMPILE_AND_NOT_CRASH_MARKS = COMPILE_AND_START_MARKS + DID_NOT_CRASH_RUNNING_MARKS;
const int COMBINED_TEST_MARKS         = 8;
const int TOTAL_MARKS                 = COMPILE_AND_NOT_CRASH_MARKS + COMBINED_TEST_MARKS;

const unsigned int MAX_NODE_COUNT_CORRECT        = 1000;
const unsigned int MAX_DESCRIPTION_COUNT_CORRECT = 1000;
const unsigned int START_MESSAGE_CORRECT = 1;
const unsigned int END_MESSAGE_CORRECT   = 2;
const Location     NO_SUCH_VALUE_CORRECT(-1);

const int NODE_COUNT_CORRECT = 62;

const Location LOCATION_DEATH  ( 4);  // one of several
const Location LOCATION_START  (55);
const Location LOCATION_VICTORY(57);

const unsigned int TEST_LOCATION_COUNT         = 5;
const unsigned int TEST_LOCATION_DEATH_INDEX   = 1;
const unsigned int TEST_LOCATION_VICTORY_INDEX = 3;
const Location TEST_LOCATIONS[TEST_LOCATION_COUNT] =
{
	Location(0),  // inaccessible
	LOCATION_DEATH,
	LOCATION_START,
	LOCATION_VICTORY,
	Location(16),  // ordinary node
};

const int INVALID_CHECK_BORDER = 5;
const int INVALID_START        = -INVALID_CHECK_BORDER;
const int INVALID_END          = NODE_COUNT_CORRECT + INVALID_CHECK_BORDER;
const int INVALID_NODE_COUNT   = INVALID_CHECK_BORDER * 2;

const unsigned int TEST_DIRECTION_COUNT = 4;
const string A_DIRECTION_NAME[TEST_DIRECTION_COUNT] =
{
	"north",
	"south",
	"east",
	"west",
};

// pointers to member functions (thoroughly weird)
//  -> allows them to be called in a loop using array syntax
//  -> don't do this unless you know what you're doing
//    -> if you are taking CS 115, you don't
typedef bool (World::*pCanGoDirectionMemberFunction)(const Location&) const;
const pCanGoDirectionMemberFunction AP_CAN_GO_DIRECTION_FUNCTION[TEST_DIRECTION_COUNT] =
{
	&World::canGoNorth,
	&World::canGoSouth,
	&World::canGoEast,
	&World::canGoWest,
};
typedef Location (World::*pGetDirectionMemberFunction)(const Location&) const;
const pGetDirectionMemberFunction AP_GET_DIRECTION_FUNCTION[TEST_DIRECTION_COUNT] =
{
	&World::getNorth,
	&World::getSouth,
	&World::getEast,
	&World::getWest,
};

const Location A_TEST_CAN_GO_INACCESSIBLE[TEST_DIRECTION_COUNT] =
{
	Location(29),
	Location(50),
	Location(25),
	Location(15),
};

const Location A_TEST_CAN_GO_OPEN[TEST_DIRECTION_COUNT] =
{
	Location(52),
	Location( 3),
	Location(58),
	Location(19),
};

const Location A_LOCATION_AFTER_GO_OPEN[TEST_DIRECTION_COUNT] =
{
	Location(44),
	Location( 9),
	Location(59),
	Location(18),
};

const unsigned int TEST_DESCRIPTION_COUNT = 5;
const unsigned int A_TEST_DESCRIPTION_NUMBER[TEST_DESCRIPTION_COUNT] =
{
	 4,
	 5,
	 6,
	25,
	55,
};
const string A_TEST_DESCRIPTION_NAME[TEST_DESCRIPTION_COUNT] =
{
	"Start node",
	"Victory node",
	"Description 6",
	"Description 25",
	"Description 55",
};
const Location A_TEST_DESCRIPTION_LOCATION[TEST_DESCRIPTION_COUNT] =
{
	LOCATION_START,
	LOCATION_VICTORY,
	47,
	26,
	52,
};
const string A_TEST_DESCRIPTION_CORRECT[TEST_DESCRIPTION_COUNT] =
{
	"You are at the north end of a tree-flanked lane.  To the north\n"
	"is a wrought iron gate.  A faded sign above the gate says\n"
	"\"GHOSTWOOD MANOR\".\n"
	"Below that, someone has scrawled \"Enter at your own risk\".\n",

	"You are at a bend in a gravel road.  From here, the road\n"
	"continues south and west, and a tree-flanked lane leads north.\n"
	"There is a pond to the east.\n"
	"You decide to stop adventuring while you're still alive.\n",

	"You are in the courtyard of the manor.  The main door to the\n"
	"north is flanked by dead trees, one of which has dropped a heavy\n"
	"branch across it.  There are open areas to the east and west,\n"
	"and a wrought iron gate hangs open to the south.\n",

	"You are at the north end of an open area.  There is a large,\n"
	"broken window leading into an old manor to the east, a wrought\n"
	"iron fence to the west, and a cave leading into a short cliff to\n"
	"the north.\n",

	"You are at the south end of a forest path, on the north shore of\n"
	"a small pond.  There is a wrought iron fence to the east and\n"
	"forest to the west.\n",
};

const string INACCESSIBLE_DESCRIPTION_CORRECT = 
	"Invalid node.\n";
const string START_MESSAGE_DESCRIPTION_CORRECT = 
	"Welcome to Ghostwood Manor!\n"
	"There are rumors of treasure in the old haunted house\n"
	"but many who venture in never come out again.\n";
const string END_MESSAGE_DESCRIPTION_CORRECT = 
	"Thank you for playing Ghostwood Manor!\n";



int main ()
{
	testHelperStartup("TestWorld4", COMPILE_AND_START_MARKS, TOTAL_MARKS);

	//
	//  Test constants
	//

	cout << "Testing MAX_NODE_COUNT" << endl;
	bool correct_max_node_count = testHelperConstant(MAX_NODE_COUNT, MAX_NODE_COUNT_CORRECT, "MAX_NODE_COUNT");
	cout << endl;

	cout << "Testing MAX_DESCRIPTION_COUNT" << endl;
	bool correct_max_description_count = testHelperConstant(MAX_DESCRIPTION_COUNT, MAX_DESCRIPTION_COUNT_CORRECT, "MAX_DESCRIPTION_COUNT");
	cout << endl;

	cout << "Testing NO_SUCH_VALUE" << endl;
	bool correct_no_such_value = testHelperConstant(NO_SUCH_VALUE, NO_SUCH_VALUE_CORRECT, "NO_SUCH_VALUE");
	cout << endl;


	//
	//  Test World type and constructor
	//

	cout << "Checking World size in bytes" << endl;
	size_t world_bytes              = sizeof(World);
	size_t world_bytes_nodes        = sizeof(Node)   * MAX_NODE_COUNT_CORRECT;
	size_t world_bytes_descriptions = sizeof(string) * MAX_DESCRIPTION_COUNT;
	size_t world_bytes_correct      = sizeof(unsigned int) * 6 + world_bytes_nodes + world_bytes_descriptions;
	bool correct_world_bytes = false;
	if(world_bytes < world_bytes_nodes)
		cout << "* Incorrect: World should contain a 1D array of Nodes" << endl;
	else if(world_bytes < world_bytes_descriptions)
		cout << "* Incorrect: World should contain a 1D array of descriptions" << endl;
	else if(world_bytes >= world_bytes_correct * 2)
		cout << "* Incorrect: World contains far too much data" << endl;
	else
	{
		cout << "* Correct" << endl;
		correct_world_bytes = true;
	}
	cout << endl;

	cout << "Loading Ghostwood world with constructor" << endl;
	World world("ghostwood");
	cout << "* Completed without crashing" << endl;
	cout << endl;

	bool is_all_good_so_far = correct_max_node_count &&
	                          correct_max_description_count &&
	                          correct_world_bytes;
	cout << "Testing World::debugPrint" << endl;
	testHelperStartCapture();
	world.debugPrint();
	string captured = testHelperEndCapture(false);
	if(is_all_good_so_far)
	{
		cout << "--------------------------------------------------------" << endl;
		cout << captured;
		// blank line printed here is not a problem
		cout << "--------------------------------------------------------" << endl;
	}
	else
		cout << "* Skipped output because there are other errors above" << endl;
	cout << "* Completed without crashing" << endl;
	cout << endl;


	//
	//  Test isValid function
	//

	cout << "Testing if nodes inside the world are valid" << endl;
	unsigned int valid_inside_correct = 0;
	bool is_first_invalid = true;
	for(int i = 0; i < NODE_COUNT_CORRECT; i++)
	{
		bool is_valid = world.isValid(Location(i));
		if(is_valid)
			valid_inside_correct++;
		else if(is_first_invalid)
		{
			cout << "* Incorrect: Node " << i << " not is valid but should be" << endl;
			is_first_invalid = false;
		}
	}
	if(valid_inside_correct == NODE_COUNT_CORRECT)
		cout << "* Correct" << endl;
	cout << endl;

	cout << "Testing if nodes outside the world are invalid" << endl;
	unsigned int valid_outside_correct = 0;
	bool is_first_valid = true;
	for(int i = INVALID_START; i < INVALID_END; i++)
	{
		if(i >= 0 && i < NODE_COUNT_CORRECT)
			continue;  // already checked above

		bool is_valid = world.isValid(Location(i));
		if(!is_valid)
			valid_outside_correct++;
		else if(is_first_valid)
		{
			cout << "* Incorrect: Node " << i << " is valid but should not be" << endl;
			is_first_valid = false;
		}
	}
	if(valid_outside_correct == INVALID_NODE_COUNT)
		cout << "* Correct" << endl;
	cout << endl;


	//
	//  Test single-node queries
	//

	cout << "Testing World::isDeath" << endl;
	bool is_death_correct = true;
	for(int i = 0; i < TEST_LOCATION_COUNT; i++)
	{
		bool should_be_death = i == TEST_LOCATION_DEATH_INDEX;
		if(world.isDeath(TEST_LOCATIONS[i]) != should_be_death)
		{
			if(is_death_correct)  // first time only
			{
				if(should_be_death)
					cout << "* Incorrect: Node " << TEST_LOCATIONS[i] << " reported as death node, shouldn't be" << endl;
				else
					cout << "* Incorrect: Node " << TEST_LOCATIONS[i] << " not reported as death node, should be" << endl;
			}
			is_death_correct = false;
		}
	}
	if(is_death_correct)
		cout << "* Correct" << endl;
	cout << endl;

	cout << "Testing World::isVictory" << endl;
	bool is_victory_correct = true;
	for(int i = 0; i < TEST_LOCATION_COUNT; i++)
	{
		bool should_be_victory = i == TEST_LOCATION_VICTORY_INDEX;
		if(world.isVictory(TEST_LOCATIONS[i]) != should_be_victory)
		{
			if(is_victory_correct)  // first time only
			{
				if(should_be_victory)
					cout << "* Incorrect: Node " << TEST_LOCATIONS[i] << " reported as victory node, shouldn't be" << endl;
				else
					cout << "* Incorrect: Node " << TEST_LOCATIONS[i] << " not reported as victory node, should be" << endl;
			}
			is_victory_correct = false;
		}
	}
	if(is_victory_correct)
		cout << "* Correct" << endl;
	cout << endl;


	//
	//  Test direction queries and getStart
	//

	cout << "Testing World::canGoNorth, etc. functions" << endl;
	bool can_go_direction_correct[TEST_DIRECTION_COUNT];
	unsigned int can_go_direction_correct_count = 0;
	for(int i = 0; i < TEST_DIRECTION_COUNT; i++)
	{
		can_go_direction_correct[i] = true;

		pCanGoDirectionMemberFunction pCanGoDirection = AP_CAN_GO_DIRECTION_FUNCTION[i];

		bool can_go_into_inaccessible = (world.*pCanGoDirection)(A_TEST_CAN_GO_INACCESSIBLE[i]);
		if(can_go_into_inaccessible)
		{
			cout << "* Incorrect: Returns true for going " << A_DIRECTION_NAME[i] << " into INACCESSIBLE" << endl;
			can_go_direction_correct[i] = false;
		}

		bool can_go_into_open = (world.*pCanGoDirection)(A_TEST_CAN_GO_OPEN[i]);
		if(!can_go_into_open)
		{
			cout << "* Incorrect: Returns false for going " << A_DIRECTION_NAME[i] << " into open node" << endl;
			can_go_direction_correct[i] = false;
		}

		if(can_go_direction_correct[i] == true)
			can_go_direction_correct_count++;
	}
	if(can_go_direction_correct_count == TEST_DIRECTION_COUNT)
		cout << "* Correct" << endl;
	cout << endl;

	cout << "Testing World::getNorth, etc. functions" << endl;
	bool get_direction_correct[TEST_DIRECTION_COUNT];
	unsigned int get_direction_correct_count = 0;
	for(int i = 0; i < TEST_DIRECTION_COUNT; i++)
	{
		get_direction_correct[i] = false;

		pCanGoDirectionMemberFunction pCanGoDirection = AP_CAN_GO_DIRECTION_FUNCTION[i];
		pGetDirectionMemberFunction   pGetDirection   = AP_GET_DIRECTION_FUNCTION   [i];

		bool can_go_into_open = (world.*pCanGoDirection)(A_TEST_CAN_GO_OPEN[i]);
		if(can_go_into_open)
		{
			Location after_move = (world.*pGetDirection)(A_TEST_CAN_GO_OPEN[i]);

			if(after_move == A_LOCATION_AFTER_GO_OPEN[i])
			{
				get_direction_correct[i] = true;
				get_direction_correct_count++;
			}
			else
				cout << "* Incorrect: Going " << A_DIRECTION_NAME[i] << " into open node goes to wrong position" << endl;
		}
		else
			cout << "* Skipped: Cannot test going " << A_DIRECTION_NAME[i] << " into open node because cannot go that way" << endl;
	}
	if(get_direction_correct_count == TEST_DIRECTION_COUNT)
		cout << "* Correct" << endl;
	cout << endl;

	cout << "Testing getStart" << endl;
	bool correct_get_start = testGetStartNode(world, LOCATION_START);
	cout << endl;


	//
	//  Testing printing messages
	//

	cout << "Testing World::printStartMessage" << endl;
	cout << "--------------------------------------------------------" << endl;
	testHelperStartCapture();
	world.printStartMessage();
	string start_message_captured = testHelperEndCapture();
	cout << "--------------------------------------------------------" << endl;
	bool print_start_message_correct = testMessagePrint(start_message_captured, START_MESSAGE_DESCRIPTION_CORRECT);
	cout << endl;

	cout << "Testing World::printEndMessage" << endl;
	cout << "--------------------------------------------------------" << endl;
	testHelperStartCapture();
	world.printEndMessage();
	string end_message_captured = testHelperEndCapture();
	cout << "--------------------------------------------------------" << endl;
	bool print_end_message_correct = testMessagePrint(end_message_captured, END_MESSAGE_DESCRIPTION_CORRECT);
	cout << endl;

	unsigned int print_description_correct = 0;
	for(unsigned int i = 0; i < TEST_DESCRIPTION_COUNT; i++)
	{
		cout << "Testing message " << A_TEST_DESCRIPTION_NUMBER[i] << " (" << A_TEST_DESCRIPTION_NAME[i] << ")" << endl;
		cout << "--------------------------------------------------------" << endl;
		testHelperStartCapture();
		world.printDescription(A_TEST_DESCRIPTION_LOCATION[i]);
		string captured = testHelperEndCapture();
		cout << "--------------------------------------------------------" << endl;
		bool is_correct = testMessagePrint(captured, A_TEST_DESCRIPTION_CORRECT[i]);
		if(is_correct)
			print_description_correct++;
		cout << endl;
	}


	//
	//  Print results
	//

	unsigned int correct_constants = (correct_max_node_count        ? 1 : 0) +
	                                 (correct_max_description_count ? 1 : 0) +
	                                 (correct_no_such_value         ? 1 : 0);

	double valid_inside_fraction_correct  = (double)(valid_inside_correct ) / (double)(NODE_COUNT_CORRECT);
	double valid_outside_fraction_correct = (double)(valid_outside_correct) / (double)(INVALID_NODE_COUNT);

	testHelperPrintSummaryHeader(28, 1, DID_NOT_CRASH_RUNNING_MARKS);
	testHelperPrintSummaryLine("Constants",                correct_constants, 3);
	testHelperPrintSummaryLine("World size in bytes",      correct_world_bytes);
	testHelperPrintSummaryLine("World::isValid (inside)",  valid_inside_fraction_correct);
	testHelperPrintSummaryLine("World::isValid (outside)", valid_outside_fraction_correct);
	testHelperPrintSummaryLine("World::isDeath",           is_death_correct);
	testHelperPrintSummaryLine("World::isVictory",         is_victory_correct);
	testHelperPrintSummaryLine("World::canGoNorth",        can_go_direction_correct[0]);
	testHelperPrintSummaryLine("World::canGoSouth",        can_go_direction_correct[1]);
	testHelperPrintSummaryLine("World::canGoEast",         can_go_direction_correct[2]);
	testHelperPrintSummaryLine("World::canGoWest",         can_go_direction_correct[3]);
	testHelperPrintSummaryLine("World::getNorth",          get_direction_correct[0]);
	testHelperPrintSummaryLine("World::getSouth",          get_direction_correct[1]);
	testHelperPrintSummaryLine("World::getEast",           get_direction_correct[2]);
	testHelperPrintSummaryLine("World::getWest",           get_direction_correct[3]);
	testHelperPrintSummaryLine("World::getStart",          correct_get_start);
	testHelperPrintSummaryLine("World::printStartMessage", print_start_message_correct);
	testHelperPrintSummaryLine("World::printEndMessage",   print_end_message_correct);
	testHelperPrintSummaryLine("World::printDescription",  print_description_correct, TEST_DESCRIPTION_COUNT);

	unsigned int mark = COMPILE_AND_NOT_CRASH_MARKS;

	if(correct_constants == 3 &&
	   correct_world_bytes &&
	   valid_inside_fraction_correct == 1.0 &&
	   valid_outside_fraction_correct == 1.0)
	{
		mark += 1;
	}
	if(is_death_correct && correct_get_start)
		mark += 1;
	for(int i = 0; i < TEST_DIRECTION_COUNT; i++)
	{
		if(can_go_direction_correct[i] && get_direction_correct[i])
			mark += 1;
	}
	if(correct_get_start &&
	   print_start_message_correct &&
	   print_end_message_correct)
	{
		mark += 1;
	}
	if(print_description_correct == TEST_DESCRIPTION_COUNT)
		mark += 1;

	assert(mark <= TOTAL_MARKS);
	testHelperPrintMark(mark, TOTAL_MARKS);

	testHelperWaitForEnter();
	return 0;
}

bool operator!= (const Location& location1, const Location& location2)
{
	return !(location1 == location2);
}

bool testGetStartNode (const World& world, const Location& desired)
{
	Location found = world.getStart();
	if(found == NO_SUCH_VALUE_CORRECT)
	{
		cout << "* Incorrect: Start node not found" << endl;
		return false;
	}

	if(found != desired)
	{
		cout << "* Incorrect: Start node reported at " << found << ", should be " << desired << endl;
		return false;
	}

	cout << "* Correct" << endl;
	return true;
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
