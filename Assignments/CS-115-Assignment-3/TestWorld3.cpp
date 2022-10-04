//
//  TestWorld3.cpp
//
//  A test program for the World module.
//
//  This program was based on TestWorld1A.cpp, TestWorld1B.cpp,
//    and TestWorld1C.cpp, although it has been significantly
//    changed.  It also loads the Ghostwood world instead of the
//    Blizzard world.
//
//  This program is to be used with Assignment 3: Part B for
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

#include "Location.h"

using namespace std;



int main ();

bool operator!= (const Location& location1, const Location& location2);
bool testGetStartNode (const World& world, const Location& desired);
bool testMessagePrint (const string& printed, const string& correct);

const int COMPILE_AND_START_MARKS     =  2;
const int DID_NOT_CRASH_RUNNING_MARKS =  3;
const int COMPILE_AND_NOT_CRASH_MARKS = COMPILE_AND_START_MARKS + DID_NOT_CRASH_RUNNING_MARKS;
const int COMBINED_TEST_MARKS         = 10;
const int TOTAL_MARKS                 = COMPILE_AND_NOT_CRASH_MARKS + COMBINED_TEST_MARKS;

const int          ROW_COUNT_CORRECT             =   10;
const int          COLUMN_COUNT_CORRECT          =   10;
const unsigned int MAX_DESCRIPTION_COUNT_CORRECT = 1000;

const unsigned int INACCESSIBLE_CORRECT  = 0;
const unsigned int START_MESSAGE_CORRECT = 1;
const unsigned int END_MESSAGE_CORRECT   = 2;
const unsigned int DEATH_NODE_CORRECT    = 3;
const unsigned int START_NODE_CORRECT    = 4;
const unsigned int VICTORY_NODE_CORRECT  = 5;
const unsigned int FIRST_ORDINARY_NODE   = 6;

const unsigned int NODE_COUNT_CORRECT = ROW_COUNT_CORRECT * COLUMN_COUNT_CORRECT;
const unsigned int AA_GHOSTWOOD_CORRECT[ROW_COUNT_CORRECT][COLUMN_COUNT_CORRECT] =
{
	{	3,	33,	0,	35,	0,	0,	3,	51,	50,	0,	},
	{	0,	32,	31,	34,	3,	42,	0,	0,	49,	0,	},
	{	27,	0,	30,	0,	0,	41,	43,	44,	47,	48,	},
	{	26,	0,	30,	0,	39,	40,	0,	45,	46,	0,	},
	{	25,	28,	29,	36,	38,	3,	0,	0,	52,	53,	},
	{	24,	0,	3,	37,	0,	18,	17,	0,	0,	54,	},
	{	23,	22,	0,	0,	8,	0,	16,	0,	0,	54,	},
	{	0,	19,	9,	6,	7,	9,	10,	11,	0,	55,	},
	{	21,	20,	0,	4,	0,	0,	0,	12,	0,	0,	},
	{	0,	0,	0,	5,	0,	0,	14,	13,	15,	3,	},
};

const Location NO_SUCH_VALUE_CORRECT(-1, -1);

const unsigned int TEST_LOCATION_COUNT = 7;
const Location TEST_LOCATIONS[TEST_LOCATION_COUNT] =
{
	Location(0, 2),  // inaccessible
	Location(5, 1),  // inaccessible
	Location(8, 9),  // inaccessible
	Location(0, 0),  // death node
	Location(8, 3),  // start node
	Location(9, 3),  // victory node
	Location(7, 3),  // ordinary node
};

const int INVALID_CHECK_BORDER = 2;
const int INVALID_START        = -INVALID_CHECK_BORDER;
const int INVALID_ROW_END      = ROW_COUNT_CORRECT    + INVALID_CHECK_BORDER;
const int INVALID_COLUMN_END   = COLUMN_COUNT_CORRECT + INVALID_CHECK_BORDER;
const int INVALID_NODE_COUNT   = ((INVALID_ROW_END    - INVALID_START) *
                                  (INVALID_COLUMN_END - INVALID_START)) - NODE_COUNT_CORRECT;

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
//  -> don't do this unless you know what your doing
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

const Location A_TEST_CAN_GO_OFF_EDGE[TEST_DIRECTION_COUNT] =
{
	Location(0, 3),
	Location(9, 1),
	Location(2, 9),
	Location(5, 0),
};

const Location A_TEST_CAN_GO_INACCESSIBLE[TEST_DIRECTION_COUNT] =
{
	Location(4, 1),
	Location(7, 4),
	Location(3, 5),
	Location(4, 8),
};

const Location A_TEST_CAN_GO_OPEN[TEST_DIRECTION_COUNT] =
{
	Location(3, 2),
	Location(5, 6),
	Location(7, 1),
	Location(3, 8),
};

