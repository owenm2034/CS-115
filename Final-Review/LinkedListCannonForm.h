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
  LinkedList &operator=(const LinkedList &toCooy);

  const bool empty();
  unsigned int memberCount();
  void remove(int datum);
  void insert(int datum);
  void print();

private:
  Node *head;
};
