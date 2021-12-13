//1
int deg(Graph *G, int x){
    int deg = 0, i;
    for(i=1; i<=G->n; i++){
        if(G->A[x][i]!=0) deg++;
    }
    return deg;
}

//2
List neighbors(Graph *G, int x){
	List L;
	make_null(&L);
	int i;
	for(i=1; i<=G->n; i++)
		if(G->A[i][x] != 0){
		    push_back(&L, i);
		}
	return L;
}

//3
#include "stdio.h"

int main(){
    int DK1, DK2, DK3; //di?u ki?n 1, 2, 3
    int tongvao[100], tongra[100]; //t?ng vào, ra
    int i, n, m, u, v, f, c;
    
    DK1 = DK2 = DK3 = 1;
    
    scanf("%d%d", &n, &m);
    
    //kh?i t?o
    for (i=1; i<=n; i++){
        tongvao[i] = tongra[i] = 0;
    }
    
    //b?t d?u d?c các cung và ki?m tra ngay di?u ki?n 1
    for (i=1; i<=m; i++){
        scanf("%d%d%d%d", &u, &v, &f, &c);
        DK1 = DK1 && (f>=0) && (f<=c);
        tongra[u] += f;
        tongvao[v] += f;
    }
    
    //di?u ki?n 2
    for (i=2; i<n; i++)
        DK2 &= (tongvao[i] == tongra[i]);
        
    //di?u ki?n 3
    DK3 = (tongra[1] == tongvao[n]);
    
    if (DK1 && DK2 && DK3) printf("hop le");
    else printf("khong hop le");
}

//4. Khoang cách ng?n nhât t? x->y
#include <stdio.h>

#define MAXSIZE 100
#define INF 999999999
#define NOTCONNECTED -999999999
#define NO_ONE -1

//Moore-Dijkstra
//Don do thi vo huong, khong co khuyen
typedef struct{
	int n;
	int A[MAXSIZE][MAXSIZE];
} Graph;

void KhoiTaoGraph(Graph* G, int n){
	int i, j;
	G->n = n;
	for (i=1;i<=n;i++){
		for (j=1;j<=n;j++) 
			G->A[i][j] = NOTCONNECTED;
	}
}

void ThemCanh(Graph* G, int a, int b, int l){
		G->A[a][b] = G->A[b][a] = l;
}

void NhapDuLieu(Graph* G, int* x, int* y){
	int n, m;
	scanf("%d%d", &n, &m);

	KhoiTaoGraph(G, n);
	
	int a,b,c,l;
	for (c=1;c<=m;c++){
		scanf("%d%d%d", &a, &b, &l);
		ThemCanh(G, a, b, l);
	}
	scanf("%d%d", x, y);
}

void M_D(Graph* G, int s, int* p, int* pi){
	int mark[MAXSIZE];		//mark[i]=1 neu i duoc danh dau		
	int i,j,n;
	
	n=G->n;
	for (i=1;i<=n;i++) {
		mark[i]=0;
		p[i]=NO_ONE;
		pi[i]=INF;
	}
	
	pi[s]=0;
	
	//Lap:
	int minpi, //pi nh? nh?t trong s? các d?nh chua du?c ch?n
	    iminpi;//d?nh có pi nh? nh?t trong s? các d?nh chua du?c ch?n
	
	do{
		//tìm d?nh chua du?c ch?n có pi nh? nh?t
		minpi=INF;
		for (i=1;i<=n;i++) 
			if ((mark[i]==0) && (minpi>pi[i])){
				minpi=pi[i];
				iminpi=i;
			}
			
		if (minpi<INF){ //tìm th?y d?nh nào dó nhu v?y
			mark[iminpi]=1; //dánh d?u ch?n
			for (j=1;j<=n;j++) 
				if ((G->A[iminpi][j] != NOTCONNECTED) //di?u ki?n d? gán/d?i nhãn
				    && (minpi+G->A[iminpi][j] < pi[j])) //...c?a d?nh j
				        {
				    //gán nhãn cho j:
					p[j]=iminpi;
					pi[j]=minpi+G->A[iminpi][j];
				}
		}
	}while (minpi<INF);
}

int main(){

	//Khai bao
	Graph G;
	int pi[MAXSIZE], p[MAXSIZE];				
	int x, y;
	
	NhapDuLieu(&G, &x, &y);

	M_D(&G,x,p,pi);
	
	printf("tu ben %d den ben %d la: %d(km)", x, y, pi[y]);
	return 1;
}

//5.BPLT it dinh nhat
#include <stdio.h>
#define MAX_Vertices 20
#define MAX_Length 20
#define MAX_Element 40
typedef struct{
	int A[MAX_Vertices][MAX_Vertices];
	int n; //so luong dinh
}Graph;

