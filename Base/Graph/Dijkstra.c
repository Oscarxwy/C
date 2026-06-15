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

