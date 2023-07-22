#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Structure to represent a graph edge
struct GraphEdge {
    int dest, weight;
    struct GraphEdge* next;
};

// Structure to represent a graph
struct Graph {
    int numVertices;
    struct GraphEdge* adjLists[MAX_VERTICES];
};

// Function to create a graph edge
struct GraphEdge* createEdge(int dest, int weight) {
    struct GraphEdge* newEdge = (struct GraphEdge*)malloc(sizeof(struct GraphEdge));
    newEdge->dest = dest;
    newEdge->weight = weight;
    newEdge->next = NULL;
    return newEdge;
}

// Function to create a graph
struct Graph createGraph(int numVertices) {
    struct Graph graph;
    graph.numVertices = numVertices;
    for (int i = 0; i < numVertices; ++i) {
        graph.adjLists[i] = NULL;
    }
    return graph;
}

// Function to add an edge to a graph
void addEdge(struct Graph* graph, int src, int dest, int weight) {
    struct GraphEdge* newEdge = createEdge(dest, weight);
    newEdge->next = graph->adjLists[src];
    graph->adjLists[src] = newEdge;
}

// Function to find the index of the vertex with the minimum distance value
int findMinDistance(int dist[], bool visited[], int numVertices) {
    int minDist = INT_MAX;
    int minIndex;

    for (int v = 0; v < numVertices; v++) {
        if (!visited[v] && dist[v] <= minDist) {
            minDist = dist[v];
            minIndex = v;
        }
    }

    return minIndex;
}

// Function to print the shortest path from source to destination
void printShortestPath(int parent[], int source, int destination) {
    if (source == destination) {
        printf("%d ", source + 1);
        return;
    }
    printShortestPath(parent, source, parent[destination]);
    printf("%d ", destination + 1);
}

// Dijkstra's algorithm to find the shortest path from a given source vertex
void dijkstra(struct Graph* graph, int source, int destination) {
    int numVertices = graph->numVertices;
    int dist[MAX_VERTICES];
    bool visited[MAX_VERTICES];
    int parent[MAX_VERTICES];

    for (int i = 0; i < numVertices; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[source] = 0;

    for (int count = 0; count < numVertices - 1; count++) {
        int u = findMinDistance(dist, visited, numVertices);
        visited[u] = true;

        struct GraphEdge* adjList = graph->adjLists[u];
        while (adjList != NULL) {
            int v = adjList->dest;
            if (!visited[v] && dist[u] != INT_MAX && dist[u] + adjList->weight < dist[v]) {
                dist[v] = dist[u] + adjList->weight;
                parent[v] = u;
            }
            adjList = adjList->next;
        }
    }

    printf("Shortest distance from vertex %d to vertex %d: %d\n", source + 1, destination + 1, dist[destination]);

    printf("Shortest path from vertex %d to vertex %d: ", source + 1, destination + 1);
    printShortestPath(parent, source, destination);
    printf("\n");
}

int main() {
    int numVertices, numEdges, source, destination;
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &numVertices);

    printf("Enter the number of edges in the graph: ");
    scanf("%d", &numEdges);

    struct Graph graph = createGraph(numVertices);

    printf("Enter the source vertex: ");
    scanf("%d", &source);
    source--;

    printf("Enter the destination vertex: ");
    scanf("%d", &destination);
    destination--;

    printf("Enter the edges and their weights (source destination weight):\n");
    for (int i = 0; i < numEdges; i++) {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(&graph, src - 1, dest - 1, weight);
    }

    dijkstra(&graph, source, destination);

    return 0;
}
