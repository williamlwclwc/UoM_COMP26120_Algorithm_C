#include "graph.h"

void max_out_degree(Graph* mygraph);
void max_in_degree(Graph* mygraph);
void min_in_degree(Graph* mygraph);
void get_in_degree(Graph* mygraph, int in_degree[]);

int main(int argc,char *argv[])
{
  Graph *mygraph = NULL;

  mygraph = read_graph(mygraph,argv[1]);

  /* you take it from here */
  max_out_degree(mygraph);
  max_in_degree(mygraph);
  min_in_degree(mygraph);
  return(0);
}

void max_out_degree(Graph* mygraph)
{
  int max = 0;
  int max_node = 0;
  for (int i = 1; i < mygraph->MaxSize; i++)
  {
    if (mygraph->table[i].name!=NULL) 
    {
      if(mygraph->table[i].outdegree > max)
      {
        max = mygraph->table[i].outdegree;
        max_node = i;
      }
    }
  }
  printf("Max out-degree is %d at node %d\n", max, max_node);
}

void max_in_degree(Graph* mygraph)
{
  int max = 0;
  int max_node = 0;
  int in_degree[mygraph->MaxSize];
  for(int i = 0; i < mygraph->MaxSize; i++)
  {
    in_degree[i] = 0;
  }
  get_in_degree(mygraph, in_degree);
  for(int i = 1; i < mygraph->MaxSize; i++)
  {
    if(max < in_degree[i])
    {
      max = in_degree[i];
      max_node = i;
    }
  }
  printf("Max in-degree is %d at node %d\n", max, max_node);
}

void min_in_degree(Graph* mygraph)
{
  int in_degree[mygraph->MaxSize];
  for(int i = 0; i < mygraph->MaxSize; i++)
  {
    in_degree[i] = 0;
  }
  get_in_degree(mygraph, in_degree);
  int min = in_degree[1];
  int min_node = 1;
  for(int i = 1; i < mygraph->MaxSize; i++)
  {
    if(min > in_degree[i])
    {
      min = in_degree[i];
      min_node = i;
    }
  }
  printf("Min in-degree is %d at node %d\n", min, min_node);
}

void get_in_degree(Graph* mygraph, int in_degree[])
{
  List* current = NULL;
  for (int i = 1; i < mygraph->MaxSize; i++)
  {
    if (mygraph->table[i].name!=NULL) 
    {
      current= mygraph->table[i].outlist;
      while (current!=NULL) 
      {
        in_degree[current->index]++;
        current= current->next;
      }
    }
  }
}