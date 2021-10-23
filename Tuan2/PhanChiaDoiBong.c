#include<stdio.h>
#define NOCO 0
#define BLUE 1
#define RED 2

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

int color[100];
int conflict;
//int B[100];
void colorize(Graph *G, int u, int c) {
	
	color[u]=c;
	int v;
	for(v=1; v<=G->n; v++) {
		if(adjecent(G, u, v)) {
			if(color[v]==NOCO)
				colorize(G, v, 3-c);
			else if(color[v]==color[u])
				conflict=1;
		}
	}
	
}


int main() {
	//freopen("dt.txt", "r", stdin);
	int i, j, m, n, u, v;
	Graph G;	
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for(i=1; i<=m; i++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	//print_graph(&G);
	for(i=1; i<=G.n; i++) {
		color[u]=NOCO;
	}
	conflict=0;
	for(j=1; j<=G.n; j++) 
		if(color[j]==NOCO)
			colorize(&G, j, 1);
	//printf("%d", color[1]);
	
	if(conflict!=1){
		for(i=1; i<=n; i++) {
			if(color[i]==BLUE) printf("%d ", i);
		}
		printf("\n");
		for(i=1; i<=n; i++) {
			if(color[i]==RED) printf("%d ", i);
		}
	} 
	else printf("IMPOSSIBLE");
	return 0;
}

