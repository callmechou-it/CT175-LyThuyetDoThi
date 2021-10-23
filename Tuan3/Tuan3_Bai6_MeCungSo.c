#include<stdio.h>
int arr[100];
//Graph
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
	pi[s]=arr[s];
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
				if(pi[j]>pi[i] + pG->A[i][j]) {
					pi[j]=pi[i]+pG->A[i][j];
					p[j]=1;
				}
	}
}

int main() {
//	freopen("tuan3.txt", "r", stdin);
	int i, j, a, b, u, v, k, dinh_i, dinh_j;
	//int arr[20];	
	scanf("%d%d", &a, &b);
	for(i=1; i<=a*b; i++) {
		scanf("%d", &arr[i]);
	}
//	for(i=1; i<=a*b; i++) {
//			printf("%d ", arr[i]);
//	}
	Graph G;
	init_graph(&G, a*b);
//	printf("%d", a*b);
	
	for(i=0; i<a; i++) {
		for(j=0; j<b; j++) {
			int di[]={-1, 1, 0, 0};
			int dj[]={0, 0, -1, 1};
			
			for(k=0; k<4; k++) {
				dinh_i=i+di[k];
				dinh_j=j+dj[k];
				
				if((dinh_i>=0)&&(dinh_i<a)&&(dinh_j>=0)&&(dinh_j<b)) {
					v=dinh_i*b+dinh_j+1;
					u=i*b+j+1;
					G.A[u][v]=arr[v];
				}
			}
		}
	}
	DJS(&G, 1);
	printf("%d", pi[G.n]);
	return 0;
}

