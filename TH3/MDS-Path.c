#include<stdio.h>
//Graph
typedef struct {
	int A[20][20];
	int n, m, w; //So luong dinh
}Graph;


void init_graph(Graph *pG, int n) {
	int i, j;
	pG->n=n;
	for(i=1; i<=n; i++) {
		for(j=1; j<=n; j++)
			pG->A[i][j]=0;	
	}
}

void add_edge(Graph *pG, int x, int y, int w) {
	pG->A[x][y]=w;
}

//Kiem tra lang gieng x, y phai lang gieng khong?
int adjecent(Graph *pG, int x, int y) {
	if(pG->A[x][y]!=0) return 1;
	else return 0;
}

void print_graph(Graph *pG) {
	int i, j;
	for(i=1; i<=pG->n; i++) {
		for(j=1; j<=pG->n; j++) 
			printf("%d ", pG->A[i][j]);
		printf("\n");
	}
}

int mark[100];
int pi[100];
int p[100];
void DJS(Graph *pG, int s) {
	int i, j, it;
	for(i=1; i<=pG->n; i++) {
		pi[i]=999;
		mark[i]=0;
	}
	pi[s]=0;
	p[s]=-1;
	for(it=1; it<=pG->n; it++) {
		int min_pi=999;
		for(j=1; j<=pG->n; j++) 
			if(mark[j]==0 && pi[j]<min_pi) {
				min_pi=pi[j];
				i=j;
			}
		mark[i]=1;
		for(j=1; j<=pG->n; j++)
			if(mark[j]==0 && pG->A[i][j] != 0) 
				if(pi[j]>min_pi + pG->A[i][j]) {
					pi[j]=min_pi+pG->A[i][j];
					p[j]=i;
				}
	}
	//printf("%d", pi[s]);
}

int main() {
	//freopen("dt.txt", "r", stdin);
	int i, m, n, u, v, w, start, end;
	Graph G;	
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for(i=1; i<=m; i++) {
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}
	scanf("%d%d", &start, &end);
	//print_graph(&G);
	DJS(&G, start);
	//printf("%d ",p[end]);
	int path[100];
	int k=0;
	int current=end;
	
	while(current!=-1) {
		path[k]=current; k++;
		current=p[current];
	}
	
	for(i=k-1; i>0; i--) 
		printf("%d -> ", path[i]);
	printf("%d", path[0]);
	return 0;
}

