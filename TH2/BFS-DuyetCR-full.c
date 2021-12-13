#include <stdio.h>
/* Khai báo CTDL Graph*/
#define MAX_N 100
typedef struct {
    int n, m;
    int A[MAX_N][MAX_N];
} Graph;

void init_graph(Graph *pG, int n) {
    pG->n = n;
    pG->m = 0;
    for (int u = 1 ; u <= n; u++)
        for (int v = 1 ; v <= n; v++)
            pG->A[u][v] = 0;
}

void add_edge(Graph *pG, int u, int v) {
    pG->A[u][v] += 1;
    if (u != v)
        pG->A[v][u] += 1;
    
    pG->m++;
}

int adjacent(Graph *pG, int u, int v) {
    return pG->A[u][v] > 0;
}
/* Khai báo CTDL Queue*/

#define MAX_SIZE 100
typedef int ElementType;

typedef struct {
	ElementType data[MAX_SIZE];
	int front, rear;
} Queue;

void make_null_queue(Queue *pQ) {
	pQ->front = 0;
	pQ->rear = -1;
}

void enqueue(Queue *pQ, int u) {
	pQ->rear++;
	pQ->data[pQ->rear] = u;
}

int front(Queue *pQ) {
	return pQ->data[pQ->front];
}

void dequeue(Queue *pQ) {
	pQ->front++;
}

int empty(Queue *pQ) {
	return pQ->front > pQ->rear;
}

int mark[MAX_N];

void BFS(Graph *pG, int s) {
	Queue Q;
	make_null_queue(&Q);
	enqueue(&Q, s);
	while (!empty(&Q)) {
		int u = front(&Q); dequeue(&Q);
		if (mark[u] != 0) 		//u dã duy?t r?i, b? qua
			continue;

		printf("%d\n", u);	//Làm gì dó trên u
		mark[u] = 1; 			//Ðánh d?u nó dã duy?t
		//3b. Xét các d?nh k? c?a u, dua vào hàng d?i Q
		for (int v = 1; v <= pG->n; v++)
			if (adjacent(pG, u, v))
				enqueue(&Q, v);
	}
}

int main() {
	Graph G;
	int n, m, u, v;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for (int e = 0; e < m; e++) {
	    scanf("%d%d", &u, &v);
	    add_edge(&G, u, v);
	}
	//3. Kh?i t?o m?ng mark[u] = 0, v?i m?i u = 1, 2, ..., n
	for (int u = 1; u <= G.n; u++)
		mark[u] = 0;
	//4. G?i hàm BFS duy?t theo chi?u r?ng t? d?nh 1
	for (int u = 1; u <= G.n; u++)
        if (mark[u] == 0)
            BFS(&G, u);
	return 0;
}


