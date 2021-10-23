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

//Stack
typedef struct {
	int data[100];
	int size;
} Stack;
void make_null_stack(Stack* S) {
	S->size = 0;
}
void push(Stack* S, int x) {
	S->data[S->size] = x;
	S->size++;
}
int top(Stack* S) {
	return S->data[S->size-1];
}
void pop(Stack* S) {
	S->size--;
}
int empty(Stack* S) {
	return S->size == 0;
}

//DFS
#define WHITE 0
#define GRAY 1
#define BLACK 2
int color[100];
int has_circle;
void DFS_x(Graph *G, int s) {
	color[s]=GRAY;
	int v;
	for(v=1; v<=G->n; v++) 
	if(adjecent(G, s, v)) {
		if(color[v]==WHITE)
			DFS_x(G, v);
		else if(color[v]==GRAY) 
			has_circle=1;
	}
	color[s]=BLACK;
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
	for(i=0; i<=G.n; i++) {
		color[u]=WHITE;
	}
	has_circle=0;
	for(j=0; j<=G.n; j++) 
		if(color[j]==WHITE)
			DFS_x(&G, j);
	
	if(has_circle) printf("NO");
		else printf("YES");
	return 0;
}

