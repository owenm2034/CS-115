//
//  TestElement5.cpp
//
//  A test program for the Element record in the ScoreTable
//    module.
//
//  This program is to be used with Assignment 5: Part B for
//    CS115, 202210.
//
//  Do not modify this file.
//
//  2022-03-25: Maximum marks increased from 12 to 15
//

#include "ScoreTable.h"
#include "ScoreTable.h"  // repeated to test for #include errors

#include <cassert>
#include <string>
#include <iostream>
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
unsigned int calculateScore (bool correct_element_bytes,
                             double correct_allocated_count_fraction,
                             double correct_destroy_linked_list_fraction,
                             double correct_copy_linked_list_fraction,
                             bool is_finished_without_crash);


const int COMPILE_AND_START_MARKS     =  2;
const int DID_NOT_CRASH_RUNNING_MARKS =  4;
const int COMPILE_AND_NOT_CRASH_MARKS = COMPILE_AND_START_MARKS + DID_NOT_CRASH_RUNNING_MARKS;
const int COMBINED_TEST_MARKS         = 24;
const int TOTAL_MARKS                 = COMPILE_AND_NOT_CRASH_MARKS + COMBINED_TEST_MARKS;

const unsigned int ELEMENT_COUNT_MAX  = 3;
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



int main ()
{
	testHelperStartup("TestElement5", COMPILE_AND_START_MARKS, TOTAL_MARKS);

	//
	//  Test Element type
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
	                                       0.0,     // destroyLinkedList
	                                       0.0,     // copyLinkedList
	                                       false);  // all finished
	unsigned int mark1 = calculateScore(correct_element_bytes, correct_allocated_count_fraction,
	                                    0.0,     // destroyLinkedList
	                                    0.0,     // copyLinkedList
	                                    false);  // all finished
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
	                                       0.0,     // copyLinkedList
	                                       false);  // all finished
	unsigned int mark2 = calculateScore(correct_element_bytes, correct_allocated_count_fraction,
	                                    correct_allocated_destroy_fraction,
	                                    0.0,     // copyLinkedList
	                                    false);  // all finished
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
	                                       true);
	unsigned int mark3 = calculateScore(correct_element_bytes, correct_allocated_count_fraction,
	                                    correct_allocated_destroy_fraction, correct_element_copy_fraction,
	                                    true);
	assert(mark3    <= TOTAL_MARKS);
	assert(highest3 <= TOTAL_MARKS);
	assert(mark3    <= highest3);
	testHelperPrintMarkPartial(mark3, highest3, TOTAL_MARKS);

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



unsigned int calculateScore (bool correct_element_bytes,
                             double correct_allocated_count_fraction,
                             double correct_destroy_linked_list_fraction,
                             double correct_copy_linked_list_fraction,
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

	assert(mark <= TOTAL_MARKS);
	return mark;
}
