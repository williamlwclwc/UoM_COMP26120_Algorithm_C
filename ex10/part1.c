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

int DijkstraShortestPaths(Graph* G, int index_v, float* total_dist);
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
    int result = 0;
    int is_small_world = 1;
    float total_dist = 0;
    for(int i = 1; i < mygraph.MaxSize; i++)
    {
        result = DijkstraShortestPaths(&mygraph, i, &total_dist);
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
    printf("Average distance in total: %.2f\n", total_dist);
    free_graph(&mygraph);

    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Total time: %.3fs\n", total_t);

    return(0);
}

int DijkstraShortestPaths(Graph* G, int index_v, float* total_dist)
{
    int D[G->MaxSize];
    int visited[G->MaxSize];
    Node* node_u;
    ElemType elem_u;
    Node* v = G->table + index_v;
    int temp;
    int pq_index;
    for(int i = 0; i < G->MaxSize; i++)
    {
        D[i] = INT_MAX;
        visited[i] = 0;
    }
    D[index_v] = 0;
    // set priority queue
    pQueue* pq = initQueue(G->MaxSize);
    //buildQueue(D, G, pq);
    insertQueue(D[index_v], G->table[index_v], pq);
    // while queue is not empty
    List* z;
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
//            pq_index = belongsQueue(G->table + z->index, pq);
//            if(pq_index != -1)
//            {
//                if(elem_u.key == INT_MAX)
//                {
//                    temp = elem_u.key;
//                }
//                else
//                {
//                    temp = elem_u.key + 1;
//                }
//                if(temp < D[z->index])
//                {
//                    D[z->index] = temp;
//                    pq->element[pq_index].key = D[z->index];
//                    for(int j = pq->size/2; j > 0; j--)
//                        minHeapify(pq, j);
//
//                }
//            }
            if(elem_u.key == INT_MAX)
            {
                temp = elem_u.key;
            }
            else
            {
                temp = elem_u.key + 1;
            }
            if(temp < D[z->index])
            {
                D[z->index] = temp;
                if(visited[z->index])
                {
                    // update
                    pq_index = belongsQueue(G->table + z->index, pq);
                    if(pq_index != -1)
                    {
                        pq->element[pq_index].key = D[z->index];
                        for(int j = pq->size/2; j > 0; j--)
                            minHeapify(pq, j);
                    }
                }
                else
                {
                    // insert
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
//                if(index_v == 268)
//                    printf("Node %s cannot reach Node %s\n", G->table[index_v].name, G->table[i].name);
                non_reachable++;
            }
            else
            {
//                if(index_v == 268)
//                    printf("Distance of Node %s and Node %s is larger than 6(%d)\n", G->table[index_v].name, G->table[i].name, D[i]);
                larger_than_six++;
                avg += D[i];
            }
        }
        else
        {
            avg += D[i];
        }
    }
    if(is_small_world)
    {
        printf("Node %s can reach all other node with in 6 steps\n", v->name);
    }
    else
    {
        printf("There are %d nodes that Node %s cannot reach\n", non_reachable, v->name);
        if(larger_than_six > 0)
          printf("There are %d nodes that Node %s have to reach with more than 6 steps\n", larger_than_six, v->name);
    }
    avg = (float)avg / G->MaxSize;
    printf("Average distance: %f\n", avg);
    *total_dist += avg;
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
    pq->size++;
    pq->element[pq->size].key = key;
    pq->element[pq->size].v = v;
    int i = pq->size;
    ElemType temp;
    while(i > 1 && pq->element[i/2].key > pq->element[i].key)
    {
        // swap elem[i/2], elem[i]
        temp = pq->element[i/2];
        pq->element[i/2] = pq->element[i];
        pq->element[i] = temp;
        i = i/2;
    }
}

// remove minimum of queue
ElemType removeMin(pQueue* pq)
{
    ElemType min = pq->element[1];
    pq->element[1] = pq->element[pq->size];
    pq->size--;
    int i = 1;
    int j = 0;
    ElemType temp;
    while(i < pq->size)
    {
        if(2*i+1 <= pq->size)
        {
            // this node has 2 internal children
            if(pq->element[i].key <= pq->element[2*i].key && \
            pq->element[i].key <= pq->element[2*i+1].key)
            {
                return min;
            }
            else
            {
                if(pq->element[2*i].key >= pq->element[2*i+1].key)
                {
                    j = 2*i+1;
                }
                else
                {
                    j = 2*i;
                }
                // swap elem[i], elem[j]
                temp = pq->element[i];
                pq->element[i] = pq->element[j];
                pq->element[j] = temp;
                i = j;
            }
        }
        else
        {
            // this node has 0 or 1 internal child
            if(2*i <= pq->size)
            {
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
    int l = 2*i;
    int r = 2*i + 1;
    int min;
    ElemType temp;
    if(l <= pq->size && pq->element[l].key < pq->element[i].key)
    {
        min = l;
    }
    else
    {
        min = i;
    }
    if(r <= pq->size && pq->element[r].key < pq->element[min].key)
    {
        min = r;
    }
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