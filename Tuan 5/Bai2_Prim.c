#include<stdio.h>
typedef struct {
	int x, y, z;
}Edge;
typedef struct {
	int n, m;
	int A[100][100];
}Graph;
void init_graph(Graph *pG, int n) {
	pG->n=n;
	int i, j;
	for(i=1; i<=n; i++) 
		for(j=1; j<=n; j++) 
			pG->A[i][j]=0;
}
void add_edge(Graph *pG, int x, int y, int z) {
	pG->A[x][y]+=z;
	pG->A[y][x]+=z;
}
void swap(Edge *a, Edge *b) {
	Edge temp;
	temp=*a;
	*a=*b;
	*b=temp;
}
int min(Edge a, Edge b) {
	if(a.x<=b.x && a.y<b.y)
		return 1;
	return 0;
}
void bb_sort(Edge e[], int n) {
	int i, j;
	for(i=0; i<n; i++) 
		for(j=n-1; j>i; j--) 
			if(min(e[j], e[j-1]))
				swap(&e[j], &e[j-1]);
}

typedef struct{
	int size;
	int L[100];
}List;
void makenullL(List *L){
	L->size=0;
}
void pushL(List *L, int x){
	L->L[L->size]=x;
	L->size++;
}
int isEmpty(List *pL) {
	return pL->L==0;
}
int elementAt(List *pL, int i) {
	return pL->L[i-1];
}
int distanceFrom(int u, List L, Graph G) {
	int min_dist=99999;
	int min_v=-1;
	int i;
	for(i-1; i<=L.size; i++) {
		int v=elementAt(&L, i);
		if(G.A[u][v]!=0 && min_dist>G.A[u][v]) {
			min_dist=G.A[u][v];
			min_v=v;
		}
	}
	return min_v;
}
int check(List L, int x) {
	int i;
	for(i=1; i<=L.size; i++)
		if(x==elementAt(&L, i))
			return 1;
		return 0;
}

Edge edges[100];
int count=0;
int mark[100];

int Prim(Graph G, Graph T) {
	int yes=0;
	init_graph(&T, G.n);
	List L;
	makenullL(&L);
	int u, w, v, e, i, sum_w=0;
	for(i=1; i<G.n; i++) 
		mark[i]=0;
	pushL(&L, 1);
	mark[1]=1;
	for(i=1; i<G.n; i++) {
		int min_dist=99999, min_u, min_v;
		for(u=1; u<=G.n; u++) 
			if(mark[u]==0) {
				int v=distanceFrom(u, L, G);
				if(v!=-1 && G.A[u][v]<min_dist) {
					min_dist=G.A[u][v];
					min_u=u;
					min_v=v;
					edges[count].x=v;
					edges[count].y=u;
					edges[count].z=min_dist;
					count++;
				}
			}
		pushL(&L, min_u);
		mark[min_u]=1;
		add_edge(&T, min_u, min_v, min_dist);
		sum_w+=min_dist;
	}
	return sum_w;
}
int main() {
	freopen("dt.txt", "r", stdin);
	int m, n, u, v, w, e, i;
	Graph G, T;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for(e=0; e<m; e++) {
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);	
	}
	int sum_w=Prim(G, T);
	printf("%d\n", sum_w);
	bb_sort(edges, count);
	for(e=0; e<count; e++)
		printf("%d %d %d\n", edges[e].x, edges[e].y, edges[e].z);
}

