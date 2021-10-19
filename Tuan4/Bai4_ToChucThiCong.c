#include<stdio.h>
//Do thi
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

//Cau truc Queue
typedef struct {
	int data[100];
	int front, rear;
}Queue;
void makenullQ(Queue *pQ) {
	pQ->front=0;
	pQ->rear=-1;
}
void push(Queue *pQ, int x) {
	pQ->rear++;
	pQ->data[pQ->rear]=x;
}
int top(Queue *pQ) {
	return pQ->data[pQ->front];
}
void pop(Queue *pQ) {
	pQ->front++;
}
int empty(Queue *pQ) {
	return pQ->front>pQ->rear;
}

//Cau truc List
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
int d[100];
List topo_sort(Graph *pG) {
	int d[100];
	int x, u;
//	int k=1, i;
	for(u=1; u<=pG->n; u++) {
		d[u]=0;
	}
	for(x=1; x<=pG->n; x++) 
		for(u=1; u<=pG->n; u++)
			if(pG->A[x][u] != 0)
				d[u]++;
	Queue Q;
	makenullQ(&Q);
	for(u=1; u<=pG->n; u++) 
		if(d[u]==0)
			push(&Q, u);
	List L;
	makenullL(&L);
	while(!empty(&Q)) {
		int u=top(&Q); pop(&Q);
		pushBack(&L, u);
		int v;
		for(v=1; v<=pG->n; v++)
			if(pG->A[u][v]!=0) {
				d[v]--;
				if(d[v]==0) 
					push(&Q, v);
			}
	}
	return L;
}
int min(int a, int b) {
	if(a<b) return a;
	else return b;
}
int max(int a, int b) {
	if(a>b) return a;
	else return b;
}
int main() {
	int n, u, v, e, i, x;
	Graph G; List L;
	freopen("ranking.txt", "r", stdin);
	scanf("%d", &n);
	init_graph(&G, n+2);
	d[n+1]=0;
	for(u=1; u<=n; u++) {
		scanf("%d", &d[u]);
		do{
			scanf("%d", &v);
			if(v>0)
				add_edge(&G, v, u);
		} while(v>0);
	}
	
	//Noi dinh n+1 voi dinh khong co cung di vao
	for(u=1; u<=n; u++) {
		int deg_neg=0;
		for(x=1; x<=n; x++) 
			if(G.A[x][u]>0)
				deg_neg++;
		if(deg_neg==0) 
			add_edge(&G, n+1, u);
	}
	//Noi dinh n+1 voi dinh khong co cung di ra
	for(u=1; u<=n; u++) {
		int deg_pos=0;
		for(v=1; v<=n; v++) 
			if(G.A[u][v]>0)
				deg_pos++;
		if(deg_pos==0) 
			add_edge(&G, u, n+2);
	}	
	
	L = topo_sort(&G);
	int t[100];
	//Thoi diem som nhat
	t[n+1]=0;//t[alpha]=0
	for(i=2; i<=L.size; i++) {
		int u=elementAt(&L, i);
		t[u]=0;
		for(e=1; e<=G.n; e++) 
			if(G.A[e][u]>0) 
				t[u]=max(t[u], t[e]+d[e]);
	}
	
	//Thoi diem tre nhat
	int T[100];
	T[n+2]=t[n+2];
	for(i=L.size-1; i>=1; i--) {
		int u=elementAt(&L, i);
		T[u]=99999;
		for(e=1; e<=G.n; e++) 
			if(G.A[u][e]>0) 
				T[u]=min(T[u], T[e]-d[u]);
	}
	printf("%d\n", t[n+2]);
	for(e=1; e<=G.n; e++) 
		printf("%d-%d\n", t[e], T[e]);
		int a, b;
	scanf("%d%d", &a, &b);
	if(b>=t[a]&&b<=T[a]) printf("YES");
	else printf("NO");
	return 0;
}

