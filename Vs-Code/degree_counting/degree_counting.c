#include <stdio.h>
#define MAX 20

int graph[MAX][MAX] = {0};
int in[MAX] = {0};
int out[MAX] = {0};
int nodes[MAX];

void create(int x, int y){
    graph[x][y] = 1;
}

int getIndex(int val, int numNodes) {
    for(int i = 0; i < numNodes; i++) {
        if(nodes[i] == val) {
            return i;
        }
    }
    return -1;
}

void calculateDegree(int v){
    for(int i = 0; i < v; i++){
        for(int j = 0; j < v; j++){
            if(graph[i][j]){
                out[i]++;
                in[j]++;
            }
        }
    }
}

int main() {
    int v, e, x, y;
    printf("Enter the number of Nodes: ");
    scanf("%d", &v);

    printf("Enter the nodes: ");
    for(int i = 0; i < v; i++){
        scanf("%d", &nodes[i]);
    }

    printf("Enter the number of edges: ");
    scanf("%d", &e);

    for(int i = 0; i < e; i++){
        printf("From: ");
        scanf("%d", &x);

        printf("To: ");
        scanf("%d", &y);

        int a = getIndex(x, v);
        int b = getIndex(y, v);

        if(a != -1 && b != -1){
            create(a, b);
        }
    }
    calculateDegree(v);
    printf("vertex\t\tIn\t\tOut\n");
    for(int i = 0; i < v; i++){
        printf("%d\t\t%d\t\t%d\n", nodes[i], in[i], out[i]);
    }
    return 0;
}
