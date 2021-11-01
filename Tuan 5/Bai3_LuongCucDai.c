#include<stdio.h>
typedef struct {
	int C[100][100];
	int F[100][100];
	int n;
}Graph;
void init_graph(Graph *pG, int n) {
	pG->n=n;
}
void init_F(Graph *pG) {
	int i, j;
	for(i=1; i<=pG->n; i++) 
		for(j=1; j<=pG->n; j++)
			pG->F[i][j]=0;
}

typedef struct {
	int dir;
	int pre;
	int sigma;
}Label;
Label labels[100];

typedef struct {
	int data[100];
	int front, rear;
} Queue;
void make_null_queue(Queue* Q) {
	Q->front = 0;
	Q->rear = -1;
}
void enqueue(Queue* Q, int x) {
	Q->rear++;
	Q->data[Q->rear] = x;
}
int top(Queue* Q) {
	return Q->data[Q->front];
}
void dequeue(Queue* Q) {
	Q->front++;
}
int empty(Queue* Q) {
	return Q->front > Q->rear;
}

int min(int a, int b) {
	return a<b?a:b;
}

int FordFullkerson(Graph *pG, int s, int t) {
	init_F(pG);
	int u, v, sum_F=0;
	Queue Q;
	do {
		for(u=1; u<=pG->n; u++) 
			labels[u].dir=0;
		labels[s].dir=1;
		labels[s].pre=s;
		labels[s].sigma=99999;
		
		make_null_queue(&Q);
		enqueue(&Q, s);
		
		int found=0;
		while(!empty(&Q)) {
			int u=top(&Q);
			dequeue(&Q);
			for(v=1; v<=pG->n; v++) {
				if(labels[v].dir==0 && pG->C[u][v]!=0 && pG->F[u][v]<pG->C[u][v]) {
					labels[v].dir=1;
					labels[v].pre=u;
					labels[v].sigma=min(labels[u].sigma, pG->C[u][v]-pG->F[u][v]);
					enqueue(&Q, v);
				}
				if(labels[v].dir==0 && pG->C[v][u]!=0 && pG->F[v][u]>0) {
					labels[v].dir=-1;
					labels[v].pre=u;
					labels[v].sigma=min(labels[u].sigma, pG->F[u][v]);
					enqueue(&Q, v);
				}
			}
			if(labels[t].dir!=0) {
				found=1;
				break;
			}
		}
		if(found==1) {
			int x=t;
			int sigma=labels[t].sigma;
			sum_F+=sigma;
			
			while(x!=s) {
				int u=labels[x].pre;
				if(labels[x].dir>0) 
					pG->F[u][x]+=sigma;
				else pG->F[x][u]-=sigma;
				x=u;
			}
		}
		else break;
	} while(1);
	return sum_F;
}

int main() {
	freopen("dt.txt", "r", stdin);
	Graph G;
	int m, n, u, v, c, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for(e=0; e<m; e++) {
		scanf("%d%d%d", &u, &v, &c);
		G.C[u][v]=c;
	}
	int max_F=FordFullkerson(&G, 1, n);
	printf("Max flow: %d\n", max_F);
	
	printf("X0:");
	for(e=1; e<=G.n; e++) {
		if(labels[e].dir!=0)
			printf(" %d",e);
	}
	printf("\nY0:");
	for(e=1; e<=G.n; e++) {
		if(labels[e].dir==0) 
			printf("%d ", e);
	}
	return 0;
}

