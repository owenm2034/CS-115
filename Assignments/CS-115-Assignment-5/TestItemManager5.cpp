//
//  TestItemManager5.cpp
//
//  A test program for the ItemManager module.
//
//  This program is based on TestItemManager4.cpp, although it
//    has been expanded to also test the canonical functions.
//
//  This program is to be used with Assignment 5: Part A for
//    CS115, 202210.
//
//  Do not modify this file.
//
//  2022-03-25: Maximum marks increased from 35 to 45
//

#include "ItemManager.h"
#include "ItemManager.h"  // repeated to test for #include errors

#include <cassert>
#include <climits>
#include <string>
#include <iostream>
#include <iomanip>
#include <typeinfo>  // for typeid
#include <sstream>
#include <vector>

#include "TestHelper.h"

#include "Location.h"
#include "Item.h"

using namespace std;
namespace
{
	struct Result
	{
		int desired_count;
		int other_descr_count;
		int bad_descr_count;
		int missing_count;
		int extra_count;
		int unsorted_count;
	};

}



int main ();

int calculateCorrectScore (unsigned int present_bits);
Result testInventoryPrint (const string& printed,
                           unsigned int present_bits);
Result testLocationPrint (const string& printed,
                          unsigned int present_bits,
                          const Location& location,
                          bool is_print_incorrect);
unsigned int getIndexInVector(const vector<string>& search_in,
                              const string& search_for);
unsigned int getIndexWithPhrase (const vector<string>& search_in,
                                 const string& phrase);
void printLineDifference (const string& line1,
                          const string& line2,
                          char item_id, const string& description_name);
bool isResultAllCorrect (const Result& result);
double getResultMark (const Result& result);
unsigned int calculateScore (bool correct_count_default,
                             bool correct_score_default,
                             bool correct_inventory_default,
                             double correct_location_default_fraction,
                             bool correct_count1,
                             bool correct_score1,
                             double correct_inventory1_fraction,
                             double correct_location1_fraction,
                             bool correct_count_copy,
                             bool correct_count_assign,
                             double correct_location_delete_fraction,
                             double correct_location_self_fraction,
                             double correct_location_chained_fraction,
                             bool correct_count2,
                             bool correct_score2,
                             double correct_inventory2_fraction,
                             double correct_location2_fraction,
                             bool correct_count3,
                             bool correct_score3,
                             double correct_inventory3_fraction,
                             double correct_location3_0_fraction,
                             double correct_location3_1_fraction,
                             double correct_location3_rest_fraction,
                             bool is_finished_without_crash);

const int COMPILE_AND_START_MARKS      =   7;
const int DID_NOT_CRASH_RUNNING_MARKS  =   8;
const int COMPILE_AND_NOT_CRASH_MARKS  = COMPILE_AND_START_MARKS + DID_NOT_CRASH_RUNNING_MARKS;
const int COMBINED_TEST_MARKS          =  30;
const int TOTAL_MARKS                  = COMPILE_AND_NOT_CRASH_MARKS + COMBINED_TEST_MARKS;
const int DESCRIPTIONS_IN_FILE_PENALTY = -10;
const int LINEAR_SEARCH_PENALTY        =  -5;

const unsigned int NOT_IN_ANY_LINE       = UINT_MAX;
const unsigned int ERROR_STRING_PADDING = 8;

const unsigned int ITEM_COUNT_DEFAULT = 0;
const int          ITEM_SCORE_DEFAULT = 0;

// we are not using Jungle because it has stacked items
const unsigned int ITEM_COUNT_GHOSTWOOD = 9;

const unsigned int TEST_LOCATION_COUNT = ITEM_COUNT_GHOSTWOOD + 1;
const Location TEST_LOCATION[TEST_LOCATION_COUNT] =
{
	Location(22),
	Location(7),
	Location(53),
	Location(13),
	Location(37),
	Location(52),
	Location(58),
	Location(3),
	Location(19),
	Location(0),  // inaccessible
};

const char ITEM_ID_CORRECT[ITEM_COUNT_GHOSTWOOD] =
{
	'b',
	'c',
	'd',
	'k',
	'm',
	'p',
	'r',
	's',
	't',
};

const int ITEM_SCORE_CORRECT[ITEM_COUNT_GHOSTWOOD] =
{
	4,
	9,
	1,
	3,
	-2,
	7,
	10,
	-5,
	-8,
};

const string ITEM_GROUND_DESCRIPTION_CORRECT[ITEM_COUNT_GHOSTWOOD] =
{
	"There is a book (b) here with an eye drawn on the cover.",
	"There is a silver candlestick (c) here.",
	"There is a rune-carved dagger (d) here.",
	"There is an old iron key (k) here.",
	"There is a giant moth (m) sleeping here.",
	"There is a golden pendant (p) here.",
	"There is a diamond ring (r) here.",
	"There is a black scarab beetle (s) here.",
	"There is a tarantula (t) here.",
};

const string ITEM_INVENTORY_DESCRIPTION_CORRECT[ITEM_COUNT_GHOSTWOOD] =
{
	"You have a book (b) under your arm with an eye drawn on the cover.",
	"You are carrying a silver candlestick (c).",
	"You have a rune-carved dagger (d) stuck in your belt.",
	"You have an old iron key (k) in your pocket.",
	"A giant moth (m) is perched on your shoulder.",
	"You are wearing a golden pendant (p).",
	"You are wearing a diamond ring (r).",
	"A black scarab beetle (s) is crawling up your arm.",
	"There is a tarantula (t) hanging on your shirt.",
};

const unsigned int STRING_NOT_IN_VECTOR = UINT_MAX;



