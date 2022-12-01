//
//  TestScoreTable5E.cpp
//
//  A test program for the ScoreTable module.
//
//  This program is to be used with Assignment 5: Part E for
//    CS115, 202210.  This is the TestScoreTable5E test program
//    with the load and save tests included.
//
//  Do not modify this file.
//
//  2022-03-25: Split off TestScoreTable5
//

#include "ScoreTable.h"
#include "ScoreTable.h"  // repeated to test for #include errors

#include <cassert>
#include <climits>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <typeinfo>  // for typeid

#include "TestHelper.h"

using namespace std;



int main ();
string getLinkedListDescription (unsigned int count);
bool checkAllocationCount (int count, int correct,
                           bool print_correct);
bool checkAllocationCount (int count_before, int correct_before,
                           int count_after, int correct_after,
                           bool print_correct);
Element* createLinkedList (unsigned int count);
bool compareLinkedLists (const Element* p_original,
                         const Element* p_copy,
                         unsigned int count_correct);
bool checkPrinted (const string& printed,
                   unsigned int present_bits,
                   bool is_print_result);
bool checkCopy (const string& source,
                const string& destination,
                unsigned int present_bits);
unsigned int getIndexInVector(const vector<string>& search_in,
                              const string& search_for);
unsigned int calculateScore (bool correct_element_bytes,
                             double correct_allocated_count_fraction,
                             double correct_destroy_linked_list_fraction,
                             double correct_copy_linked_list_fraction,
                             bool correct_score_table_bytes,
                             bool correct_print_empty,
                             double correct_insert_fraction,
                             double correct_copy_fraction,
                             double correct_delete_fraction,
                             double correct_assign_fraction,
                             bool correct_self_assign,
                             bool correct_chained_assign,
                             double correct_load_fraction,
                             double correct_save_fraction,
                             bool is_finished_without_crash);


const int COMPILE_AND_START_MARKS     =  5;
const int DID_NOT_CRASH_RUNNING_MARKS =  5;
const int COMPILE_AND_NOT_CRASH_MARKS = COMPILE_AND_START_MARKS + DID_NOT_CRASH_RUNNING_MARKS;
const int COMBINED_TEST_MARKS         = 20;
const int TOTAL_MARKS                 = COMPILE_AND_NOT_CRASH_MARKS + COMBINED_TEST_MARKS;

const unsigned int ELEMENT_COUNT_MAX = 3;
const unsigned int ELEMENT_TEST_COUNT = ELEMENT_COUNT_MAX + 1;
const string ELEMENT_NAMES[ELEMENT_COUNT_MAX] =
{
	"Name 0",
	"Name 1",
	"Name 2",
};
const int ELEMENT_SCORES[ELEMENT_COUNT_MAX] =
{
	111,
	22,
	3,
};

const int TRIANGULAR_NUMBERS[ELEMENT_TEST_COUNT] =
{
	0,
	1,
	3,
	6,
};


const string FIRST_LINE_CORRECT = "Scores:";

const unsigned int TEST_ENTRY_COUNT = 8;
const string TEST_ENTRY_NAME[TEST_ENTRY_COUNT] =
{
	// added in testing
	"Alice",
	"Bob",
	"Chris",
	"Dan",
	"Emma",
	// loaded from files
	"asdf",
	"007girl",
	"name with spaces in it",
};
const int TEST_ENTRY_SCORE[TEST_ENTRY_COUNT] =
{
	// added in testing
	36,
	14,
	6,
	6,
	-2,
	// loaded from files
	99999,
	9999,
	999,
};

const unsigned int STRING_NOT_IN_VECTOR = UINT_MAX;



