/*********************
Name: Kevin Bryniak
Assignment: Final Project
An implementation of a graph class
**********************/

#ifndef GRAPH_H
#define GRAPH_H

#include <set>
#include <vector>
#include <string>
#include "vertex.h"

using std::set;
using std::string;
using std::to_string;
using std::vector;
using std::advance;
using std::prev;

class Graph
{
private:
  set<Vertices *, vertices_cmp> list;

  bool isValid(const int, const string *);
  bool removeVertex(Vertices*);
  Vertices *findVertex(int);

public:
  ~Graph();

  bool addVertex(const int, const string *);
  bool addEdge(int, int);
  bool removeVertex(int);
  bool removeEdge(int, int);
  bool isEmpty();
  bool getVertex(int, Vertex *);
  bool getEdges(int, vector<Vertex *> *);
  bool containsVertex(int);
  bool containsEdge(int, int);
  int getVertexCount();
  int getEdgeCount(int);
  int getTotalEdgeCount();

  void dumpGraph(string &);
};

#endif