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

// These functions have an int return type so that you can return
// a status indicating the success or otherwise of the function
// as is done in read_graph. You may change the functions to
// void if you wish to do so.

extern int initialize_graph (Graph *mygraph, int MaxSize);
extern int insert_graph_node (Graph *mygraph, int n, char *name);
extern int insert_graph_link (Graph *mygraph, int source, int target);
extern int read_graph (Graph *mygraph, char *filename);
extern void print_graph (Graph *mygraph);

/*
 Here is an implementation of a Queue that you may wish to use in
 part 2. You do not need to use it but if you do use it you will
 need to be able to explain how it works and the complexity of
 enqueue and dequeue

typedef struct queue {
  // points to the first thing in the queue, next points back
  List* front;
  // points to the last thing in the queue, next will be NULL
  List* back;
} Queue;

Queue* makeQueue()
{
  Queue* queue = malloc(sizeof(Queue));
  queue->front = NULL;
  queue->back = NULL;
  return queue;
}

void enqueue(int n, Queue* queue)
{
  List* new = malloc(sizeof(List));
  check(new, "Cannot enqueue");
  new->index = n;
  new->next = NULL;

  if(queue->back == NULL){
    //queue is empty
    queue->front = new;
    queue->back = new;
  }
  else{
    //queue.back->next will be NULL
    queue->back->next = new;
    queue->back = new;
  }
}
List* dequeue(Queue* queue)
{
  // queue is empty
  if(queue->front == NULL) return NULL;

  // shift front back
  List* ret = queue->front;
  queue->front = queue->front->next;

  // if eaten last thing tell back
  if(queue->front == NULL) queue->back=NULL;

  return ret;
}

*/
