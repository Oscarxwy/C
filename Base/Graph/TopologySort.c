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

typedef struct queueNode
{
    Node* node;
    struct queueNode* next;
}queueNode;

typedef struct HashNode
{
    Node* node;
    struct HashNode* next;
}HashNode;

typedef struct HashSet
{
    HashNode** table;
    int size;
    int capacity;
}HashSet;

typedef struct NodeList
{
    Node* node;
    struct NodeList* next;
}NodeList;

Node* createNode(int value);
Node** createQueue(int capacity);
bool isQueueEmpty(queueNode* front, queueNode* rear);
void enqueue(queueNode** rear, Node* node);
Node* dequeue(queueNode** front, queueNode** rear);
Node* peek(queueNode* front);
void freeQueue(queueNode* front);
HashNode* createHashNode(Node* node);
HashSet* createHashSet(int capacity);
void addToHashSet(HashSet* set, Node* node);
int containsInHashSet(HashSet* set, Node* node);
int hashdelete(HashSet* set, Node* node);
void freeHashSet(HashSet* set);
NodeList* createNodeList(Node* node);
NodeList* addToNodeList(NodeList* head, Node* node);
NodeList* reverseNodeList(NodeList* head);
void freeNodeList(NodeList* head);
NodeList* topologysort(Graph* graph);

Node* createNode(int value)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->in = 0;
    node->out = 0;
    node->nexts = NULL;
    node->edges = NULL;
    node->nextsSize = 0;
    node->edgesSize = 0;
    return node;
}

Node** createQueue(int capacity)
{
    Node** queue = (Node**)malloc(sizeof(Node*) * capacity);
    return queue;
}

bool isQueueEmpty(queueNode* front, queueNode* rear)
{
    return front == rear;
}   

void enqueue(queueNode** rear, Node* node)
{
    queueNode* qNode = (queueNode*)malloc(sizeof(queueNode));
    qNode->node = node;
    qNode->next = NULL;
    (*rear)->next = qNode;
    *rear = qNode;
}

Node* dequeue(queueNode** front, queueNode** rear)
{
    if (isQueueEmpty(*front, *rear))
    {
        return NULL;
    }
    queueNode* temp = (*front)->next;
    Node* node = temp->node;
    (*front)->next = temp->next;
    if (*rear == temp)
    {
        *rear = *front; // If the dequeued node was the rear, move rear back to front
    }
    free(temp);
    return node;
}

Node* peek(queueNode* front)
{
    if (isQueueEmpty(front, front))
    {
        return NULL;
    }
    return front->next->node;
}

void freeQueue(queueNode* front)
{
    queueNode* current = front;
    while (current != NULL)
    {
        queueNode* temp = current;
        current = current->next;
        free(temp);
    }
}

HashNode* createHashNode(Node* node)
{
    HashNode* hNode = (HashNode*)malloc(sizeof(HashNode));
    hNode->node = node;
    hNode->next = NULL;
    return hNode;
}

