#include "graph.h"
#include "limits.h"
#include <time.h>

typedef struct ElemType
{
    int key;
    Node v;
} ElemType;

typedef struct MinHeap
{
    int capacity;
    int size;
    ElemType* element;
} pQueue;

int DijkstraShortestPaths(Graph* G, int index_v, float* total_dist, float* total_unreachable, float* total_6);
pQueue* initQueue(int max);
void insertQueue(int key, Node v, pQueue* pq);
ElemType removeMin(pQueue* pq);
void freeQueue(pQueue* pq);
//void buildQueue(int* key, Graph* G, pQueue* pq);
int belongsQueue(Node* v, pQueue* pq);
void minHeapify(pQueue* pq, int i);

int main(int argc,char *argv[])
{
    clock_t start_t, end_t;
    double total_t;
    start_t = clock();

    Graph mygraph;

    read_graph(&mygraph,argv[1]);

    printf("Graph has been read.\n");
    /* you take it from here */

    int result = 0; // temp result for Dijkstra
    int is_small_world = 1; // is small world or not
    float total_dist = 0;
    float total_unreachable = 0;
    float total_larger_than_six = 0;
    for(int i = 1; i < mygraph.MaxSize; i++)
    {
        result = DijkstraShortestPaths(&mygraph, i, &total_dist, &total_unreachable, &total_larger_than_six);
        if (!result)
        {
            is_small_world = 0;
        }
    }
    if (is_small_world)
    {
        printf("%s is small world.\n", argv[1]);
    }
    else
    {
        printf("%s is not small world.\n", argv[1]);
    }
    total_dist = total_dist / (mygraph.MaxSize-1);
    total_unreachable = total_unreachable / (mygraph.MaxSize-1);
    total_larger_than_six = total_larger_than_six / (mygraph.MaxSize-1);
    printf("Average distance in total: %.2f\n", total_dist);
    printf("Average unreachable in total: %.2f\n", total_unreachable);
    printf("Average distance larger than six nodes in total: %.2f\n", total_larger_than_six);
    free_graph(&mygraph);

    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Total time: %.3fs\n", total_t);

    return(0);
}

int DijkstraShortestPaths(Graph* G, int index_v, float* total_dist, float* total_unreachable, float* total_6)
{
    int D[G->MaxSize]; // distance array
    int visited[G->MaxSize]; // 0 not visited, 1 visited
    Node* node_u;
    ElemType elem_u;
    int temp;
    int pq_index; // priority queue index
    // initialize distance and visited array
    for(int i = 0; i < G->MaxSize; i++)
    {
        D[i] = INT_MAX;
        visited[i] = 0;
    }
    D[index_v] = 0; // set source's distance to 0
    // set priority queue
    pQueue* pq = initQueue(G->MaxSize);
    //buildQueue(D, G, pq);
    insertQueue(D[index_v], G->table[index_v], pq);
    // while queue is not empty
    List* z; // adjacent list of u
    while(pq->size != 0)
    {
        // u<-dequeue(Q)
        elem_u = removeMin(pq);
        node_u = &(elem_u.v);
        // z adjacent to u
        for(z = node_u->outlist; z != NULL; z = z->next)
        {

            // build heap for all vertexes is not optimal
            // if z belongs to Q
        //    pq_index = belongsQueue(G->table + z->index, pq);
        //    if(pq_index != -1)
        //    {
        //        if(elem_u.key == INT_MAX)
        //        {
        //            temp = elem_u.key;
        //        }
        //        else
        //        {
        //            temp = elem_u.key + 1;
        //        }
        //        if(temp < D[z->index])
        //        {
        //            D[z->index] = temp;
        //            pq->element[pq_index].key = D[z->index];
        //            for(int j = pq->size/2; j > 0; j--)
        //                minHeapify(pq, j);
        //        }
        //    }
            
            // avoid overflow for INT_MAX+1 
            if(elem_u.key == INT_MAX)
            {
                temp = elem_u.key;
            }
            else
            {
                temp = elem_u.key + 1;
            }
            // update distance if new path is shorter
            if(temp < D[z->index])
            {
                D[z->index] = temp;
                if(visited[z->index])
                {
                    // update key of pq: if this adjacent node z has been visited
                    // find the index of pq with given index of the graph
                    pq_index = belongsQueue(G->table + z->index, pq);
                    if(pq_index != -1)
                    {
                        // if found, update key and heapify heap
                        pq->element[pq_index].key = D[z->index];
                        for(int j = pq->size/2; j > 0; j--)
                            minHeapify(pq, j);
                    }
                }
                else
                {
                    // insert into pq: if this adjacent node z has not been visited
                    insertQueue(D[z->index], G->table[z->index], pq);
                    visited[z->index] = 1;
                }

            }
        }
    }

    freeQueue(pq);
    int is_small_world = 1;
    int non_reachable = 0;
    int larger_than_six = 0;
    float avg = 0;
    for(int i = 1; i < G->MaxSize; i++)
    {
        if(i == index_v)
            continue;
        if(D[i] > 6)
        {
            is_small_world = 0;
            if(D[i]==INT_MAX)
            {
                non_reachable++;
            }
            else
            {
                larger_than_six++;
                avg += D[i];
            }
        }
        else
        {
            avg += D[i];
        }
    }
    // Node* v = G->table + index_v;
    // if(is_small_world)
    // {
    //     printf("Node %s can reach all other node with in 6 steps\n", v->name);
    // }
    // else
    // {
    //     if(non_reachable > 0)
    //       printf("There are %d nodes that Node %s cannot reach\n", non_reachable, v->name);
    //     if(larger_than_six > 0)
    //       printf("There are %d nodes that Node %s have to reach with more than 6 steps\n", larger_than_six, v->name);
    // }
    avg = (float)avg / (G->MaxSize-1-non_reachable);
    // printf("Average distance: %f\n", avg);
    *total_dist += avg;
    *total_unreachable += non_reachable;
    *total_6 += larger_than_six;
    return is_small_world;
}

