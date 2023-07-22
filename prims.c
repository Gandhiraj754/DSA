#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 100

// Function to find the vertex with the minimum key value
int findMinKey(int key[], bool mstSet[], int numVertices) {
    int minKey = INT_MAX;
    int minIndex;

    for (int v = 0; v < numVertices; v++) {
        if (!mstSet[v] && key[v] < minKey) {
            minKey = key[v];
            minIndex = v;
        }
    }

    return minIndex;
}

// Function to print the MST
void printMST(int parent[], int graph[MAX_VERTICES][MAX_VERTICES], int numVertices) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < numVertices; i++) {
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
    }
}

// Function to implement Prim's algorithm for finding the MST
void primMST(int graph[MAX_VERTICES][MAX_VERTICES], int numVertices) {
    int parent[MAX_VERTICES];
    int key[MAX_VERTICES];
    bool mstSet[MAX_VERTICES];

    // Initialize all keys to INFINITY, mstSet to false, and parent to -1
    for (int i = 0; i < numVertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
        parent[i] = -1;
    }

    // Start with the first vertex
    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < numVertices - 1; count++) {
        int u = findMinKey(key, mstSet, numVertices);
        mstSet[u] = true;

        for (int v = 0; v < numVertices; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph, numVertices);
}

int main() {
    int numVertices;
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &numVertices);

    int graph[MAX_VERTICES][MAX_VERTICES];

    printf("Enter the adjacency matrix for the graph:\n");
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    primMST(graph, numVertices);

    return 0;
}
