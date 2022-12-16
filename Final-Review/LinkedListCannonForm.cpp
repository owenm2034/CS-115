#include "LinkedListCannonForm.h"
#include <algorithm>
#include <cstddef>
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
  head = toCopy.head;
  Node *copyFrom = toCopy.head;
  Node *current = head;
  
  
  
  while (copyFrom != nullptr) {
  
    current->p_next = new Node(copyFrom->p_next, copyFrom->datum);
  
    copyFrom = copyFrom->p_next;
    current = current->p_next;
  
  }
  
  current->p_next = nullptr;
}


LinkedList::~LinkedList() {
  Node *p_curr = head;
  Node *p_next;
  while (p_curr != nullptr) {
    p_next = p_curr->p_next;
    delete p_curr;
    p_curr = p_next;
  }
  head = nullptr;
}

LinkedList &LinkedList::operator=(LinkedList toCopy) {
  Node *p_curr = head;
  Node *p_next;
  while (p_curr != nullptr) {
    p_next = p_curr->p_next;
    delete p_curr;
    p_curr = p_next;
  }
  head = toCopy.head;
  Node *copyFrom = toCopy.head;
  Node *current = head;
  while (copyFrom != nullptr) {
    current->p_next = new Node(copyFrom->p_next, copyFrom->datum);
    copyFrom = copyFrom->p_next;
    current = current->p_next;
  }
  return *this;
}

void LinkedList::insert(int datum) {
  Node *current = head;
  Node *previous = nullptr;
  while (current != nullptr && current->datum < datum) {
    previous = current;
    current = current->p_next;
  }
  if (previous == nullptr) {
    head = new Node(head, datum);
  } else {
    previous->p_next = new Node(current, datum);
  }
}
