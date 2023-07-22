#include <stdio.h>
#include <stdlib.h>

// Structure to represent a graph edge
struct GraphEdge {
    int src, dest, weight;
};

// Structure to represent a graph
struct Graph {
    int numVertices, numEdges;
    struct GraphEdge* edges;
};

// Function to create a graph
struct Graph createGraph(int numVertices, int numEdges) {
    struct Graph graph;
    graph.numVertices = numVertices;
    graph.numEdges = numEdges;
    graph.edges = (struct GraphEdge*)malloc(numEdges * sizeof(struct GraphEdge));
    return graph;
}

// Function to add an edge to a graph
void addEdge(struct Graph* graph, int src, int dest, int weight, int edgeIndex) {
    graph->edges[edgeIndex].src = src;
    graph->edges[edgeIndex].dest = dest;
    graph->edges[edgeIndex].weight = weight;
}

// Function to compare edges for sorting in ascending order based on weight
int compareEdges(const void* a, const void* b) {
    return ((struct GraphEdge*)a)->weight - ((struct GraphEdge*)b)->weight;
}

// Function to find the parent of a vertex (using union-find)
int findParent(int parent[], int vertex) {
    if (parent[vertex] == vertex)
        return vertex;
    return findParent(parent, parent[vertex]);
}

// Function to perform union of two subsets (using union-find)
void unionSubsets(int parent[], int x, int y) {
    int xRoot = findParent(parent, x);
    int yRoot = findParent(parent, y);
    parent[xRoot] = yRoot;
}

// Kruskal's algorithm to find the minimum cost to connect all cities
int kruskalMST(struct Graph* graph) {
    int numVertices = graph->numVertices;
    int numEdges = graph->numEdges;
    struct GraphEdge* edges = graph->edges;

    // Sort edges in ascending order based on weight
    qsort(edges, numEdges, sizeof(struct GraphEdge), compareEdges);

    int* parent = (int*)malloc(numVertices * sizeof(int));
    for (int i = 0; i < numVertices; i++)
        parent[i] = i;

    int mstCost = 0;
    int mstEdges = 0;
    int edgeIndex = 0;

    while (mstEdges < numVertices - 1) {
        int src = edges[edgeIndex].src;
        int dest = edges[edgeIndex].dest;
        int weight = edges[edgeIndex].weight;

        int srcParent = findParent(parent, src);
        int destParent = findParent(parent, dest);

        if (srcParent != destParent) {
            mstCost += weight;
            unionSubsets(parent, srcParent, destParent);
            mstEdges++;
        }

        edgeIndex++;
    }

    free(parent);

    return mstCost;
}

int main() {
    int numVertices, numEdges;

    printf("Enter the number of cities (vertices) in the map: ");
    scanf("%d", &numVertices);

    printf("Enter the number of roads (edges) in the map: ");
    scanf("%d", &numEdges);

    struct Graph graph = createGraph(numVertices, numEdges);

    printf("Enter the roads and their costs (source destination cost):\n");
    for (int i = 0; i < numEdges; i++) {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(&graph, src, dest, weight, i);
    }

    int minCost = kruskalMST(&graph);
    printf("Minimum cost to connect all cities in the map: %d\n", minCost);

    free(graph.edges);

    return 0;
}
