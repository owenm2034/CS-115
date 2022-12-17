#include "LinkedListCannonForm.h"
#include <iostream>
using namespace std;

Node::Node(Node *p_next, int datum) : p_next(p_next), datum(datum){};

Node::Node() {
  datum = 0;
  p_next = nullptr;
}

Node &Node::operator=(Node &toAssign) {
  datum = toAssign.datum;
  p_next = toAssign.p_next;
  return *this;
}

Node::Node(const Node &toCopy) {
  if (this != &toCopy) {
    datum = toCopy.datum;
    p_next = toCopy.p_next;
  }
}

LinkedList::LinkedList() { head = nullptr; }

LinkedList::LinkedList(const LinkedList &toCopy) {
  Node *oldLLPtr = toCopy.head;
  head = new Node(nullptr, oldLLPtr->datum);

  if (toCopy.head != nullptr) {
    Node *current = head;
    while (oldLLPtr->p_next != nullptr) {
      current->p_next = new Node();
      current = current->p_next;
      current->datum = oldLLPtr->p_next->datum;
      oldLLPtr = oldLLPtr->p_next;
    }
    current->p_next = nullptr;
  }
}

LinkedList::~LinkedList() {
  Node *pPrev = NULL;
  Node *pCurr = head;

  while (pCurr != nullptr) {
    pPrev = pCurr;
    pCurr = pCurr->p_next;
    delete pPrev;
  }
}

LinkedList &LinkedList::operator=(const LinkedList &toCopy) {
  Node *pPrev = nullptr;
  Node *pCurr = head;

  while (pCurr != nullptr) {
    pPrev = pCurr;
    pCurr = pCurr->p_next;
    delete pPrev;
  }

  Node *oldLLPtr = toCopy.head;
  head = new Node(nullptr, oldLLPtr->datum);

  if (toCopy.head != nullptr) {
    Node *current = head;
    while (oldLLPtr->p_next != nullptr) {
      current->p_next = new Node();
      current = current->p_next;
      current->datum = oldLLPtr->p_next->datum;
      oldLLPtr = oldLLPtr->p_next;
    }
    current->p_next = nullptr;
  }
  return *this;
}

const bool LinkedList::empty() { return (head == nullptr); }

unsigned int LinkedList::memberCount() {
  Node *pCurr = head;
  unsigned int memberCount = 0;
  while (pCurr != nullptr) {
    pCurr = pCurr->p_next;
    memberCount++;
  }
  return memberCount;
}

void LinkedList::remove(int datum) {
  Node *pPrev = nullptr;
  Node *pCurr = head;

  if (head->datum == datum) {
    pPrev = head;
    head = head->p_next;
    delete pPrev;
  } else {
    while (pCurr != nullptr && pCurr->datum < datum) {
      pPrev = pCurr;
      pCurr = pCurr->p_next;
    }
    if (pCurr == nullptr) {
      pPrev->p_next = new Node(nullptr, datum);
    } else {
      Node *pTemp = pCurr;
      pPrev->p_next = pCurr->p_next;
      delete pTemp;
    }
  }
}
void LinkedList::insert(int datum) {
  Node *pPrev = nullptr;
  Node *pCurr = head;

  while (pCurr != nullptr && pCurr->datum < datum) {
    pPrev = pCurr;
    pCurr = pCurr->p_next;
  }
  if (pPrev == nullptr) {
    Node *pTemp = new Node(head, datum);
    head = pTemp;
  } else {
    Node *pTemp = new Node(pPrev->p_next, datum);
    pPrev->p_next = pTemp;
  }
}
void LinkedList::print() {
  Node *pCurr = head;
  for (Node *pCurr = head; pCurr != NULL; pCurr = pCurr->p_next) {
    cout << pCurr->datum << '\t';
  }
  cout << endl;
}