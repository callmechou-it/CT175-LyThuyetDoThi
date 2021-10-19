#include<stdio.h>
int rank[100];
int d[100];

//Cau truc LIST
typedef struct {
	int data[100];
	int size;
}List;
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

//Cau truc DO THI
typedef struct {
	int A[100][100];
	int n, m;
}Graph;
void init_graph(Graph *pG, int n) {
	int i, j;
	pG->n=n;
	for(i=1; i<=n; i++) 
		for(j=1; j<=n; j++) 
			pG->A[i][j]=0;
}
void add_edge(Graph *pG, int x, int y) {
	pG->A[y][x]=1;
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
int k=1;
List L1, L2;
void ranking(Graph *pG) {
	int x, u;
	for(u=1; u<=pG->n; u++) {
	//	rank[e]=0;
		d[u]=0;
	}
	for (x=1; x<=pG->n; x++) {
		for(u=1; u<=pG->n; u++) {
			if(pG->A[x][u]!=0) 
				d[u]++;
		}
	}
	makenullL(&L1);
	for(u=1; u<=pG->n; u++) 
		if(d[u]==0) 
			pushBack(&L1, u);
	
	int i;	
	while(L1.size>0) {
		makenullL(&L2);
		for(i=1; i<=L1.size; i++) {
			int u=elementAt(&L1, i);
			rank[u]=k;
			int v;
			for(v=1; v<=pG->n; v++) {
				if(pG->A[u][v]!=0) {
					d[v]--;
					if(d[v]==0) 
						pushBack(&L2, v);
				}
			}
		}
		copyL(&L1, &L2);
		k++;
	}
}

int main() {
	freopen("ranking.txt", "r", stdin);
	Graph G;
	int n, m, u, v, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	int sum=0;
	ranking(&G);
	for(u=1;u<=n;u++) {
		printf("%d \n",rank[u]);
		sum+=rank[u];
	}
	printf("%d", sum);	
	return 0;
}

