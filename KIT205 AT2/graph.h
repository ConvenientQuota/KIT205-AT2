#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

// Represents an adjacency list node
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Represents the graph structure with an adjacency list for each vertex
typedef struct Graph {
    int numVertices;
    Node** adjLists;
} Graph;

// Graph creation and manipulation
Graph* createGraph(int vertices);  // Initialize a graph with a specified number of vertices
void addEdge(Graph* graph, int src, int dest);  // Add an undirected edge between src and dest
void removeEdge(Graph* graph, int src, int dest);  // Remove an undirected edge between src and dest

// Centrality calculations
int* calculateDegreeCentrality(Graph* graph);  // Calculate the degree centrality of each vertex
double* calculateBetweennessCentrality(Graph* graph);  // Calculate betweenness centrality for each vertex

// Critical node selection and misinformation spread simulation
int* selectCriticalNodes(Graph* graph, int k);  // Select top-k critical nodes based on centrality
int propagateMisinformation(Graph* graph, int* influenced, int numInfluenced, double probability);  // Simulate misinformation spread

// Utility functions for debugging and memory management
void printGraph(Graph* graph);  // Print the adjacency list of each vertex
void freeGraph(Graph* graph);   // Free the graph and all allocated memory

#endif