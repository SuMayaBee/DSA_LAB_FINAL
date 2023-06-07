#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int abc[100];
int graph[100][100];
int vis[100];
int stack[100], top = -1;

int giveCharIndex(int abc1) {
    for(int i=0; i<100; i++) {
        if(abc[i] == abc1){
            return i;
        }
    }
    return -1;
}

void dfsTopological(int a) {
    if(vis[a]) {
        return;
    }
    vis[a] = 1;

    for(int i=0; i<100; i++) {
        if(graph[a][i]){
            dfsTopological(i);
        }
    }
    stack[++top] = a; // Push the node into the stack after all its adjacent nodes are visited.
}

int main() {
    int n, m;
    printf("Enter the number of Nodes: ");
    scanf("%d", &n);

    printf("Enter the nodes: ");
    for(int i=0; i<n; i++){
        scanf("%d", &abc[i]);
    }

    printf("Enter the number of routes: ");
    scanf("%d", &m);

    int f[100], t[100];
    for(int i=0; i<m; i++) {
        scanf("%d %d", &f[i], &t[i]);
        int a=giveCharIndex(f[i]);
        int b=giveCharIndex(t[i]);

        graph[a][b] = 1; // Only one direction for directed acyclic graph
    }

    printf("Topological Sort: ");
    for(int i=0; i<n; i++) {
        if(!vis[i]) {
            dfsTopological(i);
        }
    }
    while(top >= 0) { // Print stack in reverse order
        printf("%d ", abc[stack[top--]]);
    }
    printf("\n");

    return 0;
}
