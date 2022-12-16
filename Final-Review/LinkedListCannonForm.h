#include <cstddef>
class Node {
public:
  Node *p_next;
  int datum;

  Node(Node *p_next, int datum);

  Node();
  Node &operator=(Node &toAssign);
  Node(const Node &toCopy);
};

class LinkedList {
public:
  LinkedList();
  LinkedList(const LinkedList &toCopy);
  ~LinkedList();
  LinkedList &operator=(LinkedList);
  void insert(int datum);

private:
  Node *head;
};