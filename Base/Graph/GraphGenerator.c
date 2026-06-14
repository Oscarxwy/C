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

typedef struct Edge
{
	Node* from;
	Node* to;
	int weight;
}Edge;

typedef struct Graph
{
	struct Node** nodes;
	struct Edge** edges;
	int edgesSize;
	int nodesSize;
}Graph;

Graph *graphgenerator()
{
	Graph *graph = (Graph*)malloc(sizeof(Graph));
	graph->nodes = NULL;
	graph->edges = NULL;
	graph->nodesSize = 0;
	graph->edgesSize = 0;
	return graph;
}

Node* isNodeExist(Graph* graph, int value)
{
	for(int i = 0; i < graph->nodesSize; i++)
	{
		if(graph->nodes[i]->value == value)
		{
			return graph->nodes[i];
		}
	}
	return NULL;
}

Node* getNode(int value, Graph* graph)
{
	Node* existingNode = isNodeExist(graph, value);
	if(existingNode)
	{
		return existingNode;
	}
	Node* node = (Node*)malloc(sizeof(Node));
	node->value = value;
	node->in = 0;
	node->out = 0;
	node->nexts = NULL;
	node->edges = NULL;
	node->nextsSize = 0;
	return node;
}

//matrix[i][0] = weight, matrix[i][1] = from, matrix[i][2] = to
Graph* createGraph(int** matrix, int n)
{
	Graph* graph = graphgenerator();
	for(int i = 0; i < n; i++)
	{
		int weight = matrix[i][0];
		/*
		 * 这里需要判断一下from和to是否已经存在，如果不存在就创建一个新的节点
		 * 如果存在就直接使用这个节点
		 * 这样就可以保证每个节点只会被创建一次
		 * 也就是说每个节点的value是唯一的
		 * 这样就可以通过value来判断两个节点是否相同
		 * 也就是说如果两个节点的value相同，那么它们就是同一个节点
		 * 反之，如果两个节点的value不同，那么它们就是不同的节点
		 * 这样就可以保证每个节点只会被创建一次
		*/
		if(!isNodeExist(graph, matrix[i][1]))
		{
			Node* from = getNode(matrix[i][1], graph);
			graph->nodes[graph->nodesSize] = from;
			graph->nodesSize++;
		}
		if(!isNodeExist(graph, matrix[i][2]))
		{
			Node* to = getNode(matrix[i][2], graph);
			graph->nodes[graph->nodesSize] = to;
			graph->nodesSize++;
		}
		Node* from = getNode(matrix[i][1], graph);
		Node* to = getNode(matrix[i][2], graph);
		Edge* edge = (Edge*)malloc(sizeof(Edge));
		edge->weight = weight;
		edge->from = from;
		edge->to = to;
		from->nexts[from->nextsSize] = to;
		from->edges[from->edgesSize] = edge;
		from->out++;
		to->in++;
		graph->edges[graph->edgesSize] = edge;
		graph->edgesSize++;
	}
	return graph;
}
