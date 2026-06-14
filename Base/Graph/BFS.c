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

typedef struct QueueNode
{
    Node* node;
    struct QueueNode* next;
}QueueNode;

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

int isQueueEmpty(int front, int rear)
{
    return front == rear;
}

void enqueue(Node** queue, int* rear, Node* node)
{
    queue[*rear] = node;
    (*rear)++;
}

Node* dequeue(Node** queue, int* front)
{
    if (*front == -1)
    {
        return NULL;
    }
    Node* node = queue[*front];
    (*front)++;
    return node;
}

Node* peek(Node** queue, int front)
{
    if (front == -1)
    {
        return NULL;
    }
    return queue[front];
}

void freeQueue(Node** queue)
{
    free(queue);
}

unsigned int hashFunction(int value, int capacity)
{
    return value % capacity;
}

HashNode** createHashTable(int capacity)
{
    HashNode** hashTable = (HashNode**)malloc(sizeof(HashNode*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        hashTable[i] = NULL;
    }
    return hashTable;
}

void addToHashSet(HashSet* set, Node* node)
{
    int index = node->value % set->capacity;
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    newNode->node = node;
    newNode->next = set->table[index];
    set->table[index] = newNode;
}

int containsInHashSet(HashSet* set, Node* node)
{
    int index = node->value % set->capacity;
    HashNode* current = set->table[index];
    while (current != NULL)
    {
        if (current->node == node)
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
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

void bfs(Node* start)
{
    if (start == NULL)
    {
        return;
    }
    
    HashSet* visited = (HashSet*)malloc(sizeof(HashSet));
    visited->capacity = 1000; // Arbitrary capacity for hash set
    visited->size = 0;
    visited->table = createHashTable(visited->capacity);

    Node** queue = createQueue(1000); // Arbitrary capacity for queue
    int front = 0;
    int rear = 0;

    enqueue(queue, &rear, start);
    addToHashSet(visited, start);

    while (!isQueueEmpty(front, rear))
    {
        Node* currentNode = dequeue(queue, &front);
        printf("%d ", currentNode->value); // Process the current node

        for (int i = 0; i < currentNode->nextsSize; i++)
        {
            Node* nextNode = currentNode->nexts[i];
            if (!containsInHashSet(visited, nextNode))
            {
                enqueue(queue, &rear, nextNode);
                addToHashSet(visited, nextNode);
            }
        }
    }

    freeQueue(queue);
    freeHashSet(visited);
}

int main()
{
    // Example usage of BFS
    Node* node1 = createNode(1);
    Node* node2 = createNode(2);
    Node* node3 = createNode(3);
    Node* node4 = createNode(4);

    node1->nextsSize = 2;
    node1->nexts = (Node**)malloc(sizeof(Node*) * node1->nextsSize);
    node1->nexts[0] = node2;
    node1->nexts[1] = node3;

    node2->nextsSize = 1;
    node2->nexts = (Node**)malloc(sizeof(Node*) * node2->nextsSize);
    node2->nexts[0] = node4;

    bfs(node1);

    // Free allocated memory for nodes and their nexts
    free(node1->nexts);
    free(node2->nexts);
    free(node3);
    free(node4);
    free(node1);

    return 0;
}