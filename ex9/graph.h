#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#define __USE_BSD // make prototype for strdup visible
#include <string.h>

typedef struct linkedlist { // linked list of ints (for use in Node)
  int index;
  struct linkedlist *next;
} List;

typedef struct { // a Node of a Graph
  char *name;
  List *outlist; // adjacency list
  int outdegree; // length of outlist
  //double pagerank_score; //not needed for this exercise
} Node;

typedef struct {
  // your code goes here
  char* name; // name of the graph
  Node* table; // start of the nodes
  int num; // current index of nodes
  int MaxSize; // Max number of nodes
} Graph;

// use to check result of strdup, malloc etc.
extern void check (void *memory, char *message);

extern Graph* initialize_graph (Graph *mygraph, int MaxSize);
extern Graph* insert_graph_node (Graph *mygraph, int n, char *name);
extern Graph* insert_graph_link (Graph *mygraph, int source, int target);
extern Graph* read_graph (Graph *mygraph, char *filename);
extern void print_graph (Graph *mygraph);