int main ()
{
	testHelperStartup("TestScoreTable5E", COMPILE_AND_START_MARKS, TOTAL_MARKS);

	//
	//  Test Element and ScoreTable types
	//

	cout << "Checking Element size in bytes" << endl;
	size_t element_bytes         = sizeof(Element);
	size_t string_bytes          = sizeof(string);
	size_t next_pointer_bytes    = sizeof(Element*);
	size_t element_bytes_correct = sizeof(int) + string_bytes + next_pointer_bytes;
	bool correct_element_bytes = false;
	if(element_bytes == 0)
		cout << "* Incorrect: Element must contain member data" << endl;
	else if(element_bytes < next_pointer_bytes)
		cout << "* Incorrect: Element should contain a next pointer (Element*)" << endl;
	else if(element_bytes < string_bytes)
		cout << "* Incorrect: Element should contain a name (string)" << endl;
	else if(element_bytes < element_bytes_correct)
		cout << "* Incorrect: Element should contain more data" << endl;
	else if(element_bytes > element_bytes_correct * 2)
		cout << "* Incorrect: Element contains unnecessary data" << endl;
	else
	{
		cout << "* Correct" << endl;
		correct_element_bytes = true;
	}
	cout << endl;

	cout << "Checking allocated element count (never any elements)" << endl;
	int allocated_count1 = getAllocatedElementCount();
	bool correct_allocated_count1 = checkAllocationCount(allocated_count1, 0, true);
	cout << endl;

	cout << "Creating Element" << endl;
	Element* p_element = new Element;
	cout << "* Completed without crashing" << endl;
	cout << endl;

	cout << "Checking allocated element count (created element)" << endl;
	int allocated_count2 = getAllocatedElementCount();
	bool correct_allocated_count2 = checkAllocationCount(allocated_count2, 1, true);
	cout << endl;

	cout << "Destroying Element" << endl;
	delete p_element;
	p_element = NULL;
	cout << "* Completed without crashing" << endl;
	cout << endl;

	cout << "Checking allocated element count (destroyed element)" << endl;
	int allocated_count3 = getAllocatedElementCount();
	bool correct_allocated_count3 = checkAllocationCount(allocated_count3, 0, true);
	cout << endl;

	cout << endl;
	cout << endl;


	//
	//  Print results (1)
	//

	unsigned int correct_allocated_count_count = (correct_allocated_count1 ? 1 : 0) +
	                                             (correct_allocated_count2 ? 1 : 0) +
	                                             (correct_allocated_count3 ? 1 : 0);
	double correct_allocated_count_fraction = correct_allocated_count_count / 3.0;

	testHelperPrintSummaryHeaderPartial(30, 1, COMPILE_AND_START_MARKS);
	testHelperPrintSummaryLine("Element declaration",          correct_element_bytes);
	testHelperPrintSummaryLine("Allocation counting",          correct_allocated_count_count, 3);

	unsigned int highest1 = calculateScore(true, 1.0,
	                                       0.0,                // destroyLinkedList
	                                       0.0,                // copyLinkedList
	                                       false, false, 0.0,  // print and insert
	                                       0.0, 0.0,           // copy constructor and destructor
	                                       0.0, false, false,  // assignment operator
	                                       0.0, 0.0,           // load and save
	                                       false);             // all finished
	unsigned int mark1 = calculateScore(correct_element_bytes, correct_allocated_count_fraction,
	                                    0.0,                // destroyLinkedList
	                                    0.0,                // copyLinkedList
	                                    false, false, 0.0,  // print and insert
	                                    0.0, 0.0,           // copy constructor and destructor
	                                    0.0, false, false,  // assignment operator
	                                    0.0, 0.0,           // load and save
	                                    false);             // all finished
	assert(mark1    <= TOTAL_MARKS);
	assert(highest1 <= TOTAL_MARKS);
	assert(mark1    <= highest1);
	testHelperPrintMarkPartial(mark1, highest1, TOTAL_MARKS);

	cout << endl;
	cout << endl;


	//
	//  Test destroying linked lists
	//

	unsigned int correct_allocated_destroy = 0;

	for(unsigned int i = 0; i < ELEMENT_TEST_COUNT; i++)
	{
		cout << "Destroy " << getLinkedListDescription(i) << endl;
		Element* p_head = createLinkedList(i);
		cout << "* Created without crashing" << endl;
		int allocation_before = getAllocatedElementCount();
		destroyLinkedList(p_head);
		p_head = NULL;
		cout << "* Completed without crashing" << endl;
		int allocation_after = getAllocatedElementCount();
		if(checkAllocationCount(allocation_before, i, allocation_after, 0, true))
			correct_allocated_destroy++;
		cout << endl;
	}

	cout << endl;
	cout << endl;


	//
	//  Print results (2)
	//

	double correct_allocated_destroy_fraction = correct_allocated_destroy / 4.0;

	testHelperPrintSummaryHeaderPartial(30, 1, COMPILE_AND_START_MARKS);
	testHelperPrintSummaryLine("Element declaration",          correct_element_bytes);
	testHelperPrintSummaryLine("Allocation counting",          correct_allocated_count_count, 3);
	testHelperPrintSummaryLine("destroyLinkedList",            correct_allocated_destroy,     ELEMENT_TEST_COUNT);

	unsigned int highest2 = calculateScore(true, 1.0,
	                                       1.0,
	                                       0.0,                // copyLinkedList
	                                       false, false, 0.0,  // print and insert
	                                       0.0, 0.0,           // copy constructor and destructor
	                                       0.0, false, false,  // assignment operator
	                                       0.0, 0.0,           // load and save
	                                       false);             // all finished
	unsigned int mark2 = calculateScore(correct_element_bytes, correct_allocated_count_fraction,
	                                    correct_allocated_destroy_fraction,
	                                    0.0,                // copyLinkedList
	                                    false, false, 0.0,  // print and insert
	                                    0.0, 0.0,           // copy constructor and destructor
	                                    0.0, false, false,  // assignment operator
	                                    0.0, 0.0,           // load and save
	                                    false);             // all finished
	assert(mark2    <= TOTAL_MARKS);
	assert(highest2 <= TOTAL_MARKS);
	assert(mark2    <= highest2);
	testHelperPrintMarkPartial(mark2, highest2, TOTAL_MARKS);

	cout << endl;
	cout << endl;


	//
	//  Test copying linked lists
	//

	unsigned int correct_allocated_copy     = 0;
	unsigned int correct_element_copy_count = 0;

	Element* p_originals[ELEMENT_TEST_COUNT];
	Element* p_copies   [ELEMENT_TEST_COUNT];

	for(unsigned int i = 0; i < ELEMENT_TEST_COUNT; i++)
	{
		cout << "Copy " << getLinkedListDescription(i) << endl;
		p_originals[i] = createLinkedList(i);
		cout << "* Created without crashing" << endl;
		int allocation_before = getAllocatedElementCount();
		p_copies[i] = copyLinkedList(p_originals[i]);
		cout << "* Completed copy without crashing" << endl;
		int allocation_after = getAllocatedElementCount();

		int correct_base   = (i == 0) ? 0 : TRIANGULAR_NUMBERS[i - 1] * 2;
		int correct_before = correct_base + i;
		int correct_after  = correct_base + i * 2;

		if(checkAllocationCount(allocation_before, correct_before, allocation_after, correct_after, false))
			correct_allocated_copy++;
		if(compareLinkedLists(p_originals[i], p_copies[i], i))
			correct_element_copy_count++;
		cout << endl;
	}

	if(correct_element_copy_count < ELEMENT_TEST_COUNT)
	{
		cout << "Warning: Errors were found in copying." << endl;
		cout << "         This may cause a crash during deletion." << endl;
		testHelperWaitForEnter();
		cout << endl;
	}

	cout << "Destroy the original linked lists" << endl;
	for(unsigned int i = 0; i < ELEMENT_TEST_COUNT; i++)
	{
		destroyLinkedList(p_originals[i]);
		p_originals[i] = NULL;
	}
	cout << "* Completed without crashing" << endl;
	int allocated_after_destorying_originals = getAllocatedElementCount();
	bool correct_allocated_destroy_originals = checkAllocationCount(allocated_after_destorying_originals,
	                                           TRIANGULAR_NUMBERS[ELEMENT_TEST_COUNT - 1], true);
	cout << endl;

	cout << "Destroy the copied linked lists" << endl;
	for(unsigned int i = 0; i < ELEMENT_TEST_COUNT; i++)
	{
		destroyLinkedList(p_copies[i]);
		p_copies[i] = NULL;
	}
	cout << "* Completed without crashing" << endl;
	int allocated_after_destorying_copies = getAllocatedElementCount();
	bool correct_allocated_destroy_copies = checkAllocationCount(allocated_after_destorying_copies, 0, true);
	cout << endl;

	cout << endl;
	cout << endl;


	//
	//  Print results (3)
	//

	double correct_element_copy_fraction = (double)(correct_element_copy_count) / ELEMENT_TEST_COUNT;

	unsigned int correct_allocated_dc_count = (correct_allocated_destroy_originals ? 1 : 0) +
	                                          (correct_allocated_destroy_copies    ? 1 : 0);
	double correct_allocated_dc_fraction = correct_allocated_dc_count / 2.0;

	testHelperPrintSummaryHeaderPartial(30, 1, COMPILE_AND_START_MARKS);
	testHelperPrintSummaryLine("Element declaration",          correct_element_bytes);
	testHelperPrintSummaryLine("Allocation counting",          correct_allocated_count_count, 3);
	testHelperPrintSummaryLine("destroyLinkedList",            correct_allocated_destroy,     ELEMENT_TEST_COUNT);
	testHelperPrintSummaryLine("copyLinkedList",               correct_element_copy_count,    ELEMENT_TEST_COUNT);
	testHelperPrintSummaryLine("Allocated after copy",         correct_allocated_copy,        ELEMENT_TEST_COUNT);
	testHelperPrintSummaryLine("Allocated after destroy copy", correct_allocated_dc_count,    2);

	unsigned int highest3 = calculateScore(true, 1.0,
	                                       1.0, 1.0,
	                                       false, false, 0.0,  // print and insert
	                                       0.0, 0.0,           // copy constructor and destructor
	                                       0.0, false, false,  // assignment operator
	                                       0.0, 0.0,           // load and save
	                                       false);             // all finished
	unsigned int mark3 = calculateScore(correct_element_bytes, correct_allocated_count_fraction,
	                                    correct_allocated_destroy_fraction, correct_element_copy_fraction,
	                                    false, false, 0.0,  // print and insert
	                                    0.0, 0.0,           // copy constructor and destructor
	                                    0.0, false, false,  // assignment operator
	                                    0.0, 0.0,           // load and save
	                                    false);             // all finished
	assert(mark3    <= TOTAL_MARKS);
	assert(highest3 <= TOTAL_MARKS);
	assert(mark3    <= highest3);
	testHelperPrintMarkPartial(mark3, highest3, TOTAL_MARKS);

	cout << endl;
	cout << endl;


	//
	//  Test ScoreTable print and insert
	//

	cout << "Checking ScoreTable size in bytes" << endl;
	size_t score_table_bytes         = sizeof(ScoreTable);
	size_t score_table_bytes_correct = sizeof(Element*);
	bool correct_score_table_bytes = false;
	if(score_table_bytes == 0)
		cout << "* Incorrect: ScoreTable must contain member data" << endl;
	else if(score_table_bytes < score_table_bytes_correct)
		cout << "* Incorrect: ScoreTable should contain a head pointer (Element*)" << endl;
	else if(score_table_bytes > score_table_bytes_correct * 2)
		cout << "* Incorrect: ScoreTable contains unnecessary data" << endl;
	else
	{
		cout << "* Correct" << endl;
		correct_score_table_bytes = true;
	}
	cout << endl;

	cout << "Testing ScoreTable default constructor" << endl;
	ScoreTable* p_table1 = new ScoreTable;
	cout << "* Completed without crashing" << endl;
	cout << endl;

	cout << "Destroying default ScoreTable" << endl;
	delete p_table1;
	p_table1 = NULL;
	cout << "* Completed without crashing" << endl;
	cout << endl;

	cout << "Printing default ScoreTable" << endl;
	ScoreTable* p_table2 = new ScoreTable;
	cout << "* Created without crashing" << endl;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_table2->print();
	string captured_empty = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	bool empty_correct = checkPrinted(captured_empty, 0x00, true);
	cout << endl;

	cout << "Inserting entry \"" << TEST_ENTRY_NAME[2] << "\", " << TEST_ENTRY_SCORE[2] << " (into empty)" << endl;
	p_table2->insert(TEST_ENTRY_NAME[2], TEST_ENTRY_SCORE[2]);
	cout << "* Completed without crashing" << endl;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_table2->print();
	string captured_insert1 = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	bool insert1_correct = checkPrinted(captured_insert1, 0x04, true);
	cout << endl;

	cout << "Inserting entry \"" << TEST_ENTRY_NAME[0] << "\", " << TEST_ENTRY_SCORE[0] << " (at head)" << endl;
	p_table2->insert(TEST_ENTRY_NAME[0], TEST_ENTRY_SCORE[0]);
	cout << "* Completed without crashing" << endl;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_table2->print();
	string captured_insert2 = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	bool insert2_correct = checkPrinted(captured_insert2, 0x05, true);
	cout << endl;

	cout << "Inserting entry \"" << TEST_ENTRY_NAME[3] << "\", " << TEST_ENTRY_SCORE[3] << " (into middle)" << endl;
	p_table2->insert(TEST_ENTRY_NAME[3], TEST_ENTRY_SCORE[3]);
	cout << "* Completed without crashing" << endl;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_table2->print();
	string captured_insert3 = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	bool insert3_correct = checkPrinted(captured_insert3, 0x0D, true);
	cout << endl;

	cout << "Inserting entry \"" << TEST_ENTRY_NAME[4] << "\", " << TEST_ENTRY_SCORE[4] << " (at tail)" << endl;
	p_table2->insert(TEST_ENTRY_NAME[4], TEST_ENTRY_SCORE[4]);
	cout << "* Completed without crashing" << endl;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_table2->print();
	string captured_insert4 = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	bool insert4_correct = checkPrinted(captured_insert4, 0x1D, true);
	cout << endl;

	cout << "Inserting entry \"" << TEST_ENTRY_NAME[1] << "\", " << TEST_ENTRY_SCORE[3] << " (duplicate score)" << endl;
	p_table2->insert(TEST_ENTRY_NAME[1], TEST_ENTRY_SCORE[1]);
	cout << "* Completed without crashing" << endl;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_table2->print();
	string captured_insert5 = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	bool insert5_correct = checkPrinted(captured_insert5, 0x1F, true);
	cout << endl;

	cout << endl;
	cout << endl;


	//
	//  Print results (4)
	//

	unsigned int insert_correct_count = (insert1_correct ? 1 : 0) +
	                                    (insert2_correct ? 1 : 0) +
	                                    (insert3_correct ? 1 : 0) +
	                                    (insert4_correct ? 1 : 0) +
	                                    (insert5_correct ? 1 : 0);
	double insert_correct_fraction = insert_correct_count / 5.0;

	testHelperPrintSummaryHeaderPartial(28, 1, COMPILE_AND_START_MARKS);
	testHelperPrintSummaryLine("Element declaration",    correct_element_bytes);
	testHelperPrintSummaryLine("ScoreTable declaration", correct_score_table_bytes);
	testHelperPrintSummaryLine("print empty",            empty_correct);
	testHelperPrintSummaryLine("print after insert",     insert_correct_count, 5);

	unsigned int highest4 = calculateScore(true, 1.0,
	                                       1.0, 1.0,
	                                       true, true, 1.0,
	                                       0.0, 0.0,           // copy constructor and destructor
	                                       0.0, false, false,  // assignment operator
	                                       0.0, 0.0,           // load and save
	                                       false);             // all finished
	unsigned int mark4 = calculateScore(correct_element_bytes, correct_allocated_count_fraction,
	                                    correct_allocated_destroy_fraction, correct_element_copy_fraction,
	                                    correct_score_table_bytes, empty_correct, insert_correct_fraction,
	                                    0.0, 0.0,           // copy constructor and destructor
	                                    0.0, false, false,  // assignment operator
	                                    0.0, 0.0,           // load and save
	                                    false);             // all finished
	assert(mark4    <= TOTAL_MARKS);
	assert(highest4 <= TOTAL_MARKS);
	assert(mark4    <= highest4);
	testHelperPrintMarkPartial(mark4, highest4, TOTAL_MARKS);

	cout << endl;
	cout << endl;


	//
	//  Test copy constrcutor and destructor
	//

	cout << "Delete table with entries" << endl;
	delete p_table2;
	p_table2 = NULL;
	cout << "* Completed without crashing" << endl;
	cout << endl;

	cout << "Testing copy constructor (copy empty)" << endl;
	ScoreTable* p_table3 = new ScoreTable();
	cout << "* Created source without crashing" << endl;
	ScoreTable* p_table_empty = new ScoreTable(*p_table3);
	cout << "* Completed without crashing" << endl;
	cout << "* Original, copy" << endl;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_table3->print();
	string captured_copy1A = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_table_empty->print();
	string captured_copy1B = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	bool table_copy1_correct = checkCopy(captured_copy1A, captured_copy1B, 0x00);
	cout << endl;

	cout << "Delete original (empty)" << endl;
	delete p_table3;
	p_table3 = NULL;
	cout << "* Completed without crashing" << endl;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_table_empty->print();
	string captured_delete1 = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	bool table_delete1_correct = checkPrinted(captured_delete1, 0x00, true);
	cout << endl;

	cout << "Testing copy constructor (copy full)" << endl;
	ScoreTable* p_table4 = new ScoreTable();
	p_table4->insert(TEST_ENTRY_NAME[2], TEST_ENTRY_SCORE[2]);
	p_table4->insert(TEST_ENTRY_NAME[0], TEST_ENTRY_SCORE[0]);
	p_table4->insert(TEST_ENTRY_NAME[3], TEST_ENTRY_SCORE[3]);
	p_table4->insert(TEST_ENTRY_NAME[4], TEST_ENTRY_SCORE[4]);
	p_table4->insert(TEST_ENTRY_NAME[1], TEST_ENTRY_SCORE[1]);
	cout << "* Created and filled source without crashing" << endl;
	ScoreTable* p_table_full = new ScoreTable(*p_table4);
	cout << "* Completed without crashing" << endl;
	cout << "* Original, copy" << endl;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_table4->print();
	string captured_copy2A = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_table_full->print();
	string captured_copy2B = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	bool table_copy2_correct = checkCopy(captured_copy2A, captured_copy2B, 0x1F);
	cout << endl;

	cout << "Delete original (full)" << endl;
	delete p_table4;
	p_table4 = NULL;
	cout << "* Completed without crashing" << endl;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_table_full->print();
	string captured_delete2 = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	bool table_delete2_correct = checkPrinted(captured_delete2, 0x1F, true);
	cout << endl;

	cout << endl;
	cout << endl;


	//
	//  Print results (5)
	//

	unsigned int table_copy_correct_count = (table_copy1_correct ? 1 : 0) +
	                                        (table_copy2_correct ? 1 : 0);
	unsigned int table_delete_correct_count = (table_delete1_correct ? 1 : 0) +
	                                          (table_delete2_correct ? 1 : 0);

	double table_copy_correct_fraction   = table_copy_correct_count   / 2.0;
	double table_delete_correct_fraction = table_delete_correct_count / 2.0;

	testHelperPrintSummaryHeaderPartial(28, 1, COMPILE_AND_START_MARKS);
	testHelperPrintSummaryLine("Element declaration",        correct_element_bytes);
	testHelperPrintSummaryLine("ScoreTable declaration",     correct_score_table_bytes);
	testHelperPrintSummaryLine("print empty",                empty_correct);
	testHelperPrintSummaryLine("print after insert",         insert_correct_count, 5);
	testHelperPrintSummaryLine("Copy constructor",           table_copy_correct_count,   2);
	testHelperPrintSummaryLine("Copy after delete original", table_delete_correct_count, 2);

	unsigned int highest5 = calculateScore(true, 1.0,
	                                       1.0, 1.0,
	                                       true, true, 1.0,
	                                       1.0, 1.0,
	                                       0.0, false, false,  // assignment operator
	                                       0.0, 0.0,           // load and save
	                                       false);             // all finished
	unsigned int mark5 = calculateScore(correct_element_bytes, correct_allocated_count_fraction,
	                                    correct_allocated_destroy_fraction, correct_element_copy_fraction,
	                                    correct_score_table_bytes, empty_correct, insert_correct_fraction,
	                                    table_copy_correct_fraction, table_delete_correct_fraction,
	                                    0.0, false, false,  // assignment operator
	                                    0.0, 0.0,           // load and save
	                                    false);             // all finished
	assert(mark5    <= TOTAL_MARKS);
	assert(highest5 <= TOTAL_MARKS);
	assert(mark5    <= highest5);
	testHelperPrintMarkPartial(mark5, highest5, TOTAL_MARKS);

	cout << endl;
	cout << endl;


	//
	//  Test assignment operator
	//

	cout << "Assigning empty to empty" << endl;
	ScoreTable* p_table_extra = new ScoreTable();
	cout << "* Created source without crashing" << endl;
	testHelperStartCapture();
	p_table_extra->print();
	string captured_assign1A = testHelperEndCapture(false);
	cout << "* Captured destination state without crashing" << endl;
	*p_table_extra = *p_table_empty;
	cout << "* Completed without crashing" << endl;
	cout << "* Overwritten, source, result" << endl;
	cout << "----------------------------------------------------------------" << endl;
	cout << captured_assign1A;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_table_empty->print();
	string captured_assign1B = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_table_extra->print();
	string captured_assign1C = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	bool assign1_correct = checkCopy(captured_assign1B, captured_assign1C, 0x00);
	cout << endl;

	cout << "Assigning empty to full" << endl;
	testHelperStartCapture();
	p_table_extra->print();
	string captured_assign2A = testHelperEndCapture(false);
	cout << "* Captured destination state without crashing" << endl;
	*p_table_extra = *p_table_full;
	cout << "* Completed without crashing" << endl;
	cout << "* Overwritten, source, result" << endl;
	cout << "----------------------------------------------------------------" << endl;
	cout << captured_assign2A;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_table_full->print();
	string captured_assign2B = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_table_extra->print();
	string captured_assign2C = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	bool assign2_correct = checkCopy(captured_assign2B, captured_assign2C, 0x1F);
	cout << endl;

	cout << "Assigning full to empty" << endl;
	testHelperStartCapture();
	p_table_extra->print();
	string captured_assign3A = testHelperEndCapture(false);
	cout << "* Captured destination state without crashing" << endl;
	*p_table_extra = *p_table_empty;
	cout << "* Completed without crashing" << endl;
	cout << "* Overwritten, source, result" << endl;
	cout << "----------------------------------------------------------------" << endl;
	cout << captured_assign3A;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_table_empty->print();
	string captured_assign3B = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_table_extra->print();
	string captured_assign3C = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	bool assign3_correct = checkCopy(captured_assign3B, captured_assign3C, 0x00);
	cout << endl;

	cout << "Assigning full to full" << endl;
	p_table_extra->insert(TEST_ENTRY_NAME[2], TEST_ENTRY_SCORE[2]);
	p_table_extra->insert(TEST_ENTRY_NAME[0], TEST_ENTRY_SCORE[0]);
	p_table_extra->insert(TEST_ENTRY_NAME[3], TEST_ENTRY_SCORE[3]);
	cout << "* Filled destination without crashing" << endl;
	testHelperStartCapture();
	p_table_extra->print();
	string captured_assign4A = testHelperEndCapture(false);
	cout << "* Captured destination state without crashing" << endl;
	*p_table_extra = *p_table_full;
	cout << "* Completed without crashing" << endl;
	cout << "* Overwritten, source, result" << endl;
	cout << "----------------------------------------------------------------" << endl;
	cout << captured_assign4A;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_table_full->print();
	string captured_assign4B = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_table_extra->print();
	string captured_assign4C = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	bool assign4_correct = checkCopy(captured_assign4B, captured_assign4C, 0x1F);
	cout << endl;

	cout << "Testing self-assignment" << endl;
	testHelperStartCapture();
	p_table_extra->print();
	string captured_selfA = testHelperEndCapture(false);
	cout << "* Captured original state without crashing" << endl;
	*p_table_extra = *p_table_extra;
	cout << "* Completed without crashing" << endl;
	cout << "* Original, result" << endl;
	cout << "----------------------------------------------------------------" << endl;
	cout << captured_selfA;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_table_extra->print();
	string captured_selfC = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	bool self_correct = checkCopy(captured_selfA, captured_selfC, 0x1F);
	cout << endl;

	cout << "Testing chained assignment" << endl;
	testHelperStartCapture();
	p_table_extra->print();
	string captured_chainedA = testHelperEndCapture(false);
	cout << "* Captured original state without crashing" << endl;
	*p_table_extra = *p_table_extra = *p_table_extra;
	cout << "* Completed without crashing" << endl;
	cout << "* Original, result" << endl;
	cout << "----------------------------------------------------------------" << endl;
	cout << captured_chainedA;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_table_extra->print();
	string captured_chainedC = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	bool chained_correct = checkCopy(captured_chainedA, captured_chainedC, 0x1F);
	cout << endl;

	cout << "Delete ScoreTables" << endl;
	delete p_table_empty;
	delete p_table_full;
	delete p_table_extra;
	p_table_empty = NULL;
	p_table_full  = NULL;
	p_table_extra = NULL;
	cout << "* Completed without crashing" << endl;
	cout << endl;

	cout << endl;
	cout << endl;


	//
	//  Print results (6)
	//

	unsigned int assign_correct_count = (assign1_correct ? 1 : 0) +
	                                    (assign2_correct ? 1 : 0) +
	                                    (assign3_correct ? 1 : 0) +
	                                    (assign4_correct ? 1 : 0);
	double assign_correct_fraction = assign_correct_count / 4.0;

	testHelperPrintSummaryHeaderPartial(28, 1, COMPILE_AND_START_MARKS);
	testHelperPrintSummaryLine("Element declaration",        correct_element_bytes);
	testHelperPrintSummaryLine("ScoreTable declaration", correct_score_table_bytes);
	testHelperPrintSummaryLine("print empty",                empty_correct);
	testHelperPrintSummaryLine("print after insert",         insert_correct_count,       5);
	testHelperPrintSummaryLine("Copy constructor",           table_copy_correct_count,   2);
	testHelperPrintSummaryLine("Copy after delete original", table_delete_correct_count, 2);
	testHelperPrintSummaryLine("Assignment operator",        assign_correct_count,       4);
	testHelperPrintSummaryLine("Self-assignment",            self_correct);
	testHelperPrintSummaryLine("Chained assignment",         chained_correct);

	unsigned int highest6 = calculateScore(true, 1.0,
	                                       1.0, 1.0,
	                                       true, true, 1.0,
	                                       1.0, 1.0,
	                                       1.0, true, true,
	                                       0.0, 0.0,  // load and save
	                                       false);    // all finished
	unsigned int mark6 = calculateScore(correct_element_bytes, correct_allocated_count_fraction,
	                                    correct_allocated_destroy_fraction, correct_element_copy_fraction,
	                                    correct_score_table_bytes, empty_correct, insert_correct_fraction,
	                                    table_copy_correct_fraction, table_delete_correct_fraction,
	                                    assign_correct_fraction, self_correct, chained_correct,
	                                    0.0, 0.0,  // load and save
	                                    false);    // all finished
	assert(mark6    <= TOTAL_MARKS);
	assert(highest6 <= TOTAL_MARKS);
	assert(mark6    <= highest6);
	testHelperPrintMarkPartial(mark6, highest6, TOTAL_MARKS);

	cout << endl;
	cout << endl;


	//
	//  Test loading and saving
	//
	bool invalid_correct = false;
	bool blank_correct  = false;
	bool single_correct = false;
	bool triple_correct = false;
	bool save1_correct = false;
	bool save2_correct = false;
	bool save3_correct = false;

	cout << "Testing load constructor (no such file)" << endl;
	ScoreTable* p_table_invalid = new ScoreTable("test_invalid");
	cout << "* Completed without crashing" << endl;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_table_invalid->print();
	string captured_invalid = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	invalid_correct = checkPrinted(captured_invalid, 0x00, true);
	cout << endl;

	cout << "Delete after loading non-existant file" << endl;
	delete p_table_invalid;
	p_table_invalid = NULL;
	cout << "* Completed without crashing" << endl;
	cout << endl;

	cout << "Testing load constructor (file is empty)" << endl;
	ScoreTable* p_table_blank = new ScoreTable("test_blank");
	cout << "* Completed without crashing" << endl;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_table_blank->print();
	string captured_blank = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	blank_correct = checkPrinted(captured_blank, 0x00, true);
	cout << endl;

	cout << "Delete after loading empty" << endl;
	delete p_table_blank;
	p_table_blank = NULL;
	cout << "* Completed without crashing" << endl;
	cout << endl;

	cout << "Testing load constructor (file contains 1 score)" << endl;
	ScoreTable* p_table_single = new ScoreTable("test_single");
	cout << "* Completed without crashing" << endl;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_table_single->print();
	string captured_single = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	single_correct = checkPrinted(captured_single, 0x20, true);
	cout << endl;

	cout << "Delete after loading 1 score" << endl;
	delete p_table_single;
	p_table_single = NULL;
	cout << "* Completed without crashing" << endl;
	cout << endl;

	cout << "Testing load constructor (file contains 3 scores)" << endl;
	ScoreTable* p_table_triple = new ScoreTable("test_triple");
	cout << "* Completed without crashing" << endl;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_table_triple->print();
	string captured_triple = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	triple_correct = checkPrinted(captured_triple, 0xE0, true);
	cout << endl;

	cout << "Delete after loading 3 scores" << endl;
	delete p_table_triple;
	p_table_triple = NULL;
	cout << "* Completed without crashing" << endl;
	cout << endl;

	cout << "Testing save (empty)" << endl;
	ScoreTable* p_save1 = new ScoreTable();
	cout << "* Created source without crashing" << endl;
	p_save1->save("save1");
	cout << "* Completed save without crashing" << endl;
	ScoreTable* p_load1 = new ScoreTable("save1");
	cout << "* Completed load without crashing" << endl;
	cout << "* Original, copy" << endl;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_save1->print();
	string captured_save1A = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_load1->print();
	string captured_save1B = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	save1_correct = checkCopy(captured_save1A, captured_save1B, 0x00);
	cout << endl;

	cout << "Delete after testing save (empty)" << endl;
	delete p_save1;
	delete p_load1;
	p_save1 = NULL;
	p_load1 = NULL;
	cout << "* Completed without crashing" << endl;
	cout << endl;

	cout << "Testing save (1 score)" << endl;
	ScoreTable* p_save2 = new ScoreTable();
	p_save2->insert(TEST_ENTRY_NAME[2], TEST_ENTRY_SCORE[2]);
	cout << "* Created and filled source without crashing" << endl;
	p_save2->save("save2");
	cout << "* Completed save without crashing" << endl;
	ScoreTable* p_load2 = new ScoreTable("save2");
	cout << "* Completed load without crashing" << endl;
	cout << "* Original, copy" << endl;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_save2->print();
	string captured_save2A = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_load2->print();
	string captured_save2B = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	save2_correct = checkCopy(captured_save2A, captured_save2B, 0x04);
	cout << endl;

	cout << "Delete after testing save (1 score)" << endl;
	delete p_save2;
	delete p_load2;
	p_save2 = NULL;
	p_load2 = NULL;
	cout << "* Completed without crashing" << endl;
	cout << endl;

	cout << "Testing save (3 scores)" << endl;
	ScoreTable* p_save3 = new ScoreTable();
	p_save3->insert(TEST_ENTRY_NAME[2], TEST_ENTRY_SCORE[2]);
	p_save3->insert(TEST_ENTRY_NAME[0], TEST_ENTRY_SCORE[0]);
	p_save3->insert(TEST_ENTRY_NAME[3], TEST_ENTRY_SCORE[3]);
	cout << "* Created and filled source without crashing" << endl;
	p_save3->save("save3");
	cout << "* Completed save without crashing" << endl;
	ScoreTable* p_load3 = new ScoreTable("save3");
	cout << "* Completed load without crashing" << endl;
	cout << "* Original, copy" << endl;
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_save3->print();
	string captured_save3A = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	testHelperStartCapture();
	p_load3->print();
	string captured_save3B = testHelperEndCapture(true);
	cout << "----------------------------------------------------------------" << endl;
	save3_correct = checkCopy(captured_save3A, captured_save3B, 0x0D);
	cout << endl;

	cout << "Delete after testing save (3 scores)" << endl;
	delete p_save3;
	delete p_load3;
	p_save3 = NULL;
	p_load3 = NULL;
	cout << "* Completed without crashing" << endl;
	cout << endl;


	//
	//  Print results (7)
	//

	unsigned int load_correct_count = (invalid_correct ? 1 : 0) +
	                                  (blank_correct   ? 1 : 0) +
	                                  (single_correct  ? 1 : 0) +
	                                  (triple_correct  ? 1 : 0);
	unsigned int save_correct_count = (save1_correct ? 1 : 0) +
	                                  (save2_correct ? 1 : 0) +
	                                  (save3_correct ? 1 : 0);
	double load_correct_fraction = load_correct_count / 4.0;
	double save_correct_fraction = save_correct_count / 3.0;

	testHelperPrintSummaryHeader(28, 1, DID_NOT_CRASH_RUNNING_MARKS);
	testHelperPrintSummaryLine("Element declaration",        correct_element_bytes);
	testHelperPrintSummaryLine("ScoreTable declaration",     correct_score_table_bytes);
	testHelperPrintSummaryLine("print empty",                empty_correct);
	testHelperPrintSummaryLine("print after insert",         insert_correct_count,       5);
	testHelperPrintSummaryLine("Copy constructor",           table_copy_correct_count,   2);
	testHelperPrintSummaryLine("Copy after delete original", table_delete_correct_count, 2);
	testHelperPrintSummaryLine("Assignment operator",        assign_correct_count,       4);
	testHelperPrintSummaryLine("Self-assignment",            self_correct);
	testHelperPrintSummaryLine("Chained assignment",         chained_correct);
	testHelperPrintSummaryLine("Optional load constructor",  load_correct_count,         4);
	testHelperPrintSummaryLine("Optional save function",     save_correct_count,         3);

	unsigned int mark7 = calculateScore(correct_element_bytes, correct_allocated_count_fraction,
	                                    correct_allocated_destroy_fraction, correct_element_copy_fraction,
	                                    correct_score_table_bytes, empty_correct, insert_correct_fraction,
	                                    table_copy_correct_fraction, table_delete_correct_fraction,
	                                    assign_correct_fraction, self_correct, chained_correct,
	                                    load_correct_fraction, save_correct_fraction,
	                                    true);
	assert(mark7 <= TOTAL_MARKS);
	testHelperPrintMark(mark7, TOTAL_MARKS);

	testHelperWaitForEnter();
	return 0;
}



