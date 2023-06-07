#include <stdio.h>

#define MAX_VERTICES 20

int visited[MAX_VERTICES] = {0};
int Adj[MAX_VERTICES][MAX_VERTICES] = {0};
int paths = 0;
int path[MAX_VERTICES];

void printPath(int path[], int pathLen) {
    for (int i = 0; i < pathLen; i++) {
        printf("%d", path[i]);
        if (i < pathLen - 1) {
            printf(" -> ");
        }
    }
    printf("\n");
}

void pathCalc(int u, int dest, int numV, int pathLen)
{
    visited[u] = 1;
    path[pathLen] = u;
    pathLen++;

    if (u == dest) {
        paths++;
        printPath(path, pathLen);
    } else {
        for (int v = 0; v < numV; v++) {
            if (Adj[u][v] && !visited[v]) {
                pathCalc(v, dest, numV, pathLen);
            }
        }
    }

    pathLen--;
    visited[u] = 0;
}

int main()
{
    int numVertices, numEdges, source, dest;

    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    printf("Enter the edges (vertex1 vertex2):\n");
    for (int i = 0; i < numEdges; i++) {
        int vertex1, vertex2;
        scanf("%d %d", &vertex1, &vertex2);
        Adj[vertex1][vertex2] = 1;
    }

    printf("Enter source: ");
    scanf("%d", &source);

    printf("Enter destination: ");
    scanf("%d", &dest);

    pathCalc(source, dest, numVertices, 0);

    printf("Total paths: %d\n", paths);
    return 0;
}
