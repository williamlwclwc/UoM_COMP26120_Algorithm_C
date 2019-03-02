#include "graph.h"
#include <time.h>

int notInOutlist(Graph* G, int current, int target);
int getMaxout(Graph* G, int* visited, int current);
void findTarget(Graph* G, int current);

int main(int argc,char *argv[])
{
    clock_t start_t, end_t;
    double total_t;
    start_t = clock();

    Graph mygraph;

    read_graph(&mygraph,argv[1]);

    printf("Graph has been read.\n");
    /* you take it from here */

    for(int source = 1; source < mygraph.MaxSize; source++)
    {
        findTarget(&mygraph, source);
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

void findTarget(Graph* G, int source)
{
    int unreachable = G->MaxSize - 1;
    int larger_than_six = 0;
    int current = source;
    int visited[G->MaxSize];
    int reached[G->MaxSize];
    memset(visited, 0, sizeof(int)*G->MaxSize);
    memset(reached, 0, sizeof(int)*G->MaxSize);
    int maxOut = 0;
    int dist = -1;
    float avg_dist = 0;
    visited[current] = 1;
    reached[current] = 1;
    unreachable--;
    List* z = NULL;
    while(G->table[current].outlist != NULL)
    {
        z = G->table[current].outlist;
        while(z != NULL)
        {
            if(reached[z->index] == 0)
            {
                reached[z->index] = 1;
                unreachable--;
                if(dist+1 > 6)
                {
                    larger_than_six++;
                }
                avg_dist += (dist+1);
            }
            z = z->next;
        }
        visited[current] = 1;
        dist++;
        if(reached[current] == 0)
        {
            reached[current] = 1;
            unreachable--; 
            if(dist+1 > 6)
            {
                larger_than_six++;
            } 
            avg_dist += dist; 
        }
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
    if(unreachable > 0)
    {
        printf("There are %d nodes that Node %s cannot reach\n", unreachable, G->table[source].name);
    }
    if(larger_than_six > 0)
    {
        printf("There are %d nodes that Node %s have to reach with more than 6 steps\n", \
                larger_than_six, G->table[source].name);
    }
    else
    {
        printf("Node %s can reach all other node with in 6 steps\n", G->table[source].name);
    }
    avg_dist /= G->MaxSize;
    printf("Average distance for Node %s is %.3f\n", G->table[source].name, avg_dist);
}