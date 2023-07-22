#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 100

// Structure to represent a graph edge
struct GraphEdge {
    int src, dest, weight;
};

// Function to find the shortest distances from the source vertex using Bellman-Ford algorithm
void shortestDistances(struct GraphEdge edges[], int numVertices, int numEdges, int source) {
    int dist[MAX_VERTICES];
    int parent[MAX_VERTICES];

    // Step 1: Initialize distances from source to all other vertices as INFINITY
    for (int i = 0; i < numVertices; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }

    // Set distance of source vertex from itself to 0
    dist[source] = 0;

    // Step 2: Relax all edges numVertices - 1 times
    for (int i = 1; i <= numVertices - 1; i++) {
        for (int j = 0; j < numEdges; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;

            // Check for a shorter path to the destination vertex (v) through the source vertex (u)
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
        }
    }

    // Step 3: Check for negative-weight cycles
    for (int j = 0; j < numEdges; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int weight = edges[j].weight;

        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            // The graph contains a negative-weight cycle
            printf("The graph contains a negative-weight cycle.\n");
            return;
        }
    }

    // Step 4: Print shortest distances and their parents
    printf("Shortest distances from vertex %d to all other vertices:\n", source);
    for (int i = 0; i < numVertices; i++) {
        printf("Vertex %d: Distance = %d, Parent = %d\n", i, dist[i], parent[i]);
    }
}

int main() {
    int numVertices, numEdges;
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &numVertices);

    printf("Enter the number of edges in the graph: ");
    scanf("%d", &numEdges);

    struct GraphEdge edges[MAX_VERTICES];

    printf("Enter the edges and their weights (source destination weight):\n");
    for (int i = 0; i < numEdges; i++) {
        scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
    }

    int source;
    printf("Enter the source vertex: ");
    scanf("%d", &source);

    shortestDistances(edges, numVertices, numEdges, source);

return 0;
}