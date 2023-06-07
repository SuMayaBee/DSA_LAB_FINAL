#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char abc[100][100];
int graph[100][100];
int vis[100];
int stack[100], top = -1;

int giveCharIndex(char abc1[]) {
    for(int i=0; i<100; i++) {
        if(strcmp(abc[i], abc1) == 0){
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
    getchar(); // to consume newline character after scanf

    printf("Enter the nodes: ");
    for(int i=0; i<n; i++){
        gets(abc[i]);
    }

    printf("Enter the number of routes: ");
    scanf("%d", &m);
    getchar(); // to consume newline character after scanf

    for(int i=0; i<m; i++) {
        char f[100], t[100];
        printf("From: ");
        gets(f);
        int a=giveCharIndex(f);
        
        printf("To: ");
        gets(t);
        int b=giveCharIndex(t);
        graph[a][b] = 1; // Only one direction for directed acyclic graph
    }

    printf("Topological Sort: ");
    for(int i=0; i<n; i++) {
        if(!vis[i]) {
            dfsTopological(i);
        }
    }
    while(top >= 0) { // Print stack in reverse order
        printf("%s ", abc[stack[top--]]);
    }
    printf("\n");

    return 0;
}
