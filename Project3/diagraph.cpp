#include <iostream>
#include <unordered_map>
#include <fstream>
#include <cstring>
#include <stack>
#include <vector>
#include "digraphMatrix.h"


DigraphMatrix::DigraphMatrix(const string& k)
{
	n = m = 0;
	ifstream in;
	in.open(k,ios::in);

	int v1, v2,i = 0;
	
	if (in.is_open()) 
	{
		while (in >> v1 >> v2) 
		{
			if (i == 0)
			{
				n = v1;
				m = v2;
				i++;
				continue;
			}

			if(vertex.find(v1) == vertex.end())
				addVertex(v1);

			if (vertex.find(v2) == vertex.end())
				addVertex(v2);

			addEdge(v1, v2);
		}
		in.close();
	}
}


void DigraphMatrix::addVertex(const int& val)
{
	vertex_t* v = new vertex_t;
	v->vertexID = val;
	v->I = new unordered_set<edge_t*>();
	vertex.insert(make_pair(val, v));
}


void DigraphMatrix::addEdge(const int& out, const int& in)
{
	vertex_t* u = vertex[out];
	vertex_t* v = vertex[in];

	edge_t * e = new edge_t;
	e->out = u;
	e->in = v;
	edge.insert(e);
	u->I->insert(e);
	v->I->insert(e);
}

void DigraphMatrix::reverseEdges()
{
	vertex_t* temp = new vertex_t;

	for (auto e : edge) {
		temp = e->out;
		e->out = e->in;
		e->in = temp;
	}
}


vector<int> DigraphMatrix::getOutNeighbors(const int& val) const
{
	const vertex_t* v = vertex.at(val);
	vector<int> N;

	for (auto edge : *v->I)
	{
		if (edge->out == v)
			N.push_back(edge->in->vertexID);
	}
	
	return N;
}


vector<int> DigraphMatrix::stronglyConnectedComponents()
{
	vector<int> vec;

	DFS(true);		//first pass
	DFS(false);		//second pass

	for (int i = 0; i < vertex.size(); i++)
	{   
		auto p = vertex.find(i);
		vec.push_back(p->second->componentID);
	}

	return vec;
}

/*
1st Pass
	-Add the vertices of the graph to stack as we explore them
	-iterate through the out neighbors

2nd Pass
	-uses the in neighbors**** instead of out neighbors
	-initialize each vertex to undiscovered
	-instead of selecting undiscovered vertex with lowest ID, perform recursive DFS on the first undiscovered vertex in the stack
	-each iteration of this loop represents a different SCC and assign same componentID to all vertices encountered in the recursive fn
			can store maybe with a componentID int value in struct 

*/

void DigraphMatrix::DFS(bool firstPass)
{
	unordered_map <int, mark_t> marks;

	for (auto p : getVertices())
		marks[p.first] = UNDISCOVERED;
		
	if (firstPass == true) {
		
		for (auto p : getVertices())
		{
			if (marks[p.first] == UNDISCOVERED)
				DFS_recursive(p.first, marks, 0, true);
		}
	}
	else {
		reverseEdges();
		int count = 0;

		while(!vert.empty())
		{
			if (marks[vert.top()] == UNDISCOVERED)
			{
				DFS_recursive(vert.top(), marks, count, false);
				count++;
				vert.pop();
			}
			else
				vert.pop();
		}
	}}


void DigraphMatrix::DFS_recursive(int v, unordered_map<int, mark_t>& marks, int count, bool firstPass)
{
	marks[v] = DISCOVERED;

	for (int k : getOutNeighbors(v))
	{
		if (marks[k] == UNDISCOVERED)
			if (firstPass == true)
				DFS_recursive(k, marks, 0, true);
			else
				DFS_recursive(k, marks, count, false);	
	
		
	}
	
	marks[v] = EXPLORED;
	
	
	if (firstPass == true && marks[v] == EXPLORED)
	{
		vert.push(v);	
	}
	else if (firstPass == false && marks[v] == EXPLORED)
		(vertex.find(v))->second->componentID = count;

	
}
