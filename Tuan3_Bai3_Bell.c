#include<stdio.h>
//Graph mà ds cung_Buoi1_Bieudiendothi 
typedef struct {
	int u, v, w;
}Edge;

typedef struct {
	Edge edges[100];
	int n, m; 
}Graph;


void init_graph(Graph *pG, int n, int m) {
	pG->n=n;
	pG->m=0;
}

void add_edge(Graph *pG, int x, int y, int w) {
	pG->edges[pG->m].u=x;
	pG->edges[pG->m].v=y;
	pG->edges[pG->m].w=w;	
	pG->m++;
}

 void print_graph(Graph *pG) {
 	int i, j;
 	for(i=0; i<pG->m; i++) {
 		printf("%d %d %d",pG->edges[i].u, pG->edges[i].v, pG->edges[i].w);
 		printf("\n");
 	}
 }

int pi[100];
int p[100];
void BMF(Graph *pG, int s) {
	int i, j, it;
	
	for(i=1; i<=pG->n; i++)
		pi[i]=9999;
	pi[s]=0;
	p[s]=-1;
	for(it=1; it<pG->n; it++) {
		for(j=0; j<=pG->m-1; j++) {
			int u=pG->edges[j].u;
			int v=pG->edges[j].v;
			int w=pG->edges[j].w;
			if(pi[u]+w < pi[v]) {
				pi[v]=pi[u]+w;
				p[v]=u;
			}
		}
	}
}

int main() {
	freopen("tuan3.txt", "r", stdin);
	int i, m, n, u, v, w, s;
	Graph G;	
	scanf("%d%d", &n, &m);
	init_graph(&G, n, m);
	for(i=1; i<=m; i++) {
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}
	scanf("%d", &s);
	print_graph(&G);
	BMF(&G, s);
	for(i=1; i<=n; i++) 
		printf("%d \n", pi[i]);
	return 0;
}

