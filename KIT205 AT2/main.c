#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

void test_createGraph() {
    printf("Testing createGraph()...\n");
    Graph* graph = createGraph(5);
    if (graph->numVertices == 5 && graph->adjLists != NULL) {
        printf("createGraph() passed.\n");
    } else {
        printf("createGraph() failed.\n");
    }
    free(graph);
}

void test_addEdge() {
    printf("Testing addEdge()...\n");
    Graph* graph = createGraph(5);
    addEdge(graph, 0, 1);
    if (graph->adjLists[0]->vertex == 1 && graph->adjLists[1]->vertex == 0) {
        printf("addEdge() passed.\n");
    } else {
        printf("addEdge() failed.\n");
    }
    free(graph);
}

void test_calculateDegreeCentrality() {
    printf("Testing calculateDegreeCentrality()...\n");
    Graph* graph = createGraph(5);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);

    int* degreeCentrality = calculateDegreeCentrality(graph);
    if (degreeCentrality[0] == 2 && degreeCentrality[1] == 2 && degreeCentrality[2] == 1) {
        printf("calculateDegreeCentrality() passed.\n");
    } else {
        printf("calculateDegreeCentrality() failed.\n");
    }
    free(degreeCentrality);
    free(graph);
}

void test_calculateBetweennessCentrality() {
    printf("Testing calculateBetweennessCentrality()...\n");
    Graph* graph = createGraph(5);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    double* betweennessCentrality = calculateBetweennessCentrality(graph);
    printf("Betweenness Centrality Scores:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("Node %d: %.2f\n", i, betweennessCentrality[i]);
    }

    free(betweennessCentrality);
    free(graph);
}

void test_selectCriticalNodes() {
    printf("Testing selectCriticalNodes()...\n");
    Graph* graph = createGraph(5);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    int* criticalNodes = selectCriticalNodes(graph, 2);
    printf("Critical nodes selected to minimize misinformation spread: %d, %d\n", criticalNodes[0], criticalNodes[1]);

    free(criticalNodes);
    free(graph);
}

int main() {
    test_createGraph();
    test_addEdge();
    test_calculateDegreeCentrality();
    test_calculateBetweennessCentrality();
    test_selectCriticalNodes();
    
    return 0;
}