// init pq
pQueue* initQueue(int max)
{
    pQueue* pq;
    if(max <= 0)
    {
        printf("failed to init priority queue\n");
        return NULL;
    }
    pq = (pQueue*)malloc(sizeof(pQueue));
    check(pq, "pQueue");
    // initialization
    pq->size = 0;
    pq->capacity = max;
    // "head" counts for real memory space but not size and capacity
    pq->element = (ElemType*)malloc(sizeof(ElemType)*(pq->capacity+1));
    check(pq, "pq->element");
    pq->element[0].key = -1; // let -1 be "head" of the heap
    return pq;
}

// insert
void insertQueue(int key, Node v, pQueue* pq)
{
    if(pq == NULL)
    {
        printf("priority queue is not initialized\n");
        return;
    }
    if(pq->size == pq->capacity)
    {
        printf("priority queue is full\n");
        return;
    }
    // insert data
    pq->size++;
    pq->element[pq->size].key = key;
    pq->element[pq->size].v = v;
    int i = pq->size;
    ElemType temp;
    // up heap
    // if parent > new then swap(until reach the top)
    while(i > 1 && pq->element[i/2].key > pq->element[i].key)
    {
        // swap elem[i/2], elem[i]
        temp = pq->element[i/2];
        pq->element[i/2] = pq->element[i];
        pq->element[i] = temp;
        i = i/2; // update new node's index
    }
}

// remove minimum of queue
ElemType removeMin(pQueue* pq)
{
    ElemType min = pq->element[1]; // minimum is at top
    pq->element[1] = pq->element[pq->size]; // switch the last element to top
    pq->size--;
    int i = 1;
    int j = 0;
    ElemType temp;
    // last element: down heap until the last(pq->size)
    while(i < pq->size)
    {
        // right child: 2*i+1
        if(2*i+1 <= pq->size)
        {
            // this node has 2 internal children
            if(pq->element[i].key <= pq->element[2*i].key && \
            pq->element[i].key <= pq->element[2*i+1].key)
            {
                // already smaller than children
                return min;
            }
            else
            {
                // select the smaller index of left and right child
                if(pq->element[2*i].key >= pq->element[2*i+1].key)
                {
                    j = 2*i+1;
                }
                else
                {
                    j = 2*i;
                }
                // down heap to the smaller one
                // swap elem[i], elem[j]
                temp = pq->element[i];
                pq->element[i] = pq->element[j];
                pq->element[j] = temp;
                i = j; // update top element's index
            }
        }
        else
        {
            // 2*i: left child
            // this node has 0 or 1 internal child(left and the last)
            if(2*i <= pq->size)
            {
                // has left child, if child is smaller, then swap
                if(pq->element[i].key > pq->element[2*i].key)
                {
                    // swap elem[i], elem[2i]
                    temp = pq->element[i];
                    pq->element[i] = pq->element[2 * i];
                    pq->element[2 * i] = temp;
                }
            }
            return min;
        }
    }
    return min;
}

// clear pq
void freeQueue(pQueue* pq)
{
    if(pq != NULL)
    {
        free(pq->element);
        free(pq);
    }
}

void minHeapify(pQueue* pq, int i)
{
    // i is the index we want to heapify
    int l = 2*i; // left index
    int r = 2*i + 1; // right index
    int min;
    ElemType temp;
    // has left child and left child is smaller
    if(l <= pq->size && pq->element[l].key < pq->element[i].key)
    {
        min = l;
    }
    else
    {
        min = i;
    }
    // has right child and right child is smaller
    if(r <= pq->size && pq->element[r].key < pq->element[min].key)
    {
        min = r;
    }
    // if one of the children is smaller
    if(min != i)
    {
        // swap elem[i], elem[min]
        temp = pq->element[i];
        pq->element[i] = pq->element[min];
        pq->element[min] = temp;
        minHeapify(pq, min);
    }
}

// not optimal: build queue
//void buildQueue(int* key, Graph* G, pQueue* pq)
//{
//    // insert to build priority queue
////    for(int i = 1; i < G->MaxSize; i++)
////    {
////        insertQueue(key[i], G->table[i], pq);
////    }
//    // heapify to build priority queue
//    for(int i = 1; i < G->MaxSize; i++)
//    {
//        pq->element[i].key = key[i];
//        pq->element[i].v = G->table[i];
//        pq->size++;
//    }
//    for(int j = pq->size/2;j > 0; j--)
//        minHeapify(pq, j);
//}

// belongs to queue
int belongsQueue(Node* v, pQueue* pq)
{
    char *name = v->name;
    for(int i = 1; i <= pq->size; i++)
    {
        if(strcmp(name, pq->element[i].v.name) == 0)
        {
            // found: belongs to queue
            return i;
        }
    }
    return -1;
}