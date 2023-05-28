#include<stdio.h>
#include<string.h>

#define n 100
int color[n]; // 0 for WHITE, 1 for GREY, 2 for BLACK
int time;
int prev[n];
int d[n];
int f[n];
int graph[n][n], graph2[n][n];
int stack[n];
int top = -1;

int is_empty() {
    if(top == -1) {
        return 1; 
    } else {
        return 0; 
    }
}


void push(int v) {
    stack[++top] = v;
}

int pop() {
    if(top == -1) {
        printf("Underflow");
        return -1; 
    } else {
        return stack[top--]; 
    }
}

void dfs_visit(int u, int nv) {
    color[u] = 1;
    for (int v = 0; v < nv; v++) {
        if (graph[u][v] && !color[v]) {
            prev[v] = u;
            dfs_visit(v, nv);
        }
    }
    color[u] = 2;
    push(u);
}


void dfs_visit2(int u, int nv) {
    color[u]= 1;
    printf("%d ", u);  
    for(int i=0; i<nv; i++) {
        if(graph2[u][i] && !color[i]) {
            dfs_visit2(i, nv);
        }
    }  
    color[u] = 2;
}


void dfs(int nv) {
    for(int i=0; i<nv; i++) {
        color[i] = 0;
        prev[i] = -1;
        f[i] = d[i] = -1;
    }
    time =0;
    for(int i=0; i<nv; i++) {
        if(!color[i]) {
            dfs_visit(i, nv);
        }
    }
}

void transpose(int nv) {
    for(int i=0; i<nv; i++) {
        for(int j=0; j<nv; j++) {
            graph2[j][i] = graph[i][j];
        }
    }
}

void findSCC(int nv) {
    dfs(nv);
    transpose(nv);
    for(int i=0; i<nv; i++) {
        color[i]= 0;
    }

    while(!is_empty()) {
        int temp = pop();
        if(!color[temp]) {
            dfs_visit2(temp, nv);
            printf("\n");
        }
    }


}



int main() {
    int nv, ne;

    printf("Enter the number of verteces: ");
    scanf("%d", &nv);
    printf("Enter the number of edges: ");
    scanf("%d", &ne);

    for(int i=0; i<ne; i++) {
        int v1, v2;
        scanf("%d %d", &v1, &v2);
        graph[v1][v2]=1;

    }
  
    printf("Show the connected components:\n");
    findSCC(nv);

    
   
   return 0;

}

/*
7 0
0 2
0 1
1 7
7 2
7 3
2 1
3 2
4 2
6 2
3 4
5 4
5 3
5 6
*/