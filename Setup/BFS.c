# include <stdio.h>

# define MAX_ELEMENTS 100

	typedef struct {
		int data[MAX_ELEMENTS];
		int front, rear;
	} Queue;

	void make_null_queue(Queue* Q) {
		Q->front = 0;
		Q->rear = -1;
	}
	void push(Queue* Q, int x) {
		Q->rear++;
		Q->data[Q->rear] = x;
	}
	int top(Queue* Q) {
		return Q->data[Q->front];
	}
	void pop(Queue* Q) {
		Q->front++;
	}
	int empty(Queue* Q) {
		return Q->front > Q->rear;
	}
	
	/* Duyệt đồ thị theo chiều rộng */
	void breath_first_search(Graph* G) {
		Queue L;
		int mark[MAX_VERTEXES];
		make_null_queue(&L);
		/* Khởi tạo mark, chưa đỉnh nào được xét */
		int j;
		for (j = 1; j <= G->n; j++)
		mark[j] = 0;
		/* Đưa 1 vào frontier */
		push(&frontier, 1);
		/* Duyệt 1 */
		printf("Duyet 1\n");
		mark[1] = 1;
		/* Vòng lặp chính dùng để duyệt */
		while (!empty(&L)) {
			/* Lấy phần tử đầu tiên trong L ra */
			int x = top(&L); pop(&L);
			/* Lấy các đỉnh kề của nó */
			List list = neighbors(G, x);
			/* Xét các đỉnh kề của nó */
			for (j = 1; j <= list.size; j++) {
				int y = element_at(&list, j);
				if (marl[y] == 0) { // y chưa duyệt, duyệt nó
					printf("Duyet %d\n", y);
					mark[y] = 1; //Đánh dấu y đã duyệt
					push(&L, y); //Đưa vào hàng đợi để lát nữa xét
				}
			}
		}
	}

int main(){
	
	freopen("dt.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
	Graph G;
	int n, m, u, v, w, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	
	for (e = 0; e < m; e++) {
		printf()
	}
	return 0;
}