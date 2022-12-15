#include <cstddef>
class Node {
 int* p_next = nullptr;
 int datum = 0;
 
 Node(int* p_next, int datum);
 
 Node();
 ~Node();
 Node& operator= (Node& toAssign);
 Node(const Node& toCopy);
};


class LinkedList{
	public:
		LinkedList();
		LinkedLi st(const LinkedList &toCopy);
		~LinkedList();
		LinkedList& operator=(LinkedList); 
	private:
		Node head;		
};