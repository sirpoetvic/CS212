/* Authors:
Evan Olds / Senior Content Developer / zyBooks
Roman Lysecky / Professor of Electrical and Computer Engineering / Univ.of Arizona
Frank Vahid / Professor of Computer Science and Engineering / Univ.of California, Riverside

February 2024
*/

/*
 * Victor Wong
 * Spring 2024, CS212, William Iverson
 * 06/03/2024
 * Program 10
 * Adjacency List Graph structure class
 */

#ifndef ADJACENCYLISTGRAPH_H
#define ADJACENCYLISTGRAPH_H

#include "DirectedGraph.h"
#include "AdjacencyListVertex.h"

class AdjacencyListGraph : public DirectedGraph {
protected:
   std::vector<AdjacencyListVertex*> vertices;
   
public:    
   virtual ~AdjacencyListGraph() {
      for (AdjacencyListVertex* vertex : vertices) {
         delete vertex;
      }
   }

   // Creates and adds a new vertex to the graph, provided a vertex with the
   // same label doesn't already exist in the graph. Returns the new vertex on
   // success, nullptr on failure.
   virtual Vertex* AddVertex(std::string newVertexLabel) override {
      if(GetVertex(newVertexLabel))
         return nullptr;

      AdjacencyListVertex *vertex = new AdjacencyListVertex(newVertexLabel);
      vertices.push_back(vertex);
      return vertex;
   }

   // Adds a directed edge from the first to the second vertex. If the edge
   // already exists in the graph, no change is made and false is returned.
   // Otherwise the new edge is added and true is returned.
   virtual bool AddDirectedEdge(Vertex* fromVertex, Vertex* toVertex) override {
      // checks if the "from vertex" exists
      AdjacencyListVertex* fromVertexPtr = GetVertex(fromVertex->GetLabel());
      if(!fromVertexPtr) return false;
      
      // checks if the "to vertex" exists
      AdjacencyListVertex* toVertexPtr = GetVertex(toVertex->GetLabel());
      if(!toVertexPtr) return false;

      // checks if the two have an edge
      if(HasEdge(fromVertexPtr, toVertexPtr)) return false;
      fromVertexPtr->adjacent.push_back(toVertexPtr);
      return true;
   }

   // Returns a vector of edges with the specified fromVertex.
   virtual std::vector<Edge> GetEdgesFrom(Vertex* fromVertex) override {
      std::vector<Edge> edgeVector;
      AdjacencyListVertex* avlFromVertex = GetVertex(fromVertex->GetLabel());
     
      for (AdjacencyListVertex *vertex : vertices)
      {
         if(HasEdge(avlFromVertex, vertex)) {
            edgeVector.push_back(Edge(avlFromVertex, vertex));
         }
      }
      return edgeVector;
   }

   // Returns a vector of edges with the specified toVertex.
   virtual std::vector<Edge> GetEdgesTo(Vertex* toVertex) override {
      std::vector<Edge> edgeVector;
      AdjacencyListVertex* avlToVertex = GetVertex(toVertex->GetLabel());
     
      for (AdjacencyListVertex *vertex : vertices)
      {
         if(HasEdge(vertex, toVertex)) {
            edgeVector.push_back(Edge(vertex, toVertex));
         }
      }
      return edgeVector;
   }
    
   // Returns a vertex with a matching label, or nullptr if no such vertex
   // exists
   virtual AdjacencyListVertex* GetVertex(std::string vertexLabel) override {
      for(AdjacencyListVertex* alv : vertices) {
         if(alv->GetLabel() == vertexLabel)
            return alv;
      }
      return nullptr;
   }

   // Returns true if this graph has an edge from fromVertex to toVertex
   virtual bool HasEdge(Vertex* fromVertex, Vertex* toVertex) override {
      // Get the pointer of the vertex
      AdjacencyListVertex *fromVertexPtr = GetVertex(fromVertex->GetLabel());
      
      for (Vertex *vertex : fromVertexPtr->adjacent)
         if(vertex == toVertex) return true;
      return false;
   }
};

#endif