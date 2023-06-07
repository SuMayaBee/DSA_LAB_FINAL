#include<stdio.h>
#include<string.h>

char abc[100][100];
int graph[100][100];
int vis[100];
int discovery[100];
int finish[100];
int time = 0;

int giveCharIndex(char abc1[]) {
    for(int i=0; i<100; i++) {
        if(strcmp(abc[i], abc1) == 0){
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
    dfs(j);

    printf("\n");
    for(int i=0; i<n; i++) {
        if(vis[i]){
            printf("%s (Discovery time: %d, Finish time: %d)\n", abc[i], discovery[i], finish[i]);
        }
    }

    return 0;
}
