#include <stdio.h>
#define MAX 20

int graph[MAX][MAX] = {0};
int deg[MAX] = {0};

void create(int x, int y){
    graph[x][y] = 1;
    graph[y][x] = 1;
}

void calculateDegree(int v){
    for(int i=0; i<v; i++)
    {
        for(int j=0; j<v; j++)
        {
            if(graph[i][j])
            {
                deg[i]++;
                deg[j]++;
            }
        }
    }
}

int hasEulerPath(int v){
    int odd=0;
    calculateDegree(v);
    for(int i=0; i<v; i++)
    {
        if(deg[i] % 2)
        odd++;
    }
    return (odd==0 || odd==2);
}

int main() {
    int v, e, x, y;
    printf("Enter the number of vertices and edges: ");
    scanf("%d %d", &v, &e);
    
    printf("Enter the edges (x y):\n");
    for(int i=0; i<e; i++)
    {
        scanf("%d %d", &x, &y);
        create(x, y);
    }
    
    if(hasEulerPath(v))
        printf("Graph has an Euler path or circuit\n");
    else
        printf("Graph does not have an Euler path or circuit\n");

    return 0;
}