void init_Graph(Graph *G, int n){
	int i, j;
	G->n = n;
	for(i=1; i<=n; i++)//dong cua ma tran
		for(j=1; j<=n; j++) // cot cua ma tran
			G->A[i][j] = 0;
}

//Them cung vao do thi
void add_edge(Graph *G, int x, int y){
	G->A[x][y] = 1;
	G->A[y][x] = 1;
}
//Kiem tra dinh x va dinh y co phai la lang gieng cua nhau hay ko?
int adjacent(Graph *G, int x, int y){
	return (G->A[x][y] != 0);
}

//Tinh bac cua dinh x trong do thi
int degree(Graph *G, int x){
	int deg = 0, i;
	for(i=1; i<=G->n; i++)
		if(adjacent(G, i, x)) //adjacent(G, i, x)
			deg++;
	return deg;
}
//Khai bao cau truc danh sach List
typedef struct{
	int data[MAX_Length];
	int size;
}List;

//Ham khoi tao danh sach rong
void make_null(List *list){
	list->size = 0;
}

//Them mot phan tu (dinh) vao cuoi danh sach
void push_back(List *list, int x){
	list->data[list->size] = x;
	list->size++;
}

//Lay mot phan tu (dinh) trong danh sach tai vi tri i
int element_at(List *list, int i){
	return list->data[i-1];
}

//Tim lang gieng cua dinh x
List neighbors(Graph *G, int x){
	List L;
	make_null(&L);
	int i;
	for(i=1; i<=G->n; i++)
		if(G->A[i][x] == 1){
			push_back(&L, i);
		}
	return L;
}
//Khai bao cau truc cua Ngan xep
typedef struct{
	int data[MAX_Element];
	int size;
}Stack;

//Khoi tao ngan xep rong
void make_null_stack(Stack *stack){
	stack->size = 0;
}

//Them mot phan tu vao trong ngan xep
void push_stack(Stack *stack, int x){
	stack->data[stack->size] = x;
	stack->size++;
}

//Lay mot phan tu trong Stack
int top(Stack *stack){
	return stack->data[stack->size-1];
}

//Xoa mot phan tu thuoc Stack
void pop(Stack *stack){
	stack->size--;
}

//Kiem tra Stack co rong hay khong
int empty(Stack *stack){
	return stack->size == 0;
}

List depth_first_search(Graph *G, int x, int parent[]){
	Stack S;
	make_null_stack(&S);
	push_stack(&S, x);
	parent[x] = 0;
	List list_dfs;
	make_null(&list_dfs);
	int mark[MAX_Vertices];
	int i;
	for(i=1; i<=G->n; i++)
		mark[i]=0;
	while(!empty(&S)){
		int u = top(&S);
		pop(&S);
		if(mark[u] == 1)
			continue;
		push_back(&list_dfs, u);
		mark[u] = 1;
		List list = neighbors(G, u);
		for(i=1; i<=list.size; i++){
			int v = element_at(&list, i);
			if(mark[v] == 0){
				push_stack(&S, v);
				parent[v] = u;
			}
				
		}
	}
	return list_dfs;
}



