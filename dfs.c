#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // Add the necessary header for 'malloc'

#define MAX_VERTICES 100

// Structure to represent a graph node
struct GraphNode {
    int dest;
    struct GraphNode* next;
};

// Structure to represent a graph
struct Graph {
    int numVertices;
    struct GraphNode* adjLists[MAX_VERTICES];
};

// Function to create a graph node
struct GraphNode* createNode(int dest) {
    struct GraphNode* newNode = (struct GraphNode*)malloc(sizeof(struct GraphNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
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
void addEdge(struct Graph* graph, int src, int dest) {
    struct GraphNode* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

// Helper function for DFS to detect cycles
bool hasCycleUtil(struct Graph* graph, int vertex, bool visited[], bool stack[]) {
    if (!visited[vertex]) {
        visited[vertex] = true;
        stack[vertex] = true;

        struct GraphNode* adjacentNode = graph->adjLists[vertex];
        while (adjacentNode != NULL) {
            int adjVertex = adjacentNode->dest;
            if (!visited[adjVertex] && hasCycleUtil(graph, adjVertex, visited, stack))
                return true;
            else if (stack[adjVertex])
                return true;

            adjacentNode = adjacentNode->next;
        }
    }

    stack[vertex] = false;
    return false;
}

// Function to detect cycles in a directed graph using DFS
bool hasCycle(struct Graph* graph) {
    int numVertices = graph->numVertices;
    bool visited[MAX_VERTICES] = { false };
    bool stack[MAX_VERTICES] = { false };

    for (int i = 0; i < numVertices; ++i) {
        if (hasCycleUtil(graph, i, visited, stack))
            return true;
    }

    return false;
}

// Function to free the memory used by the graph
void freeGraph(struct Graph* graph) {
    for (int i = 0; i < graph->numVertices; ++i) {
        struct GraphNode* current = graph->adjLists[i];
        while (current != NULL) {
            struct GraphNode* next = current->next;
            free(current);
            current = next;
        }
    }
}

int main() {
    int numVertices, numEdges;
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &numVertices);

    printf("Enter the number of edges in the graph: ");
    scanf("%d", &numEdges);

    struct Graph graph = createGraph(numVertices);

    printf("Enter the edges (source destination) of the graph:\n");
    for (int i = 0; i < numEdges; ++i) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(&graph, src, dest);
    }

    if (hasCycle(&graph))
        printf("The directed graph contains a cycle.\n");
    else
        printf("The directed graph does not contain a cycle.\n");

    // Free the memory used by the graph
    freeGraph(&graph);

    return 0;
}
