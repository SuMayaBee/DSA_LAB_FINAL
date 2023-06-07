#include<stdio.h>
#include<string.h>

int abc[100];
int graph[100][100];
int vis[100];
int discovery[100];
int finish[100];
int time = 0;

int giveCharIndex(int abc1) {
    for(int i=0; i<100; i++) {
        if(abc[i] == abc1){
            return i;
        }
    }
    return -1;
}

void dfs(int a) {
    if(vis[a]) {
        return;
    }
    vis[a] = 1;
    discovery[a] = ++time; 

    for(int i=0; i<100; i++) {
        if(graph[a][i]){
            dfs(i);
        }
    }
    finish[a] = ++time; 
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

        graph[a][b] = 1;
    }

    int h;
    printf("Enter your node:");
    scanf("%d", &h);
    int j= giveCharIndex(h);
    dfs(j);

    printf("\n");
    for(int i=0; i<n; i++) {
        if(vis[i] ){
            printf("%d (Discovery time: %d, Finish time: %d)\n", abc[i], discovery[i], finish[i]);
        }
    }

    return 0;
}
