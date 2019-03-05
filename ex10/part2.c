#include "graph.h"
#include <time.h>

float findTarget(Graph* G, int source, float* total_unreachable, float* total_larger_than_six);

int main(int argc,char *argv[])
{
    clock_t start_t, end_t;
    double total_t;
    start_t = clock();

    Graph mygraph;

    read_graph(&mygraph,argv[1]);

    printf("Graph has been read.\n");
    /* you take it from here */

    float avg_dist = 0;
    float total_unreachable = 0;
    float total_larger_than_six = 0;
    for(int source = 1; source < mygraph.MaxSize; source++)
    {
        avg_dist += findTarget(&mygraph, source, &total_unreachable, &total_larger_than_six);
    }
    avg_dist /= (mygraph.MaxSize-1);
    total_unreachable /= (mygraph.MaxSize-1);
    total_larger_than_six /= (mygraph.MaxSize-1);
    printf("Average distance in total: %.2f\n", avg_dist);
    printf("Average unreachable nodes in total: %.2f\n", total_unreachable);
    printf("Average distance more than six nodes in total: %.2f\n", total_larger_than_six);
    free_graph(&mygraph);

    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Total time: %.3fs\n", total_t);

    return(0);
}

float findTarget(Graph* G, int source, float* total_unreachable, float* total_larger_than_six)
{
    int maxOutdegree = 0;
    int max_index = 0;
    int unreachable = G->MaxSize - 1;
    int larger_than_six = 0;
    int current = source;
    int visited[G->MaxSize];
    int reached[G->MaxSize];
    memset(visited, 0, sizeof(int)*G->MaxSize);
    memset(reached, 0, sizeof(int)*G->MaxSize);
    int dist = 0;
    float avg_dist = 0;
    visited[current] = 1;
    reached[current] = 1;
    unreachable--;
    List* z = NULL;
    while(G->table[current].outlist != NULL)
    {
        z = G->table[current].outlist;
        maxOutdegree = 0;
        max_index = 0;
        while(z != NULL)
        {
            // reachable nodes and calculate dist
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
            // get max outdegree node's index
            // adjacent node z not visited
            if(visited[z->index] == 0)
            {
                if(G->table[z->index].outdegree < G->MaxSize/50)
                    visited[z->index] = 1;
                if(G->table[z->index].outdegree > maxOutdegree)
                {
                    maxOutdegree = G->table[z->index].outdegree;
                    max_index = z->index;
                }
            }
            z = z->next;
        }
        if(max_index == 0)
        {
            break;
        }
        else
        {
            // get next node in the path
            current = max_index;
        }
        // visited the next node
        visited[current] = 1;
        dist++;
        // if not reached yet
        if(reached[current] == 0)
        {
            reached[current] = 1;
            unreachable--; 
            if(dist > 6)
            {
                larger_than_six++;
            } 
            avg_dist += dist; 
        }
    }
    // if(unreachable > 0)
    // {
    //     printf("There are %d nodes that Node %s cannot reach\n", unreachable, G->table[source].name);
    // }
    // if(larger_than_six > 0)
    // {
    //     printf("There are %d nodes that Node %s have to reach with more than 6 steps\n", \
    //             larger_than_six, G->table[source].name);
    // }
    // if(unreachable == 0 && larger_than_six == 0)
    // {
    //     printf("Node %s can reach all other node with in 6 steps\n", G->table[source].name);
    // }
    // printf("Average distance for Node %s is %.3f\n", G->table[source].name, avg_dist);
    avg_dist /= (G->MaxSize-1-unreachable);
    *total_unreachable += unreachable;
    *total_larger_than_six += larger_than_six;
    return avg_dist;
}