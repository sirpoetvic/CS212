#ifndef SET_H
#define SET_H

// Original code from:
// Roman Lysecky / Professor of Electrical and Computer Engineering / Univ. of Arizona
// Frank Vahid / Professor of Computer Science and Engineering / Univ. of California

/*
 * Victor Wong
 * Spring 2024, CS212, William Iverson
 * 05/28/2024
 * Program 9
 * Iterator and Set structure
 */

#include <functional>
#include <iterator>

class BSTNode {
public:
    int data;
    BSTNode* parent;
    BSTNode* left;
    BSTNode* right;
    bool checked;

    BSTNode(int data, BSTNode* parent, BSTNode* left = nullptr, BSTNode* right = nullptr) {
        this->data = data;
        this->parent = parent;
        this->left = left;
        this->right = right;
        this->checked = false;
    }

    int Count() {
        int leftCount = 0;
        int rightCount = 0;
        if (left) {
            leftCount = left->Count();
        }
        if (right) {
            rightCount = right->Count();
        }
        return 1 + leftCount + rightCount;
    }

    BSTNode* GetSuccessor() {
        // Successor resides in right subtree, if present
        if (right) {
            BSTNode* successor = right;
            while (successor->left != nullptr) {
                successor = successor->left;
            }
            return successor;
        }

        // Otherwise the successor is up the tree
        // Traverse up the tree until a parent is encountered from the left
        BSTNode* node = this;
        while (node->parent && node == node->parent->right) {
            node = node->parent;
        }
        return node->parent;
    }

    void ReplaceChild(BSTNode* currentChild, BSTNode* newChild) {
        if (currentChild == left) {
            left = newChild;
            if (left) {
                left->parent = this;
            }
        }
        else if (currentChild == right) {
            right = newChild;
            if (right) {
                right->parent = this;
            }
        }
    }
};

class BSTIterator : public std::iterator<std::input_iterator_tag, int> {
private:
    BSTNode* startNode;
    BSTNode* currentNode;
    bool endReached;

public:
    BSTIterator(const BSTIterator& copyMe) {
        currentNode = copyMe.currentNode;
        startNode = copyMe.startNode;
        endReached = false;
    }

    BSTIterator(BSTNode* startNode) {
        currentNode = startNode;
        this->startNode = startNode;
        endReached = false;
    }

    bool operator==(const BSTIterator& rhs) const {
        return currentNode == rhs.currentNode;
    }

    bool operator!=(const BSTIterator& rhs) const {
        return currentNode != rhs.currentNode;
    }

    // Dereference operator
    int& operator*() const {
        return currentNode->data;
    }

    // sets current node to the min node
    void returnToMin() {
        // go back all the way up the tree (to the root)
        while(startNode->parent != nullptr) {
            startNode = startNode->parent;
        }
        //keep going left, until the smallest node is found
        //(most left is the smallest in a BST)
        while(startNode->left != nullptr) {
            startNode = startNode->left;
        }
        currentNode = startNode;
    }

    // Pre-increment operator
    BSTIterator& operator++() {
        if(!endReached) {
            if(currentNode) {
                currentNode = currentNode->GetSuccessor();
                if (!currentNode) {
                    endReached = true;
                    returnToMin();
                }
                else {
                    currentNode->checked = true;
                }
            }
        }
        if(endReached) {
            while(currentNode) {
                if (!currentNode->checked) {
                    currentNode->checked = true;
                    break;
                }
                currentNode = currentNode->GetSuccessor();
            }
        }
        return *this;
    }

    // Post-increment operator
    BSTIterator operator++(int) {
        BSTIterator previous(*this);
        if(!endReached) {
            if(currentNode) {
                currentNode = currentNode->GetSuccessor();
                if (!currentNode) {
                    endReached = true;
                    returnToMin();
                }
                else {
                    currentNode->checked = true;
                }
            }
        }
        if(endReached) {
            while(currentNode) {
                if (!currentNode->checked) {
                    currentNode->checked = true;
                    break;
                }
                currentNode = currentNode->GetSuccessor();
            }
        }
        return *this;
    }
};

class Set {
private:
    BSTNode* root;

