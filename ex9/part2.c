#include "graph.h"

int LocateVex(Graph* G, Node* u);
int not_visited(Graph* mygraph, int* visited);
Node* NextAdjVex(Graph* mygraph, Node* v,Node* w);

#ifdef BFS

	/*
	Here is an implementation of a Queue that you may wish to use in
	part 2. You do not need to use it but if you do use it you will
	need to be able to explain how it works and the complexity of
	enqueue and dequeue
	*/

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

    void breadth_first_search(Graph* mygraph)
    {
		Node *v,*w;
		//初始化队列q
		Queue* q = makeQueue();
		int pos;
		int visited[mygraph->MaxSize];
		for(int i = 0; i < mygraph->MaxSize; i++)
        {
            visited[i] = 0;
        }
		int count = 1;
		int nv = not_visited(mygraph, visited);
		while (nv != -1)
		{
			printf("Connected component No.%d traverse：\n", count);
			count++;
			//Visit
			printf("Node:%s, out degree: %d\n", mygraph->table[nv].name, mygraph->table[nv].outdegree);
			visited[nv] = 1;
			enqueue(nv, q);//第一个顶点入队
			while (q->front != NULL || q->back != NULL)//若队列q非空
			{
				v = mygraph->table + dequeue(q)->index;
				if(v->outlist != NULL)
				{
					w = mygraph->table + v->outlist->index;
				}
				else
				{
					w = NULL;
				}
				while (w != NULL)
				{
					pos = LocateVex(mygraph, w);
					if (visited[pos] == 0)
					{
						// Visit w(pos)
						printf("Node:%s, out degree: %d\n", mygraph->table[pos].name, mygraph->table[pos].outdegree);
						visited[pos] = 1;
						enqueue(pos, q);
					}
					w = NextAdjVex(mygraph, v, w);//w后移一个邻接点
				}
			}
			nv = not_visited(mygraph, visited);
		}
    }
#endif

#ifdef DFS
    // recursive part of DFS
    void DFS_re(Graph* mygraph, Node* v, int* visited)
    {
	    // Visit v
        printf("Node:%s, out degree: %d\n", v->name, v->outdegree);
        visited[LocateVex(mygraph,v)] = 1; // label v as visited
        if (v->outlist != NULL)
        {
            Node *w = mygraph->table+(v->outlist->index);//w为第一个邻接点
            while (w != NULL)
            {
                if (visited[LocateVex(mygraph, w)] == 0)//邻接点没有访问，则递归访问
                {
                    DFS_re(mygraph, w, visited);
                }
                w = NextAdjVex(mygraph, v, w);//否则寻找下一个邻接点访问
            }
        }
    }
    void depth_first_search(Graph* mygraph, Node* v)
    {
        int visited[mygraph->MaxSize];
        Node* entrance;
        for(int i = 0; i < mygraph->MaxSize; i++)
        {
            visited[i] = 0;
        }
	    int count = 1;
	    int nv = not_visited(mygraph, visited);
	    while (nv != -1)
	    {
		    printf("Connected component No.%d traverse：\n", count);
		    count++;
		    entrance = mygraph->table + nv;
		    DFS_re(mygraph, entrance, visited);
		    nv = not_visited(mygraph, visited);//更新nv的值
	    }
    }
#endif

int main(int argc, char *argv[])
{
    Graph mygraph;

    read_graph(&mygraph,argv[1]);
    #ifdef DFS
        depth_first_search(&mygraph, mygraph.table);
    #endif
    #ifdef BFS
        breadth_first_search(&mygraph);
	#endif
    return(0);
}

// return index of node u
int LocateVex(Graph* G, Node* u)
{
	for (int i = 0; i < G->MaxSize; i++)
	{
		if (G->table[i].name != NULL && strcmp(G->table[i].name, u->name) == 0)
		{
			return i;
		}
	}
	return -1;
}

//判断非连通图还有哪个顶点没有遍历
int not_visited(Graph* mygraph, int* visited)
{
	for (int i = 1; i < mygraph->MaxSize; i++)
	{
		if (visited[i] != 1)
		{
			return i;//返回没有遍历的顶点序号
		}
	}
	return -1;//全部遍历过了返回-1
}

Node* NextAdjVex(Graph* mygraph, Node* v,Node* w)
{
	int v_index, w_index, index, flag = 0;
	//找到顶点v和w的序号
	v_index = LocateVex(mygraph, v);
	w_index = LocateVex(mygraph, w);
	if (v_index == -1 || w_index == -1)
	{
		return NULL;
	}
	List *p = mygraph->table[v_index].outlist;//初始p为第一个邻接点
	while (p != NULL)
	{
		if (p->index == w_index)
		{
			if (p->next != NULL)//如果w不是最后一个邻接点
			{
				index = p->next->index;//目标顶点的序号
				flag = 1;
				break;
			}
			else
			{
				return NULL;
			}
		}
		else
		{
			p = p->next;
		}
	}
	if (flag == 1)
	{
		return mygraph->table + index;
	}
	else
	{
		//遍历v的所有邻接点依然没有找到w
		return NULL;
	}
}

