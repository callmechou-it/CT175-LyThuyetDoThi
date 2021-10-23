#include<stdio.h>
typedef struct{
	int n,m;
	int A[100][100];
}Graph;
void initG(Graph *G, int n){
	G->n=n;
	int i,j;
	for(i=1;i<=G->n;i++){
		for(j=1;j<=n;j++){
			G->A[i][j]=0;
		}
	}
}
void addedge(Graph *G, int x, int y){
	if(x!=y){
	G->A[x][y]++;
	G->A[y][x]++;
	}
	else G->A[x][x]+=2;
}

typedef struct{
	int size;
	int L[100];
}List;
void makenullL(List *L){
	L->size=0;
}
void pushL(List *L, int x){
	L->L[L->size]=x;
	L->size++;
}

typedef struct{
	int S[100];
	int size;
}Stack;
void makenullS(Stack *S){
	S->size=0;
}
int topS(Stack *S){
	return S->S[S->size-1];
}
void popS(Stack *S){
	S->size--;
}
void pushS(Stack *S, int x){
	S->S[S->size]=x;
	S->size++;
}
int emptyS(Stack *S){
	return S->size==0;
}


void inMT(Graph *G){
	int i,j;
	for(i=1;i<=G->n;i++){
		for(j=1;j<=G->n;j++){
			printf("%d ",G->A[i][j]);
		}
		printf("\n");
	}
}
List neighbour(Graph *G,int x){
	List L;
	makenullL(&L);
	int i,j;
	for(i=0;i<=G->n;i++){
		for(j=1;j<=G->A[x][i];j++){
			pushL(&L,i);
		}
	}
	return L;
}
int KTtrungL(List *L){
	int i,j,tmp=0;
	for(i=0;i<L->size-1;i++){
		for(j=i+1;j<L->size;j++){
			if(L->L[i]==L->L[j]) tmp=1;
		}
	}
	return tmp;
}
int color[100],cycle;
#define while 0
#define black 1
#define gray 2
void dfs(Graph *G,int x,int par){
	color[x]=gray;
	int j;
	List L=neighbour(G,x);
	if(KTtrungL(&L)==1){
		cycle=1;
		return;
	}
	for(j=1;j<=L.size;j++){
		int y=L.L[j-1];
		if(y==par)continue;
		if(color[y]==gray){
			cycle=1;
			return;
		}
		if(color[y]==while)dfs(G,y,x);
	}
	color[x]=black;
}
int contains(Graph *G){
	int i;
	for(i=1;i<=G->n;i++){
		color[i]=while;
	}
	cycle=0;
	for(i=1;i<=G->n;i++){
		if(color[i]==while) dfs(G,i,0);
	}
	return cycle;
}


int main(){
 
	Graph G;
	int n, m, u, v, e;
	scanf("%d%d", &n, &m);
	initG(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d %d", &u, &v);
		addedge(&G, u, v);
	}
//	inMT(&G);
	if(contains(&G)==0)printf("NO");
	else printf("YES");
    return 0;
}
