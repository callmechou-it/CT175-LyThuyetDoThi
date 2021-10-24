#include<stdio.h>
//Graph
typedef struct {
	int A[20][20];
	int n; //So luong dinh
}Graph;

void init_graph(Graph *pG, int n) {
	int i, j;
	pG->n=n;
	for(i=1; i<=n; i++) {
		for(j=1; j<=n; j++)
			pG->A[i][j]=0;	
	}
}

void add_edge(Graph *pG, int x, int y) {
	pG->A[x][y]=1;
	pG->A[y][x]=1;
}

//Kiem tra lang gieng x, y phai lang gieng khong?
int adjecent(Graph *pG, int x, int y) {
	return pG->A[x][y];
}

void print_graph(Graph *pG) {
	int i, j;
	for(i=1; i<=pG->n; i++) {
		for(j=1; j<=pG->n; j++) 
			printf("%d ", pG->A[i][j]);
		printf("\n");
	}
}


//DFS
int mark[100];
void DQ_x(Graph *G, int s) {
	if(mark[s]) return ;
	printf("%d\n", s);
	mark[s]=1;
	int v;
	for(v=1; v<=G->n; v++) 
		if(adjecent(G, s, v)) 
			DQ_x(G, v);
}

void DQ(Graph *G) {
	int i;
	for(i=1; i<=G->n; i++) 
		mark[i]=0;
	DQ_x(G, 1);
	for(i=1; i<=G->n; i++)
		if(mark[i]==0) {
			DQ_x(G, i);
		}
}
int main() {
	//freopen("dt.txt", "r", stdin);
	int i, j, m, n, u, v;
	Graph G;	
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for(i=0; i<=m; i++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	//int mark[100];
	for(j=1; j<=G.n; j++)
		mark[j]=0;
	//print_graph(&G);
	DQ(&G);
	return 0;
}


