#include "graph.h"
#include <time.h>

int notInOutlist(Graph* G, int current, int target);
int getMaxout(Graph* G, int* visited, int current);
void findDist(Graph* G, int current, int target, int* unreachable, int* larger_than_six);

int main(int argc,char *argv[])
{
    clock_t start_t, end_t;
    double total_t;
    start_t = clock();

    Graph mygraph;

    read_graph(&mygraph,argv[1]);

    printf("Graph has been read.\n");
    /* you take it from here */

    int larger_than_six = 0;
    int unreachable = 0;
    for(int i = 1; i < mygraph.MaxSize; i++)
    {
        larger_than_six = 0;
        unreachable = 0;
        for(int j = 1; j < mygraph.MaxSize; j++)
        {
            findDist(&mygraph, i, j, &unreachable, &larger_than_six);
        }
        if(unreachable > 0)
        {
            printf("There are %d nodes that Node %s cannot reach\n", unreachable, mygraph.table[i].name);
        }
        else if(larger_than_six > 0)
        {
            printf("There are %d nodes that Node %s have to reach with more than 6 steps\n", \
                   larger_than_six, mygraph.table[i].name);
        }
        else
        {
            printf("Node %s can reach all other node with in 6 steps\n", mygraph.table[i].name);
        }
    }

    free_graph(&mygraph);

    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Total time: %.3fs\n", total_t);

    return(0);
}

int notInOutlist(Graph* G, int current, int target)
{
    List* z = (G->table + current)->outlist;
    while(z != NULL)
    {
        if(z->index == target)
        {
            return 0;
        }
        z = z->next;
    }
    return 1;
}

int getMaxout(Graph* G, int* visited, int current)
{
    int maxOutdegree = 0;
    int max_index = 0;
    List* z = G->table[current].outlist;
    while(z != NULL)
    {
        // adjacent node z not visited
        if(visited[z->index] == 0)
        {
            if(G->table[z->index].outdegree > maxOutdegree)
            {
                maxOutdegree = G->table[z->index].outdegree;
                max_index = z->index;
            }
        }
        z = z->next;
    }
    return max_index;
}

void findDist(Graph* G, int current, int target, int* unreachable, int* larger_than_six)
{
    int visited[G->MaxSize];
    memset(visited, 0, sizeof(int)*G->MaxSize);
    int maxOut = 0;
    int dist = 0;
    visited[current] = 1;
    while(G->table[current].outlist != NULL)
    {
        if(!notInOutlist(G, current, target))
        {
            dist++;
            visited[target] = 1;
            break;
        } 
        visited[current] = 1;
        dist++;
        maxOut = getMaxout(G, visited, current);
        if(maxOut == 0)
        {
            break;
        }
        else
        {
            current = maxOut;
        }
    }
    dist++;
    // distance = number of nodes in path - 1
    if(visited[target] == 0)
    {
        (*unreachable)++;
    }
    else if(dist > 6)
    {
        (*larger_than_six)++;
    }
}