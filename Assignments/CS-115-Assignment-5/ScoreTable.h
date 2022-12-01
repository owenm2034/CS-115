// Name: Owen Monus
// Student Number: 200482797
// Date: Dec 1, 2022

#ifndef CS_115_ASSIGNMENT_5_SCORETABLE_H
#define CS_115_ASSIGNMENT_5_SCORETABLE_H

#include <string>

using namespace std;

static int element_count = 0;

class Element {
public:
    string name;
    int score;
    Element *p_next;

    /**
     * @brief Initializes all members to appropriate values. Sets p_next to
     * nullptr. Increments element_count by 1
     */
    Element();

    ~Element();
};

/**
 * @return the amount of elements that exist
 */
int getAllocatedElementCount();

Element *copyLinkedList(const Element *p_head1);

void destroyLinkedList(Element *p_head);

class ScoreTable {
public:
    Element* p_head = nullptr;

    //
    //  ScoreTable
    //  default constructor
    //
    //  Purpose: Initialize all members to appropriate values
    //  Parameter(s): N/A
    //  Precondition(s): N/A
    //  Returns: N/A
    //  Side Effect: N/A
    //  Post-condition(s):
    //    <1> p_head is set to nullptr
    ScoreTable();

    //
    //  ScoreTable
    //  copy constructor
    //
    //  Purpose: Create a deep copy of an already existing instance of score table
    //  Parameter(s):
    //    <1> to_copy: a pass-by-constant-reference instance of ScoreTable you'd like to copy from
    //  Precondition(s):
    //    <1> the passed instance of ScoreTable is sorted in descending order
    //  Returns: N/A
    //  Side Effect: N/A
    //  Post-condition(s):
    //    <1> p_head is the head of a linked list identical to to_copy's linked list.
    ScoreTable(const ScoreTable &to_copy);

    ~ScoreTable();

    //
    //  operator=
    //  assignment operator
    //
    //  Purpose: Assign a deep copy of a ScoreTable to another ScoreTable
    //  Parameter(s):
    //    <1> to_copy: a pass-by-constant-reference instance of ScoreTable you'd like to assign to another ScoreTable
    //  Precondition(s):
    //    <1> the passed instance of ScoreTable is sorted in descending order
    //  Returns: An address of the newly assigned ScoreTable
    //  Side Effect: N/A
    //  Post-condition(s):
    //    <1> the returned ScoreTable is identical to the passed ScoreTable
    ScoreTable& operator=(const ScoreTable &to_copy);

    //
    //  print
    //
    //  Purpose: Print out the contents of a ScoreTable
    //  Parameter(s): N/A
    //  Precondition(s): N/A
    //  Returns: N/A
    //  Side Effect: N/A
    //  Post-condition(s): N/A
    //
    void print() const;

    //
    //  insert
    //
    //  Purpose: Insert a new Element into a ScoreTable in descending order
    //  Parameter(s):
    //    <1> player_name: a pass-by-constant-reference string with a players name
    //    <2> score: an integer containing the players score
    //  Precondition(s): N/A
    //  Returns: N/A
    //  Side Effect: N/A
    //  Post-condition(s):
    //    <1> a new element is created containing the players data and is inserted appropriately
    //          (in descending order) into the linked list
    void insert(const string &player_name, int score);

private:
    bool isInvariantTrue() const;
};



#endif //CS_115_ASSIGNMENT_5_SCORETABLE_H

