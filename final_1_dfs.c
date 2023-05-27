#include<stdio.h>
#include<string.h>

char desherNam[100][100];
int graph[100][100];

int desherIndexDao(char num[] ) {
    for(int i=0; i<100; i++)  {
        if(strcmp(desherNam[i], num)==0) {
            return i;
        } 
    }  return -1;
}

int vis[100];
void dfs(int u) {
    if(vis[u]) {
        return;
    }
    vis[u] = 1;
    for(int v=0; v<100; v++) {
        if(graph[u][v]) {
            dfs(v);
        }
    }
} 



int main() {
    printf("Number of country: ");
    int n;
    scanf("%d", &n);
    getchar();

    for(int i=0; i<n; i++) {
        gets(desherNam[i]);
    }

    printf("Number of routes: ");
    int m;
    scanf("%d", &m);
    getchar();

    for(int i=0; i<m; i++) {
        char from[100], to[100];
        
        printf("From: ");
        gets(from);
        int f = desherIndexDao(from);
        
        printf("To: ");
        gets(to);
        int t= desherIndexDao(to);

        graph[f][t] = graph[t][f] = 1;
    }

    char home[100];
    printf("Starting from: ");
    gets(home);
    int h = desherIndexDao(home);

    dfs(h);
    
    printf("You can go to:\n ");
    for(int i=0; i<n; i++) {
        if(vis[i]) {
            printf("%s\n", desherNam[i]);
        }
    }


    return 0;
}