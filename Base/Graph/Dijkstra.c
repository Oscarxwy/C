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
HashSetNode* dijkstra(Node* head)
{
	HashSetNode* map = (HashSetNode*)malloc(sizeof(HashSetNode));
	addToHashSetNode(map, head, 0);

	HashSet* visited = (HashSet*)malloc(sizeof(HashSet));

	Node* minnode = getMinDistanceAndUnSelectNode(map, visited);

	while(minnode != NULL)
	{
		addToHashSet(visited, minnode);
		for(int i = 0; i < minnode->edgesSize; i++)
		{
			Edge* edge = minnode->edge[i];
			if(!containsInHashSetNode(map, edge->to))
			{
				addToHashSetNode(map, edge->to, edge->weight);
			}	
			addToHashSetNode(map, edge->to, min(map[edge->to]->distance, map[edge->from]->distance + edge->weight));
		}
		minnode = getMinDistanceAndUnSelectNode(map, visited);
	}

	free(visited);
	free(minnode);
	return map;
}
*/