int main ()
{
	testHelperStartup("TestItemManager5", COMPILE_AND_START_MARKS, TOTAL_MARKS);


	//
	//  Test default constructor
	//

	cout << "Creating ItemManager with default constructor" << endl;
	cout << "---------------------------------------------" << endl;
	cout << endl;

	cout << "Creating an ItemManager with the default constructor" << endl;
	ItemManager* p_item_manager_1 = new ItemManager();
	cout << "* Created without crashing" << endl;
	cout << endl;

	cout << "Testing getCount" << endl;
	unsigned int reported_count0 = p_item_manager_1->getCount();
	bool correct_count0 = reported_count0 == ITEM_COUNT_DEFAULT;
	if(!correct_count0)
		cout << "* Incorrect: Item count is " << reported_count0 << ", should be " << ITEM_COUNT_DEFAULT << endl;
	else
		cout << "* Correct" << endl;
	cout << endl;

	cout << "Testing getScore" << endl;
	int reported_score0 = p_item_manager_1->getScore();
	bool correct_score0 = reported_score0 == 0;
	if(!correct_score0)
		cout << "* Incorrect: Score is " << reported_score0 << ", should be " << ITEM_SCORE_DEFAULT << endl;
	else
		cout << "* Correct" << endl;
	cout << endl;

	cout << "Testing printInventory" << endl;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_item_manager_1->printInventory();
	string captured_inventory0 = testHelperEndCapture();
	cout << "----------------------------------------------------------------" << endl;
	bool correct_inventory0 = captured_inventory0 == "";
	if(correct_inventory0)
		cout << "* Correct" << endl;
	cout << endl;

	cout << "Testing printAtLocation (at " << TEST_LOCATION_COUNT << " locations)" << endl;
	int correct_location0 = 0;
	for(unsigned int i = 0; i < TEST_LOCATION_COUNT; i++)
	{
		testHelperStartCapture();
		p_item_manager_1->printAtLocation(TEST_LOCATION[i]);
		string captured_location0 = testHelperEndCapture(false);

		bool correct_here = captured_location0 == "";
		if(correct_here)
			correct_location0++;
		else if(correct_location0 == i)  // first time only
		{
			cout << "----------------------------------------------------------------" << endl;
			cout << captured_location0;
			cout << "----------------------------------------------------------------" << endl;
			cout << "* Incorrect: Should be no items at location " << TEST_LOCATION[i] << endl;
		}
	}
	if(correct_location0 == TEST_LOCATION_COUNT)
		cout << "* Correct" << endl;
	else if(correct_location0 + 1 < TEST_LOCATION_COUNT)
	{
		cout << "* " << setw(2) << (TEST_LOCATION_COUNT - 1 - correct_location0) << " more (of "
		     << setw(2) << TEST_LOCATION_COUNT << ") locations with items" << endl;
	}
	cout << endl;

	cout << endl;
	cout << endl;


	//
	//  Print results (1)
	//

	unsigned int correct_count_count = correct_count0 ? 1 : 0;
	unsigned int correct_score_count = correct_score0 ? 1 : 0;

	double correct_location0_fraction = (double)(correct_location0) / TEST_LOCATION_COUNT;

	testHelperPrintSummaryHeaderPartial(28, 1, COMPILE_AND_START_MARKS);
	testHelperPrintSummaryLine("getCount",                   correct_count_count, 1);
	testHelperPrintSummaryLine("getScore",                   correct_score_count, 1);
	testHelperPrintSummaryLine("printInventory  (default)",  correct_inventory0);
	testHelperPrintSummaryLine("printAtLocation (default)",  correct_location0_fraction);

	unsigned int highest1 = calculateScore(true, true, true, 1.0,
	                                       false, false, 0.0, 0.0,            // load from file
	                                       false, false, 0.0, 0.0, 0.0,       // canonical functions
	                                       false, false, 0.0, 0.0,            // take items
	                                       false, false, 0.0, 0.0, 0.0, 0.0,  // leave items
	                                       false);                            // all finished
	unsigned int mark1 = calculateScore(correct_count0, correct_score0,
	                                    correct_inventory0, correct_location0_fraction,
	                                    false, false, 0.0, 0.0,            // load from file
	                                    false, false, 0.0, 0.0, 0.0,       // canonical functions
	                                    false, false, 0.0, 0.0,            // take items
	                                    false, false, 0.0, 0.0, 0.0, 0.0,  // leave items
	                                    false);                            // all finished
	assert(mark1 <= TOTAL_MARKS);
	testHelperPrintMarkPartial(mark1, highest1, TOTAL_MARKS);

	cout << endl;
	cout << endl;


	//
	//  Test initializing constructor
	//

	cout << "Loading items from a file" << endl;
	cout << "-------------------------" << endl;
	cout << endl;

	cout << "Creating an ItemManager with the initializing constructor" << endl;
	ItemManager* p_item_manager_2 = new ItemManager("ghostwood");
	cout << "* Created without crashing" << endl;
	cout << endl;

	cout << "Testing getCount" << endl;
	unsigned int reported_count1 = p_item_manager_2->getCount();
	bool correct_count1 = reported_count1 == ITEM_COUNT_GHOSTWOOD;
	if(!correct_count1)
		cout << "* Incorrect: Item count is " << reported_count1 << ", should be " << ITEM_COUNT_GHOSTWOOD << endl;
	else
		cout << "* Correct" << endl;
	cout << endl;

	cout << "Testing getScore" << endl;
	int desired_score1  = calculateCorrectScore(0x000);
	int reported_score1 = p_item_manager_2->getScore();
	bool correct_score1 = reported_score1 == desired_score1;
	if(!correct_score1)
		cout << "* Incorrect: Score is " << reported_score1 << ", should be " << desired_score1 << endl;
	else
		cout << "* Correct" << endl;
	cout << endl;

	cout << "Testing printInventory" << endl;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_item_manager_2->printInventory();
	string captured_inventory1 = testHelperEndCapture();
	cout << "----------------------------------------------------------------" << endl;
	Result result_inventory1 = testInventoryPrint(captured_inventory1, 0x000);
	if(isResultAllCorrect(result_inventory1))
		cout << "* Correct" << endl;
	cout << endl;

	Result result_location1[TEST_LOCATION_COUNT];
	for(unsigned int i = 0; i < TEST_LOCATION_COUNT; i++)
	{
		cout << "Testing printAtLocation at " << TEST_LOCATION[i] << endl;
		cout << "----------------------------------------------------------------" << endl;
		testHelperStartCapture();
		p_item_manager_2->printAtLocation(TEST_LOCATION[i]);
		string captured_location = testHelperEndCapture();
		cout << "----------------------------------------------------------------" << endl;

		unsigned int present_bits = 0x0;
		if(i < ITEM_COUNT_GHOSTWOOD)
			present_bits = 0x1 << i;
		result_location1[i] = testLocationPrint(captured_location, present_bits, TEST_LOCATION[i], true);

		if(isResultAllCorrect(result_location1[i]))
			cout << "* Correct" << endl;
		cout << endl;
	}

	cout << endl;
	cout << endl;


	//
	//  Print results (2)
	//

	correct_count_count += correct_count1 ? 1 : 0;
	correct_score_count += correct_score1 ? 1 : 0;

	double correct_inventory1_fraction = getResultMark(result_inventory1);

	double correct_location1_fraction = 0.0;
	for(unsigned int i = 0; i < TEST_LOCATION_COUNT; i++)
		correct_location1_fraction += getResultMark(result_location1[i]);
	correct_location1_fraction /= TEST_LOCATION_COUNT;

	testHelperPrintSummaryHeaderPartial(28, 1, COMPILE_AND_START_MARKS);
	testHelperPrintSummaryLine("getCount",                   correct_count_count, 2);
	testHelperPrintSummaryLine("getScore",                   correct_score_count, 2);
	testHelperPrintSummaryLine("printInventory  (default)",  correct_inventory0);
	testHelperPrintSummaryLine("printAtLocation (default)",  correct_location0_fraction);
	testHelperPrintSummaryLine("printInventory  (loaded)",   correct_inventory1_fraction);
	testHelperPrintSummaryLine("printAtLocation (loaded)",   correct_location1_fraction);

	unsigned int highest2 = calculateScore(true, true, true, 1.0,
	                                       true, true, 1.0, 1.0,
	                                       false, false, 0.0, 0.0, 0.0,       // canonical functions
	                                       false, false, 0.0, 0.0,            // take items
	                                       false, false, 0.0, 0.0, 0.0, 0.0,  // leave items
	                                       false);                            // all finished
	unsigned int mark2 = calculateScore(correct_count0, correct_score0,
	                                    correct_inventory0, correct_location0_fraction,
	                                    correct_count1, correct_score1,
	                                    correct_inventory1_fraction, correct_location1_fraction,
	                                    false, false, 0.0, 0.0, 0.0,       // canonical functions
	                                    false, false, 0.0, 0.0,            // take items
	                                    false, false, 0.0, 0.0, 0.0, 0.0,  // leave items
	                                    false);                            // all finished
	assert(mark2 <= TOTAL_MARKS);
	testHelperPrintMarkPartial(mark2, highest2, TOTAL_MARKS);

	cout << endl;
	cout << endl;


	//
	//  Test canonical functions
	//

	cout << "Testing copy constructor" << endl;
	cout << "------------------------" << endl;
	cout << endl;

	cout << "Creating an ItemManager with the copy constructor" << endl;
	ItemManager* p_item_manager_3 = new ItemManager(*p_item_manager_2);
	cout << "* Created without crashing" << endl;
	unsigned int reported_count_copy = p_item_manager_3->getCount();
	bool correct_count_copy = reported_count_copy == ITEM_COUNT_GHOSTWOOD;
	if(!correct_count_copy)
		cout << "* Incorrect: Item count is " << reported_count_copy << ", should be " << ITEM_COUNT_GHOSTWOOD << endl;
	else
		cout << "* Correct" << endl;
	cout << endl;

	cout << "Assigning an ItemManager with the assignment operator (operator==)" << endl;
	*p_item_manager_1 = *p_item_manager_3;
	cout << "* Assigned without crashing" << endl;
	unsigned int reported_count_assign = p_item_manager_1->getCount();
	bool correct_count_assign = reported_count_assign == ITEM_COUNT_GHOSTWOOD;
	if(!correct_count_assign)
		cout << "* Incorrect: Item count is " << reported_count_assign << ", should be " << ITEM_COUNT_GHOSTWOOD << endl;
	else
		cout << "* Correct" << endl;
	cout << endl;

	cout << "Destroying ItemManager" << endl;
	delete p_item_manager_3;
	p_item_manager_3 = NULL;
	cout << "* Destroyed without crashing" << endl;
	cout << endl;

	cout << "Testing printAtLocation for other ItemManagers" << endl;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_item_manager_1->printAtLocation(TEST_LOCATION[0]);
	string captured_location_delete1 = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	Result result_delete1 = testLocationPrint(captured_location_delete1, 0x001, TEST_LOCATION[0], true);
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_item_manager_2->printAtLocation(TEST_LOCATION[1]);
	string captured_location_delete2 = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	Result result_delete2 = testLocationPrint(captured_location_delete2, 0x002, TEST_LOCATION[1], true);
	if(isResultAllCorrect(result_delete1) && isResultAllCorrect(result_delete2))
		cout << "* Correct" << endl;
	cout << endl;

	cout << "Testing self-assignment" << endl;
	*p_item_manager_1 = *p_item_manager_1;
	cout << "* Assigned without crashing" << endl;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_item_manager_1->printAtLocation(TEST_LOCATION[2]);
	string captured_location_self = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	Result result_self = testLocationPrint(captured_location_self, 0x004, TEST_LOCATION[2], true);
	if(isResultAllCorrect(result_self))
		cout << "* Correct" << endl;
	cout << endl;

	cout << "Testing chained-assignment" << endl;
	*p_item_manager_1 = *p_item_manager_1 = *p_item_manager_1;
	cout << "* Assigned without crashing" << endl;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_item_manager_1->printAtLocation(TEST_LOCATION[3]);
	string captured_location_chained = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	Result result_chained = testLocationPrint(captured_location_chained, 0x008, TEST_LOCATION[3], true);
	if(isResultAllCorrect(result_chained))
		cout << "* Correct" << endl;
	cout << endl;

	cout << endl;
	cout << endl;


	//
	//  Print results (3)
	//

	double correct_location_delete_fraction  = (getResultMark(result_delete1) +
	                                            getResultMark(result_delete2)) / 2;
	double correct_location_self_fraction    =  getResultMark(result_self);
	double correct_location_chained_fraction =  getResultMark(result_chained);

	testHelperPrintSummaryHeaderPartial(28, 1, COMPILE_AND_START_MARKS);
	testHelperPrintSummaryLine("getCount",                   correct_count_count, 2);
	testHelperPrintSummaryLine("getScore",                   correct_score_count, 2);
	testHelperPrintSummaryLine("printInventory  (default)",  correct_inventory0);
	testHelperPrintSummaryLine("printAtLocation (default)",  correct_location0_fraction);
	testHelperPrintSummaryLine("printInventory  (loaded)",   correct_inventory1_fraction);
	testHelperPrintSummaryLine("printAtLocation (loaded)",   correct_location1_fraction);
	testHelperPrintSummaryLine("Copy constructor",           correct_count_copy);
	testHelperPrintSummaryLine("Assignment operator",        correct_count_assign);
	testHelperPrintSummaryLine("Locations after delete",     correct_location_delete_fraction);
	testHelperPrintSummaryLine("Self-assignment",            correct_location_self_fraction);
	testHelperPrintSummaryLine("Chained assignment",         correct_location_chained_fraction);

	unsigned int highest3 = calculateScore(true, true, true, 1.0,
	                                       true, true, 1.0, 1.0,
	                                       true, true, 1.0, 1.0, 1.0,
	                                       false, false, 0.0, 0.0,            // take items
	                                       false, false, 0.0, 0.0, 0.0, 0.0,  // leave items
	                                       false);                            // all finished
	unsigned int mark3 = calculateScore(correct_count0, correct_score0,
	                                    correct_inventory0, correct_location0_fraction,
	                                    correct_count1, correct_score1,
	                                    correct_inventory1_fraction, correct_location1_fraction,
	                                    correct_count_copy, correct_count_assign,
	                                    correct_location_delete_fraction, correct_location_self_fraction, correct_location_chained_fraction,
	                                    false, false, 0.0, 0.0,            // take items
	                                    false, false, 0.0, 0.0, 0.0, 0.0,  // leave items
	                                    false);                            // all finished
	assert(mark3 <= TOTAL_MARKS);
	testHelperPrintMarkPartial(mark3, highest3, TOTAL_MARKS);

	cout << endl;
	cout << endl;


	//
	//  Test taking items
	//

	cout << "With all items in inventory" << endl;
	cout << "---------------------------" << endl;
	cout << endl;

	cout << "Taking all items" << endl;
	for(unsigned int i = 0; i < ITEM_COUNT_GHOSTWOOD; i++)
		p_item_manager_2->take(ITEM_ID_CORRECT[i], TEST_LOCATION[i]);
	cout << "* Completed without crashing" << endl;
	cout << endl;

	cout << "Testing getCount" << endl;
	unsigned int reported_count2 = p_item_manager_2->getCount();
	bool correct_count2 = reported_count2 == ITEM_COUNT_GHOSTWOOD;
	if(!correct_count2)
		cout << "* Incorrect: Item count is " << reported_count2 << ", should be " << ITEM_COUNT_GHOSTWOOD << endl;
	else
		cout << "* Correct" << endl;
	cout << endl;

	cout << "Testing getScore" << endl;
	int desired_score2  = calculateCorrectScore(0x1FF);
	int reported_score2 = p_item_manager_2->getScore();
	bool correct_score2 = reported_score2 == desired_score2;
	if(!correct_score2)
		cout << "* Incorrect: Score is " << reported_score2 << ", should be " << desired_score2 << endl;
	else
		cout << "* Correct" << endl;
	cout << endl;

	cout << "Testing printInventory" << endl;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_item_manager_2->printInventory();
	string captured_inventory2 = testHelperEndCapture();
	cout << "----------------------------------------------------------------" << endl;
	Result result_inventory2 = testInventoryPrint(captured_inventory2, 0x1FF);
	if(isResultAllCorrect(result_inventory2))
		cout << "* Correct" << endl;
	cout << endl;

	cout << "Testing printAtLocation at all locations" << endl;
	Result result_location2[TEST_LOCATION_COUNT];
	int location2_wrong_count = 0;
	for(unsigned int i = 0; i < TEST_LOCATION_COUNT; i++)
	{
		testHelperStartCapture();
		p_item_manager_2->printAtLocation(TEST_LOCATION[i]);
		string captured_location = testHelperEndCapture(false);

		bool is_print_incorrect = location2_wrong_count == 0;
		result_location2[i] = testLocationPrint(captured_location, 0x000, TEST_LOCATION[i], is_print_incorrect);
		if(!isResultAllCorrect(result_location2[i]))
			location2_wrong_count++;
	}
	if(location2_wrong_count == 0)
		cout << "* Correct" << endl;
	else if(location2_wrong_count > 1)
		cout << "* Errors at " << (location2_wrong_count - 1) << " more locations" << endl;
	cout << endl;

	cout << endl;
	cout << endl;


	//
	//  Test leaving items
	//

	cout << "With items in 3 groups" << endl;
	cout << "----------------------" << endl;
	cout << endl;

	cout << "Leaving 2 groups of items" << endl;
	for(unsigned int i = 0; i < ITEM_COUNT_GHOSTWOOD; i++)
	{
		switch(i % 3)
		{
		case 0:
			p_item_manager_2->leave(ITEM_ID_CORRECT[i], TEST_LOCATION[0]);
			break;
		case 1:
			p_item_manager_2->leave(ITEM_ID_CORRECT[i], TEST_LOCATION[1]);
			break;
		case 2:
			// item stays in inventory
			break;
		}
	}
	cout << "* Completed without crashing" << endl;
	cout << endl;

	cout << "Testing getCount" << endl;
	unsigned int reported_count3 = p_item_manager_2->getCount();
	bool correct_count3 = reported_count3 == ITEM_COUNT_GHOSTWOOD;
	if(!correct_count3)
		cout << "* Incorrect: Item count is " << reported_count3 << ", should be " << ITEM_COUNT_GHOSTWOOD << endl;
	else
		cout << "* Correct" << endl;
	cout << endl;

	cout << "Testing getScore" << endl;
	int desired_score3  = calculateCorrectScore(0x124);
	int reported_score3 = p_item_manager_2->getScore();
	bool correct_score3 = reported_score3 == desired_score3;
	if(!correct_score3)
		cout << "* Incorrect: Score is " << reported_score3 << ", should be " << desired_score3 << endl;
	else
		cout << "* Correct" << endl;
	cout << endl;

	cout << "Testing printInventory" << endl;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_item_manager_2->printInventory();
	string captured_inventory3 = testHelperEndCapture();
	cout << "----------------------------------------------------------------" << endl;
	Result result_inventory3 = testInventoryPrint(captured_inventory3, 0x124);
	if(isResultAllCorrect(result_inventory3))
		cout << "* Correct" << endl;
	cout << endl;

	Result result_location3[TEST_LOCATION_COUNT];
	cout << "Testing printAtLocation at location " << TEST_LOCATION[0] << endl;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_item_manager_2->printAtLocation(TEST_LOCATION[0]);
	string captured_location3 = testHelperEndCapture();
	cout << "----------------------------------------------------------------" << endl;
	result_location3[0] = testLocationPrint(captured_location3, 0x049, TEST_LOCATION[0], true);
	if(isResultAllCorrect(result_location3[0]))
		cout << "* Correct" << endl;
	cout << endl;

	cout << "Testing printAtLocation at location " << TEST_LOCATION[1] << endl;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_item_manager_2->printAtLocation(TEST_LOCATION[1]);
	string captured_location4 = testHelperEndCapture();
	cout << "----------------------------------------------------------------" << endl;
	result_location3[1] = testLocationPrint(captured_location4, 0x092, TEST_LOCATION[1], true);
	if(isResultAllCorrect(result_location3[0]))
		cout << "* Correct" << endl;
	cout << endl;

	cout << "Testing printAtLocation at all other locations" << endl;
	int location3_wrong_count = 0;
	for(unsigned int i = 2; i < TEST_LOCATION_COUNT; i++)
	{
		testHelperStartCapture();
		p_item_manager_2->printAtLocation(TEST_LOCATION[i]);
		string captured_location = testHelperEndCapture(false);

		bool is_print_incorrect = location3_wrong_count == 0;
		result_location3[i] = testLocationPrint(captured_location, 0x000, TEST_LOCATION[i], is_print_incorrect);
		if(!isResultAllCorrect(result_location3[i]))
			location3_wrong_count++;
	}
	if(location3_wrong_count == 0)
		cout << "* Correct" << endl;
	else if(location3_wrong_count > 1)
		cout << "* Errors at " << (location3_wrong_count - 1) << " more locations" << endl;
	cout << endl;

	cout << endl;
	cout << endl;

	//
	//  Print results (4)
	//

	correct_count_count += (correct_count2 ? 1 : 0) +
	                       (correct_count3 ? 1 : 0);
	correct_score_count += (correct_score2 ? 1 : 0) +
	                       (correct_score3 ? 1 : 0);

	double correct_inventory2_fraction = getResultMark(result_inventory2);
	double correct_inventory3_fraction = getResultMark(result_inventory3);

	double correct_location2_fraction = 0.0;
	for(unsigned int i = 0; i < TEST_LOCATION_COUNT; i++)
		correct_location2_fraction += getResultMark(result_location2[i]);
	correct_location2_fraction /= TEST_LOCATION_COUNT;

	double correct_location3_0_fraction    = getResultMark(result_location3[0]);
	double correct_location3_1_fraction    = getResultMark(result_location3[1]);
	double correct_location3_rest_fraction = 0.0;
	for(unsigned int i = 2; i < TEST_LOCATION_COUNT; i++)
		correct_location3_rest_fraction += getResultMark(result_location3[i]);
	correct_location3_rest_fraction /= (TEST_LOCATION_COUNT - 2);

	testHelperPrintSummaryHeaderPartial(28, 1, COMPILE_AND_START_MARKS);
	testHelperPrintSummaryLine("getCount",                   correct_count_count, 4);
	testHelperPrintSummaryLine("getScore",                   correct_score_count, 4);
	testHelperPrintSummaryLine("printInventory  (default)",  correct_inventory0);
	testHelperPrintSummaryLine("printAtLocation (default)",  correct_location0_fraction);
	testHelperPrintSummaryLine("printInventory  (loaded)",   correct_inventory1_fraction);
	testHelperPrintSummaryLine("printAtLocation (loaded)",   correct_location1_fraction);
	testHelperPrintSummaryLine("Copy constructor",           correct_count_copy);
	testHelperPrintSummaryLine("Assignment operator",        correct_count_assign);
	testHelperPrintSummaryLine("Locations after delete",     correct_location_delete_fraction);
	testHelperPrintSummaryLine("Self-assignment",            correct_location_self_fraction);
	testHelperPrintSummaryLine("Chained assignment",         correct_location_chained_fraction);
	testHelperPrintSummaryLine("printInventory  (taken)",    correct_inventory2_fraction);
	testHelperPrintSummaryLine("printAtLocation (taken)",    correct_location2_fraction);
	testHelperPrintSummaryLine("printInventory  (groups)",   correct_inventory3_fraction);
	testHelperPrintSummaryLine("printAtLocation (group 1)",  correct_location3_0_fraction);
	testHelperPrintSummaryLine("printAtLocation (group 2)",  correct_location3_1_fraction);
	testHelperPrintSummaryLine("printAtLocation (no group)", correct_location3_rest_fraction);

	unsigned int highest4 = calculateScore(true, true, true, 1.0,
	                                       true, true, 1.0, 1.0,
	                                       true, true, 1.0, 1.0, 1.0,
	                                       true, true, 1.0, 1.0,
	                                       true, true, 1.0, 1.0, 1.0, 1.0,
	                                       false);  // all finished
	unsigned int mark4 = calculateScore(correct_count0, correct_score0,
	                                    correct_inventory0, correct_location0_fraction,
	                                    correct_count1, correct_score1,
	                                    correct_inventory1_fraction, correct_location1_fraction,
	                                    correct_count_copy, correct_count_assign,
	                                    correct_location_delete_fraction, correct_location_self_fraction, correct_location_chained_fraction,
	                                    correct_count2, correct_score2,
	                                    correct_inventory2_fraction, correct_location2_fraction,
	                                    correct_count3, correct_score3,
	                                    correct_inventory3_fraction, correct_location3_0_fraction,
	                                    correct_location3_1_fraction, correct_location3_rest_fraction,
	                                    false);  // all finished

	assert(mark4 <= TOTAL_MARKS);
	testHelperPrintMarkPartial(mark4, highest4, TOTAL_MARKS);

	cout << endl;
	cout << endl;


	//
	//  Cleanup
	//

	cout << "About to destroy ItemManagers" << endl;
	delete p_item_manager_1;
	delete p_item_manager_2;
	p_item_manager_1 = NULL;
	p_item_manager_2 = NULL;
	cout << "* Destroyed without crashing" << endl;
	cout << endl;


	//
	//  Print results (5)
	//

	testHelperPrintSummaryHeader(28, 1, DID_NOT_CRASH_RUNNING_MARKS);
	testHelperPrintSummaryLine("getCount",                   correct_count_count, 4);
	testHelperPrintSummaryLine("getScore",                   correct_score_count, 4);
	testHelperPrintSummaryLine("printInventory  (default)",  correct_inventory0);
	testHelperPrintSummaryLine("printAtLocation (default)",  correct_location0_fraction);
	testHelperPrintSummaryLine("printInventory  (loaded)",   correct_inventory1_fraction);
	testHelperPrintSummaryLine("printAtLocation (loaded)",   correct_location1_fraction);
	testHelperPrintSummaryLine("Copy constructor",           correct_count_copy);
	testHelperPrintSummaryLine("Assignment operator",        correct_count_assign);
	testHelperPrintSummaryLine("Locations after delete",     correct_location_delete_fraction);
	testHelperPrintSummaryLine("Self-assignment",            correct_location_self_fraction);
	testHelperPrintSummaryLine("Chained assignment",         correct_location_chained_fraction);
	testHelperPrintSummaryLine("printInventory  (taken)",    correct_inventory2_fraction);
	testHelperPrintSummaryLine("printAtLocation (taken)",    correct_location2_fraction);
	testHelperPrintSummaryLine("printInventory  (groups)",   correct_inventory3_fraction);
	testHelperPrintSummaryLine("printAtLocation (group 1)",  correct_location3_0_fraction);
	testHelperPrintSummaryLine("printAtLocation (group 2)",  correct_location3_1_fraction);
	testHelperPrintSummaryLine("printAtLocation (no group)", correct_location3_rest_fraction);

	unsigned int mark5 = calculateScore(correct_count0, correct_score0,
	                                    correct_inventory0, correct_location0_fraction,
	                                    correct_count1, correct_score1,
	                                    correct_inventory1_fraction, correct_location1_fraction,
	                                    correct_count_copy, correct_count_assign,
	                                    correct_location_delete_fraction, correct_location_self_fraction, correct_location_chained_fraction,
	                                    correct_count2, correct_score2,
	                                    correct_inventory2_fraction, correct_location2_fraction,
	                                    correct_count3, correct_score3,
	                                    correct_inventory3_fraction, correct_location3_0_fraction,
	                                    correct_location3_1_fraction, correct_location3_rest_fraction,
	                                    true);

	bool is_inventory_print_sorted = correct_inventory2_fraction  == 1.0;
	bool is_location_print_sorted  = correct_location3_0_fraction == 1.0 &&
	                                 correct_location3_1_fraction == 1.0;
	if(is_inventory_print_sorted || is_location_print_sorted)
	{
		cout << endl;
		cout << "* Descriptions were printed sorted" << endl;
		cout << "    " << setw(3) << DESCRIPTIONS_IN_FILE_PENALTY
		     << " marks if they are in the ItemManager.cpp file" << endl;
		cout << "    " << setw(3) << LINEAR_SEARCH_PENALTY
		     << " marks if find function uses linear search" << endl;
	}
	else if(correct_location1_fraction == 1.0 ||
	        result_inventory2.missing_count == 0)
	{
		cout << endl;
		cout << "* Descriptions were printed for each item" << endl;
		cout << "    " << setw(3) << DESCRIPTIONS_IN_FILE_PENALTY
		     << " marks if they are in the ItemManager.cpp file" << endl;
	}
	else
	{
		cout << endl;
		cout << "* Descriptions were missing or incorrect" << endl;
	}

	assert(mark5 <= TOTAL_MARKS);
	testHelperPrintMark(mark5, TOTAL_MARKS);

	testHelperWaitForEnter();
	return 0;
}



