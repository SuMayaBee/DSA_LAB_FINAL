#include <stdio.h>
#include <string.h>
#define MAX 20

int graph[MAX][MAX] = {0};
int in[MAX] = {0};
int out[MAX] = {0};
char countries[MAX][100];

void create(int x, int y){
    graph[x][y] = 1;
}

int giveCharIndex(char* val, int numNodes) {
    for(int i = 0; i < numNodes; i++) {
        if(strcmp(countries[i], val) == 0) {
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
    int v, e;
    char f[100], t[100];

    printf("Enter the number of Nodes: ");
    scanf("%d", &v);
    getchar(); // to consume newline character after scanf

    printf("Enter the nodes: ");
    for(int i = 0; i < v; i++){
        gets(countries[i]);
    }

    printf("Enter the number of edges: ");
    scanf("%d", &e);
    getchar(); // to consume newline character after scanf

    for(int i = 0; i < e; i++){
        printf("From: ");
        gets(f);
        
        printf("To: ");
        gets(t);

        int a = giveCharIndex(f, v);
        int b = giveCharIndex(t, v);

        if(a != -1 && b != -1){
            create(a, b);
        }
    }
    calculateDegree(v);
    printf("vertex\t\tIn\t\tOut\n");
    for(int i = 0; i < v; i++){
        printf("%s\t\t%d\t\t%d\n", countries[i], in[i], out[i]);
    }
    return 0;
}
