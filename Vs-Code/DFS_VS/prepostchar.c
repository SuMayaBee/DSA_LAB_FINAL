#include<stdio.h>
#include<string.h>

char abc[100][100];
int graph[100][100];
int vis[100];

int giveCharIndex(char abc1[]) {
    for(int i=0; i<100; i++) {
        if(strcmp(abc[i], abc1) == 0){
            return i;
        }
    }
    return -1;
}

void dfsPreorder(int a) {
    if(vis[a]) {
        return;
    }
    printf("%s ", abc[a]); // Print when first visiting a node
    vis[a] = 1;

    for(int i=0; i<100; i++) {
        if(graph[a][i]){
            dfsPreorder(i);
        }
    }
}

void dfsPostorder(int a) {
    if(vis[a]) {
        return;
    }
    vis[a] = 1;

    for(int i=0; i<100; i++) {
        if(graph[a][i]){
            dfsPostorder(i);
        }
    }
    printf("%s ", abc[a]); // Print after visiting all adjacent nodes
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

    for(int i = 0; i < 100; i++) {
        vis[i] = 0;
    }

    printf("Preorder DFS traversal:\n");
    dfsPreorder(j);
    printf("\n");

    for(int i = 0; i < 100; i++) {
        vis[i] = 0;
    }

    printf("Postorder DFS traversal:\n");
    dfsPostorder(j);
    printf("\n");

    return 0;
}
