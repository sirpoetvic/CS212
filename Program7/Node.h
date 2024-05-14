#ifndef NODE_H
#define NODE_H

class Node {
public:
   enum Child { LEFTCHILD, RIGHTCHILD };

   float key;
   Node* parent;
   Node* left;
   Node* right;
   int height;

   // Constructor with a key parameter creates the Node object.
   Node(float nodeKey) {
      key = nodeKey;
      parent = nullptr;
      left = nullptr;
      right = nullptr;
      height = 0;
   }
   
   // Calculate this nodes' balance factor, defined as 
   // height(left subtree) - height(right subtree)
   int GetBalance() {
      // Get current height of left subtree, or -1 if null
      int leftHeight = -1;
      if (left) {
         leftHeight = left->height;
      }
            
      // Get current height of right subtree, or -1 if null
      int rightHeight = -1;
      if (right) {
         rightHeight = right->height;
      }
            
      // Calculate the balance factor.
      return leftHeight - rightHeight;
   }
   
   // Recalculate the current height of the subtree rooted at
   // the node, usually called after a subtree has been 
   // modified.
   void UpdateHeight() {
      // Get current height of left subtree, or -1 if null
      int leftHeight = -1;
      if (left) {
         leftHeight = left->height;
      }
            
      // Get current height of right subtree, or -1 if null
      int rightHeight = -1;
      if (right) {
         rightHeight = right->height;
      }

      // Assign height with calculated node height.
      height = ((leftHeight > rightHeight) ? leftHeight : rightHeight) + 1;
   }
   
   // Assign either the left or right data member with a new
   // child. Returns true if the new child is successfully 
   // assigned to this node, false otherwise.
   bool SetChild(Child whichChild, Node* child) {
      // Assign the left or right data member.
      if (whichChild == LEFTCHILD) {
         left = child;
      }
      else {
         right = child;
      }

      // Assign the parent data member of the new child,
      // if the child is not null.
      if (child) {
         child->parent = this;
      }

      // Update the node's height, since the subtree's structure
      // may have changed.
      UpdateHeight();
      return true;
   }
   
   // Replace a current child with a new child. Determines if
   // the current child is on the left or right, and calls
   // setChild() with the new node appropriately.
   // Returns true if the new child is assigned, false otherwise.
   bool ReplaceChild(Node* currentChild, Node* newChild) {
      if (left == currentChild) {
         return SetChild(LEFTCHILD, newChild);
      }
      else if (right == currentChild) {
         return SetChild(RIGHTCHILD, newChild);
      }
      
      // If neither of the above cases applied, then the new child
      // could not be attached to this node.
      return false;
   }
};

#endif