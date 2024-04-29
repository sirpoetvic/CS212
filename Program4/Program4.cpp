#include <iostream>
#include <string>
#include "LinkedList.h"
#include <cassert>
using namespace std;

int main() {
  LinkedList<int> list;

  // Test add and printList
  list.add(1);
  list.add(2);
  list.add(3);
  list.printList(); // Should print "1 2 3"

  // Test addLast
  list.addLast(4);
  list.printList(); // Should print "1 2 3 4"

  // Test contains
  assert(list.contains(1));
  assert(!list.contains(5));

  // Test lastIndexOf
  assert(list.lastIndexOf(1) == 1);
  assert(list.lastIndexOf(4) == 4);
  assert(list.lastIndexOf(5) == -1);

  // Test remove
  assert(list.remove(1));
  list.printList(); // Should print "2 3 4"
  assert(!list.remove(1));
  list.printList(); // Should still print "2 3 4"

  // Test addAll
  LinkedList<int> otherList;
  otherList.add(5);
  otherList.add(6);
  assert(list.addAll(otherList));
  list.printList(); // Should print "2 3 4 5 6"

  // Test removeAll
  assert(list.removeAll(otherList));
  list.printList(); // Should print "2 3 4"

  // Test retainAll
  otherList.add(4);
  assert(list.retainAll(otherList));
  list.printList(); // Should print "4"

  return 0;
}
