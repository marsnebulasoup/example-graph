/*********************
Name: Kevin Bryniak
Assignment: Final Project
An implementation of a graph class
**********************/

#include "main.h"

TEST_SUITE_BEGIN("Graph Tests");

TEST_CASE("empty tests")
{
  srand(time(NULL));

  Graph graph;
  vector<TestVertex> items = vector<TestVertex>(TEST_DATA_SIZE);

  for (TestVertex &vertex : items)
  {
    rand_vertex(&vertex);
  }

  SUBCASE("graph initializes")
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


TEST_CASE("random tests")
{
  Graph graph;
  map<int, TestVertex> vertexRecord;
  map<int, set<int>> edgeRecord;

  int addedCount = 0;
  for (int i = 0; i < RANDOM_TEST_ITERATIONS; i++)
  {
    TestVertex item;
    rand_vertex(&item);
    switch (rand() % 4)
    {
    case 0: // addVertex
    {
      MESSAGE(i << " | adding vertex " << item.id);
      bool alreadyInserted = vertexRecord.count(item.id);
      bool shouldBeAdded = item.isValid && !alreadyInserted;

      CHECK(graph.addVertex(item.id, &item.data) == shouldBeAdded);

      if (shouldBeAdded)
      {
        addedCount++;
        vertexRecord[item.id] = item;
        alreadyInserted = true;
        CHECK(graph.getEdgeCount(item.id) == 0); // no edges added yet
      }

      CHECK(graph.containsVertex(item.id) == alreadyInserted);

      Vertex vertex;
      CHECK(graph.getVertex(item.id, &vertex) == alreadyInserted);
      CHECK(alreadyInserted ? vertex.id == item.id : vertex.id == -1);
      CHECK(alreadyInserted ? vertex.data == vertexRecord[item.id].data : vertex.data == "");

      break;
    }
    case 1: // addEdge
    {
      TestVertex edge;
      rand_vertex(&edge);
      MESSAGE(i << " | adding edge " << item.id << " <---> " << edge.id);

      bool shouldBeAdded =
          item.id > 0 &&                       // item id/data are valid
          item.id != edge.id &&                // shouldn't create loops
          vertexRecord.count(item.id) &&       // vertex of item exists in graph
          vertexRecord.count(edge.id) &&       // vertex of edge exists in graph
          !edgeRecord[item.id].count(edge.id); // vertex of item does not already have this edge

      CHECK(graph.addEdge(item.id, edge.id) == shouldBeAdded);

      if (shouldBeAdded)
      {
        edgeRecord[item.id].insert(edge.id);
        edgeRecord[edge.id].insert(item.id);
      }

      bool edgeIsEdgeOfItem = edgeRecord[item.id].count(edge.id);
      bool itemIsEdgeOfEdge = edgeRecord[edge.id].count(item.id);
      CHECK(graph.containsEdge(item.id, edge.id) == itemIsEdgeOfEdge);
      CHECK(graph.containsEdge(edge.id, item.id) == edgeIsEdgeOfItem);

      int itemEdgeCount = edgeRecord[item.id].size();
      CHECK(graph.getEdgeCount(item.id) == itemEdgeCount);

      // compare graph edges to local records
      vector<Vertex *> edges1;
      vector<Vertex *> edges2;
      CHECK(graph.getEdges(item.id, &edges1) == vertexRecord.count(item.id));
      CHECK(graph.getEdges(edge.id, &edges2) == vertexRecord.count(edge.id));

      for (const Vertex *vertex : edges1)
      {
        CHECK(edgeRecord[item.id].count(vertex->id));
      }
      for (const Vertex *vertex : edges2)
      {
        CHECK(edgeRecord[edge.id].count(vertex->id));
      }

      break;
    }
    case 2: // removeVertex
    {
      MESSAGE(i << " | removing vertex " << item.id);
      bool alreadyInserted = vertexRecord.count(item.id);
      bool shouldBeRemoved = alreadyInserted;
      bool shouldExist = vertexRecord.count(item.id);

      CHECK(graph.removeVertex(item.id) == shouldBeRemoved);
      if (shouldBeRemoved || !item.isValid)
      {
        CHECK_FALSE(graph.containsVertex(item.id));
      }
      else
      {
        CHECK(graph.containsVertex(item.id) == shouldExist);
      }

      set<int> edges = edgeRecord[item.id];
      if (shouldBeRemoved)
      {
        addedCount--;
        shouldExist = false;
        vertexRecord.erase(item.id);
        edgeRecord.erase(item.id);
        for (const int edgeId : edges)
        {
          edgeRecord[edgeId].erase(item.id);
        }
        CHECK(graph.getEdgeCount(item.id) == 0);
      }

      Vertex vertex;
      CHECK(graph.getVertex(item.id, &vertex) == shouldExist);
      CHECK(shouldExist ? vertex.id == item.id : vertex.id == -1);
      CHECK(shouldExist ? vertex.data == vertexRecord[item.id].data : vertex.data == "");

      for (const int &edgeId : edges)
      {
        vector<Vertex *> edges1;
        vector<Vertex *> edges2;
        CHECK(graph.getEdges(item.id, &edges1) == vertexRecord.count(item.id));
        CHECK(graph.getEdges(edgeId, &edges2) == vertexRecord.count(edgeId));

        for (const Vertex *vertex : edges1)
        {
          CHECK(edgeRecord[item.id].count(vertex->id) == shouldExist);
        }
        for (const Vertex *vertex : edges2)
        {
          CHECK(edgeRecord[edgeId].count(item.id) == shouldExist);
        }
      }
      break;
    }
    case 3: // removeEdge
    {
      TestVertex edge;
      rand_vertex(&edge);
      MESSAGE(i << " | removing edge " << item.id << " <---> " << edge.id);

      const int initialItemEdgeCount = edgeRecord[item.id].size();
      const int initialEdgeEdgeCount = edgeRecord[edge.id].size();

      bool alreadyInserted = vertexRecord.count(item.id);
      bool shouldBeRemoved =
          item.id > 0 &&                        // valid item
          edge.id > 0 &&                        // valid edge
          edgeRecord[item.id].count(edge.id) && // item has edge as an edge
          edgeRecord[edge.id].count(item.id);   // edge has item as an edge

      CHECK(graph.removeEdge(item.id, edge.id) == shouldBeRemoved);
      CHECK(graph.containsEdge(item.id, edge.id) == false);

      if (shouldBeRemoved)
      {
        edgeRecord[item.id].erase(edge.id);
        edgeRecord[edge.id].erase(item.id);
        CHECK(graph.getEdgeCount(item.id) == initialItemEdgeCount - shouldBeRemoved);
        CHECK(graph.getEdgeCount(edge.id) == initialEdgeEdgeCount - shouldBeRemoved);
      }

      vector<Vertex *> edges1;
      vector<Vertex *> edges2;
      CHECK(graph.getEdges(item.id, &edges1) == vertexRecord.count(item.id));
      CHECK(graph.getEdges(edge.id, &edges2) == vertexRecord.count(edge.id));

      for (const Vertex *vertex : edges1)
      {
        CHECK(vertex->id != edge.id);
      }
      for (const Vertex *vertex : edges2)
      {
        CHECK(vertex->id != item.id);
      }

      break;
    }
    }
  }

  // verify sizes match
  CHECK(graph.getVertexCount() == vertexRecord.size());
  int totalEdgeCount = 0;
  for (const auto edge : edgeRecord)
  {
    CHECK(graph.getEdgeCount(edge.first) == edge.second.size());
    totalEdgeCount += edge.second.size();
  }
  totalEdgeCount /= 2;
  CHECK(graph.getTotalEdgeCount() == totalEdgeCount);

  string out;
  graph.dumpGraph(out);
  MESSAGE(out);
}

TEST_SUITE_END();