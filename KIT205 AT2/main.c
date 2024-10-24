#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

// Helper function to free the graph and all its nodes
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* current = graph->adjLists[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);  // Free each node in the adjacency list
        }
    }
    free(graph->adjLists);  // Free the adjacency lists array
    free(graph);  // Finally, free the graph structure itself
}

void test_createGraph() {
    printf("Testing createGraph()...\n");
    Graph* graph = createGraph(5);
    if (graph->numVertices == 5 && graph->adjLists != NULL) {
        printf("createGraph() passed.\n");
    }
    else {
        printf("createGraph() failed.\n");
    }
    freeGraph(graph);  // Properly free the graph
}

void test_addEdge() {
    printf("Testing addEdge()...\n");
    Graph* graph = createGraph(5);
    addEdge(graph, 0, 1);
    if (graph->adjLists[0]->vertex == 1 && graph->adjLists[1]->vertex == 0) {
        printf("addEdge() passed.\n");
    }
    else {
        printf("addEdge() failed.\n");
    }
    freeGraph(graph);  // Properly free the graph
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
    }
    else {
        printf("calculateDegreeCentrality() failed.\n");
    }
    free(degreeCentrality);
    freeGraph(graph);  // Properly free the graph
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
    freeGraph(graph);  // Properly free the graph
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
    freeGraph(graph);  // Properly free the graph
}

/* Testing different graph structures */

// Testing a simple connected graph
void test_simpleConnectedGraph() {
    printf("Testing simple connected graph...\n");
    Graph* graph = createGraph(5);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    printGraph(graph);

    int* degreeCentrality = calculateDegreeCentrality(graph);
    printf("Degree centrality for simple connected graph:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("Node %d: %d\n", i, degreeCentrality[i]);
    }
    free(degreeCentrality);
    freeGraph(graph);
}

// Testing a disconnected graph
void test_disconnectedGraph() {
    printf("Testing disconnected graph...\n");
    Graph* graph = createGraph(6);
    addEdge(graph, 0, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 4, 5);

    printGraph(graph);

    int* degreeCentrality = calculateDegreeCentrality(graph);
    printf("Degree centrality for disconnected graph:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("Node %d: %d\n", i, degreeCentrality[i]);
    }
    free(degreeCentrality);
    freeGraph(graph);
}

// Testing a cyclic graph
void test_cyclicGraph() {
    printf("Testing cyclic graph...\n");
    Graph* graph = createGraph(4);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 0);  // Creating a cycle

    printGraph(graph);

    int* degreeCentrality = calculateDegreeCentrality(graph);
    printf("Degree centrality for cyclic graph:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("Node %d: %d\n", i, degreeCentrality[i]);
    }
    free(degreeCentrality);
    freeGraph(graph);
}

// Testing a fully connected graph (complete graph)
void test_fullyConnectedGraph() {
    printf("Testing fully connected graph...\n");
    int vertices = 4;
    Graph* graph = createGraph(vertices);
    for (int i = 0; i < vertices; i++) {
        for (int j = i + 1; j < vertices; j++) {
            addEdge(graph, i, j);
        }
    }

    printGraph(graph);

    int* degreeCentrality = calculateDegreeCentrality(graph);
    printf("Degree centrality for fully connected graph:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("Node %d: %d\n", i, degreeCentrality[i]);
    }
    free(degreeCentrality);
    freeGraph(graph);
}

// Testing a sparse graph
void test_sparseGraph() {
    printf("Testing sparse graph...\n");
    Graph* graph = createGraph(7);
    addEdge(graph, 0, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 4, 5);

    printGraph(graph);

    int* degreeCentrality = calculateDegreeCentrality(graph);
    printf("Degree centrality for sparse graph:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("Node %d: %d\n", i, degreeCentrality[i]);
    }
    free(degreeCentrality);
    freeGraph(graph);
}



int main() {

    // Seed the random number generator for stochastic ICM
    srand(time(NULL));

    test_createGraph();
    test_addEdge();
    test_calculateDegreeCentrality();
    test_calculateBetweennessCentrality();
    test_selectCriticalNodes();

    // testing the various graph structures
    test_simpleConnectedGraph();
    test_disconnectedGraph();
    test_cyclicGraph();
    test_fullyConnectedGraph();
    test_sparseGraph();


    // Create a sample graph
    Graph* graph = createGraph(5);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    // Print the graph (for verification)
    printf("Graph structure:\n");
    printGraph(graph);

    // Test Independent Cascade Model (ICM) without targeting any nodes
    int initialInfluenced[] = { 0 };  // Start misinformation spread from node 0
    double propagationProbability = 0.3;  // Probability of influencing neighbors
    int totalInfluencedWithoutTargeting = propagateMisinformation(graph, initialInfluenced, 1, propagationProbability);
    printf("Total influenced without targeting: %d\n", totalInfluencedWithoutTargeting);

    // Select critical nodes to target (to minimize misinformation spread)
    int* criticalNodes = selectCriticalNodes(graph, 2);  // Select 2 critical nodes
    printf("Selected critical nodes: %d, %d\n", criticalNodes[0], criticalNodes[1]);

    // Test ICM after targeting the critical nodes (removing them from the spread)
    int totalInfluencedWithTargeting = propagateMisinformation(graph, criticalNodes, 2, propagationProbability);
    printf("Total influenced after targeting: %d\n", totalInfluencedWithTargeting);

    // Free allocated memory
    free(criticalNodes);
    freeGraph(graph);  // Properly free the graph
    return 0;
}
