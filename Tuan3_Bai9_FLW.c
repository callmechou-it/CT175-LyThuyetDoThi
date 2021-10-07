#include<stdio.h>
typedef struct {
	int A[200][200];
	int n, m, w; //So luong dinh
}Graph;
void init_graph(Graph *pG, int n) {
	int i, j;
	pG->n=n;
	for(i=1; i<=pG->n; i++) {
		for(j=1; j<=pG->n; j++)
			pG->A[i][j]=0;	
	}
}
void add_edge(Graph *pG, int x, int y, int w) {
	pG->A[x][y]=w;
}
void print_graph(Graph *pG) {
	int i, j;
	for(i=1; i<=pG->n; i++) {
		for(j=1; j<=pG->n; j++) 
			printf("%d   ", pG->A[i][j]);
		printf("\n");
	}
}

int pi[100][100];
int next[100][100];
void FLW(Graph *pG) {
	int i, j, it;
	for(i=1; i<=pG->n; i++) {
		for(j=1; j<=pG->n; j++) {
			pi[i][j]=99999;
			next[i][j]=-1;
		}
	}
	
	for(i=1; i<=pG->n; i++) 
		pi[i][i]=0;
		
	for(i=1; i<=pG->n; i++) 
		for(j=1; j<=pG->n; j++) {
			if(pG->A[i][j] != 0) {
				pi[i][j]=pG->A[i][j];
				next[i][j]=j;
			}
		}
	
	for(it=1; it<=pG->n; it++) {
		for(i=1; i<=pG->n; i++)	
			for(j=1; j<=pG->n; j++)
				if(pi[i][it]+pi[it][j]<pi[i][j]) {
					pi[i][j]=pi[i][it]+pi[it][j];
					next[i][j]=next[i][it];
				}
	}
}

int main() {
	freopen("tuan3.txt", "r", stdin);
	int i, j, m, n, w, u, v;
	Graph G;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for(i=1; i<=m; i++) {
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}
//	print_graph(&G);
	
	FLW(&G);
	for(i=1; i<=G.n; i++) {
		for(j=1; j<=G.n; j++) {
			if(pi[i][j]>=99999-5)
				printf("%d -> %d: oo\n", i, j);
			else printf("%d -> %d: %d\n", i, j, pi[i][j]);
		}
	}
	return 0;
}

