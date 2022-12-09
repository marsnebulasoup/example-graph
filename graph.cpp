/*********************
Name: Kevin Bryniak
Assignment: Final Project
An implementation of a graph class
**********************/

#include "graph.h"

Graph::~Graph()
{
  auto vertex = list.begin();
  while (vertex != list.cend())
  {
    advance(vertex, 1);
    removeVertex(*prev(vertex));
  }
}

bool Graph::isValid(const int id, const string *data)
{
  return id > 0 && data && data->length();
}

bool Graph::removeVertex(Vertices *vertex)
{
  bool wasRemoved = false;
  if (vertex)
  {
    auto edge = vertex->vertices.begin();
    while (edge != vertex->vertices.cend())
    {
      advance(edge, 1);
      removeEdge(vertex->vertex.id, (*prev(edge))->id);
    }
    list.erase(vertex);
    delete vertex;
    wasRemoved = true;
  }
  return wasRemoved;
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
  Vertices *search = findVertex(id);
  return removeVertex(search);
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
bool Graph::getVertex(int id, Vertex *out)
{
  Vertices *search = findVertex(id);
  out->id = search ? search->vertex.id : -1;
  out->data = search ? search->vertex.data : "";
  return search;
}
bool Graph::getEdges(int id, vector<Vertex *> *out)
{
  bool wasFound = false;
  Vertices *search = findVertex(id);
  if (search)
  {
    for (const Vertex *vertex : search->vertices)
    {
      out->push_back(new Vertex{vertex->id, vertex->data});
    }
    wasFound = true;
  }
  return wasFound;
}
bool Graph::containsVertex(int id)
{
  Vertices search = Vertices{Vertex{id}};
  return list.count(&search);
}
bool Graph::containsEdge(int id1, int id2)
{
  bool wasFound = false;
  if (id1 != id2 && containsVertex(id1) && containsVertex(id2))
  {
    Vertices *vertex1 = findVertex(id1);
    Vertices *vertex2 = findVertex(id2);
    wasFound =
        vertex1->vertices.count(&vertex2->vertex) &&
        vertex2->vertices.count(&vertex1->vertex);
  }
  return wasFound;
}
int Graph::getVertexCount()
{
  return list.size();
}
int Graph::getEdgeCount(int id)
{
  Vertices *search = findVertex(id);
  return search ? search->vertices.size() : 0;
}
int Graph::getTotalEdgeCount()
{
  int count = 0;
  for (const Vertices *vertices : list)
  {
    count += vertices->vertices.size();
  }
  return count / 2;
}

void Graph::dumpGraph(string &out)
{
  out = "\nGRAPH:\n";
  for (const Vertices *vertex : list)
  {
    out += "[" + to_string(vertex->vertex.id);
    out += ", " + vertex->vertex.data + "]";
    for (const Vertex *edge : vertex->vertices)
    {
      out += " -> " + to_string(edge->id);
    }
    out += "\n";
  }
}