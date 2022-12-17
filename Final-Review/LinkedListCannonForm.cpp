#include "LinkedListCannonForm.h"
#include <iostream>

using namespace std;

template <typename data_type>
Node<data_type>::Node(Node<data_type> *p_next, data_type datum)
    : p_next(p_next), datum(datum){};

template <typename data_type> Node<data_type>::Node() {
  datum = 0;
  p_next = nullptr;
}

template <typename data_type>
Node<data_type> &Node<data_type>::operator=(Node &toAssign) {
  datum = toAssign.datum;
  p_next = toAssign.p_next;
  return *this;
}

template <typename data_type>
Node<data_type>::Node(const Node<data_type> &toCopy) {
  if (this != &toCopy) {
    datum = toCopy.datum;
    p_next = toCopy.p_next;
  }
}

template <typename data_type> LinkedList<data_type>::LinkedList() {
  head = nullptr;
}

template <typename data_type>
LinkedList<data_type>::LinkedList(const LinkedList &toCopy) {
  Node<data_type> *oldLLPtr = toCopy.head;
  head = new Node<data_type>(nullptr, oldLLPtr->datum);

  if (toCopy.head != nullptr) {
    Node<data_type> *current = head;
    while (oldLLPtr->p_next != nullptr) {
      current->p_next = new Node<data_type>();
      current = current->p_next;
      current->datum = oldLLPtr->p_next->datum;
      oldLLPtr = oldLLPtr->p_next;
    }
    current->p_next = nullptr;
  }
}

template <typename data_type> LinkedList<data_type>::~LinkedList() {
  Node<data_type> *pPrev = NULL;
  Node<data_type> *pCurr = head;

  while (pCurr != nullptr) {
    pPrev = pCurr;
    pCurr = pCurr->p_next;
    delete pPrev;
  }
}

template <typename data_type>
LinkedList<data_type> &
LinkedList<data_type>::operator=(const LinkedList<data_type> &toCopy) {
  Node<data_type> *pPrev = nullptr;
  Node<data_type> *pCurr = head;

  while (pCurr != nullptr) {
    pPrev = pCurr;
    pCurr = pCurr->p_next;
    delete pPrev;
  }

  Node<data_type> *oldLLPtr = toCopy.head;
  head = new Node<data_type>(nullptr, oldLLPtr->datum);

  if (toCopy.head != nullptr) {
    Node<data_type> *current = head;
    while (oldLLPtr->p_next != nullptr) {
      current->p_next = new Node<data_type>();
      current = current->p_next;
      current->datum = oldLLPtr->p_next->datum;
      oldLLPtr = oldLLPtr->p_next;
    }
    current->p_next = nullptr;
  }
  return *this;
}

template <typename data_type> const bool LinkedList<data_type>::empty() {
  return (head == nullptr);
}

template <typename data_type>
unsigned int LinkedList<data_type>::memberCount() {
  Node<data_type> *pCurr = head;
  unsigned int memberCount = 0;
  while (pCurr != nullptr) {
    pCurr = pCurr->p_next;
    memberCount++;
  }
  return memberCount;
}

template <typename data_type>
void LinkedList<data_type>::remove(data_type datum) {
  Node<data_type> *pPrev = nullptr;
  Node<data_type> *pCurr = head;

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
      pPrev->p_next = new Node<data_type>(nullptr, datum);
    } else {
      Node<data_type> *pTemp = pCurr;
      pPrev->p_next = pCurr->p_next;
      delete pTemp;
    }
  }
}

template <typename data_type>
void LinkedList<data_type>::insert(data_type datum) {
  Node<data_type> *pPrev = nullptr;
  Node<data_type> *pCurr = head;

  while (pCurr != nullptr && pCurr->datum < datum) {
    pPrev = pCurr;
    pCurr = pCurr->p_next;
  }
  if (pPrev == nullptr) {
    Node<data_type> *pTemp = new Node<data_type>(head, datum);
    head = pTemp;
  } else {
    Node<data_type> *pTemp = new Node<data_type>(pPrev->p_next, datum);
    pPrev->p_next = pTemp;
  }
}

template <typename data_type> void LinkedList<data_type>::print() {
  for (Node<data_type> *pCurr = head; pCurr != NULL; pCurr = pCurr->p_next) {
    cout << pCurr->datum << '\t';
  }
  cout << endl;
}