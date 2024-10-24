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

// Calculate betweenness centrality using Brandes' algorithm
double* calculateBetweennessCentrality(Graph* graph) {
    if (graph == NULL || graph->adjLists == NULL) {
        printf("Graph is NULL or uninitialized.\n");
        return NULL;
    }

    double* betweenness = malloc(graph->numVertices * sizeof(double));
    if (betweenness == NULL) {
        printf("Memory allocation failed for betweenness.\n");
        return NULL;
    }

    // Initialize betweenness values to 0
    for (int i = 0; i < graph->numVertices; i++) {
        betweenness[i] = 0.0;
    }

    // Loop over each node as the source
    for (int s = 0; s < graph->numVertices; s++) {
        // Initialize data structures
        int* sigma = malloc(graph->numVertices * sizeof(int));    // Shortest paths count
        int* dist = malloc(graph->numVertices * sizeof(int));     // Distance from source
        double* delta = malloc(graph->numVertices * sizeof(double));  // Dependency score
        int** pred = malloc(graph->numVertices * sizeof(int*));   // Predecessor list
        Queue* q = createQueue(graph->numVertices);

        // Memory allocation checks
        if (sigma == NULL || dist == NULL || delta == NULL || pred == NULL || q == NULL) {
            printf("Memory allocation failed in calculateBetweennessCentrality.\n");
            free(sigma); free(dist); free(delta);
            if (pred != NULL) { free(pred); }
            if (q != NULL) { free(q->items); free(q); }
            return NULL;
        }

        for (int i = 0; i < graph->numVertices; i++) {
            sigma[i] = 0;
            dist[i] = -1;
            delta[i] = 0.0;
            pred[i] = malloc(graph->numVertices * sizeof(int));
            if (pred[i] == NULL) {  // Check memory allocation for pred[i]
                printf("Memory allocation failed for pred[%d].\n", i);
                // Free allocated memory before returning
                free(sigma); free(dist); free(delta);
                for (int j = 0; j < i; j++) {
                    free(pred[j]);
                }
                free(pred);
                free(q->items); free(q);
                return NULL;
            }

            // Initialize pred[i] to -1 to mark no predecessors
            for (int j = 0; j < graph->numVertices; j++) {
                pred[i][j] = -1;  // Initialize to invalid values (-1)
            }
        }

        sigma[s] = 1;  // Only one shortest path to itself
        dist[s] = 0;

        // BFS from source node s
        enqueue(q, s);
        while (!isEmpty(q)) {
            int v = dequeue(q);
            Node* adj = graph->adjLists[v];

            // Traverse neighbors
            while (adj) {
                int w = adj->vertex;
                if (dist[w] < 0) {  // w is not visited
                    enqueue(q, w);
                    dist[w] = dist[v] + 1;
                }
                if (dist[w] == dist[v] + 1) {
                    sigma[w] += sigma[v];  // Count shortest paths
                    pred[w][sigma[w] - 1] = v;  // Add v as predecessor of w
                }
                adj = adj->next;
            }
        }

        // Backpropagate dependencies
        while (q->front > 0) {  // Ensure the queue has elements before accessing it
            int w = q->items[--q->front];  // Backtracking in reverse BFS order

            // Validate that 'w' is within valid bounds
            if (w < 0 || w >= graph->numVertices) {
                printf("Invalid index w: %d\n", w);
                continue;  // Skip this iteration if the index is invalid
            }

            // Check if sigma[w] is zero, which would indicate no shortest paths
            if (sigma[w] == 0) {
                printf("No shortest paths found for w = %d\n", w);
                continue;  // Skip this iteration if there are no shortest paths
            }

            // Iterate over the predecessors
            for (int i = 0; i < sigma[w]; i++) {
                int v = pred[w][i];

                // Skip invalid predecessor values (-1)
                if (v == -1) {
                    continue;  // Skip uninitialized or invalid predecessors
                }

                // Validate that 'v' is within valid bounds
                if (v < 0 || v >= graph->numVertices) {
                    printf("Invalid index v: %d\n", v);
                    continue;  // Skip this iteration if the index is invalid
                }

                // Ensure sigma[w] is valid before performing the division
                if (sigma[w] > 0) {
                    delta[v] += (sigma[v] / (double)sigma[w]) * (1 + delta[w]);
                }
                else {
                    printf("Warning: Division by zero avoided at w = %d\n", w);
                }
            }

            if (w != s) {
                betweenness[w] += delta[w];
            }
        }

        // Clean up
        free(sigma);
        free(dist);
        free(delta);
        for (int i = 0; i < graph->numVertices; i++) {
            free(pred[i]);
        }
        free(pred);
        free(q->items);
        free(q);
    }

    // Normalize betweenness centrality for undirected graph
    for (int i = 0; i < graph->numVertices; i++) {
        betweenness[i] /= 2.0;
    }

    return betweenness;  // Return the betweenness array
}

// Greedy selection of critical nodes based on combined centrality measures
int* selectCriticalNodes(Graph* graph, int k) {
    int* degreeCentrality = calculateDegreeCentrality(graph);
    double* betweennessCentrality = calculateBetweennessCentrality(graph);
    double* combinedScore = malloc(graph->numVertices * sizeof(double));

    // Combine degree and betweenness centrality scores
    for (int i = 0; i < graph->numVertices; i++) {
        combinedScore[i] = degreeCentrality[i] + betweennessCentrality[i];
    }

    // Select the top-k nodes with the highest combined score
    int* selectedNodes = malloc(k * sizeof(int));
    int* used = calloc(graph->numVertices, sizeof(int));  // Track selected nodes

    for (int i = 0; i < k; i++) {
        int maxIndex = -1;
        double maxScore = -1;

        for (int j = 0; j < graph->numVertices; j++) {
            if (!used[j] && combinedScore[j] > maxScore) {
                maxScore = combinedScore[j];
                maxIndex = j;
            }
        }

        selectedNodes[i] = maxIndex;
        used[maxIndex] = 1;
    }

    free(degreeCentrality);
    free(betweennessCentrality);
    free(combinedScore);
    free(used);

    return selectedNodes;
}

// Simulate the spread of misinformation using the Independent Cascade Model (ICM)
int propagateMisinformation(Graph* graph, int* influenced, int numInfluenced, double probability) {
    int* status = calloc(graph->numVertices, sizeof(int));
    int totalInfluenced = numInfluenced;

    for (int i = 0; i < numInfluenced; i++) {
        status[influenced[i]] = 1;
    }

    for (int i = 0; i < numInfluenced; i++) {
        int currentNode = influenced[i];
        Node* neighbor = graph->adjLists[currentNode];

        while (neighbor) {
            int neighborNode = neighbor->vertex;

            if (status[neighborNode] == 0) {
                double randProb = (double)rand() / RAND_MAX;
                if (randProb < probability) {
                    status[neighborNode] = 1;
                    totalInfluenced++;
                }
            }
            neighbor = neighbor->next;
        }
    }

    free(status);
    return totalInfluenced;
}


void printGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* temp = graph->adjLists[i];
        printf("Vertex %d: ", i);
        while (temp) {
            printf("-> %d ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}