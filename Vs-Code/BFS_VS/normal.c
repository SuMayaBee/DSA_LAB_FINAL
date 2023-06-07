#include<stdio.h>


int abc[100];
int graph[100][100];
int queue[100];
int front=0, back=-1;

int giveCharIndex(int abc1) {
    for(int i=0; i<100; i++) {
        if(abc[i] == abc1){
            return i;

        }
    }  return -1;
}

void push(int a) {
    back++;
    queue[back] = a;
}

int pop() {
    return queue[front++];
}

int vis[100];
int dis[100];

void bfs(int a){
    dis[a] =0;
    push(a);

    while(front<=back){
        int b=pop();
        if(vis[b]){
            continue;
        } vis[b]=1;
        for(int i=0; i<100; i++) {
            if(!vis[i] && graph[b][i]){
                dis[i] = dis[b] +1;
                push(i);
            }
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

        graph[a][b] = graph[b][a]= 1;

    }

    int h;
    printf("Enter your node:");
    scanf("%d", &h);
    int j= giveCharIndex(h);
    bfs(j);
    printf("You can go to:\n");
    for(int i=0; i<n; i++) {
        if(vis[i] && i!=j){
            printf("%d %d\n", abc[i], dis[i]);
        }
    }

    return 0;


}