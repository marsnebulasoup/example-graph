/*********************
Name: Kevin Bryniak
Assignment: Final Project
An implementation of a graph class
**********************/

#ifndef GRAPH_VERTEX_H
#define GRAPH_VERTEX_H

#include <string>
#include <set>

using std::set;
using std::string;

struct Vertex
{
  int id;
  string data;
  bool operator<(const Vertex &v) const
  {
    return id < v.id;
  }
};

struct vertex_cmp
{
  bool operator()(const Vertex *v1, const Vertex *v2) const
  {
    return v1->id < v2->id;
  }
};

struct Vertices
{
  Vertex vertex;
  set<const Vertex *, vertex_cmp> vertices; // adjacent vertices
};

struct vertices_cmp
{
  bool operator()(const Vertices *v1, const Vertices *v2) const
  {
    return v1->vertex.id < v2->vertex.id;
  }
};

#endif