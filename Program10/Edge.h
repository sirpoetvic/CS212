/* Authors:
Evan Olds / Senior Content Developer / zyBooks
Roman Lysecky / Professor of Electrical and Computer Engineering / Univ.of Arizona
Frank Vahid / Professor of Computer Science and Engineering / Univ.of California, Riverside

February 2024
*/

#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include "Vertex.h"

class Edge {
public:
   Vertex* fromVertex;
   Vertex* toVertex;
    
   Edge(Vertex* from, Vertex* to) {
      fromVertex = from;
      toVertex = to;
   }
   
   bool operator==(const Edge& other) const {
      return fromVertex == other.fromVertex && toVertex == other.toVertex;
   }

   bool operator!=(const Edge& other) const {
      return !(*this == other);
   }
   
   // Prints this edge in the form "A to B", where "A" is fromVertex's label
   // and "B" is toVertex's label.
   void Print(std::ostream& output) const {
      fromVertex->Print(output);
      output << " to ";
      toVertex->Print(output);
   }
};

#endif