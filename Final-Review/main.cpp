#include "LinkedListCannonForm.h"
#include <iostream>

using namespace std;

int main() {
  LinkedList<int> ll = LinkedList<int>();

  // grab input
  cout << "Enter integers line by line to create a linked list" << endl;
  int entry;
  cin >> entry;
  while (entry != 999) {
    ll.insert(entry);
    cin >> entry;
  }

  // print linked list
  cout << "Printed LL" << endl;
  ll.print();

  // delete linked list

  // testing assignment operator
  cout << "Testing the assigmment operator" << endl;
  LinkedList<int> ll2 = ll;

  ll2.print();

  cout << "Testing the assignment constructor" << endl;
  LinkedList<int> ll3(ll2);

  ll3.print();

  cout << "Enter a number to be removed from the LL" << endl;
  cin >> entry;
  ll.remove(entry);

  cout << "After removing entry: " << endl;
  ll.print();

  return 0;
}