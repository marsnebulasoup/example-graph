/*********************
Name: Kevin Bryniak
Assignment: Final Project
An implementation of a graph class
**********************/

#include "main.h"

TEST_SUITE_BEGIN("Adjacency graph Tests");

TEST_CASE("empty adjacency graph")
{
  srand(time(NULL));

  Graph graph;
  vector<TestVertex> items = vector<TestVertex>(TEST_DATA_SIZE);

  for (TestVertex &vertex : items)
  {
    rand_testdata(&vertex);
  }

  SUBCASE("adjacency graph initializes")
  {
    CHECK(graph.isEmpty());
    CHECK(graph.getVertexCount() == 0);
    CHECK(graph.getTotalEdgeCount() == 0);
  }

  SUBCASE("addVertex() with no vertices")
  {
    int addedCount = 0;
    set<int> added;
    for (const TestVertex &item : items)
    {
      bool isNotDuplicate = !added.count(item.id);
      bool wasAdded = graph.addVertex(item.id, &item.data);
      CHECK(wasAdded == (item.isValid && isNotDuplicate));

      if (wasAdded)
      {
        added.insert(item.id);
      }

      CHECK(graph.containsVertex(item.id) == item.isValid);

      addedCount += (item.isValid && isNotDuplicate);
      CHECK(graph.getVertexCount() == addedCount);
      CHECK(graph.isEmpty() == !addedCount);

      CHECK(graph.getEdgeCount(item.id) == 0);
      CHECK(graph.getTotalEdgeCount() == 0);

      Vertex vertex;
      CHECK(graph.getVertex(item.id, &vertex) == item.isValid);
      CHECK(item.isValid ? vertex.id == item.id : vertex.id == -1);
      if (item.isValid)
      {
        if (item.isUnique)
        {
          CHECK(vertex.data == item.data);
        }
      }
      else
      {
        CHECK(vertex.data == "");
      }
    }

    string out;
    graph.dumpGraph(out);
    MESSAGE(out);
  }

  SUBCASE("addEdge() with no vertices")
  {
    for (const TestVertex &item1 : items)
    {
      for (const TestVertex &item2 : items)
      {
        CHECK(graph.addEdge(item1.id, item2.id) == false);

        CHECK(graph.containsEdge(item1.id, item2.id) == false);
        CHECK(graph.isEmpty());
        CHECK(graph.getVertexCount() == 0);
        CHECK(graph.getEdgeCount(item1.id) == 0);
        CHECK(graph.getEdgeCount(item2.id) == 0);
        CHECK(graph.getTotalEdgeCount() == 0);

        vector<Vertex *> edges1;
        vector<Vertex *> edges2;
        CHECK(graph.getEdges(item1.id, &edges1) == false);
        CHECK(graph.getEdges(item2.id, &edges2) == false);
        CHECK(edges1.size() == 0);
        CHECK(edges2.size() == 0);
      }
    }
  }

  SUBCASE("removeVertex() with no vertices")
  {
    for (const TestVertex &item : items)
    {
      CHECK(graph.containsVertex(item.id) == false);
      CHECK(graph.removeVertex(item.id) == false);
      CHECK(graph.containsVertex(item.id) == false);

      CHECK(graph.isEmpty());
      CHECK(graph.getVertexCount() == 0);

      CHECK(graph.getEdgeCount(item.id) == 0);
      CHECK(graph.getTotalEdgeCount() == 0);

      Vertex vertex;
      CHECK(graph.getVertex(item.id, &vertex) == false);
      CHECK(vertex.id == -1);
      CHECK(vertex.data == "");

      vector<Vertex *> edges;
      CHECK(graph.getEdges(item.id, &edges) == false);
      CHECK(edges.size() == 0);
    }
  }

  SUBCASE("removeEdge() with no vertices")
  {
    for (const TestVertex &item1 : items)
    {
      for (const TestVertex &item2 : items)
      {
        CHECK(graph.containsEdge(item1.id, item2.id) == false);
        CHECK(graph.removeEdge(item1.id, item2.id) == false);
        CHECK(graph.containsEdge(item1.id, item2.id) == false);

        CHECK(graph.isEmpty());
        CHECK(graph.getVertexCount() == 0);
        CHECK(graph.getEdgeCount(item1.id) == 0);
        CHECK(graph.getEdgeCount(item2.id) == 0);
        CHECK(graph.getTotalEdgeCount() == 0);

        vector<Vertex *> edges1;
        vector<Vertex *> edges2;
        CHECK(graph.getEdges(item1.id, &edges1) == false);
        CHECK(graph.getEdges(item2.id, &edges2) == false);
        CHECK(edges1.size() == 0);
        CHECK(edges2.size() == 0);
      }
    }
  }

  SUBCASE("isEmpty() with no vertices")
  {
    CHECK(graph.isEmpty());
  }

  SUBCASE("getVertex() with no vertices")
  {
    for (const TestVertex &item : items)
    {
      Vertex vertex;
      CHECK(graph.getVertex(item.id, &vertex) == false);
      CHECK(vertex.id == -1);
      CHECK(vertex.data == "");
    }
  }

  SUBCASE("getEdges() with no vertices")
  {
    for (const TestVertex &item : items)
    {
      vector<Vertex *> edges;
      CHECK(graph.getEdges(item.id, &edges) == false);
      CHECK(edges.size() == 0);
    }
  }

  SUBCASE("containsVertex() with no vertices")
  {
    for (const TestVertex &item : items)
    {
      CHECK(graph.containsVertex(item.id) == false);
    }
  }

  SUBCASE("containsEdge() with no vertices")
  {
    for (const TestVertex &item1 : items)
    {
      for (const TestVertex &item2 : items)
      {
        CHECK(graph.containsEdge(item1.id, item2.id) == false);
      }
    }
  }

  SUBCASE("getVertexCount() with no vertices")
  {
    CHECK(graph.getVertexCount() == 0);
  }

  SUBCASE("getEdgeCount() with no vertices")
  {
    for (const TestVertex &item : items)
    {
      CHECK(graph.getEdgeCount(item.id) == 0);
    }
  }

  SUBCASE("getTotalEdgeCount() with no vertices")
  {
    CHECK(graph.getTotalEdgeCount() == 0);
  }
}

TEST_SUITE_END();