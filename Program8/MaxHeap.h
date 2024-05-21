#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <iostream>
#include <string>

/*
 * Victor Wong
 * Spring 2024, CS212, William Iverson
 * 05/20/2024
 * Program 8
 * Max Heap Data Structure
 */

class MaxHeap {
private:
   int* heapArray;
   int allocationSize;
   int heapSize;
    
   void PercolateDown(int nodeIndex) {
      int childIndex = 2 * nodeIndex + 1;
      int value = heapArray[nodeIndex];

      while (childIndex < heapSize) {
         // Find the max among the node and all the node's children
         int maxValue = value;
         int maxIndex = -1;
         int i = 0;
         while (i < 2 && i + childIndex < heapSize) {
            if (heapArray[i + childIndex] > maxValue) {
               maxValue = heapArray[i + childIndex];
               maxIndex = i + childIndex;
            }
            i++;
         }

         // Check for a violation of the max-heap property
         if (maxValue == value) {
            return;
         }
         else {
            // Swap heapArray[nodeIndex] and heapArray[maxIndex]
            std::cout << "   PercolateDown() swap: " << heapArray[nodeIndex];
            std::cout << " <-> " << heapArray[maxIndex] << std::endl;
            int temp = heapArray[nodeIndex];
            heapArray[nodeIndex] = heapArray[maxIndex];
            heapArray[maxIndex] = temp;
                    
            // Continue loop from the max index node
            nodeIndex = maxIndex;
            childIndex = 2 * nodeIndex + 1;
         }
      }
   }
    
   void PercolateUp(int nodeIndex) {
      while (nodeIndex > 0) {
         // Compute the parent node's index
         int parentIndex = (nodeIndex - 1) / 2;
            
         // Check for a violation of the max-heap property
         if (heapArray[nodeIndex] <= heapArray[parentIndex]) {
            // No violation, so percolate up is done.
            return;
         }
         else {
            // Swap heapArray[nodeIndex] and heapArray[parentIndex]
            std::cout << "   PercolateUp() swap: " << heapArray[parentIndex];
            std::cout<< " <-> " << heapArray[nodeIndex] << std::endl;
            int temp = heapArray[nodeIndex];
            heapArray[nodeIndex] = heapArray[parentIndex];
            heapArray[parentIndex] = temp;
                    
            // Continue the loop from the parent node
            nodeIndex = parentIndex;
         }
      }
   }
    
   void ResizeArray() {
      int newAllocationSize = allocationSize * 2;
      int* newArray = new int[newAllocationSize];
      if (newArray) {
         // Copy from existing array to new array
         for (int i = 0; i < allocationSize; i++) {
            newArray[i] = heapArray[i];
         }
         
         // Delete old array and set pointer to new
         delete[] heapArray;
         heapArray = newArray;
            
         // Update allocation size
         allocationSize = newAllocationSize;
      }
   }

public:
   MaxHeap() {
      allocationSize = 1;
      heapArray = new int[allocationSize];
      heapSize = 0;
   }

   MaxHeap(int* numbers, int size) {
       allocationSize = size > 0 ? size : 1;
       heapArray = new int[allocationSize];
       heapSize = size;
       for (int i = 0; i < size; i++) {
          Insert(numbers[i]);
       }
       for (int i = (heapSize / 2) - 1; i >= 0; i--) {
        PercolateDown(i);
       }
   }
    
   virtual ~MaxHeap() {
      delete[] heapArray;
   }
   
   void Insert(int value) {
      // Resize if needed
      if (heapSize == allocationSize) {
         ResizeArray();
      }
      
      // Add the new value to the end of the array
      std::cout << "Insert(" << value << "):" << std::endl;
      heapArray[heapSize] = value;
      heapSize++;
        
      // Percolate up from the last index to restore heap property
      PercolateUp(heapSize - 1);
   }
   
   int Remove() {
      // Save the max value from the root of the heap
      std::cout << "Remove():" << std::endl;
      int maxValue = heapArray[0];
        
      // Move the last item in the array into index 0
      int replaceValue = heapArray[heapSize - 1];
      heapSize--;
      if (heapSize > 0) {
         heapArray[0] = replaceValue;

         // Percolate down to restore max-heap property
         PercolateDown(0);
      }
                
      // Return the max value
      return maxValue;
   }
    
   std::string GetHeapArrayString() const {
      if (heapSize == 0) {
         return std::string("[]");
      }
      
      std::string arrayString("[");
      arrayString += std::to_string(heapArray[0]);
      for (int i = 1; i < heapSize; i++) {
         arrayString += ", ";
         arrayString += std::to_string(heapArray[i]);
      }
      arrayString += "]";
      return arrayString;
   }
   
   int GetHeapSize() {
      return heapSize;
   }

   friend std::ostream& operator<<(std::ostream& os, MaxHeap& maxHeap) {
   return os << maxHeap.GetHeapArrayString();
}
};

#endif