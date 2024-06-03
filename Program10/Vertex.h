/* Authors:
Evan Olds / Senior Content Developer / zyBooks
Roman Lysecky / Professor of Electrical and Computer Engineering / Univ.of Arizona
Frank Vahid / Professor of Computer Science and Engineering / Univ.of California, Riverside

February 2024
*/

#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <string>

class Vertex {
protected:
   std::string label;

public:
   Vertex(const std::string vertexLabel) {
      label = vertexLabel;
   }
   
   virtual ~Vertex() {
   }
   
   virtual std::string GetLabel() {
      return label;
   }
   
   // Prints this vertex's label
   virtual void Print(std::ostream& output) {
      output << label;
   }
   
   virtual void SetLabel(std::string newLabel) {
      label = newLabel;
   }
};

#endif