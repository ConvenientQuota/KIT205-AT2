#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Queue {
    int* items;
    int front;
    int rear;
    int size;
} Queue;

Queue* createQueue(int size) {
    Queue* q = malloc(sizeof(Queue));
    q->items = malloc(size * sizeof(int));
    q->front = 0;
    q->rear = -1;
    q->size = 0;
    return q;
}

void enqueue(Queue* q, int value) {
    q->rear++;
    q->items[q->rear] = value;
    q->size++;
}

int dequeue(Queue* q) {
    int item = q->items[q->front];
    q->front++;
    q->size--;
    return item;
}

int isEmpty(Queue* q) {
    return q->size == 0;
}


Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(Node*));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }

    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Since the graph is undirected, add an edge from dest to src as well
    newNode = malloc(sizeof(Node));
    newNode->vertex = src;
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

int* calculateDegreeCentrality(Graph* graph) {
    int* degree = malloc(graph->numVertices * sizeof(int));

    for (int i = 0; i < graph->numVertices; i++) {
        Node* temp = graph->adjLists[i];
        degree[i] = 0;

        while (temp) {
            degree[i]++;
            temp = temp->next;
        }
    }

    return degree;
}

