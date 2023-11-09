
#include <iostream>
#include <vector>


int main() {
  vector<int> v1 = {7, 14, 21, 28, 9};
  LinkedListNode* list_head = LinkedList::create_linked_list(v1);

  cout << "Original list: ";
  LinkedList::display(list_head);

  list_head = reverse_even_nodes(list_head);
  cout <<"After reversing even nodes: ";
  LinkedList::display(list_head);
}
