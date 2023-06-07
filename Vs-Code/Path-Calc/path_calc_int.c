#include <stdio.h>

#define MAX_NODES 20

int visited[MAX_NODES] = {0};
int Adj[MAX_NODES][MAX_NODES] = {0};
int paths = 0;
int path[MAX_NODES];
int nodes[MAX_NODES];

void printPath(int path[], int pathLen) {
    for (int i = 0; i < pathLen; i++) {
        printf("%d", nodes[path[i]]);
        if (i < pathLen - 1) {
            printf(" -> ");
        }
    }
    printf("\n");
}

void pathCalc(int u, int dest, int numV, int pathLen) {
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

int getIndex(int val, int numNodes) {
    for(int i = 0; i < numNodes; i++) {
        if(nodes[i] == val) {
            return i;
        }
    }
    return -1;
}

int main() {
    int numNodes, numRoutes;

    printf("Enter the number of Nodes: ");
    scanf("%d", &numNodes);

    printf("Enter the nodes: ");
    for(int i = 0; i < numNodes; i++){
        scanf("%d", &nodes[i]);
    }

    printf("Enter the number of routes: ");
    scanf("%d", &numRoutes);

    for(int i = 0; i < numRoutes; i++) {
        int from, to;
        printf("From: ");
        scanf("%d", &from);
        
        printf("To: ");
        scanf("%d", &to);

        int a = getIndex(from, numNodes);
        int b = getIndex(to, numNodes);

        if(a != -1 && b != -1){
            Adj[a][b] = 1;
        }
    }

    int source, dest;
    printf("Enter source: ");
    scanf("%d", &source);
    int s = getIndex(source, numNodes);

    printf("Enter destination: ");
    scanf("%d", &dest);
    int d = getIndex(dest, numNodes);

    if(s != -1 && d != -1){
        pathCalc(s, d, numNodes, 0);
    }

    printf("Total paths: %d\n", paths);
    return 0;
}