    BSTNode* CopySubtree(BSTNode* subtreeRoot, BSTNode* parent = nullptr) {
        BSTNode* newNode = nullptr;
        if (subtreeRoot) {
            newNode = new BSTNode(subtreeRoot->data, parent);
            newNode->left = CopySubtree(subtreeRoot->left, newNode);
            newNode->right = CopySubtree(subtreeRoot->right, newNode);
        }
        return newNode;
    }

    void DeleteTree(BSTNode* treeRoot) {
        if (treeRoot) {
            DeleteTree(treeRoot->left);
            DeleteTree(treeRoot->right);
            delete treeRoot;
        }
    }

    BSTNode* NodeSearch(int element) const {
        // Search the BST
        BSTNode* node = root;
        while (node) {
            // Compare node's data against the search element
            if (element == node->data) {
                return node;
            }
            else if (element > node->data) {
                node = node->right;
            }
            else {
                node = node->left;
            }
        }
        return node;
    }

    void RemoveNode(BSTNode* nodeToRemove) {
        if (nodeToRemove == nullptr) {
            return;
        }

        // Case 1: Internal node with 2 children
        if (nodeToRemove->left && nodeToRemove->right) {
            BSTNode* successor = nodeToRemove->GetSuccessor();

            // Copy the data value from the successor
            int dataCopy = successor->data;

            // Remove successor
            RemoveNode(successor);

            // Replace nodeToRemove's data with successor data
            nodeToRemove->data = dataCopy;
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
        }

        // Case 3: Internal node with left child only
        else if (nodeToRemove->left) {
            nodeToRemove->parent->ReplaceChild(nodeToRemove, nodeToRemove->left);
            delete nodeToRemove;
        }

        // Case 4: Internal node with right child only, or leaf node
        else {
            nodeToRemove->parent->ReplaceChild(nodeToRemove, nodeToRemove->right);
            delete nodeToRemove;
        }
    }

public:
    Set() {
        root = nullptr;
    }

    // Copy constructor
    Set(const Set& copyMe) {
        root = CopySubtree(copyMe.root);
    }

    virtual ~Set() {
        DeleteTree(root);
    }

    bool Add(int newElement) {
        if (Contains(newElement)) {
            return false;
        }

        BSTNode* newNode = new BSTNode(newElement, nullptr);

        // Special case for empty set
        if (root == nullptr) {
            root = newNode;
            return true;
        }

        BSTNode* node = root;
        while (node) {
            if (newElement < node->data) {
                // Go left
                if (node->left) {
                    node = node->left;
                }
                else {
                    node->left = newNode;
                    newNode->parent = node;
                    node = nullptr;
                }
            }
            else {
                // Go right
                if (node->right) {
                    node = node->right;
                }
                else {
                    node->right = newNode;
                    newNode->parent = node;
                    node = nullptr;
                }
            }
        }
        return true;
    }

    bool Contains(int element) const {
        return NodeSearch(element) != nullptr;
    }

    Set Difference(const Set& otherSet) const {
        Set result;
        for (int element : *this) {
            if (!otherSet.Contains(element)) {
                result.Add(element);
            }
        }
        return result;
    }

    Set Filter(std::function<bool(int)> predicate) const {
        Set result;
        for (int element : *this) {
            if (predicate(element)) {
                result.Add(element);
            }
        }
        return result;
    }

    Set Intersection(const Set& otherSet) const {
        Set result;
        for (int element : *this) {
            if (otherSet.Contains(element)) {
                result.Add(element);
            }
        }
        return result;
    }

    Set Map(std::function<int(int)> mapFunction) const {
        Set result;
        for (int element : *this) {
            int newElement = mapFunction(element);
            result.Add(newElement);
        }
        return result;
    }

    void Remove(int element) {
        RemoveNode(NodeSearch(element));
    }

    int Size() const {
        if (root) {
            return root->Count();
        }
        return 0;
    }

    Set Union(const Set& otherSet) const {
        Set result;
        for (int element : *this) {
            result.Add(element);
        }
        for (int element : otherSet) {
            result.Add(element);
        }
        return result;
    }

    BSTIterator begin() const {
        // Special case for empty set
        if (root == nullptr) {
            return BSTIterator(nullptr);
        }

        // Start the iterator at the minimum node
        BSTNode* minNode = root;
        while (minNode->left) {
            minNode = minNode->left;
        }
        return BSTIterator(minNode);
    }

    BSTIterator end() const {
        return BSTIterator(nullptr);
    }
};

#endif