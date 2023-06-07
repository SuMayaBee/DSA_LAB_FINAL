#include<stdio.h>
#include<string.h>

char abc[100][100];
int graph[100][100];
int vis[100];
int parent[100];
int cycleStart, cycleEnd;

int giveCharIndex(char abc1[]) {
    for(int i=0; i<100; i++) {
        if(strcmp(abc[i], abc1) == 0){
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
        printf("%s ", abc[v]);
    }
    printf("%s\n", abc[cycleStart]);
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
        graph[a][b] = 1;
    }

    char h[100];
    printf("Enter your node:");
    gets(h);
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
            printf("%s\n", abc[i]);
        }
    }

    return 0;
}