int calculateCorrectScore (unsigned int present_bits)
{
	unsigned int score = 0;
	for(unsigned int i = 0; i < ITEM_COUNT_GHOSTWOOD; i++)
	{
		bool should_be_present = ((present_bits >> i) & 0x1) != 0x0;
		if(should_be_present)
			score += ITEM_SCORE_CORRECT[i];
	}
	return score;
}

Result testInventoryPrint (const string& printed,
                           unsigned int present_bits)
{
	vector<string> lines = testHelperSplitWithoutEmpty(printed, '\n');

	Result result;
	result.desired_count     = 0;
	result.other_descr_count = 0;
	result.bad_descr_count   = 0;
	result.missing_count     = 0;
	result.extra_count       = 0;
	result.unsorted_count    = 0;

	unsigned int next_ordered_index = 0;
	for(unsigned int i = 0; i < ITEM_COUNT_GHOSTWOOD; i++)
	{
		unsigned int ground_index    = getIndexInVector(lines, ITEM_GROUND_DESCRIPTION_CORRECT   [i]);
		unsigned int inventory_index = getIndexInVector(lines, ITEM_INVENTORY_DESCRIPTION_CORRECT[i]);

		bool should_be_present    = ((present_bits >> i) & 0x1) != 0x0;
		bool is_ground_present    = ground_index    != STRING_NOT_IN_VECTOR;
		bool is_inventory_present = inventory_index != STRING_NOT_IN_VECTOR;

		if(should_be_present)
			result.desired_count++;

		if(is_ground_present)
		{
			if(result.other_descr_count == 0)
				cout << "* Incorrect: Printed ground description for item '" << ITEM_ID_CORRECT[i] << "'" << endl;
			result.other_descr_count++;
		}
		else if(!should_be_present && is_inventory_present)
		{
			if(result.extra_count == 0)
				cout << "* Incorrect: Item '" << ITEM_ID_CORRECT[i] << "' prints in inventory but shouldn't" << endl;
			result.extra_count++;
		}
		else if(should_be_present && !is_inventory_present)
		{
			string phrase = "(?)";
			phrase[1] = ITEM_ID_CORRECT[i];
			unsigned int phrase_line_index = getIndexWithPhrase(lines, phrase);

			if(phrase_line_index != NOT_IN_ANY_LINE)
			{
				printLineDifference(lines[phrase_line_index], ITEM_INVENTORY_DESCRIPTION_CORRECT[i],
				                    ITEM_ID_CORRECT[i], "Inventory");
				result.bad_descr_count++;
			}
			else
			{
				if(result.missing_count == 0)
					cout << "* Incorrect: Item '" << ITEM_ID_CORRECT[i] << "' should print in inventory but doesn't" << endl;
				result.missing_count++;
			}
		}

		if(should_be_present && is_inventory_present)
		{
			if(inventory_index < next_ordered_index)
			{
				if(result.unsorted_count == 0)
					cout << "* Incorrect: Item '" << ITEM_ID_CORRECT[i] << "' was not in sorted order" << endl;
				result.unsorted_count++;
			}
			if(next_ordered_index <= inventory_index)
				next_ordered_index = inventory_index + 1;
		}
	}

	if(result.other_descr_count > 1)
		cout << "* Printed ground description for " << (result.other_descr_count - 1) << " more items in inventory" << endl;
	if(result.missing_count > 1)
		cout << "* " << (result.missing_count - 1) << " more items missing from inventory" << endl;
	if(result.extra_count > 1)
		cout << "* " << (result.extra_count - 1) << " more extra items in inventory" << endl;
	if(result.unsorted_count > 1)
		cout << "* " << (result.unsorted_count - 1) << " more unsorted items in inventory" << endl;

	return result;
}

