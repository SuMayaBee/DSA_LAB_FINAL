#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Structure to represent a graph node
struct Node {
    int value;
    struct Node* next;
};

// Structure to represent a graph
struct Graph {
    int V;
    struct Node** adj;
};

// Function to create a new graph node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with given vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->adj = (struct Node**)malloc(V * sizeof(struct Node*));
    for (int i = 0; i < V; i++)
        graph->adj[i] = NULL;
    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adj[src];
    graph->adj[src] = newNode;
}

// A recursive function used by topologicalSort
void topologicalSortUtil(int v, bool visited[], struct Graph* graph, struct Node* stack) {
    visited[v] = true;

    struct Node* i;
    for (i = graph->adj[v]; i != NULL; i = i->next)
        if (!visited[i->value])
            topologicalSortUtil(i->value, visited, graph, stack);

    struct Node* new_node = createNode(v);
    new_node->next = stack->next;
    stack->next = new_node;
}

// The function to do Topological Sort.
void topologicalSort(struct Graph* graph) {
    bool* visited = (bool*)malloc(graph->V * sizeof(bool));
    struct Node* stack = createNode(-1);

    for (int i = 0; i < graph->V; i++)
        visited[i] = false;

    for (int i = 0; i < graph->V; i++)
        if (visited[i] == false)
            topologicalSortUtil(i, visited, graph, stack);

    while (stack->next != NULL) {
        printf("%d ", stack->next->value);
        struct Node* temp = stack->next;
        stack->next = stack->next->next;
        free(temp);
    }

    free(stack);
    free(visited);
}

// Driver code
int main() {
    // Create a graph given in the above diagram
    struct Graph* graph = createGraph(6);
    addEdge(graph, 5, 2);
    addEdge(graph, 5, 0);
    addEdge(graph, 4, 0);
    addEdge(graph, 4, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 1);

    printf("Following is a Topological Sort of the given graph \n");

    // Function Call
    topologicalSort(graph);

    return 0;
}
