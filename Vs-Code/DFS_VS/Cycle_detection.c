#include<stdio.h>
#include<string.h>

int abc[100];
int graph[100][100];
int vis[100];
int parent[100];
int cycleStart, cycleEnd;

int giveCharIndex(int abc1) {
    for(int i=0; i<100; i++) {
        if(abc[i] == abc1){
            return i;
        }
    }  
    return -1;
}

int detectCycle(int a, int p) {
    vis[a] = 1;
    parent[a] = p;
    for(int i = 0; i < 100; i++) {
        if(graph[a][i]) {
            if(vis[i] && i != p) {
                cycleStart = i;
                cycleEnd = a;
                return 1;
            }
            if(!vis[i] && detectCycle(i, a)) {
                return 1;
            }
        }
    }
    return 0;
}

void printCycle() {
    printf("Cycle: ");
    for (int v = cycleEnd; v != cycleStart; v = parent[v]) {
        printf("%d ", abc[v]);
    }
    printf("%d ", abc[cycleStart]);
    printf("\n");
}

void dfs(int a) {
    if(vis[a]) {
        return;
    } 
    vis[a] = 1;
    for(int i=0; i<100; i++) {
        if(graph[a][i] && i != parent[a]){
            dfs(i);
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

    int f[100], t[100];
    for(int i=0; i<m; i++) {
        printf("Connections: ");
        scanf("%d %d", &f[i], &t[i]);
        int a=giveCharIndex(f[i]);
        int b=giveCharIndex(t[i]);
        graph[a][b] = graph[b][a] = 1;
    }

    int h;
    printf("Enter your node:");
    scanf("%d", &h);
    int j= giveCharIndex(h);

    // Initialize the parent array
    for(int i = 0; i < n; i++) {
        parent[i] = -1;
    }

    if(detectCycle(j, -1)) {
        printf("A cycle is detected in the graph.\n");
        printCycle();
    } else {
        printf("No cycle is detected in the graph.\n");
    }

    dfs(j);

    printf("You can go to:\n");
    for(int i=0; i<n; i++) {
        if(vis[i] && i!=j){
            printf("%d\n", abc[i]);
        }
    }

    return 0;
}
