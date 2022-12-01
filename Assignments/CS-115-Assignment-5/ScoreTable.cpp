// Name: Owen Monus
// Student Number: 200482797
// Date: Dec 1, 2022

#include "ScoreTable.h"
#include <iostream>

using namespace std;

Element::Element() {
    name = "";
    score = 0;
    p_next = nullptr;
    element_count++;
}

Element::~Element() {
    element_count--;
}

int getAllocatedElementCount() {
    return element_count;
}

Element *copyLinkedList(const Element *p_head1) {
    if (p_head1 == nullptr) {
        return nullptr;
    }
    Element *p_head = new Element();

    // Copy the p_head data over
    p_head->p_next = p_head1->p_next;
    p_head->score = p_head1->score;
    p_head->name = p_head1->name;

    // Create a temp variable
    Element *tmp = p_head;
    Element *current = p_head;

    // Move to next item in linked list.
    tmp = tmp->p_next;

    while (tmp != nullptr) {
        // Allocate new memory for a new 'node'.
        current->p_next = new Element();
        // Point to this new 'node'.
        current = current->p_next;
        // Copy over the data.
        current->score = tmp->score;
        current->name = tmp->name;
        // By default, set the 'next' to null.
        current->p_next = nullptr;
        // Move along ll's list.
        tmp = tmp->p_next;
    }
    return p_head;
}

void destroyLinkedList(Element *p_head) {
//    Store the address of the first node in a pointer.
//     move the p_head node to the next node
//    dispose or free memory  of the pointer node
    if (p_head == nullptr) {
        return;
    }

    while (p_head->p_next != nullptr) {
        Element *tmp = p_head;
        p_head = p_head->p_next;
        delete tmp;
    }
    delete p_head;
}

ScoreTable::ScoreTable() {
    p_head = nullptr;
    assert(isInvariantTrue());
}

void ScoreTable::print() const {
    assert(isInvariantTrue());
    cout << "Scores:" << endl;
    Element *currPtr = p_head;
    while (currPtr != nullptr) {
        cout << currPtr->score << '\t' << currPtr->name << endl;
        currPtr = currPtr->p_next;
    }
}

void ScoreTable::insert(const std::string &player_name, int score) {
    assert(isInvariantTrue());
    Element *pPrev = nullptr;
    Element *pCurrent = p_head;
    while (pCurrent != nullptr && pCurrent->score > score) {
        pPrev = pCurrent;
        pCurrent = pCurrent->p_next;
    }
    Element *newElement = new Element();
    newElement->score = score;
    newElement->name = player_name;

    if (pPrev == nullptr) {
        // Insert at head
        newElement->p_next = p_head;
        p_head = newElement;
    } else {
        // Insert after pPrev
        newElement->p_next = pPrev->p_next;
        pPrev->p_next = newElement;
    }
    assert(isInvariantTrue());
}

ScoreTable::ScoreTable(const ScoreTable &to_copy) {
    assert(to_copy.isInvariantTrue());
    p_head = copyLinkedList(to_copy.p_head);
    assert(isInvariantTrue());
}

ScoreTable::~ScoreTable() {
    destroyLinkedList(p_head);
    p_head = nullptr;
}

ScoreTable &ScoreTable::operator=(const ScoreTable &to_copy) {
    assert(to_copy.isInvariantTrue());
    if (this != &to_copy) {
        destroyLinkedList(p_head);
        p_head = copyLinkedList(to_copy.p_head);
    }
    assert(isInvariantTrue());
    return *this;
}

bool ScoreTable::isInvariantTrue() const {
    if (p_head == nullptr) {
        return true;
    }

    Element* pPrevious = p_head;
    for (Element* pCurrent = p_head -> p_next; pCurrent != nullptr; pCurrent = pCurrent -> p_next) {
        if (pPrevious -> score < pCurrent -> score)
            return false;
    }
    return true;
}

