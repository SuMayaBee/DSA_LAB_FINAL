#include<stdio.h>
#include<malloc.h>

int graph[20][20] = {0};
int q[20]={0}, f=-1, r=-1;

void enqueue(int n) {
    if(r==19) {
        printf("Overflow");
    }
    if(f==-1) {
        f=0;
    }
    r++;
    q[r]=n;
}

int dequeue() {
    if(f>r || r==-1) {
        printf("Underflow");
        return -1;
    }
    return q[f++];
    
}

void create(int x, int y) {
    graph[x][y]=1;
    graph[y][x]=1;
}

void print(int v) {
    for(int i=0; i<v; i++) {
        printf("Adjacent of %d is ", i);
        for(int j=0; j<v; j++) {
            if(graph[i][j]) {
            printf("%d ", j);
            }
        } printf("\n");

    }
}

void bfs(int start, int v) {
    int visited[v];
    int path[v];
    for(int i = 0; i < v; i++) {
        visited[i] = 0;
        path[i] = 0;
    }
    enqueue(start);
    visited[start] = 1;

    while(f<=r) {
        int temp = dequeue();
        printf("%d ", temp);
        for(int i=0; i<v; i++) {
            if(graph[temp][i] && !visited[i]) {
                visited[i] =1;
                enqueue(i);
                path[i] = path[temp] +1;
            }
        }
    }

    printf("\n");

    for(int i=0; i<v; i++) {
        printf("Distance from %d to %d is %d\n", start, i, path[i]);
    }
}

int main() {
    int v, e, x, y, start;
    printf("Enter the number of vertices: ");
    scanf("%d", &v);
    printf("Enter the number of edges: ");
    scanf("%d", &e);

    printf("Print the edges of the graph:\n");
    for(int i=0; i<e; i++) {
           scanf("%d %d", &x, &y);
           create(x, y);
    }

    printf("Enter starting vertex:");
    scanf("%d", &start);

    bfs(start, v);
    printf("\n");
    print(v);

    return 0;

}