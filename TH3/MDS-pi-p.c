#include <stdio.h>

#define MAXN 100
#define oo 999999
#define NO_EDGE -1


typedef struct {
    int n, m;
    int W[MAXN][MAXN];
} Graph;

void init_graph(Graph *pG, int n) {
    pG->n = n;
    pG->m = 0;
    for (int u = 1; u <= n; u++)
        for (int v = 1; v <= n; v++)
            pG->W[u][v] = NO_EDGE;
}

void add_edge(Graph *pG, int u, int v, int w) {
    pG->W[u][v] = w;
}

int mark[MAXN];
int pi[MAXN];
int p[MAXN];

void MooreDijkstra(Graph *pG, int s) {
	int u, v, it;
	for (u = 1; u <= pG->n; u++) {
		pi[u] = oo;
		mark[u] = 0;
	}

	pi[s] = 0; //chi?u d�i du?ng di ng?n nh?t t? s d?n ch�nh n� b?ng 0
	p[s] = -1; //tru?c d?nh s kh�ng c� d?nh n�o c?

	//L?p n-1 l?n
	for (it = 1; it < pG->n; it++) {
		//1. T�m u c� mark[u] == 0 v� c� pi[u] nh? nh?t
		int j, min_pi = oo;
		for (j = 1; j <= pG->n; j++)
			if (mark[j] == 0 && pi[j] < min_pi) {
				min_pi = pi[j];
				u = j;
			}
		//2. ��nh d?u u d� x�t
		mark[u] = 1;

		//3. C?p nh?t pi v� p c?a c�c d?nh k? c?a v (n?u tho?)
		for (v = 1; v <= pG->n; v++)
			if (pG->W[u][v] != NO_EDGE && mark[v] == 0)
				if (pi[u] + pG->W[u][v] < pi[v]) {
					pi[v] = pi[u] + pG->W[u][v];
					p[v] = u;
				}
	}
}


int main() {
    Graph G;
    int n, m;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    
    for (int e = 0; e < m; e++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }
    
    MooreDijkstra(&G, 1);
    for (int u = 1; u <= G.n; u++)
    	printf("pi[%d] = %d, p[%d] = %d\n", u, pi[u], u, p[u]);

    return 0;
}
