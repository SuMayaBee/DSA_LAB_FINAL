#include<stdio.h>
#include<string.h>

int abc[100];
int graph[100][100];
int vis[100];

int giveCharIndex(int abc1) {
    for(int i=0; i<100; i++) {
        if(abc[i] == abc1){
            return i;
        }
    }
    return -1;
}

void dfsPreorder(int a) {
    if(vis[a]) {
        return;
    }
    printf("%d ", abc[a]); // Print when first visiting a node
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
    printf("%d ", abc[a]); // Print after visiting all adjacent nodes
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

        graph[a][b] = graph[b][a] = 1;
    }

    int h;
    printf("Enter your node:");
    scanf("%d", &h);
    int j= giveCharIndex(h);

    for(int i = 0; i < 100; i++) {
             vis[i] = 0;
         }

    printf("Preorder DFS traversal:\n");
   // memset(vis, 0, sizeof(vis)); // Reset visited array
    dfsPreorder(j);
    printf("\n");

    for(int i = 0; i < 100; i++) {
              vis[i] = 0;
           }


    printf("Postorder DFS traversal:\n");
   // memset(vis, 0, sizeof(vis)); // Reset visited array
    dfsPostorder(j);
    printf("\n");

    return 0;
}

/*
20
100
19
2
15
98
80
71
*/

/*
100 20
100 2
2 80
2 15
15 98
98 71
80 71
20 19
*/