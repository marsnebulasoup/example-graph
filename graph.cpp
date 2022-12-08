/*********************
Name: Kevin Bryniak
Assignment: Final Project
An implementation of a graph class
**********************/

#include "graph.h"

bool Graph::isValid(const int id, const string *data)
{
  return id > 0 && data && data->length();
}

Vertices *Graph::findVertex(int id)
{
  Vertices search = Vertices{Vertex{id}};
  Vertices *vertices = *list.find(&search);
  return vertices == *list.end() ? NULL : vertices;
}