#include "graph.h"

void (*graph_search)(Graph* mygraph));

#ifdef BFS
    void breadth_first_search(Graph* mygraph, Node* v)
    {
        
    }
    graph_search = &bread_first_search;
#endif
#ifdef DFS
    void depth_first_search(Graph* mygraph, Node* v)
    {

    }
    graph_search = &bread_first_search;
#endif

int main(int argc,char *argv[])
{
  Graph mygraph;

  read_graph(&mygraph,argv[1]);
  
  return(0);
}
