#include "graph.h"

#define MAX_NAME_LEN 100

// Important: you do not need to allocate memory for
// mygraph. Currently this is already allocated on
// the stack in the stub for part1 and read_graph
// passes a pointer to this stack-allocated graph
// into this function
int initialize_graph (Graph *mygraph, int MaxSize) 
{
  // your code goes here
  mygraph->name = (char*)malloc(MAX_NAME_LEN);
  check(mygraph->name, "name");
  strcpy(mygraph->name, "Graph 1");
  mygraph->table = (Node*)malloc(sizeof(Node)*MaxSize);
  check(mygraph->table, "nodes");
  // initialize table
  for(int i = 0; i < MaxSize; i++)
  {
    mygraph->table[i].name = NULL;
    mygraph->table[i].outdegree = 0;
    mygraph->table[i].outlist = NULL;
  }
  mygraph->num = 0;
  mygraph->MaxSize = MaxSize;
  return 0;
}
int insert_graph_node (Graph *mygraph, int n, char *name) 
{
  // your code goes here
  if(n >= mygraph->MaxSize)
  {
    printf("invalid index\n");
    return -1;
  }
  mygraph->table[n].name = (char*)malloc(MAX_NAME_LEN);
  check(mygraph->table[n].name, "name");
  strcpy(mygraph->table[n].name, name);
  mygraph->table[n].outlist = NULL;
  mygraph->table[n].outdegree = 0;
  mygraph->num++;
  return 0;
}
int insert_graph_link (Graph *mygraph, int source, int target) 
{
  // your code goes here
  if(source > mygraph->num)
  {
    printf("Please check 'source'\n");
    return -1;
  }
  // check duplicate links
  // List* p = mygraph->table[source].outlist;
  // while(p != NULL)
  // {
  //   if(p->index == target)
  //   {
  //     printf("%d %d\n", source, target);
  //     return -1;
  //   }
  //   p = p->next;
  // }
  List* new = (List*)malloc(sizeof(List));
  check(new, "new_link");
  new->index = target;
  new->next = mygraph->table[source].outlist;
  mygraph->table[source].outlist = new;
  mygraph->table[source].outdegree++;
  return 0;
}
// use to check result of strdup, malloc etc.
void check (void *memory, char *message) 
{
  if (memory == NULL) 
  {
    fprintf (stderr, "Can't allocate memory for %s\n", message);
    exit (3);
  }
}
int read_graph (Graph *mygraph, char *filename)
/* 
 * Reads in graph from FILE *filename which is of .gx format.
 * Stores it as Graph in *mygraph. 
 * Returns an error if file does not start with MAX command,
 * or if any subsequent line is not a NODE or EDGE command. 
 * Does not check that node numbers do not exceed the maximum number
 * Defined by the MAX command. 
 * 8/2/2010 - JLS
 */
{
  FILE *fp;
  char command[80], name[80];
  int i, s, t;
  fp= fopen (filename, "r");
  if (fp==NULL) 
  {
    fprintf(stderr,"cannot open file %s\n", filename);
    return -1;
  }
  printf ("Reading graph from %s\n", filename);
  fscanf (fp,"%s", command);
  if (strcmp (command, "MAX")!=0) 
  {
    fprintf (stderr, "Error in graphics file format\n");
    fclose (fp);
    return -1;
  } 
  else 
  {
    fscanf (fp, "%d", &i);
    initialize_graph (mygraph, i+1); // +1 so nodes can be numbered 1..MAX
    while (fscanf (fp, "%s", command)!=EOF) 
    {
      if (strcmp (command, "NODE")==0) 
      {
        fscanf (fp, "%d %s", &i, name);
        insert_graph_node (mygraph, i, name);
      } 
      else 
      {
        if (strcmp (command, "EDGE")==0) 
        {
          fscanf (fp, "%d %d", &s, &t);
          insert_graph_link (mygraph, s, t);
        } 
        else 
        {
          fclose (fp);
          return -1;
        }
      }
    }
  }
  fclose (fp);
  return 0;
}

void print_graph (Graph *mygraph)
/* 
 * Prints out Graph *mygraph to the stdout in .gx format - JLS
 */
{
  int i;
  List *current;
  printf ("MAX %d\n", mygraph->MaxSize);
  for (i=0; i<mygraph->MaxSize; i++)
    if (mygraph->table[i].name!=NULL) 
    {
      printf ("NODE %d %s\n", i, mygraph->table[i].name);
      current= mygraph->table[i].outlist;
      while (current!=NULL) 
      {
        printf ("EDGE %d %d\n", i, current->index);
        current= current->next;
      }
    }
}

void free_graph (Graph *mygraph)
/* 
 * Free memory Graph *mygraph
 */
{
  int i;
  List *current;
  List *temp;
  for (i = 0; i < mygraph->MaxSize; i++)
  {
    if (mygraph->table[i].name != NULL) 
    {
      free(mygraph->table[i].name);
      current = mygraph->table[i].outlist;
      while (current != NULL) 
      {
        temp = current;
        current = current->next;
        free(temp);
      }
    }
  }
  free(mygraph->name);
  free(mygraph->table);
}
