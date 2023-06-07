#include <stdio.h>
#include <string.h>

#define MAX_NODES 20

int visited[MAX_NODES] = {0};
int Adj[MAX_NODES][MAX_NODES] = {0};
int paths = 0;
int path[MAX_NODES];
char abc[MAX_NODES][100];

void printPath(int path[], int pathLen) {
    for (int i = 0; i < pathLen; i++) {
        printf("%s", abc[path[i]]);
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

int giveCharIndex(char* f) {
    for(int i = 0; i < MAX_NODES; i++) {
        if(strcmp(abc[i], f) == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
    int numNodes, numRoutes;

    printf("Enter the number of Nodes: ");
    scanf("%d", &numNodes);
    getchar();

    printf("Enter the nodes: ");
    for(int i=0; i<numNodes; i++){
        gets(abc[i]);

         
    }

    printf("Enter the number of routes: ");
    scanf("%d", &numRoutes);
    getchar();

    for(int i=0; i<numRoutes; i++) {
        char f[100], t[100];
        printf("From: ");
        gets(f);
        int a = giveCharIndex(f);

        printf("To: ");
        gets(t);
        int b = giveCharIndex(t);

          Adj[a][b] = 1; 

    }

    char source[100], dest[100];
    printf("Enter source: ");
    gets(source);
    int s = giveCharIndex(source);

    printf("Enter destination: ");
    gets(dest);
    int d = giveCharIndex(dest);

    pathCalc(s, d, numNodes, 0);

    printf("Total paths: %d\n", paths);
     
    return 0;
}
