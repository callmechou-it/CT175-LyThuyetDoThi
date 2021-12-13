//Dung do thi, vo huong don tu dinh 1 theo chieu rong

#include <stdio.h>

/* Khai b�o CTDL Graph*/
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

/* Khai b�o CTDL Queue */

#define MAX_SIZE 100
typedef struct {
    int u, p;
} ElementType;

typedef struct {
	ElementType data[MAX_SIZE];
	int front, rear;
} Queue;

/* Kh?i t?o h�ng d?i r?ng */
void make_null_queue(Queue *pQ) {
	pQ->front = 0;
	pQ->rear = -1;
}
/* �ua ph?n t? u v�o cu?i h�ng d?i */
void enqueue(Queue *pQ, ElementType u) {
	pQ->rear++;
	pQ->data[pQ->rear] = u;
}

/* Xem ph?n t? d?u h�ng d?i */
ElementType front(Queue *pQ) {
	return pQ->data[pQ->front];
}

/* Xo� b? ph?n b? d?u h�ng d?i */
void dequeue(Queue *pQ) {
	pQ->front++;
}

/* Ki?m tra h�ng d?i r?ng */
int empty(Queue *pQ) {
	return pQ->front > pQ->rear;
}


//Bi?n h? tr? d�ng d? luu tr?ng th�i c?a d?nh: d� duy?t/chua duy?t
int mark[MAX_N];
int parent[MAX_N];

void BFS(Graph *pG, int s) {
	//1. Khai b�o h�ng d?i Q, kh?i t?o r?ng
	Queue Q;
	make_null_queue(&Q);
	//2. �ua s v�o Q, b?t d?u duy?t t? d?nh s */
	ElementType pair; 									
	pair.u = s; pair.p = -1; 								
	enqueue(&Q, pair); 									
	//3. V�ng l?p ch�nh d�ng d? duy?t
	while (!empty(&Q)) {
		//3a. L?y ph?n t? ? d?u h�ng d?i
		ElementType pair = front(&Q); dequeue(&Q); 				
		int u = pair.u, p = pair.p; 							
		if (mark[u] != 0) 		//u d� duy?t r?i, b? qua
			continue;

		//printf("Duyet %d\n", u);	//L�m g� d� tr�n u
		mark[u] = 1; 			//��nh d?u n� d� duy?t
		parent[u] = p; 			//��nh d?u n� d� duy?t			

		//3b. X�t c�c d?nh k? c?a u, dua v�o h�ng d?i Q
		for (int v = 1; v <= pG->n; v++)
			if (adjacent(pG, u, v)) {
				ElementType pair; 						
				pair.u = v; pair.p = u; 					
				enqueue(&Q, pair); 						
			}
	}
}



int main() {
	//1. Khai b�o d? th? G
	Graph G;
	//2. �?c d? li?u v� d?ng d? th?
	int n, m, u, v;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for (int e = 0; e < m; e++) {
	    scanf("%d%d", &u, &v);
	    add_edge(&G, u, v);
	}

	//3. Kh?i t?o m?ng mark[u] = 0, v?i m?i u = 1, 2, ..., n
	for (int u = 1; u <= G.n; u++) {
		mark[u] = 0;
	    parent[u] = -1;
	}

	//4. G?i h�m DFS
	for (int u = 1; u <= G.n; u++)
        if (mark[u] == 0)
            BFS(&G, u);
	

    for (int u = 1; u <= G.n; u++)
        printf("%d %d\n", u, parent[u]);

    
    return 0;
}