string getLinkedListDescription (unsigned int count)
{
	assert(count < 10);

	switch(count)
	{
	case 0:
		return "an empty linked list";
	case 1:
		return "a linked list of 1 element";
	default:
		{
			string message = "a linked list of ? elements";
			message[17] = '0' + count;
			return message;
		}
	}
}

bool checkAllocationCount (int count, int correct,
                           bool print_correct)
{
	if(count != correct)
	{
		cout << "* Incorrect: Allocation count is " << count << ", but should be " << correct << endl;
		return false;
	}

	if(print_correct)
		cout << "* Correct" << endl;
	return true;
}

bool checkAllocationCount (int count_before, int correct_before,
                           int count_after,  int correct_after,
                           bool print_correct)
{
	if(count_before != correct_before)
	{
		cout << "* Skipped: Allocation count was " << count_before << " before, but should be " << correct_before << endl;
		return false;
	}
	else if(count_after != correct_after)
	{
		cout << "* Incorrect: Allocation count is " << count_after << " after, but should be " << correct_after << endl;
		return false;
	}

	if(print_correct)
		cout << "* Correct" << endl;
	return true;
}

Element* createLinkedList (unsigned int count)
{
	Element* p_head    = NULL;
	Element* p_current = NULL;

	for(unsigned int i = 0; i < count; i++)
	{
		if(p_head == NULL)
		{
			p_head    = new Element;
			p_current = p_head;
		}
		else
		{
			p_current->p_next = new Element;
			p_current         = p_current->p_next;
		}

		p_current->name   = ELEMENT_NAMES[i];
		p_current->score  = ELEMENT_SCORES[i];
		p_current->p_next = NULL;
	}

	return p_head;
}

