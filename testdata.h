/*********************
Name: Kevin Bryniak
Assignment: Final Project
An implementation of a graph class
**********************/

#ifndef GRAPH_TESTDATA_H
#define GRAPH_TESTDATA_H

#define MAXINT 10
#define MAXSTR 10

#include <stdlib.h>
#include <string>

using std::string;

struct TestVertex
{
  int id;
  string data;
  bool isValid;
  bool isUnique;
};

void rand_int(int *);
void rand_string(string *);
void rand_testdata(TestVertex *item);

#endif /* GRAPH_TESTDATA_H */