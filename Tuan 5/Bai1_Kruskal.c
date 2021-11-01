#include<stdio.h>
//Do thi danh sach cung
typedef struct {
	int x, y, z;
}Edge;
typedef struct {
	int n, m;
	Edge edges[100];
}Graph;
void init_graph(Graph *pG, int n) {
	pG->n=n;
	pG->m=0;
}
void add_edge(Graph *pG, int x, int y, int w) {
	pG->edges[pG->m].x=x;
	pG->edges[pG->m].y=y;
	pG->edges[pG->m].z=w;
	pG->m++;
}
int parent[100];
int findRoot(int u) {
	if(parent[u]==u) 
		return u;
	return findRoot(parent[u]);
}
int kruskal(Graph *pG, Graph *pT) {
	int i, j, e, u;
	Edge temp;
	for(i=0; i<pG->m; i++) 
		for(j=i+1; j<pG->m; j++) 
			if(pG->edges[i].z > pG->edges[j].z) {
				temp = pG->edges[i];
				pG->edges[i]=pG->edges[j];
				pG->edges[j]=temp;
			}
	init_graph(pT, pG->n);
	for(u=1; u<=pG->n; u++)
		parent[u]=u;
	int sum_w=0;
	for(e=0; e<pG->m; e++) {
		int u=pG->edges[e].x;
		int v=pG->edges[e].y;
		int w=pG->edges[e].z;
		int r_u=findRoot(u);
		int r_v=findRoot(v);
		if(r_u!=r_v) {
			if(u<v)
				add_edge(pT, u, v, w);
			else add_edge(pT, v, u, w);
			parent[r_v]=r_u;
			sum_w+=w;
		}
	}
	return sum_w;
}

int main() {
	freopen("dt.txt", "r", stdin);
	int m, n, u, v, w, e;
	Graph G, T;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for(e=0; e<m; e++) {
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);	
	}
	int sum_w=kruskal(&G, &T);
	printf("%d\n", sum_w);
	for(e=0; e<T.m; e++)
		printf("%d %d %d\n", T.edges[e].x, T.edges[e].y, T.edges[e].z); 
}

