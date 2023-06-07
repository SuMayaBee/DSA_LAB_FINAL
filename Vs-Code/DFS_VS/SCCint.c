#include<stdio.h>
#include<string.h>

int abc[100];
int graph[100][100];
int revGraph[100][100];
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

void dfs1(int a) {
    vis[a] = 1;

    for(int i=0; i<100; i++) {
        if(graph[a][i] && !vis[i]){
            dfs1(i);
        }
    }
    stack[++top] = a;
}

void dfs2(int a) {
    printf("%d ", abc[a]);
    vis[a] = 1;

    for(int i=0; i<100; i++) {
        if(revGraph[a][i] && !vis[i]){
            dfs2(i);
        }
    }
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

    for(int i=0; i<m; i++) {
        int f, t;
        printf("From: ");
        scanf("%d", &f);
        int a = giveCharIndex(f);
        
        printf("To: ");
        scanf("%d", &t);
        int b = giveCharIndex(t);

        graph[a][b] = 1;
        revGraph[b][a] = 1; 
    }

    for(int i=0; i<100; i++) {
        vis[i] = 0;
    }

    for(int i=0; i<n; i++) {
        if(!vis[i]) {
            dfs1(i);
        }
    }

    for(int i=0; i<100; i++) {
        vis[i] = 0;
    }

    printf("Strongly Connected Components:\n");
    while(top >= 0) {
        int j = stack[top--];
        if(!vis[j]) {
            dfs2(j);
            printf("\n");
        }
    }

    return 0;
}
