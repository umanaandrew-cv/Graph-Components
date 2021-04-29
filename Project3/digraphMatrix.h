#ifndef __DIGRAPH_MATRIX_H
#define __DIGRAPH_MATRIX_H

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <stack>
using namespace std;

enum mark_t { UNDISCOVERED, DISCOVERED, EXPLORED };

struct edge;

typedef struct vertex
{
	int vertexID; 
	int componentID;
	unordered_set<struct edge*>* I;
}vertex_t;

typedef struct edge
{
	vertex_t* in;
	vertex_t* out;
}edge_t;

class DigraphMatrix
{
private:
  int n=0; //number of vertices
  int m=0; //number of edges
  unordered_map<int, vertex_t*> vertex;
  unordered_set<edge_t*> edge;
  stack<int> vert;
  vector<bool> A;
public:
  //Reads in digraph from given file
  //Stores graph as an adjacency matrix
  DigraphMatrix(const string&);

  //Returns number of vertices
  int getOrder() const { return n; }

  //Returns vector containing component ID for each vertex
  vector<int> stronglyConnectedComponents();

  void DFS(bool);
  void DFS_recursive(int v, unordered_map<int,mark_t>&,int, bool);

  void addVertex(const int&);
  void addEdge(const int&, const int&);
  void reverseEdges();
  vector<int> getOutNeighbors(const int&) const;

  const unordered_map<int, vertex_t*>& getVertices() const { return vertex; };

};

#endif