bool compareLinkedLists (const Element* p_original,
                         const Element* p_copy,
                         unsigned int count_correct)
{
	if(p_original == NULL)
	{
		assert(count_correct == 0);

		if(p_copy == NULL)
		{
			// special case: comparing 2 empty linked lists
			cout << "* Correct" << endl;
			return true;
		}
		else
		{
			cout << "* Incorrect: Head pointer isn't NULL but should be" << endl;
			return false;
		}
	}
	else
	{
		assert(count_correct != 0);

		if(p_copy == NULL)
		{
			cout << "* Incorrect: Head pointer is NULL but shouldn't be" << endl;
			return false;
		}
		else if(p_copy == p_original)
		{
			cout << "* Incorrect: Head pointer points at original list" << endl;
			return false;
		}
	}

	const Element* p_original_head = p_original;
	const Element* p_copy_head     = p_copy;

	for(unsigned int i = 0; i < count_correct; i++)
	{
		assert(p_original != NULL);
		assert(p_copy     != NULL);

		if(p_original->name != ELEMENT_NAMES[i])
			cout << "* Incorrect: Name for original element " << i << " has been damaged" << endl;
		else if(p_copy->name != ELEMENT_NAMES[i])
		{
			cout << "* Incorrect: Element " << i << " has name \"" << p_copy->name
			     << "\" but should have \"" << ELEMENT_NAMES[i] << "\"" << endl;
			return false;
		}

		if(p_original->score != ELEMENT_SCORES[i])
			cout << "* Incorrect: Name for original element " << i << " has been damaged" << endl;
		else if(p_copy->score != ELEMENT_SCORES[i])
		{
			cout << "* Incorrect: Element " << i << " has score " << p_copy->score
			     << " but should have " << ELEMENT_SCORES[i] << endl;
		}

		if(p_original->p_next == NULL)
		{
			if(i + 1 != count_correct)
			{
				cout << "* Incorrect: Next pointer for original element " << i << " has been damaged" << endl;
				return false;
			}
			else if(p_copy->p_next != NULL)
			{
				cout << "* Incorrect: Next pointer for element " << i << " isn't NULL but should be" << endl;
				return false;
			}
		}
		else
		{
			if(i + 1 == count_correct)
			{
				cout << "* Incorrect: Next pointer for original element " << i << " has been damaged" << endl;
				return false;
			}
			else if(p_copy->p_next == NULL)
			{
				cout << "* Incorrect: Next pointer for element " << i << " is NULL but shouldn't be" << endl;
				return false;
			}
			else if(p_copy->p_next == p_copy)
			{
				cout << "* Incorrect: Next pointer for element " << i << " points at itself" << endl;
				return false;
			}
			else if(p_copy->p_next == p_copy_head)
			{
				cout << "* Incorrect: Next pointer for element " << i << " points at the lists head" << endl;
				return false;
			}
			else if(p_copy->p_next == p_original->p_next ||
			        p_copy->p_next == p_original         ||
			        p_copy->p_next == p_original_head)
			{
				cout << "* Incorrect: Next pointer for element " << i << " points at original list" << endl;
				return false;
			}
		}

		p_original = p_original->p_next;
		p_copy     = p_copy    ->p_next;
	}

	// general case: linked lists are the same
	cout << "* Correct" << endl;
	return true;
}