Result testLocationPrint (const string& printed,
                          unsigned int present_bits,
                          const Location& location,
                          bool is_print_incorrect)
{
	vector<string> lines = testHelperSplitWithoutEmpty(printed, '\n');

	Result result;
	result.desired_count     = 0;
	result.other_descr_count = 0;
	result.bad_descr_count   = 0;
	result.missing_count     = 0;
	result.extra_count       = 0;
	result.unsorted_count    = 0;

	unsigned int next_ordered_index = 0;
	for(unsigned int i = 0; i < ITEM_COUNT_GHOSTWOOD; i++)
	{
		unsigned int ground_index    = getIndexInVector(lines, ITEM_GROUND_DESCRIPTION_CORRECT   [i]);
		unsigned int inventory_index = getIndexInVector(lines, ITEM_INVENTORY_DESCRIPTION_CORRECT[i]);

		bool should_be_present    = ((present_bits >> i) & 0x1) != 0x0;
		bool is_ground_present    = ground_index    != STRING_NOT_IN_VECTOR;
		bool is_inventory_present = inventory_index != STRING_NOT_IN_VECTOR;

		if(should_be_present)
			result.desired_count++;

		if(is_inventory_present)
		{
			if(result.other_descr_count == 0 && is_print_incorrect)
				cout << "* Incorrect: Printed inventory description for '" << ITEM_ID_CORRECT[i] << "' at " << location << endl;
			result.other_descr_count++;
		}
		else if(!should_be_present && is_ground_present)
		{
			if(result.extra_count == 0 && is_print_incorrect)
				cout << "* Incorrect: Item '" << ITEM_ID_CORRECT[i] << "' prints at " << location << " but shouldn't" << endl;
			result.extra_count++;
		}
		else if(should_be_present && !is_ground_present)
		{
			string phrase = "(?)";
			phrase[1] = ITEM_ID_CORRECT[i];
			unsigned int phrase_line_index = getIndexWithPhrase(lines, phrase);

			if(phrase_line_index != NOT_IN_ANY_LINE)
			{
				if(is_print_incorrect)
				{
					printLineDifference(lines[phrase_line_index], ITEM_GROUND_DESCRIPTION_CORRECT[i],
					                    ITEM_ID_CORRECT[i], "Ground");
				}
				result.bad_descr_count++;
			}
			else if(result.missing_count == 0)
			{
				if(is_print_incorrect)
					cout << "* Incorrect: Item '" << ITEM_ID_CORRECT[i] << "' should print at " << location << " but doesn't" << endl;
				result.missing_count++;
			}
		}

		if(should_be_present && is_ground_present)
		{
			if(ground_index < next_ordered_index)
			{
				if(result.unsorted_count == 0)
					cout << "* Incorrect: Item '" << ITEM_ID_CORRECT[i] << "' was not in sorted order" << endl;
				result.unsorted_count++;
			}
			if(next_ordered_index <= ground_index)
				next_ordered_index = ground_index + 1;
		}
	}

	if(is_print_incorrect)
	{
		if(result.other_descr_count > 1)
			cout << "* Printed inventory description for " << (result.other_descr_count - 1) << " more items at " << location << endl;
		if(result.missing_count > 1)
			cout << "* " << (result.missing_count - 1) << " more items missing from " << location << endl;
		if(result.extra_count > 1)
			cout << "* " << (result.extra_count - 1) << " more extra items at " << location << endl;
		if(result.unsorted_count > 1)
			cout << "* " << (result.unsorted_count - 1) << " more unsorted items at " << location << endl;
	}

	return result;
}

