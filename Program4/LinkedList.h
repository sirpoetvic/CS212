// Original code from Daniel Liang (2003)
// now animated at yongdanielliang.github.io/animation/web/LinkedList.html
// 
// Extensively modified by W.P. Iverson
// Bellevue College, April 2024
// for CS212

/*
 * Victor Wong
 * Spring 2024, CS212, William Iverson
 * 04/22/2024
 * Program 4
 * LinkedList Data Structure
 */

#include <stdexcept>
#include <iostream>
using namespace std;

template<typename T>
class Node
{
public:
  Node() // No-arg constructor
  {
    next = NULL;
  }

  Node(T element) // Constructor
  {
    this->element = element;
    next = NULL;
  }

  // just for console testing:
  void printNodes()
  {
      Node<T>* current = this;
      while (current->next != NULL)
      {
          cout << current->element << " ";
          current = current->next;
      }
      cout << current->element << endl;
  }

  // so we can keep nodes private
  void setNext(Node<T>* change)
  {
      next = change;
  }

  T getData()
  {
      return element;
  }

  Node<T>* getNext()
  {
    return next;
  }

private:
    T element;  // Element contained in the node
    Node<T>* next; // Pointer to the next node
};

// template linked list class
template<typename T>
class LinkedList
{
public:
  LinkedList();
  void addLast(T);
  void add(T);
  void printList();

  // New methods added
  bool addAll(LinkedList<T>& otherList);
  bool removeAll(LinkedList<T>& otherList);
  bool retainAll(LinkedList<T>& otherList);
  bool remove(T);
  int lastIndexOf(T);
  bool contains(T);


private:
    Node<T>* head;
	Node<T>* tail;
    int size;
};

template<typename T>
LinkedList<T>::LinkedList()
{
  head = tail = NULL;
  size = 0;
}

template<typename T>
void LinkedList<T>::printList()
{
    head->printNodes();
}

template<typename T>
void LinkedList<T>::addLast(T element)
{
  if (tail == NULL)
  {
    head = tail = new Node<T>(element);
  }
  else
  {
      Node<T>* temp = new Node<T>(element);
      tail->setNext(temp);
      tail = temp;
  }
  size++;
}

// Standard List adds data at end of list
template<typename T>
void LinkedList<T>::add(T element)
{
  addLast(element);
}

template<typename T>
bool LinkedList<T>::remove(T element) {
  if (head == NULL) {
        return false;
    }

  // Case 1: Removing the first node (at the head of the list)
  if (head->getData() == element) {
    head = head->getNext();
    size--;
    return true;
  }

  // Case 2: Removing a node in the middle or end of the list 
  Node<T>* current = head;
  Node<T>* nextNode = current->getNext();
  while (nextNode != NULL) {
      if (nextNode->getData() == element) {
        current->setNext(nextNode->getNext());
        if (nextNode == tail) {
            tail = current; // Update tail if the node to be removed is the tail
            tail->setNext(NULL);
        }
        delete nextNode;
        size--;
        return true;
      }
    current = nextNode;
    nextNode = current->getNext();
  }

  //Case 3: not found
  return false;
}

template<typename T>
int LinkedList<T>::lastIndexOf(T element) {
  int elementIndex = -1;
  int currentIndex = 1;
  Node<T>* current = head;
  while (current != NULL) {
    if (current->getData() == element) {
      elementIndex = currentIndex;
    }
    currentIndex++;
    current = current->getNext();
  }
  return elementIndex;
}

template<typename T>
bool LinkedList<T>::contains(T element) {
  return !(lastIndexOf(element) == -1);
}

template<typename T>
bool LinkedList<T>::removeAll(LinkedList<T>& otherList) {
  if (otherList.head == NULL) {
    return false;
  }

  Node<T>* currentNode = otherList.head;
  bool listChanged = false;
  
  while(currentNode != NULL) {
    if (remove(currentNode->getData())) {
      listChanged = true;
    }
    currentNode = currentNode->getNext();
  }
  return listChanged;
}

template<typename T>
bool LinkedList<T>::retainAll(LinkedList<T>& otherList) {
  if (otherList.head == NULL) {
    return false;
  }

  Node<T>* currentNode = head;
  bool listChanged = false;

  while(currentNode != NULL) {
    T currentNodeData = currentNode->getData();
    currentNode = currentNode->getNext();  
    if (!otherList.contains(currentNodeData)) {
      if (remove(currentNodeData)) {
        listChanged = true;
      }
    }
  }
  return listChanged;
}

template<typename T>
bool LinkedList<T>::addAll(LinkedList<T>& otherList) {
  if (otherList.head == NULL) {
    return false;
  }

  Node<T>* current = otherList.head;

  for (int i = 0; i < otherList.size; i++) {
    addLast(current->getData());
    current = current->getNext();
  }

  return true;
}