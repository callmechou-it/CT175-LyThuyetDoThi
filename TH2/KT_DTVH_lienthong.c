//Kiem tra do thi vo huong lien thong
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

void DFS(Graph *pG, int u) {
	mark[u] = 1; 			//Ðánh d?u nó dã duy?t
	//2. Xét các d?nh k? c?a u
	for (int v = 1; v <= pG->n; v++)
		if (adjacent(pG, u, v) && mark[v] == 0) //N?u v chua duy?t
			DFS(pG, v); 			    //g?i d? quy duy?t nó	

}
// Ki?m tra pG có liên thông không
int connected(Graph *pG) {
	for (int u = 1; u <= pG->n; u++)//1. Kh?i t?o t?t c? d?nh d?u chua duy?t
		mark[u] = 0;
	//2. Duy?t d? th? t? d?nh b?t k?, ví d?: 1
	DFS(pG, 1);
	//3. Ki?m tra xem có d?nh nào chua duy?t không
	for (int u = 1; u <= pG->n; u++)
		if (mark[u] == 0)	//V?n còn d?nh chua duy?t
			return 0; 	//Ð? th? không liên thông, thoát luôn
	return 1;			//T?t c? các d?nh d?u dã duy?t => liên thông
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
	for (int u = 1; u <= G.n; u++) {
		mark[u] = 0;
	}
    if (connected(&G))
        printf("CONNECTED\n");
    else  printf("DISCONNECTED\n");
    return 0;
}


