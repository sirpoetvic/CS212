#include <iostream>
#include <string>
#include <vector>
#include "Node.h"
#include "BinarySearchTree.h"
#include "BSTPrint.h"
using namespace std;

void SpaceSplit(const string& str, vector<string>& output) {
   size_t startIndex = 0;
   size_t endIndex = str.find(' ', startIndex);
   while (endIndex != string::npos) {
      // Only push non-empty strings
      if (endIndex > startIndex) {
         output.push_back(str.substr(startIndex, endIndex - startIndex));
      }
      
      // Get the next start and end indices
      startIndex = endIndex + 1;
      endIndex = str.find(' ', startIndex);
   }
   output.push_back(str.substr(startIndex));
}

int main() {
   BinarySearchTree tree;
      
   // Ask user for values to insert
   cout << "Enter values to insert with spaces between: ";
   string userValuesString;
   getline(cin, userValuesString);
   cout << endl;
      
   // Add each value to the tree
   vector<string> userValues;
   SpaceSplit(userValuesString, userValues);
   for (string value : userValues) {
      int key = stoi(value);
      tree.Insert(new Node(key));
   }
      
   // Show the tree
   cout << "Initial tree:" << endl;
   cout << BSTPrint::TreeToString(tree.GetRoot()) << endl;
   cout << endl;
      
   // Ask the user for a value to remove
   cout << "Enter value to remove: ";
   string removeValueString;
   getline(cin, removeValueString);
   int removeValue = stoi(removeValueString);
   cout << endl;
      
   cout << "Tree after removing " << removeValue << ":" << endl;
   tree.Remove(removeValue);
   cout << BSTPrint::TreeToString(tree.GetRoot()) << endl;
}