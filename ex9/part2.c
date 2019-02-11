#include "graph.h"

#define MAX_NAME_LEN 100
#define MAX_INT 9999

int LocateVex(Graph* G, Node* u);
int not_visited(Graph* mygraph, int* visited);
Node* min_out_degree(Graph* mygraph);

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
		List *temp;
		// initialize queue q
		Queue* q = makeQueue();
		int pos;
		// initialize visited array
		int visited[mygraph->MaxSize];
		for(int i = 0; i < mygraph->MaxSize; i++)
        {
            visited[i] = 0;
        }
		int count = 1;
		// get the smallest non-zero outdegree node
		Node* min_node = min_out_degree(mygraph);
		// initialize not-visited to be the start point
		int nv = LocateVex(mygraph, min_node);
		Node max_outdegree;
		max_outdegree.outdegree = mygraph->table[nv].outdegree;
		max_outdegree.name = (char*)malloc(MAX_NAME_LEN);
		Node min_outdegree;
		min_outdegree.outdegree = MAX_INT; // init to a large number
		min_outdegree.name = (char*)malloc(MAX_NAME_LEN);
		int min_flag = 1; // min is in which connected component
		int max_flag = 1; // max is in which connected component
		int min_node_cnt = 0;
		int inner_cnt; // count nodes for each connected component
		while (nv != -1)
		{
			inner_cnt = 0;
			// printf("Connected component No.%d traverse：\n", count);
			//Visit
			if(min_outdegree.outdegree > mygraph->table[nv].outdegree && mygraph->table[nv].outdegree != 0)
			{
				strcpy(min_outdegree.name, mygraph->table[nv].name); 
				min_outdegree.outdegree = mygraph->table[nv].outdegree;
				min_flag = count;
			}
			if((max_outdegree.outdegree < mygraph->table[nv].outdegree && min_flag == count) || min_flag != max_flag)
			{
				strcpy(max_outdegree.name, mygraph->table[nv].name);
				max_outdegree.outdegree = mygraph->table[nv].outdegree;
				max_flag = count;
			}
			// printf("Node:%s, out degree: %d\n", mygraph->table[nv].name, mygraph->table[nv].outdegree);
			visited[nv] = 1;
			inner_cnt++;
			enqueue(nv, q); // enqueue the first node
			while (q->front != NULL) // if the queue is not empty 
			{
				temp = dequeue(q);
				v = mygraph->table + temp->index;
				free(temp);
				temp = v->outlist;
				if(temp != NULL)
				{
					w = mygraph->table + temp->index;
				}
				else
				{
					w = NULL;
				}
				while (w != NULL)
				{
					pos = LocateVex(mygraph, w);
					//printf("%d\n", pos);
					if (visited[pos] == 0)
					{
						// Visit w(pos)
						if(min_outdegree.outdegree > mygraph->table[pos].outdegree && mygraph->table[pos].outdegree != 0)
						{
							strcpy(min_outdegree.name, mygraph->table[pos].name);
							min_outdegree.outdegree = mygraph->table[pos].outdegree;
							min_flag = count;
						}
						if((max_outdegree.outdegree < mygraph->table[pos].outdegree && min_flag == count) || min_flag != max_flag)
						{
							strcpy(max_outdegree.name, mygraph->table[pos].name);
							max_outdegree.outdegree = mygraph->table[pos].outdegree;
							max_flag = count;
						}
						// printf("Node:%s, out degree: %d\n", mygraph->table[pos].name, mygraph->table[pos].outdegree);
						visited[pos] = 1;
						inner_cnt++;
						enqueue(pos, q);
					}
					// move w to next adjcent node
					temp = temp->next;
					if(temp != NULL)
					{
						w = mygraph->table + temp->index;
					}
					else
					{
						w = NULL;
					}
				}
			}
			nv = not_visited(mygraph, visited);
			if(min_flag == count)
			{
				min_node_cnt = inner_cnt;
			}
			count++;
		}
		printf("The node with the smallest (non-zero) out-degree is %s with out-degree %d\n"
		"There are %d nodes reachable from the node with the "
		"smallest (non-zero) out-degree and the node with the "
		"largest out-degree is %s with out-degree %d\n", \
		min_outdegree.name, min_outdegree.outdegree, min_node_cnt, max_outdegree.name, max_outdegree.outdegree);
    free(q);
	free(min_outdegree.name);
	free(max_outdegree.name);
    }

