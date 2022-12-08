/*********************
Name: Kevin Bryniak
Assignment: Final Project
An implementation of a graph class
**********************/

#include "testdata.h"

void rand_int(int *integer)
{
  *integer = (rand() % MAXINT) * (rand() % 2 ? 1 : -1);
}

void rand_string(string *str)
{
  // create size 0 to MAXSTRSIZE-1
  int rnum = rand() % MAXSTR;

  // make buffer to hold rand string
  char *buffer = new char[rnum + 1];

  // fill buffer with random characters A to Z
  int i = 0;
  for (; i < rnum; i++)
  {
    buffer[i] = (rand() % ('Z' - 'A' + 1)) + 'A';
  }
  buffer[i] = '\0';

  // transfer buffer to passed in string
  *str = buffer;

  // clean up
  delete buffer;
  return;
}

void rand_testdata(TestVertex *item)
{
  rand_int(&item->id);
  rand_string(&item->data);
  item->isValid = item->id > 0 && item->data.size();
}
