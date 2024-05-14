#include <iostream>
#include "AVLTree.h"
#include "BSTPrint.h"
using namespace std;

int main() {
   // Create an empty AVLTree object.
   AVLTree tree;

   // Insert some random-looking integers into the tree.
   float keys[] = { 11.0, 20.4, 5.8, 2,2, 1.5, 4.7, 1.9, 3.9, 1.2, 1.8 };
   for (float key : keys) {
      Node* node = new Node(key);
      tree.Insert(node);
   }
      
   // Print the tree after all inserts are complete.
   cout << "Tree after initial insertions:" << endl;
   cout << BSTPrint::TreeToString(tree.GetRoot()) << endl;
   cout << endl;
       
   // Find and remove the node with the key value 12.
   // This should cause a right rotation on node 10.
   cout << "Remove node 12:" << endl;
   tree.RemoveKey(12);
   cout << BSTPrint::TreeToString(tree.GetRoot()) << endl;
   cout << endl;
       
   // Find and remove the node with the key value 20.
   // This should cause its right child to shift up into
   // the 20 node's position without any other reordering
   // required.
   cout << "Remove node 20:" << endl;
   tree.RemoveKey(20);
   cout << BSTPrint::TreeToString(tree.GetRoot()) << endl;
   cout << endl;
       
   // Attempt to remove a node with key 30, a value not in the tree.
   cout << "Remove node 30 (should not be in tree):" << endl;
   if (!tree.RemoveKey(30)) {
      cout << "*** Key not found. Tree is not changed. ***" << endl;
   }
   cout << BSTPrint::TreeToString(tree.GetRoot()) << endl;
}