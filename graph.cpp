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
bool Graph::addVertex(const int id, const string *data)
{
  bool wasAdded = false;
  if (isValid(id, data) && !containsVertex(id))
  {
    Vertices *vertices = new Vertices{Vertex{id, *data}};
    wasAdded = list.insert(vertices).second;
  }
  return wasAdded;
}
bool Graph::addEdge(int id1, int id2)
{
  bool wasAdded = false;
  if (id1 != id2 && containsVertex(id1) && containsVertex(id2))
  {
    Vertices *vertex1 = findVertex(id1);
    Vertices *vertex2 = findVertex(id2);
    wasAdded =
        vertex1->vertices.insert(&vertex2->vertex).second &&
        vertex2->vertices.insert(&vertex1->vertex).second;
  }
  return wasAdded;
}
bool Graph::removeVertex(int id)
{
  bool wasRemoved = false;
  Vertices *search = findVertex(id);
  if (search)
  {
    auto edge = search->vertices.begin();
    while (edge != search->vertices.cend())
    {
      std::advance(edge, 1);
      removeEdge(search->vertex.id, (*std::prev(edge))->id);
    }
    list.erase(search);
    delete search;
    wasRemoved = true;
  }
  return wasRemoved;
}
bool Graph::removeEdge(int id1, int id2)
{
  bool wasRemoved = false;
  Vertices *vertex1 = findVertex(id1);
  Vertices *vertex2 = findVertex(id2);
  if (vertex1 && vertex2)
  {
    wasRemoved =
        vertex1->vertices.erase(&vertex2->vertex) &&
        vertex2->vertices.erase(&vertex1->vertex);
  }
  return wasRemoved;
}
bool Graph::isEmpty()
{
  return list.empty();
}
