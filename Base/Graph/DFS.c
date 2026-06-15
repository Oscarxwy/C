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

typedef struct stackNode
{
    Node* node;
    struct stackNode* next;
}stackNode;

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

stackNode* createStackNode(Node* node)
{
    stackNode* sNode = (stackNode*)malloc(sizeof(stackNode));
    sNode->node = node;
    sNode->next = NULL;
    return sNode;
}   

bool isStackEmpty(stackNode* top)
{
    return top == NULL;
}

void push(stackNode** top, Node* node)
{
    stackNode* sNode = createStackNode(node);
    sNode->next = *top;
    *top = sNode;
}

Node* pop(stackNode** top)
{
    if (*top == NULL)
    {
        return NULL; // Stack is empty
    }
    stackNode* temp = *top;
    Node* node = temp->node;
    *top = (*top)->next;
    free(temp);
    return node;
}

Node* peek(stackNode* top)
{
    if (top == NULL)
    {
        return NULL; // Stack is empty
    }
    return top->node;
}

void freeStack(stackNode* top)
{
    while (top != NULL)
    {
        stackNode* temp = top;
        top = top->next;
        free(temp);
    }
}

unsigned int hashFunction(int value, int capacity)
{
    return value % capacity;
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

bool containsInHashSet(HashSet* set, Node* node)
{
    int index = node->value % set->capacity;
    HashNode* current = set->table[index];
    while (current != NULL)
    {
        if (current->node == node)
        {
            return true;
        }
        current = current->next;
    }
    return false;
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

void dfs(Node* start)
{
    if (start == NULL)
    {
        return;
    }
    
    HashSet* visited = createHashSet(1000); // Arbitrary capacity for hash set
    stackNode* stack = NULL;

    push(&stack, start);
    addToHashSet(visited, start);  
    printf("%d ", start->value);

    while (!isStackEmpty(stack))
    {
        Node* currentNode = pop(&stack);
        for (int i = 0; i < currentNode->nextsSize; i++)
        {
            Node* nextNode = currentNode->nexts[i];
            if (!containsInHashSet(visited, nextNode))
            {
                push(&stack, currentNode); // Push current node back to stack to continue after exploring nextNode
                push(&stack, nextNode);
                addToHashSet(visited, nextNode);
                printf("%d ", nextNode->value);
                break; // Break to explore nextNode first
            }
        }
    }

    freeStack(stack);
    freeHashSet(visited);
}

int main()
{
    // Example usage
    Node* node1 = createNode(1);
    Node* node2 = createNode(2);
    Node* node3 = createNode(3);
    Node* node4 = createNode(4);

    node1->nexts = (Node**)malloc(sizeof(Node*) * 2);
    node1->nexts[0] = node2;
    node1->nexts[1] = node3;
    node1->nextsSize = 2;

    node2->nexts = (Node**)malloc(sizeof(Node*) * 1);
    node2->nexts[0] = node4;
    node2->nextsSize = 1;

    dfs(node1);

    // Free allocated memory for nodes and their nexts
    free(node1->nexts);
    free(node2->nexts);
    free(node1);
    free(node2);
    free(node3);
    free(node4);    

    return 0;
}

/*
 * xwy 伪代码

bool isEmptyStack(stackNode* top, stackNode* bottom)
{
    return top == bottom;
}

void dfs(Node* start)
{
	if(start == NULL)
		return;

	HashSet* visited = (HashSet*)malloc(sizeof(HashSet));
	visited->capacity = 1000;
	visited->size = 0;
	
	Node** stack = createStack(1000);
	int front = 0;
	int rear = 0;

	push(stack, start);
	addToHashSet(visited);
	printf("%d", start->value);

	while(!isEmptyStack(stack))
	{
		Node* currentnode = (Node*)malloc(sizeof(Node));
		currentnode = pop(stack);
		for(int i = 0; i < currentnode->nextsize; i++)
		{
			if(!isContainsInHashSet(visted))
			{
				push(stack, currentnode);
				push(stack, currentnode[i]);
				addToHashSet(currentnode[i]);
				printf("%d", currentnode[i]->value);
				break;
			}
		}
	}

	free(stack);
	free(visited);

}
*/