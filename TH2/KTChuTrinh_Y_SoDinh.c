//Kiem tra chu trinh, in ra so dinh
#include <stdio.h>
#define MAX_N 100
typedef struct {
    int n, m;
    int A[MAX_N][MAX_N];
} Graph;

void init_graph(Graph *pG, int n) {
    pG->n = n;
    pG->m = 0;
    for (int u = 1 ; u <= n; u++)
        for (int v = 1 ; v <= n; v++)
            pG->A[u][v] = 0;
}

void add_edge(Graph *pG, int u, int v) {
    pG->A[u][v] += 1;
    //if (u != v)
    //    pG->A[v][u] += 1;
        
    if (pG->A[u][v] > 1)
        printf("da cung (%d, %d)\n", u, v);
    if (u == v)
        printf("khuyen %d\n", u);
    pG->m++;
}

int adjacent(Graph *pG, int u, int v) {
    return pG->A[u][v] > 0;
}

#define WHITE 0
#define GRAY  1
#define BLACK 2

int color[MAX_N];		//Luu tr?ng thái c?a các d?nh
int parent[MAX_N];		//Luu tr?ng thái c?a các d?nh
int has_circle;		//Ð? th? ch?a trình hay không
int start, end;

void DFS(Graph *pG, int u, int p) {								
	color[u] = GRAY;
	parent[u] = p;

	for (int v = 1; v <= pG->n; v++)
		if (adjacent(pG, u, v)) {
			if (color[v] == WHITE) 		//2a. N?u v chua duy?t
				DFS(pG, v, u);   		//g?i d? quy duy?t nó
			else if (color[v] == GRAY) { //2b. v dang duy?t
				has_circle = 1;   	//ch?a chu trình
				start = u;
				end = v;
			}
		}

	color[u] = BLACK;
}


int main() {
	Graph G;
	int n, m, u, v;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for (int e = 0; e < m; e++) {
	    scanf("%d%d", &u, &v);
	    add_edge(&G, u, v);
	}

	for (int u = 1; u <= G.n; u++)							
		color[u] = WHITE; 								
									
	has_circle = 0;										
					
	for (int u = 1; u <= G.n; u++)							
		if (color[u] == WHITE)	//u chua duy?t				
			DFS(&G, u, -1);		//g?i DFS(&G, u) d? duy?t t? u

    if (has_circle) {
        int A[100], i = 0;
        A[0] = start;
        int u = start;
        do {
            u = parent[u];
            i++;
            A[i] = u;
        } while (u != v);
        for (int j = i; j >= 0; j--)
            printf("%d ", A[j]);
        printf("%d\n", A[i]);
    } else
        printf("-1\n");
    return 0;
}