int main(){
	Graph G;
	int n, m, i, j;
	scanf("%d%d", &n, &m);
	init_Graph(&G, n);
	int e, u, v;
	for(e=1; e<=m; e++){
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	
	int parent[MAX_Vertices];
	for(i=1; i<=G.n; i++){
		parent[i] = -1;
	}
	
	int mark_dfs[MAX_Vertices];
	for(i=1; i<=G.n; i++){
		mark_dfs[i] = 0;
	}
	int min = 1000;
	for(i=1; i<=G.n; i++){
		if(mark_dfs[i] == 0){
			List dfs = depth_first_search(&G, i, parent);
			for(j=1; j<=dfs.size; j++){
				int k = element_at(&dfs, j);
				mark_dfs[k]=1;
			}
			if(dfs.size < min)
				min = dfs.size; 
		}
	}
	printf("%d", min);
	return 0;
}

//6. tong chi phí xay dung w+t
#define MAXN 100
#define NO_EDGE 0
#define INFINITY 9000

#include <stdio.h>

typedef struct {
	int n;
	int L[MAXN][MAXN];
} Graph;

void init_graph(Graph* pG, int n) {
	pG->n = n;
	int i, j;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			pG->L[i][j] = NO_EDGE;
}

void add_edge(Graph *G, int u, int v, int w){
	G->L[u][v]=w;
	G->L[v][u]=w;
}

int mark[MAXN];
int pi[MAXN];
int p[MAXN];

int Prim(Graph *G, int s, Graph *T) {
	int u, v, it, sum_w=0;
	for (u = 1; u <= G->n; u++) {
		pi[u] = INFINITY;
		mark[u] = 0;
	}

	pi[s] = 0;
	p[s] = s;

	for (it = 1; it <= G->n; it++) {
		int j, min_pi = INFINITY;
		for (j = 1; j <= G->n; j++)
			if (mark[j] == 0 && pi[j] < min_pi) {
				min_pi = pi[j];
				u = j;
			}
		mark[u] = 1;
		if(p[u]!=u){
			add_edge(T, p[u], u, min_pi);
			//printf("%d %d %d\n",p[u], u, min_pi);
			sum_w += min_pi;
		}

		for (v = 1; v <= G->n; v++)
			if (G->L[u][v] != NO_EDGE && mark[v] == 0)
				if (pi[v] > G->L[u][v]) {
					pi[v] = G->L[u][v];
					p[v] = u;
				}
	}
	return sum_w;
}


int main(){
	Graph G, T;
	int n, m, u, v, w,t, i;

	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	init_graph(&T, n);
	for(i=0; i<m; i++){
		scanf("%d%d%d%d", &u, &v, &w, &t);
		add_edge(&G, u, v, w + t);
	}
	int sum_w = Prim(&G, 1, &T);
	printf("%d", sum_w);
	return 0;
}


//7. Tong chi phi xay dugn thap nhat w
#define MAX_VERTICES 50
#define MAX_EDGES 50
#define NO_EDGE 0
#define INFINITY 9000
#define MAX_ELEMENTS 50

#include <stdio.h>

int parent[MAX_VERTICES];

typedef struct{
    int u, v, w;
}Edge;

typedef struct{
    Edge edge[MAX_EDGES];
    int n, m;
}Graph;

void init_graph(Graph* G, int n) {
    G->n = n;
    G->m = 0;
}

void add_edge(Graph *G, int u, int v, int w){
    G->edge[G->m].u=u;
    G->edge[G->m].v=v;
    G->edge[G->m].w=w;
    G->m++;
}

void swap_edge(Edge *e1, Edge *e2){
    Edge tmp;
    tmp = *e1;
    *e1 = *e2;
    *e2 = tmp;
}

void sorting_edge(Graph *G){
    int i, j;
    for(i=0; i<G->m-1; i++)
        for(j=i+1;j<G->m; j++)
            if(G->edge[i].w>G->edge[j].w)
                swap_edge(&G->edge[i], &G->edge[j]);
}

int find_root(int u){
    while(parent[u] != u)
        u=parent[u];
    return u;
}

int kruskal(Graph *G, Graph *T){
    int i, e, sum_w=0, u, v, w, root_u, root_v;
    init_graph(T, G->n);
    sorting_edge(G);
    for(i=1; i<=G->n; i++)
        parent[i]=i;
    for(e=0; e < G->m; e++){
        u = G->edge[e].u;
        v = G->edge[e].v;
        w = G->edge[e].w;
        root_u = find_root(u);
        root_v = find_root(v);
        if(root_u != root_v){
            add_edge(T, u, v, w);
            parent[root_u]=root_v;
            sum_w = sum_w + w;
        }
    }
    return sum_w;
}

int main(){
    Graph G, T;
    int i, u, v, w, n, m;
    //freopen("DoThiCay.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    for(i=1; i<=m; i++){
        scanf("%d%d%d", &u, &v, &w);
        if(u<v)
            add_edge(&G, u, v, w);
        else
            add_edge(&G, v, u, w);
    }
    int sum = kruskal(&G, &T);
    printf("%d", sum);

    return 0;
        
}

//8.Xep hang
//Hàm x?p h?ng d? th?
int XepHang(
    Graph* G, //d? th? c?n x?p h?ng
    int rank[] //m?ng luu k?t qu?, chua kh?i t?o, h?ng nh? nh?t là 1
){
    int d[100], i, j;
    for (i=1; i<=G->n; i++)
        rank[i] = 0;
        
    for (i=1; i<=G->n; i++)
        for (j=1; j<=G->n; j++)
            if (G->A[i][j])
                d[j]++; //s? t?o ?nh
    
    int luot=1; //lu?t
    int sddxh = 0; //s? d?nh dã x?p h?ng
    do{
        for (i=1; i<=G->n; i++)
            if ((rank[i] == 0) // 
                && (d[i] == 0)){ //
                rank[i] = luot;
                sddxh++;
            }
                
        for (i=1; i<=G->n; i++)
            if (rank[i] == luot) {
                for (j=1; j<=G->n; j++)
                    if (G->A[i][j])
                        d[j]--;
            }
            
        luot++;
    } while (sddxh < G->n);
                
    return 1;
}//h?t hàm XepHang()