bool checkPrinted (const string& printed,
                   unsigned int present_bits,
                   bool is_print_result)
{
	if(printed.empty())
	{
		if(is_print_result)
			cout << "* Incorrect: Printed nothing" << endl;
		return false;
	}

	vector<string> lines = testHelperSplitWithoutEmpty(printed, '\n');
	if(lines.empty())
	{
		if(is_print_result)
			cout << "* Incorrect: Printed only blank lines" << endl;
		return false;
	}

	if(lines[0] != FIRST_LINE_CORRECT)
	{
		if(is_print_result)
			cout << "* Incorrect: First line should be \"" << FIRST_LINE_CORRECT << "\"" << endl;
		return false;
	}

	unsigned int extra_count    = 0;
	unsigned int missing_count  = 0;
	unsigned int unsorted_count = 0;

	int previous_score = INT_MAX;  // very large
	for(unsigned int i = 0; i < TEST_ENTRY_COUNT; i++)
	{
		stringstream ss;
		ss << TEST_ENTRY_SCORE[i] << "\t" << TEST_ENTRY_NAME[i];
		string desired_line = ss.str();
		unsigned int line_index = getIndexInVector(lines, desired_line);

		bool should_be_present = ((present_bits >> i) & 0x1) != 0x0;
		bool is_present        = line_index != STRING_NOT_IN_VECTOR;

		if(!should_be_present && is_present)
		{
			if(extra_count == 0 && is_print_result)
				cout << "* Incorrect: \"" << TEST_ENTRY_NAME[i] << "\" has a line but shouldn't" << endl;
			extra_count++;
		}
		else if(should_be_present && !is_present)
		{
			if(missing_count == 0 && is_print_result)
				cout << "* Incorrect: \"" << TEST_ENTRY_NAME[i] << "\" should have a line but doesn't" << endl;
			missing_count++;
		}

		if(should_be_present && is_present)
		{
			if(TEST_ENTRY_SCORE[i] > previous_score)
			{
				if(unsorted_count == 0 && is_print_result)
					cout << "* Incorrect: \"" << TEST_ENTRY_NAME[i] << "\" was not in sorted order" << endl;
				unsorted_count++;
			}
			if(previous_score > TEST_ENTRY_SCORE[i])
				previous_score = TEST_ENTRY_SCORE[i];
		}
	}

	bool is_correct = extra_count == 0   &&
	                  missing_count == 0 &&
	                  unsorted_count == 0;
	if(is_print_result)
	{
		if(missing_count > 1)
			cout << "* " << (missing_count - 1) << " more lines missing" << endl;
		if(extra_count > 1)
			cout << "* " << (extra_count - 1) << " more extra lines" << endl;
		if(unsorted_count > 1)
			cout << "* " << (unsorted_count - 1) << " more unsorted lines" << endl;
		if(is_correct)
			cout << "* Correct" << endl;
	}

	return is_correct;
}

