// Name: Owen Monus
// Student Number: 200482797
// Date: Nov 21

// Filename: LinkedList.cpp

// Note: This implementation of LinkedList is based on 
// Chapter 4 of Bruno R. Preiss's Textbook: 
// "Data Structures and Algorithms with Object-Oriented Design Patterns in C++"

#include <cstdlib>
#include <cassert>
#include "LinkedList.h"
using namespace std;

//---------------------------------------------------
//List Element Members
//---------------------------------------------------
ListElement::ListElement(int _datum, ListElement * _next):
   datum (_datum), next (_next)
{}


int ListElement::getDatum () const
{ 
  return datum; 
}


ListElement const* ListElement::getNext () const
{ 
  return next; 
}



//---------------------------------------------------
//LinkedList Members
//---------------------------------------------------
LinkedList::LinkedList () :
  head (0)
{}

void LinkedList::insertItem(int item)
{
  ListElement* currPtr = head;
  ListElement* prevPtr = nullptr; //prevPtr points to the element before currPtr in the list
  ListElement* newNodePtr;      // points to a new node
  
  while(currPtr != nullptr && item > currPtr->datum)
  {
    prevPtr = currPtr;
    currPtr = currPtr->next;
  } 

  newNodePtr = new ListElement(item, currPtr);
  
  if (prevPtr == nullptr) // insert at the beginning
    head = newNodePtr;
  else
    prevPtr->next = newNodePtr;
}

void LinkedList::makeList()
{
  int input;
  ListElement* currPtr;
  ListElement* newNodePtr;   
  
  cout << "Enter values for a linked list, one per line." << endl;
  cout << "Enter 999 to end the list." << endl;

  cin >> input;
  //Adding elements to end so that "next" will be nullptr
  newNodePtr = new ListElement(input, nullptr);
  head = newNodePtr;  //assign head to the first Node
  currPtr = head; 
  cin >> input;

  while (input != 999)
  {
    newNodePtr = new ListElement(input, nullptr);
    currPtr->next = newNodePtr;     //link the new node to list
    currPtr = newNodePtr;           //move the currPtr so it is at end of list
    cin >> input;
  }
              
}

void LinkedList::appendItem (int item)
{
  // REMOVE the cout statement on line 94
  // then write your code here!
   
    ListElement* currPtr = head;
    while(currPtr -> next != NULL) {
      currPtr = currPtr -> next;
    }
    ListElement* newNodePtr = new ListElement(item, nullptr);  
    currPtr -> next = newNodePtr;
}

void LinkedList::deleteItem (int item)
{
  // REMOVE the cout statement on line 101
  // then write your code here!

 // If "item" is in the first node
  if ( head -> datum == item) {
    ListElement* deletePtr = head;
    head = deletePtr -> next;
    delete deletePtr;
  } else {
      ListElement* previousPtr = head;
      while (previousPtr -> next != nullptr && previousPtr -> next -> datum != item) {
      previousPtr = previousPtr -> next;
      }

      if (previousPtr -> next != nullptr) {
        ListElement* deletePtr = previousPtr -> next;
        previousPtr -> next = deletePtr -> next;
        delete deletePtr;
      } else {
      cout << item << " was not found in the linked list" << endl;
    }
  }


}

void LinkedList::printList () 
{
  // REMOVE the cout statement on line 108
  // then write your code here!

  ListElement* currPtr = head;
  while(currPtr != NULL) {
    cout << currPtr -> datum << endl;
    currPtr = currPtr -> next;
  }
}