unsigned int getIndexInVector(const vector<string>& search_in,
                              const string& search_for)
{
	for(unsigned int i = 0; i < search_in.size(); i++)
		if(search_in[i] == search_for)
			return i;
	return STRING_NOT_IN_VECTOR;
}

unsigned int getIndexWithPhrase (const vector<string>& search_in,
                                 const string& phrase)
{
	for(unsigned int i = 0; i < search_in.size(); i++)
		if(search_in[i].find(phrase) != string::npos)
			return i;
	return NOT_IN_ANY_LINE;
}

void printLineDifference (const string& line1,
                          const string& line2,
                          char item_id, const string& description_name)
{
	assert(!line1.empty());
	assert(!line2.empty());
	assert(line1 != line2);

	unsigned int first_diff = 0;
	while(first_diff + 1 < line1.size() && 
	      first_diff + 1 < line2.size() && 
	      line1[first_diff + 1] == line2[first_diff + 1])
	{
		first_diff++;
	}

	unsigned int last_diff1 = line1.size();
	unsigned int last_diff2 = line2.size();
	while(last_diff1 > 0 && 
	      last_diff2 > 0 && 
	      line1[last_diff1 - 1] == line2[last_diff2 - 1])
	{
		last_diff1--;
		last_diff2--;
	}

	// "same" ranges can overlap if part of the string is repeated
	//  e.g. "aba" vs. "abcba" has 4 char of overlap in a 3 char string
	if(last_diff1 < first_diff)
		last_diff1 = first_diff;
	if(last_diff2 < first_diff)
		last_diff2 = first_diff;
	assert(first_diff <= last_diff1);
	assert(first_diff <= last_diff2);

	cout << "* Incorrect: " << description_name << " description for item '" << item_id << "' is incorrect" << endl;

	unsigned int before_diff = 0;
	string before_quote = "\"";
	if(first_diff > ERROR_STRING_PADDING)
	{
		before_diff = first_diff - ERROR_STRING_PADDING;
		before_quote = "\"...";
	}

	unsigned int after_diff1 = line1.size();
	string after_quote1 = "\"";
	if(last_diff1 + ERROR_STRING_PADDING < line1.size())
	{
		after_diff1 = last_diff1 + ERROR_STRING_PADDING;
		after_quote1 = "...\"";
	}

	unsigned int after_diff2 = line2.size();
	string after_quote2 = "\"";
	if(last_diff2 + ERROR_STRING_PADDING < line2.size())
	{
		after_diff2 = last_diff2 + ERROR_STRING_PADDING;
		after_quote2 = "...\"";
	}

	assert(before_diff <= after_diff1);
	assert(before_diff <= after_diff2);
	unsigned int length_diff1 = after_diff1 - before_diff;
	unsigned int length_diff2 = after_diff2 - before_diff;

	cout << "             " << before_quote << line1.substr(before_diff, length_diff1) << after_quote1 << endl;
	cout << "                 Should be" << endl;
	cout << "             " << before_quote << line2.substr(before_diff, length_diff2) << after_quote2 << endl;
}

