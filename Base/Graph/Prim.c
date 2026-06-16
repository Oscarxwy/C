#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Node
{
    int value;
    int in;
    int out;
    struct Node** nexts;
    struct Edge** edges;
    int nextsSize;
    int edgesSize;
}Node;

/*
ListEdge* prim(Graph* graph)
{
	queueEdge* queuefront = (quueueEdge*)malloc(sizeof(queueEdge));
	Node* queuerear = queuefront;
	front->next = NULL;

	HashSet* visited = (HashSet*)malloc(sizeof(HashSet)*capacity);

	EdgeList* listfront = (EdgeList*)malloc(sizeof(EdgeList));
	Edge* listrear = listfront;
	front->next = NULL;

	for(int i = 0; i < graph->nodesSize; i++)
	{
		if(!contains(visited, graph->nodes[i]))
		{
			Node* node = graph->nodes[i];
			addHashSet(visited, node);
			for(int j = 0; j < node->edgesSize; j++)
			{
				enqueue(queuerear, node->edges[j]);
				smallqueue(queuefront, queuerear);
			}
		}

		while(!isEmptyQueue(front, rear))
		{
			Edge* smalledge = dequeue(front, rear);
			if(!containInHashSet(visited, smalledge->to))
			{
				addToEdgeList(listfront, smalledge);
				Node* node = smalledge->to;
				addHashSet(visited, node);
				for(int k = 0; k < node->edgesSize; k++)
				{
					enqueue(queuerear, node->edges[j]);
					smallqueue(queuefront, queuerear);
				}
			}
		}
	}

	free(queuefront);
	free(visited);
	return reverseEdgeList(listfront);
}
*/