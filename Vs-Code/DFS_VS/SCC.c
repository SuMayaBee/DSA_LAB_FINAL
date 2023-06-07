#include<stdio.h>
#include<string.h>

char abc[100][100];
int graph[100][100];
int revGraph[100][100];
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
    printf("%s ", abc[a]);
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
    getchar(); 

    printf("Enter the nodes: ");
    for(int i=0; i<n; i++){
        gets(abc[i]);
    }

    printf("Enter the number of routes: ");
    scanf("%d", &m);
    getchar(); 

    
    for(int i=0; i<m; i++) {
        char f[100], t[100];
        printf("From: ");
        gets(f);
        int a = giveCharIndex(f);
        
        printf("To: ");
        gets(t);
        int b= giveCharIndex(t);

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

}

