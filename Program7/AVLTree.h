#ifndef AVLTREE_H
#define AVLTREE_H

#include "Node.h"

class AVLTree {
private:
   Node* root;
   
   void DeleteTree(Node* subtreeRoot) {
      if (subtreeRoot) {
         DeleteTree(subtreeRoot->left);
         DeleteTree(subtreeRoot->right);
         delete subtreeRoot;
      }
   }
   
   bool RemoveNode(Node* nodeToRemove) {
      // Base case: 
      if (!nodeToRemove) {
         return false;
      }
        
      // Parent needed for rebalancing.
      Node* parent = nodeToRemove->parent;
        
      // Case 1: Internal node with 2 children
      if (nodeToRemove->left && nodeToRemove->right) {
         // Find successor
         Node* successorNode = nodeToRemove->right;
         while (successorNode->left) {
            successorNode = successorNode->left;
         }
            
         // Copy the value from the node
         nodeToRemove->key = successorNode->key;
            
         // Recursively remove successor
         RemoveNode(successorNode);
            
         // Nothing left to do since the recursive call will have rebalanced
         return true;
      }
    
      // Case 2: Root node (with 1 or 0 children)
      else if (nodeToRemove == root) {
         if (nodeToRemove->left) {
            root = nodeToRemove->left;
         }
         else {
            root = nodeToRemove->right;
         }

         if (root) {
            root->parent = nullptr;
         }

         delete nodeToRemove;
         return true;
      }
      
      // Case 3: Internal with left child only
      else if (nodeToRemove->left) {
         parent->ReplaceChild(nodeToRemove, nodeToRemove->left);
      }
        
      // Case 4: Internal with right child only OR leaf
      else {
         parent->ReplaceChild(nodeToRemove, nodeToRemove->right);
      }
      
      // nodeToRemove is removed from the tree and can be deleted
      delete nodeToRemove;
        
      // Anything that was below nodeToRemove that has persisted is already 
      // correctly balanced, but ancestors of nodeToRemove may need rebalancing.
      Node* nodeToRebalance = parent;
      while (nodeToRebalance) {
         Rebalance(nodeToRebalance);         
         nodeToRebalance = nodeToRebalance->parent;
      }
    
      return true;
   }
   
public:
   AVLTree() {
      root = nullptr;
   }
   
   virtual ~AVLTree() {
      DeleteTree(root);
      root = nullptr;
   }
   
   Node* GetRoot() {
      return root;
   }
   
   // Performs a left rotation at the given node. Returns the
   // subtree's new root.
   Node* RotateLeft(Node* node) {
      // Define a convenience pointer to the right child of the 
      // left child.
      Node* rightLeftChild = node->right->left;
        
      // Step 1 - the right child moves up to the node's position.
      // node is temporarily detached from the tree, but will be reattached
      // later.
      if (node->parent) {
         node->parent->ReplaceChild(node, node->right);
      }
      else { // node is root
         root = node->right;
         root->parent = nullptr;
      }

      // Step 2 - the node becomes the left child of what used
      // to be node's right child, but is now node's parent. This will
      // detach rightLeftChild from the tree.
      node->right->SetChild(Node::LEFTCHILD, node);
        
      // Step 3 - reattach rightLeftChild as the right child of node.
      node->SetChild(Node::RIGHTCHILD, rightLeftChild);
        
      return node->parent;
   }
   
   // Performs a right rotation at the given node. Returns the
   // subtree's new root.
   Node* RotateRight(Node* node) {
      // Define a convenience pointer to the left child of the 
      // right child.
      Node* leftRightChild = node->left->right;
        
      // Step 1 - the left child moves up to the node's position.
      // node is temporarily detached from the tree, but will be reattached
      // later.
      if (node->parent != nullptr) {
         node->parent->ReplaceChild(node, node->left);
      }
      else { // node is root
         root = node->left;
         root->parent = nullptr;
      }

      // Step 2 - the node becomes the right child of what used
      // to be node's left child, but is now node's parent. This will
      // detach leftRightChild from the tree.
      node->left->SetChild(Node::RIGHTCHILD, node);
        
      // Step 3 - reattach leftRightChild as the right child of node.
      node->SetChild(Node::LEFTCHILD, leftRightChild);
        
      return node->parent;
   }
   
   // Updates the given node's height and rebalances the subtree if
   // the balancing factor is now -2 or +2. Rebalancing is done by
   // performing a rotation. Returns the subtree's new root if
   // a rotation occurred, or the node if no rebalancing was required.
   Node* Rebalance(Node* node) {
      // First update the height of this node.
      node->UpdateHeight();      

      // Check for an imbalance.
      if (node->GetBalance() == -2) {
         // The subtree is too big to the right.
         if (node->right->GetBalance() == 1) {
            // Double rotation case. First do a right rotation
            // on the right child.
            RotateRight(node->right);
         }

         // A left rotation will now make the subtree balanced.
         return RotateLeft(node);
      }
      else if (node->GetBalance() == 2) {
         // The subtree is too big to the left
         if (node->left->GetBalance() == -1) {
            // Double rotation case. First do a left rotation
            // on the left child.
            RotateLeft(node->left);
         }

         // A right rotation will now make the subtree balanced.
         return RotateRight(node);
      }
            
      // No imbalance, so just return the original node.
      return node;
   }
   
   // Searches for a node with a matching key. Does a regular
   // binary search tree search operation. Returns the node with the
   // matching key, or nullptr if no matching key exists in the tree.
   Node* Search(float desiredKey) {
      Node* currentNode = root;
      while (currentNode) {
         // Return the node if the key matches
         if (currentNode->key == desiredKey) {
            return currentNode;
         }
         
         // Navigate to the left if the search key is 
         // less than the node's key.
         else if (desiredKey < currentNode->key) {
            currentNode = currentNode->left;
         }
         
         // Navigate to the right if the search key is 
         // greater than the node's key.
         else {
            currentNode = currentNode->right;
         }
      }
      
      // The key was not found in the tree.
      return nullptr;
   }
   
   void Insert(Node* node) {
      // Check if tree is empty
      if (!root) {
         root = node;
      }
      else {
         // Step 1 - do a regular binary search tree insert.
         Node* currentNode = root;
         while (currentNode) {
            // Choose to go left or right
            if (node->key < currentNode->key) {
               // Go left. If left child is null, insert the new
               // node here.
               if (currentNode->left == nullptr) {
                  currentNode->left = node;
                  node->parent = currentNode;
                  currentNode = nullptr;
               }
               else {
                  // Go left and do the loop again.
                  currentNode = currentNode->left;
               }
            }
            else {
               // Go right. If the right child is null, insert the
               // new node here.
               if (currentNode->right == nullptr) {
                  currentNode->right = node;
                  node->parent = currentNode;
                  currentNode = nullptr;
               }
               else {
                  // Go right and do the loop again.
                  currentNode = currentNode->right;
               }
            }
         }

         // Step 2 - Rebalance along a path from the new node's parent up
         // to the root.
         node = node->parent;
         while (node) {
            Rebalance(node);
            node = node->parent;
         }
      }
   }
   
   // Attempts to remove a node with a matching key. If no node has a matching 
   // key then nothing is done and false is returned; otherwise the node is 
   // removed and true is returned.
   bool RemoveKey(int key) {
      Node* node = Search(key);
      if (!node) {
         return false;
      }
      else {
         return RemoveNode(node);
      }
   }
};

#endif