HashSet* createHashSet(int capacity)
{
    HashSet* set = (HashSet*)malloc(sizeof(HashSet));
    set->capacity = capacity;
    set->size = 0;
    set->table = (HashNode**)malloc(sizeof(HashNode*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        set->table[i] = NULL;
    }
    return set;
}

void addToHashSet(HashSet* set, Node* node)
{
    int index = node->value % set->capacity;
    HashNode* newNode = createHashNode(node);
    newNode->node = node;
    newNode->next = set->table[index];
    set->table[index] = newNode;
    set->size++;
}

int containsInHashSet(HashSet* set, Node* node)
{
    int index = node->value % set->capacity;
    HashNode* current = set->table[index];
    while (current != NULL)
    {
        if (current->node == node)
        {
            return 1; // Node found in hash set
        }
        current = current->next;
    }
    return 0; // Node not found in hash set
}

int hashdelete(HashSet* set, Node* node)
{
    int index = node->value % set->capacity;
    HashNode* current = set->table[index];
    HashNode* prev = NULL;
    while (current != NULL)
    {
        if (current->node == node)
        {
            if (prev == NULL)
            {
                set->table[index] = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            free(current);
            return 1; // Node deleted successfully
        }
        prev = current;
        current = current->next;
    }
    return 0; // Node not found
}   

void freeHashSet(HashSet* set)
{
    for (int i = 0; i < set->capacity; i++)
    {
        HashNode* current = set->table[i];
        while (current != NULL)
        {
            HashNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(set->table);
    free(set);
}

NodeList* createNodeList(Node* node)
{
    NodeList* nList = (NodeList*)malloc(sizeof(NodeList));
    nList->node = node;
    nList->next = NULL;
    return nList;
}

NodeList* addToNodeList(NodeList* head, Node* node)
{
    NodeList* newNode = createNodeList(node);
    newNode->next = head;
    return newNode;
}

NodeList* reverseNodeList(NodeList* head)
{
    NodeList* prev = NULL;
    NodeList* current = head;
    while (current != NULL)
    {
        NodeList* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev; // New head of the reversed list
}

void freeNodeList(NodeList* head)
{
    NodeList* current = head;
    while (current != NULL)
    {
        NodeList* temp = current;
        current = current->next;
        free(temp);
    }
}

NodeList* topologysort(Graph* graph)
{
    queueNode* front = (queueNode*)malloc(sizeof(queueNode));
    queueNode* rear = front;
    front->next = NULL;

    for (int i = 0; i < graph->nodesSize; i++)
    {
        if (graph->nodes[i]->in == 0)
        {
            enqueue(&rear, graph->nodes[i]);
        }
    }

    NodeList* nodelist = NULL;

    while (!isQueueEmpty(front, rear))
    {
        Node* zeronode = dequeue(&front, &rear);
        nodelist = addToNodeList(nodelist, zeronode);
        for (int i = 0; i < zeronode->nextsSize; i++)
        {
            Node* nextnode = zeronode->nexts[i];
            nextnode->in--;
            if (nextnode->in == 0)
            {
                enqueue(&rear, nextnode);  
            }
        }
    }

    freeQueue(front);
    return reverseNodeList(nodelist);
}

int main()
{
    // Example usage
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->nodesSize = 4;
    graph->nodes = (Node**)malloc(sizeof(Node*) * graph->nodesSize);
    
    graph->nodes[0] = createNode(1);
    graph->nodes[1] = createNode(2);
    graph->nodes[2] = createNode(3);
    graph->nodes[3] = createNode(4);

    graph->nodes[0]->nexts = (Node**)malloc(sizeof(Node*) * 2);
    graph->nodes[0]->nexts[0] = graph->nodes[1];
    graph->nodes[0]->nexts[1] = graph->nodes[2];
    graph->nodes[0]->nextsSize = 2;
    graph->nodes[1]->in++;
    graph->nodes[2]->in++;

    graph->nodes[1]->nexts = (Node**)malloc(sizeof(Node*) * 1);
    graph->nodes[1]->nexts[0] = graph->nodes[3];
    graph->nodes[1]->nextsSize = 1;
    graph->nodes[3]->in++;

    NodeList* sortedList = topologysort(graph);

    // Print sorted nodes
    NodeList* current = sortedList;
    while (current != NULL)
    {
        printf("%d ", current->node->value);
        current = current->next;
    }
    printf("\n");

    // Free allocated memory for nodes, their nexts, and the node list
    free(graph->nodes[0]->nexts);
    free(graph->nodes[1]->nexts);
    free(graph->nodes);
    
    freeNodeList(sortedList);
    
    free(graph);

    return 0;
}

/*
NodeList* topologysort(Graph* graph)
{
    HashSet* visited = createHashSet(1000); // Arbitrary capacity for hash set
    queueNode* queue = (queueNode*)malloc(sizeof(queueNode));
    queue->next = NULL; // Initialize the queue

    for (int i = 0; i < graph->nodesSize; i++)
    {
        if (graph->nodes[i]->in == 0)
        {
            enqueue(&queue, graph->nodes[i]);
            addToHashSet(visited, graph->nodes[i]);
        }
    }

    NodeList* nodelist = NULL;

    while (!isQueueEmpty(queue, queue))
    {
        Node* zeronode = dequeue(&queue);
        if(!containsInHashSet(visited, zeronode))
        {
            addToHashSet(visited, zeronode);
            nodelist = addToNodeList(nodelist, zeronode);
            for (int i = 0; i < zeronode->nextsSize; i++)
            {
                Node* nextNode = zeronode->nexts[i];
                nextNode->in--;
                if (nextNode->in == 0)
                {
                    enqueue(&queue, nextNode);
                }
            }
        }
    }

    freeQueue(queue);
    freeHashSet(visited);
    return nodelist;
}
*/
/*
 * xwy
NodeList* topologysort(Graph* graph)
{
	HashSet* visited = createHashSet();
	queueNode* quene = createQueue();

	while(graph->nodes->in == 0)
	{
		enqueue(queue, graph->nodes);
		graph->nodes = graph->nodes->next;
	}

	NodeList* nodelist = createNodeList();

	while(!isEmptyQueue(queue))
	{
		Node* zeronode = dequeue(queue);
		for(int i = 0; i < nextsSize; i++)
		{
			addNodeList(nodelist, zeronode);
			zeronode->nexts[i]->in--;
			if(zeronode->next[i]->in == 0)
				enqueue(queue, zeronode->nexts[i])
		}
	}

    freeQueue(queue);
    freeHashSet(visited);

    return nodelist;
}
*/