bool isResultAllCorrect (const Result& result)
{
	if(result.other_descr_count > 0)
		return false;
	if(result.bad_descr_count > 0)
		return false;
	if(result.missing_count > 0)
		return false;
	if(result.extra_count > 0)
		return false;
	if(result.unsorted_count > 0)
		return false;
	return true;
}

double getResultMark (const Result& result)
{
	assert(result.desired_count >= 0);

	if(result.desired_count == 0)
		return isResultAllCorrect(result) ? 1.0 : 0.0;
	else
	{
		int mark = result.desired_count;
		mark -= result.other_descr_count;
		mark -= result.bad_descr_count;
		mark -= result.missing_count;
		mark -= result.extra_count;
		mark -= result.unsorted_count;

		if(mark <= 0)
			return 0.0;
		else
			return (double)(mark) / result.desired_count;
	}
}

unsigned int calculateScore (bool correct_count_default,
                             bool correct_score_default,
                             bool correct_inventory_default,
                             double correct_location_default_fraction,
                             bool correct_count1,
                             bool correct_score1,
                             double correct_inventory1_fraction,
                             double correct_location1_fraction,
                             bool correct_count_copy,
                             bool correct_count_assign,
                             double correct_location_delete_fraction,
                             double correct_location_self_fraction,
                             double correct_location_chained_fraction,
                             bool correct_count2,
                             bool correct_score2,
                             double correct_inventory2_fraction,
                             double correct_location2_fraction,
                             bool correct_count3,
                             bool correct_score3,
                             double correct_inventory3_fraction,
                             double correct_location3_0_fraction,
                             double correct_location3_1_fraction,
                             double correct_location3_rest_fraction,
                             bool is_finished_without_crash)
{
	unsigned int mark = COMPILE_AND_START_MARKS;
	if(is_finished_without_crash)
		mark = COMPILE_AND_NOT_CRASH_MARKS;

	if(correct_count_default && correct_score_default && correct_count1 && correct_score1)
		mark += 1;
	if(correct_inventory_default)
		mark += 1;
	if(correct_location_default_fraction == 1.0)
		mark += 1;
	mark += (int)(correct_inventory1_fraction * 2);
	mark += (int)(correct_location1_fraction  * 4);
	if(correct_count_copy)
		mark += 1;
	if(correct_count_assign)
		mark += 1;
	if(correct_location_delete_fraction == 1.0)
		mark += 1;
	if(correct_location_self_fraction    == 1.0)
		mark += 1;
	if(correct_location_chained_fraction == 1.0)
		mark += 1;
	if(correct_count2 && correct_score2 && correct_count3 && correct_score3)
		mark += 1;

	// lots of marks here because also testing sorting
	mark += (int)(correct_inventory2_fraction * 4);
	mark += (int)(correct_location2_fraction  * 2);
	mark += (int)(correct_inventory3_fraction * 3);
	int location3_mark = (int)(correct_location3_0_fraction    * 4 +
	                           correct_location3_1_fraction    * 4 +
	                           correct_location3_rest_fraction * 4 - 6);
	if(location3_mark > 0)
		mark += location3_mark;

	assert(mark <= TOTAL_MARKS);
	return mark;
}
