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
int mark[100];
void DFS_x(Graph *G, int s) {
	Stack S;
	make_null_stack(&S);
	
	push(&S, s);
	
	while(!empty(&S)) {
		int u=top(&S); pop(&S);
		if(mark[u]!=0) {
			continue;
		}
		printf("%d\n", u);
		mark[u]=1;
		int v;
		for(v=1; v<=G->n; v++) {
			if(adjecent(G, u, v))
				push(&S, v);
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
	//int mark[100];
	for(j=1; j<=G.n; j++)
		mark[j]=0;
	//print_graph(&G);
	DFS(&G);
	return 0;
}