unsigned int getIndexInVector(const vector<string>& search_in,
                              const string& search_for)
{
	for(unsigned int i = 0; i < search_in.size(); i++)
		if(search_in[i] == search_for)
			return i;
	return STRING_NOT_IN_VECTOR;
}

bool checkCopy (const string& source,
                const string& destination,
                unsigned int present_bits)

{
	bool is_source_correct = checkPrinted(source, present_bits, false);
	if(!is_source_correct)
	{
		cout << "* Check failed: source data was incorrect" << endl;
		return false;
	}

	vector<string> source_lines      = testHelperSplitWithoutEmpty(source,      '\n');
	vector<string> destination_lines = testHelperSplitWithoutEmpty(destination, '\n');
	assert(!source_lines.empty());
	assert(!destination_lines.empty());

	if(source_lines.size() == 1)
	{
		if(destination_lines.size() == 1)
		{
			if(source_lines[0] != destination_lines[0])
			{
				cout << "* Incorrect: First line didn't match somehow" << endl;
				return false;
			}
		}
		else
		{
			assert(destination_lines.size() > 1);
			cout << "* Incorrect: Destination shouldn't have printed any scores" << endl;
			return false;
		}
	}
	else
	{
		assert(source_lines.size() > 1);
		if(destination_lines.size() == 1)
		{
			cout << "* Incorrect: Destination should print scores" << endl;
			return false;
		}
		else
		{
			assert(destination_lines.size() > 1);

			if(source_lines.size() != destination_lines.size())
			{
				cout << "* Incorrect: Destination printed " << destination_lines.size()
						<< " scores, should be " << source_lines.size() << endl;
				return false;
			}
			assert(source_lines.size() == destination_lines.size());

			for(unsigned int i = 1; i < source_lines.size(); i++)
			{
				bool is_matched = false;
				for(unsigned int j = 1; j < destination_lines.size(); j++)
					if(source_lines[i] == destination_lines[j])
					{
						is_matched = true;
						break;
					}

				if(!is_matched)
				{
					cout << "* Incorrect: Score " << i << " doesn't match" << endl;
					return false;
				}
			}
		}
	}

	cout << "* Correct" << endl;
	return true;
}



