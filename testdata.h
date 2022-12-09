/*********************
Name: Kevin Bryniak
Assignment: Final Project
An implementation of a graph class
**********************/

#ifndef GRAPH_TESTDATA_H
#define GRAPH_TESTDATA_H

#define MAXINT 100
#define MAXSTR 10

#include <stdlib.h>
#include <string>

using std::string;

struct TestVertex
{
  int id;
  string data;
  bool isValid;
};

void rand_int(int *);
void rand_string(string *);
void rand_vertex(TestVertex *item);

#endif /* GRAPH_TESTDATA_H */