const Location A_LOCATION_AFTER_GO_OPEN[TEST_DIRECTION_COUNT] =
{
	Location(2, 2),
	Location(6, 6),
	Location(7, 2),
	Location(3, 7),
};

const unsigned int TEST_DESCRIPTION_COUNT = 5;
const unsigned int A_TEST_DESCRIPTION_NODE_VALUE[TEST_DESCRIPTION_COUNT] =
{
	START_NODE_CORRECT,
	VICTORY_NODE_CORRECT,
	FIRST_ORDINARY_NODE,
	25,
	55,
};
const string A_TEST_DESCRIPTION_NAME[TEST_DESCRIPTION_COUNT] =
{
	"Start node",
	"Victory node",
	"Node 6",
	"Node 25",
	"Node 55",
};
const Location A_TEST_DESCRIPTION_LOCATION[TEST_DESCRIPTION_COUNT] =
{
	TEST_LOCATIONS[START_NODE_CORRECT],
	TEST_LOCATIONS[VICTORY_NODE_CORRECT],
	TEST_LOCATIONS[FIRST_ORDINARY_NODE],
	Location(4, 0),
	Location(7, 9),
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
	testHelperStartup("TestWorld3", COMPILE_AND_START_MARKS, TOTAL_MARKS);

	//
	//  Test size constants
	//

	cout << "Testing ROW_COUNT" << endl;
	bool correct_row_count = testHelperConstant(ROW_COUNT, ROW_COUNT_CORRECT, "ROW_COUNT");
	cout << endl;

	cout << "Testing COLUMN_COUNT" << endl;
	bool correct_column_count = testHelperConstant(COLUMN_COUNT, COLUMN_COUNT_CORRECT, "COLUMN_COUNT");
	cout << endl;

	cout << "Testing MAX_DESCRIPTION_COUNT" << endl;
	bool correct_max_description_count = testHelperConstant(MAX_DESCRIPTION_COUNT, MAX_DESCRIPTION_COUNT_CORRECT, "MAX_DESCRIPTION_COUNT");
	cout << endl;

	//
	//  Test node value stuff
	//

	cout << "Testing NodeValue type" << endl;
	bool correct_node_value_type = typeid(NodeValue) == typeid(unsigned int);
	if(!correct_node_value_type)
		cout << "* Incorrect: NodeValue should be a typedef for unsigned int" << endl;
	else
		cout << "* Correct" << endl;
	cout << endl;

	cout << "Testing INACCESSIBLE" << endl;
	bool correct_inaccessible = testHelperConstant(INACCESSIBLE, INACCESSIBLE_CORRECT, "INACCESSIBLE");
	cout << endl;

	cout << "Testing START_MESSAGE" << endl;
	bool correct_start_message = testHelperConstant(START_MESSAGE, START_MESSAGE_CORRECT, "START_MESSAGE");
	cout << endl;

	cout << "Testing END_MESSAGE" << endl;
	bool correct_end_message = testHelperConstant(END_MESSAGE, END_MESSAGE_CORRECT, "END_MESSAGE");
	cout << endl;

	cout << "Testing DEATH_NODE" << endl;
	bool correct_death_node = testHelperConstant(DEATH_NODE, DEATH_NODE_CORRECT, "DEATH_NODE");
	cout << endl;

	cout << "Testing START_NODE" << endl;
	bool correct_start_node = testHelperConstant(START_NODE, START_NODE_CORRECT, "START_NODE");
	cout << endl;

	cout << "Testing VICTORY_NODE" << endl;
	bool correct_victory_node = testHelperConstant(VICTORY_NODE, VICTORY_NODE_CORRECT, "VICTORY_NODE");
	cout << endl;


	//
	//  Test World type and constructor
	//

	cout << "Checking World size in bytes" << endl;
	size_t world_bytes              = sizeof(World);
	size_t world_bytes_grid         = sizeof(unsigned int) * NODE_COUNT_CORRECT;
	size_t world_bytes_descriptions = sizeof(string) * MAX_DESCRIPTION_COUNT;
	size_t world_bytes_correct      = sizeof(unsigned int) + world_bytes_grid + world_bytes_descriptions;
	bool correct_world_bytes = false;
	if(world_bytes < world_bytes_grid)
		cout << "* Incorrect: World should contain a 2D array of NodeValues" << endl;
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

	bool is_all_good_so_far = correct_row_count &&
	                          correct_column_count &&
	                          correct_max_description_count &&
	                          correct_node_value_type &&
	                          correct_inaccessible &&
	                          correct_start_message &&
	                          correct_end_message &&
	                          correct_death_node &&
	                          correct_start_node &&
	                          correct_victory_node &&
	                          correct_world_bytes;
	if(is_all_good_so_far)
	{
		cout << "Testing World::debugPrint" << endl;
		cout << "--------------------------------------------------------" << endl;
		world.debugPrint();
		cout << "--------------------------------------------------------" << endl;
		cout << "* Completed without crashing" << endl;
	}
	else
	{
		cout << "Not testing World::debugPrint" << endl;
		cout << "* Output is very long (if correct) and there are other errors above" << endl;
	}
	cout << endl;


	//
	//  Test isValid function
	//

	cout << "Testing if nodes inside the world are valid" << endl;
	unsigned int valid_inside_correct = 0;
	bool is_first_invalid = true;
	for(int r = 0; r < ROW_COUNT_CORRECT; r++)
		for(int c = 0; c < COLUMN_COUNT_CORRECT; c++)
		{
			bool is_valid = world.isValid(Location(r, c));
			if(is_valid)
				valid_inside_correct++;
			else if(is_first_invalid)
			{
				cout << "* Incorrect: Node (" << r << ", " << c << ") not is valid but should be" << endl;
				is_first_invalid = false;
			}
		}
	if(valid_inside_correct == NODE_COUNT_CORRECT)
		cout << "* Correct" << endl;
	cout << endl;

	cout << "Testing if nodes outside the world are invalid" << endl;
	unsigned int valid_outside_correct = 0;
	bool is_first_valid = true;
	for(int r = INVALID_START; r < INVALID_ROW_END; r++)
		for(int c = INVALID_START; c < INVALID_COLUMN_END; c++)
		{
			if(r >= 0 && r < ROW_COUNT_CORRECT)
				if(c >= 0 && c < COLUMN_COUNT_CORRECT)
					continue;  // already checked above

			bool is_valid = world.isValid(Location(r, c));
			if(!is_valid)
				valid_outside_correct++;
			else if(is_first_valid)
			{
				cout << "* Incorrect: Node (" << r << ", " << c << ") is valid but should not be" << endl;
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
		bool should_be_death = i == DEATH_NODE_CORRECT;
		if(world.isDeath(TEST_LOCATIONS[i]) != should_be_death)
		{
			if(is_death_correct)  // first time obly
			{
				unsigned int node_value = AA_GHOSTWOOD_CORRECT[TEST_LOCATIONS[i].row   ]
				                                              [TEST_LOCATIONS[i].column];
				if(should_be_death)
					cout << "* Incorrect: Node value " << node_value << " reported as death node, shouldn't be" << endl;
				else
					cout << "* Incorrect: Node value " << node_value << " not reported as death node, should be" << endl;
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
		bool should_be_victory = i == VICTORY_NODE_CORRECT;
		if(world.isVictory(TEST_LOCATIONS[i]) != should_be_victory)
		{
			if(is_victory_correct)  // first time obly
			{
				unsigned int node_value = AA_GHOSTWOOD_CORRECT[TEST_LOCATIONS[i].row   ]
				                                              [TEST_LOCATIONS[i].column];
				if(should_be_victory)
					cout << "* Incorrect: Node value " << node_value << " reported as victory node, shouldn't be" << endl;
				else
					cout << "* Incorrect: Node value " << node_value << " not reported as victory node, should be" << endl;
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

	cout << "Testing World::canGoNorth, etc. functions" << endl;
	bool can_go_direction_correct[TEST_DIRECTION_COUNT];
	unsigned int can_go_direction_correct_count = 0;
	for(int i = 0; i < TEST_DIRECTION_COUNT; i++)
	{
		can_go_direction_correct[i] = true;

		pCanGoDirectionMemberFunction pCanGoDirection = AP_CAN_GO_DIRECTION_FUNCTION[i];

		bool can_go_off_edge = (world.*pCanGoDirection)(A_TEST_CAN_GO_OFF_EDGE[i]);
		if(can_go_off_edge)
		{
			cout << "* Incorrect: Returns true for going " << A_DIRECTION_NAME[i] << " off map edge" << endl;
			can_go_direction_correct[i] = false;
		}

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
			cout << "* Incorrect: Cannot test going " << A_DIRECTION_NAME[i] << " into open node because cannot go that way" << endl;
	}
	if(get_direction_correct_count == TEST_DIRECTION_COUNT)
		cout << "* Correct" << endl;
	cout << endl;


	//
	//  Test World::findValue
	//

	cout << "Testing NO_SUCH_VALUE" << endl;
	bool correct_no_such_value = testHelperConstant(NO_SUCH_VALUE, NO_SUCH_VALUE_CORRECT, "NO_SUCH_VALUE");
	cout << endl;

	cout << "Testing getStart" << endl;
	bool correct_get_start = testGetStartNode(world, TEST_LOCATIONS[START_NODE_CORRECT]);
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
		cout << "Testing message " << A_TEST_DESCRIPTION_NODE_VALUE[i] << " (" << A_TEST_DESCRIPTION_NAME[i] << ")" << endl;
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

	unsigned int correct_sizes = (correct_row_count             ? 1 : 0) +
	                             (correct_column_count          ? 1 : 0) +
	                             (correct_max_description_count ? 1 : 0);

	unsigned int correct_node_constants = (correct_inaccessible  ? 1 : 0) +
	                                      (correct_start_message ? 1 : 0) +
	                                      (correct_end_message   ? 1 : 0) +
	                                      (correct_death_node    ? 1 : 0) +
	                                      (correct_start_node    ? 1 : 0) +
	                                      (correct_victory_node  ? 1 : 0);

	double valid_inside_fraction_correct  = (double)(valid_inside_correct ) / (double)(NODE_COUNT_CORRECT);
	double valid_outside_fraction_correct = (double)(valid_outside_correct) / (double)(INVALID_NODE_COUNT);

	bool can_go_all_directions_correct = true;
	for(int i = 0; i < TEST_DIRECTION_COUNT; i++)
		if(!can_go_direction_correct[i])
			can_go_all_directions_correct = false;

	testHelperPrintSummaryHeader(28, 1, DID_NOT_CRASH_RUNNING_MARKS);
	testHelperPrintSummaryLine("World size constants",     correct_sizes,          3);
	testHelperPrintSummaryLine("Node value constants",     correct_node_constants, 6);
	testHelperPrintSummaryLine("NodeValue declaration",    correct_node_value_type);
	testHelperPrintSummaryLine("World size in bytes",      correct_world_bytes);
	testHelperPrintSummaryLine("world::isValid (inside)",  valid_inside_fraction_correct);
	testHelperPrintSummaryLine("world::isValid (outside)", valid_outside_fraction_correct);
	testHelperPrintSummaryLine("world::isDeath",           is_death_correct);
	testHelperPrintSummaryLine("world::isVictory",         is_victory_correct);
	testHelperPrintSummaryLine("world::canGoNorth",        can_go_direction_correct[0]);
	testHelperPrintSummaryLine("world::canGoSouth",        can_go_direction_correct[1]);
	testHelperPrintSummaryLine("world::canGoEast",         can_go_direction_correct[2]);
	testHelperPrintSummaryLine("world::canGoWest",         can_go_direction_correct[3]);
	testHelperPrintSummaryLine("world::getNorth",          get_direction_correct[0]);
	testHelperPrintSummaryLine("world::getSouth",          get_direction_correct[1]);
	testHelperPrintSummaryLine("world::getEast",           get_direction_correct[2]);
	testHelperPrintSummaryLine("world::getWest",           get_direction_correct[3]);
	testHelperPrintSummaryLine("NO_SUCH_VALUE constant",   correct_no_such_value);
	testHelperPrintSummaryLine("world::getStart",          correct_get_start);
	testHelperPrintSummaryLine("world::printStartMessage", print_start_message_correct);
	testHelperPrintSummaryLine("world::printEndMessage",   print_end_message_correct);
	testHelperPrintSummaryLine("world::printDescription",  print_description_correct, TEST_DESCRIPTION_COUNT);

	unsigned int mark = COMPILE_AND_NOT_CRASH_MARKS;

	if(correct_sizes          == 3 &&
	   correct_node_constants == 6 &&
	   correct_node_value_type &&
	   correct_world_bytes)
	{
		mark += 1;
	}

	if(valid_inside_fraction_correct == 1.0 && valid_outside_fraction_correct == 1.0)
		mark += 1;
	if(is_death_correct && is_victory_correct && can_go_all_directions_correct)
		mark += 1;
	for(int i = 0; i < TEST_DIRECTION_COUNT; i++)
		if(get_direction_correct[i])  // new in A3
			mark += 1;
	if(correct_no_such_value && correct_get_start)
		mark += 1;

	if(print_start_message_correct && print_end_message_correct)
		mark += 1;
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

	bool correct_row    = found.row    == desired.row;
	bool correct_column = found.column == desired.column;
	if(!correct_row)
	{
		if(!correct_column)
		{
			cout << "* Incorrect: Start node found at (" << found.row << ", " << found.column
			     << "), should be (" << desired.row << ", " << desired.column << ")" << endl;
		}
		else
			cout << "* Incorrect: Start node found at row " << found.row << ", should be " << desired.row << endl;
	}
	else
	{
		if(!correct_column)
			cout << "* Incorrect: Start node found at column " << found.column << ", should be " << desired.column << endl;
		// else correct will be printed by main
	}

	return correct_row && correct_column;
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