unsigned int calculateScore (bool correct_element_bytes,
                             double correct_allocated_count_fraction,
                             double correct_destroy_linked_list_fraction,
                             double correct_copy_linked_list_fraction,
                             bool correct_score_table_bytes,
                             bool correct_print_empty,
                             double correct_insert_fraction,
                             double correct_copy_fraction,
                             double correct_delete_fraction,
                             double correct_assign_fraction,
                             bool correct_self_assign,
                             bool correct_chained_assign,
                             double correct_load_fraction,
                             double correct_save_fraction,
                             bool is_finished_without_crash)
{
	unsigned int mark = COMPILE_AND_START_MARKS;
	if(is_finished_without_crash)
		mark = COMPILE_AND_NOT_CRASH_MARKS;

	if(correct_element_bytes)
		mark += 1;
	if(correct_allocated_count_fraction == 1.0)
		mark += 2;
	mark += (int)(correct_destroy_linked_list_fraction * 2);
	mark += (int)(correct_copy_linked_list_fraction    * 4);

	if(correct_score_table_bytes)
		mark += 1;
	if(correct_print_empty)
		mark += 2;
	mark += (int)(correct_insert_fraction * 6);

	// code is mostly checked with correct_copy_linked_list_fraction and correct_destroy_linked_list_fraction
	if(correct_copy_fraction == 1.0 && correct_delete_fraction == 1.0)
		mark += 1;
	if(correct_assign_fraction == 1.0 && correct_self_assign && correct_chained_assign)
		mark += 1;

	// now optional, so worth no marks
	mark += (int)(correct_load_fraction * 0);
	mark += (int)(correct_save_fraction * 0);

	assert(mark <= TOTAL_MARKS);
	return mark;
}
