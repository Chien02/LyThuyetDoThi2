#include <stdio.h>
#define MAX_VERTEXES 100
typedef struct {
	int A[100][100];
	int n;
} Graph;

/* Khoi tao do thi G co n dinh, m cung */
void init_graph(Graph* G, int n) {
int i, j;
G->n = n;
for (i = 1; i <= n; i++)
	for (j = 1; j <= n; j++)
		G->A[i][j] = 0;
}

/* Them cung e = (x, y) vao do thi G */
void add_edge(Graph* G, int x, int y) {
G->A[x][y] = 1; //x lien thuoc voi e
G->A[y][x] = 1; //y lien thuoc voi e
}

/* Kiem tra y co ke voi x khong */
int adjacent(Graph* G, int x, int y) {
	int e;
	for (e = 1; e <= G->n; e++)
		if (G->A[x][y] == 1 && G->A[y][x] == 1)
			return 1;
	return 0;
}

/* Tinh bac cua dinh x: deg(x) */
int degree(Graph* G, int x) {
int e, deg = 0;
for (e = 1; e <= G->n; e++)
if (G->A[x][e] == 1)
deg++;
return deg;
}

/* KHAI BAO VA DINH NGHIA CTDL DANH SACH */
#define MAX_ELEMENTS 100
typedef int ElementType;
typedef struct {
ElementType data[MAX_ELEMENTS];
int size;
} List;
/* Tao danh sach rong */
void make_null(List* L) {
L->size = 0;
}
/* Them mot phan tu vao cuoi danh sach */
void push_back(List* L, ElementType x) {
L->data[L->size] = x;
L->size++;
}
/* Lay phan tu tai vi tri i, phan tu bat dau o vi tri 1 
*/
ElementType element_at(List* L, int i) {
return L->data[i-1];
}
/* Tra ve so phan tu cua danh sach */
int count_list(List* L) {
return L->size;
}

/* Tim cac dinh ke cua dinh x */
List neighbors(Graph* G, int x) {
	int y;
	List list;
	make_null(&list);
	for (y = 1; y <= G->n; y++)
		if (adjacent(G, x, y)){
			push_back(&list, y);
		}
	return list;
}
/*****************************************/
/* Khai bao Stack*/
#define MAX_ELEMENTS 100
typedef struct {
	int data[MAX_ELEMENTS];
	int size;
} Stack;

void make_null_stack(Stack* S) {
	S->size = 0;
}

void s_push(Stack* S, int x) {
	S->data[S->size] = x;
	S->size++;
}

int s_top(Stack* S) {
	return S->data[S->size - 1];
}

void s_pop(Stack* S) {
	S->size--;
}

int s_empty(Stack* S) {
	return S->size == 0;
}
/* Duyet do thi theo chieu sau */
void depth_first_search(Graph* G, int x) {
	Stack frontier;
	int mark[MAX_VERTEXES];
	make_null_stack(&frontier);
	/* Khởi tạo mark, chưa đỉnh nào được xét */
	int j;
	for (j = 1; j <= G->n; j++)
		mark[j] = 0;
	/* Đưa 1 vào frontier */
	s_push(&frontier, x);
	mark[x] = 1;
	/* Vòng lặp chính dùng để duyệt */
	while (!s_empty(&frontier)) {
		/* Lấy phần tử đầu tiên trong frontier ra */
		int x = s_top(&frontier);
		s_pop(&frontier);
		printf("Duyet %d\n", x);
		/* Lấy các đỉnh kề của nó */
		List list = neighbors(G, x);
		/* Xét các đỉnh kề của nó */
		for (j = 1; j <= list.size; j++) {
			int y = element_at(&list, j);
			if (mark[y] == 0) {
				mark[y] = 1;
				s_push(&frontier, y);
			}
		}
	}
}

/* Khai bao Queue */
#define MAX_ELEMENTS 100
typedef struct {
int data[MAX_ELEMENTS];
	int front, rear;
} Queue;

void make_null_queue(Queue* Q) {
	Q->front = 0;
	Q->rear = -1;
}
void q_push(Queue* Q, int x) {
	Q->rear++;
	Q->data[Q->rear] = x;
}

int q_top(Queue* Q) {
	return Q->data[Q->front];
}

void q_pop(Queue* Q) {
	Q->front++;
}
int q_empty(Queue* Q) {
	return Q->front > Q->rear;
}

/* Duyệt đồ thị theo chiều rộng */
void breath_first_search(Graph* G) {
	Queue frontier;
	int mark[MAX_VERTEXES];
	make_null_queue(&frontier);
	/* Khởi tạo mark, chưa đỉnh nào được xét */
	int j;
	for (j = 1; j <= G->n; j++)
		mark[j] = 0;
	/* Đưa 1 vào frontier */
	q_push(&frontier, 1);
	mark[1] = 1;
	/* Vòng lặp chính dùng để duyệt */
	while (!q_empty(&frontier)) {
		/* Lấy phần tử đầu tiên trong frontier ra */
		int x = q_top(&frontier); q_pop(&frontier);
		printf("Duyet %d\n", x);
		/* Lấy các đỉnh kề của nó */
		List list = neighbors(G, x);
		/* Xét các đỉnh kề của nó */
		for (j = 1; j <= list.size; j++) {
			int y = element_at(&list, j);
			if (mark[y] == 0) {
				mark[y] = 1;
				q_push(&frontier, y);
			}
		}
	}
}



/* Biến hỗ trợ */
int mark[MAX_VERTEXES];
/* Duyệt đệ quy đỉnh x */
void traversal(Graph* G, int x) {
	/* Nếu đỉnh x đã duyệt, không làm gì cả */
	if (mark[x] == 1)
		return;
	/* Ngược lại, duyệt nó */
	printf("Duyet dinh %d\n", x);
	mark[x] = 1;
	/* Lấy các đỉnh kề của nó và duyệt các đỉnh kề */
	List list = neighbors(G, x);
	int j;
	for (j = 1; j <= list.size; j++) {
		int y = element_at(&list, j);
		traversal(G, y);
	}
}
/* Đếm số thành phần liên thông của đồ thị */
int count_connected_components(Graph* G) {
	/* Khởi tạo mark, chưa đỉnh nào được duyệt */
	int j;
	for (j = 1; j <= G->n; j++)
		mark[j] = 0;
	int cnt = 0;
	for (j = 1; j <= G->n; j++)
	/* Nếu đỉnh j chưa được duyệt, duyệt nó */
	if (mark[j] == 0) {
		traversal(G, j);
		cnt++;
	}
	return cnt;
}

void dfs(Graph* G, int x) {
	/* Khởi tạo mark, chưa đỉnh nào được xét */
	int j;
	for (j = 1; j <= G->n; j++)
		mark[j] = 0;
	traversal(G, x);
	for (j = 1; j <= G->n; j++) {
		if (mark[j] == 0) {
			traversal(G, j);
		}
	}
}

int main() {
	freopen("dothi.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
	Graph G;
	int n, m, u, v, w, x, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	
	dfs(&G, 1);
//	for (v = 1; v <= n; v++) {
//		
//		printf("\n");
//	}
//		
	return 0;
}