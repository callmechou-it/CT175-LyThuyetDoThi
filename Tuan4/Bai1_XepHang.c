#include<stdio.h>
int rank[100];
int d[100];
int bacvao[100];

typedef struct {
	int data[100];
	int size;
}List;
typedef struct {
	int A[100][100];
	int n, m;
}Graph;

void makenullL(List *pL) {
	pL->size=0;
}
void pushBack(List *pL, int x) {
	pL->data[pL->size]=x;
	pL->size++;
}
int elementAt(List *pL, int i) {
	return pL->data[i-1];
}
int countL(List *pL) {
	return pL->size;
}

void init_Graph(Graph *pG, int n) {
	int i, j;
	pG->n=n;
	for(i=1; i<=n; i++) 
		for(j=1; j<=n; j++) 
			pG->A[i][j]=0;
}
void add_edge(Graph *pG, int x, int y) {
	pG->A[x][y]=1;
}
int adjecent(Graph *pG, int x, int y) {
	return pG->A[x][y];
}
int degIn(Graph *pG, int x) {
	int i, deg=0;
	for(i=1; i<=pG->n; i++) 
		if(pG->A[i][x]!=0) deg++;
	return deg;
}

List neighbors(Graph *pG, int x) {
	int i;
	List L;
	makenullL(&L);
	for(i=1; i<=pG->n; i++) 
		if(adjecent(pG, x, i))
			pushBack(&L, i);
	return L;
}
void copyL(List *L1, List *L2) {
	int i, x;
	makenullL(L1);
	for(i=1; i<=L2->size; i++) {
		x=elementAt(L2, i);
		pushBack(L1, x);
	}
}
//int k=0;
List L1, L2;
void ranking(Graph *pG) {
	int i, k=0;
	List S1, S2;
	makenullL(&S1);
	for(i=1; i<=pG->n; i++) 
		if(d[i]==0) pushBack(&S1, i);
	while(S1.size>0) {
		makenullL(&S2);
		for(i=1; i<=S1.size; i++) {
			int u=elementAt(&S1, i);
			rank[u]=k;
			int v;
			for(v=1; v<=pG->n; v++) {
				if(pG->A[u][v]!=0) {
					bacvao[v]--;
					if(d[v]==0) 
						pushBack(&S2, v);
				}
			}
		}
		copyL(&S1, &S2);
		k++;
	}
}

int main() {
	freopen("ranking.txt", "r", stdin);
	Graph G;
	int n, m, u, v, x, w, e;
	scanf("%d%d", &n, &m);
	init_Graph(&G, n);
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
//	for (e = 1; e <= n; e++) {
//		for (u = 1; u <= n; u++) {
//		printf("%d ", G.A[e][u]);
//	}
//	printf("\n");
//	}
	for(e=1; e<=n; e++) {
		rank[e]=0;
		bacvao[e]=0;
	}

	for (e = 1; e <= n; e++) {
		bacvao[e]=degIn(&G,e);
	}
//	for (e = 1; e <= n; e++) {
//		printf("%d", bacvao[e]);
//	}
	
	ranking(&G);
	for(u=1;u<=n;u++)
		printf("%d \n",rank[u]);
	return 0;
}

