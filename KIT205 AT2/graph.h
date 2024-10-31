#pragma once
#ifndef GRAPH_H
#define GRAPH_H

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists;
} Graph;

Graph* createGraph(int vertices);
void addEdge(Graph* graph, int src, int dest);
int* calculateDegreeCentrality(Graph* graph);
double* calculateBetweennessCentrality(Graph* graph);
int* selectCriticalNodes(Graph* graph, int k);
int propagateMisinformation(Graph* graph, int* influenced, int numInfluenced, double probability);
void removeEdge(Graph* graph, int src, int dest);

#endif