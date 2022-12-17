template <typename data_type> class Node {
public:
  Node *p_next;
  data_type datum;

  Node<data_type>(Node<data_type> *p_next, data_type datum);

  Node<data_type>();
  Node<data_type> &operator=(Node<data_type> &toAssign);
  Node<data_type>(const Node<data_type> &toCopy);
};

template <typename data_type> class LinkedList {
public:
  LinkedList();
  LinkedList(const LinkedList<data_type> &toCopy);
  ~LinkedList();
  LinkedList &operator=(const LinkedList<data_type> &toCooy);

  const bool empty();
  unsigned int memberCount();
  void remove(data_type datum);
  void insert(data_type datum);
  void print();

private:
  Node<data_type> *head;
};