#endif

#ifdef DFS

    // recursive part of DFS
    void DFS_re(int* node_cnt, Node* each_max_node, Graph* mygraph, Node* v, int* visited)
    {
	    // Visit v
        // printf("Node:%s, out degree: %d\n", v->name, v->outdegree);
		(*node_cnt)++; // count the nodes
		// update the max node
		if(v->outdegree > each_max_node->outdegree)
		{
			each_max_node->name = v->name;
			each_max_node->outdegree = v->outdegree;
		}
		visited[LocateVex(mygraph,v)] = 1; // label v as visited
		List * temp = v->outlist;
        if (temp != NULL)
        {
            Node *w = mygraph->table + (temp->index); // w is the first adjacent node
            while (w != NULL)
            {
                if (visited[LocateVex(mygraph, w)] == 0) // if the adjacent node is not visited, then recursive visit
                {
                    DFS_re(node_cnt, each_max_node, mygraph, w, visited);
                }
				// move w to next adjcent node
				temp = temp->next;
				if(temp != NULL)
				{
					w = mygraph->table + temp->index;
				}
				else
				{
					w = NULL;
				}
            }
        }
    }

    void depth_first_search(Graph* mygraph, Node* v)
    {
        int visited[mygraph->MaxSize];
        Node* entrance; // start point for dfs
        for(int i = 0; i < mygraph->MaxSize; i++)
        {
            visited[i] = 0;
        }
		Node* min_node = min_out_degree(mygraph); // minimum node of whole graph
		Node each_max_node;
		each_max_node.name = min_node->name;
		each_max_node.outdegree = min_node->outdegree;
		Node max_node;
	    int count = 1;
		int min_node_cnt = -1; // how many nodes in the smallest connected component
	    int node_cnt = 0;
		// int nv = not_visited(mygraph, visited);
		int nv = LocateVex(mygraph, min_node); // start from the min outdegree node
	    while (nv != -1)
	    {
		    // printf("Connected component No.%d traverse：\n", count);
		    count++;
		    entrance = mygraph->table + nv;
		    DFS_re(&node_cnt, &each_max_node, mygraph, entrance, visited);
			// the number of nodes of with the smallest outdegree
			if(count == 2)
			{
				min_node_cnt = node_cnt;
				max_node.name = each_max_node.name;
				max_node.outdegree = each_max_node.outdegree;
			}
		    nv = not_visited(mygraph, visited); // update the value of visited
			node_cnt = 0;
	    }
		printf("The node with the smallest (non-zero) out-degree is %s with out-degree %d\n"
		"There are %d nodes reachable from the node with the "
		"smallest (non-zero) out-degree and the node with the "
		"largest out-degree is %s with out-degree %d\n", \
		min_node->name, min_node->outdegree, min_node_cnt, max_node.name, max_node.outdegree);
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
	free_graph(&mygraph);
    return(0);
}

// return index of node u
int LocateVex(Graph* mygraph, Node* u)
{
	for (int i = 0; i < mygraph->MaxSize; i++)
	{
		if (mygraph->table[i].name != NULL && strcmp(mygraph->table[i].name, u->name) == 0)
		{
			return i;
		}
	}
	return -1;
}

// return the index of the node which has not been visited 
int not_visited(Graph* mygraph, int* visited)
{
	for (int i = 1; i < mygraph->MaxSize; i++)
	{
		if (visited[i] != 1)
		{
			return i; // return the index which has not been visited
		}
	}
	return -1; // all nodes are visited, return -1
}

// calculate minimum out degree node of the whole graph
Node* min_out_degree(Graph* mygraph)
{
	int i = 1;
	while(mygraph->table[i].outdegree == 0) i++;
	Node* min_node = mygraph->table + i;
	for (int i = 1; i < mygraph->MaxSize; i++)
	{
		if (mygraph->table[i].name!=NULL) 
		{
			if(mygraph->table[i].outdegree < min_node->outdegree \
				&& mygraph->table[i].outdegree != 0)
			{
				min_node = mygraph->table + i;
			}
		}
	}
	return min_node;
}

