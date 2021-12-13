//In ra so dinh cua BPLT nhieu dinh nhat
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
    if (u != v)
        pG->A[v][u] += 1;
    
    pG->m++;
}

int adjacent(Graph *pG, int u, int v) {
    return pG->A[u][v] > 0;
}
int mark[MAX_N];
int nb_u;

void DFS(Graph *pG, int u) {
	mark[u] = 1; 			//Ðánh d?u nó dã duy?t
	nb_u++;

	for (int v = 1; v <= pG->n; v++)
		if (adjacent(pG, u, v) && mark[v] == 0) //N?u v chua duy?t
			DFS(pG, v); 			    //g?i d? quy duy?t nó	
}

int main() {
	Graph G;
	int n, m, u, v, s;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for (int e = 0; e < m; e++) {
	    scanf("%d%d", &u, &v);
	    add_edge(&G, u, v);
	}

    scanf("%d", &s);

	for (int u = 1; u <= G.n; u++) {
		mark[u] = 0;
	}

	int max_cnt = 0;
	for (int u = 1; u <= G.n; u++)
        if (mark[u] == 0) {
        	nb_u = 0;
            DFS(&G, u);
            if (nb_u > max_cnt)
                max_cnt = nb_u;
        }
	printf("%d\n", max_cnt);
    return 0;
}


