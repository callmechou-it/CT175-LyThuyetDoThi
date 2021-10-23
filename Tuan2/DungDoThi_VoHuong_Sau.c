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

//Stack
typedef struct {
	int u, p;
}ElementType;
typedef struct {
	ElementType data[100];
	int size;
} Stack;
void make_null_stack(Stack* S) {
	S->size = 0;
}
void push(Stack* S, ElementType pair) {
	S->data[S->size].u = pair.u;
	S->data[S->size].p = pair.p;
	S->size++;
}
ElementType top(Stack* S) {
	return S->data[S->size-1];
}
void pop(Stack* S) {
	S->size--;
}
int empty(Stack* S) {
	return S->size == 0;
}

//BFS
int mark[100];
int parent[100];
void DFS_x(Graph *G, int s) {
	Stack S;
	make_null_stack(&S);
	
	ElementType pair;
	pair.u=s; pair.p=0;
	push(&S, pair);
	
	while(!empty(&S)) {
		ElementType pair=top(&S); pop(&S);
		int u=pair.u, p=pair.p;
		if(mark[u]!=0) {
			continue;
		}
	
		mark[u]=1;
		parent[u]=p;
		//printf("%d %d\n", u, parent[u]);
		int v;
		for(v=1; v<=G->n; v++) {
			if(adjecent(G, u, v)){
				ElementType pair;
				pair.u=v; pair.p=u;
				push(&S, pair);	
			}
		}
	}
}

void DFS(Graph *G) {
	int i;
	for(i=1; i<=G->n; i++) 
		mark[i]=0;
	DFS_x(G, 1);
	for(i=1; i<=G->n; i++)
		if(mark[i]==0) {
			DFS_x(G, i);
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
	for(j=1; j<=G.n; j++)
		mark[j]=0;
	//print_graph(&G);
	DFS(&G);
	for(i = 1;i<=n;i++){
		printf("%d %d\n",i,parent[i]);
	}
	return 0;
}

