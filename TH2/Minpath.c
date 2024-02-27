#include <stdio.h>

#define MAXN 100
#define NO_EDGE 0
#define INFINITY 1000

	int mark[MAXN];
	int pi[MAXN];
	int p[MAXN];
	
	typedef struct {
		int n;
		int L[MAXN][MAXN];
	} Graph;
	
	void init_graph(Graph* G, int n) {
		G->n = n;
		int i, j;
		for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
		G->L[i][j] = NO_EDGE;
	}
    	
    void add_edge(Graph *pG, int u, int v, int w) {
        pG->L[u][v] = w;
        pG->L[v][u] = w;
    }
	
	void Dijkstra(Graph* G, int s, int t) {
		int i, j, it;
		for (i = 1; i <= G->n; i++) {
			pi[i] = INFINITY;
			mark[i] = 0;
		}
		
		pi[s] = 0;
		p[s] = -1; //trước đỉnh s không có đỉnh nào cả
	 
		// lặp n hoặc n-1 lần đều được
		for (it = 1; it < G->n; it++) {
			 //1. Tìm i có mark[i] == 0 va có pi[i] nhỏ nhất
			int min_pi = INFINITY;
			for (j = 1; j <= G->n; j++)
				if (mark[j] == 0 && pi[j] < min_pi) {
					min_pi = pi[j];
					i = j;
				}
		 //Đánh dấu i đã xét
		mark[i] = 1;
		 //2. Cập nhật pi và p của các đỉnh kề của i (nếu thoả)
		for (j = 1; j <= G->n; j++)
			if (G->L[i][j] != NO_EDGE && mark[j] == 0) {
				if (pi[i] + G->L[i][j] < pi[j]) {
					pi[j] = pi[i] + G->L[i][j];
					p[j] = i;
			 	}
			}
		}
		for (j = 1; j<=G->n; j++) {
			if (pi[j] == INFINITY) {
				pi[j] = -1;
			}
		}
	}
	
	void check_negative(Graph *pG){
		int u, v;
		for (u=1; u<=pG->n; u++)
			for (v=1; v<=pG->n; v++) {
				if (pG->L[u][v] != INFINITY) {
					if (pG->L[u][v] < 0) {
						printf("negative cycle");
						return;
					}
				}
			}
		printf("ok");
	}
int main() {
	freopen("dt.txt", "r", stdin);
	Graph G;
	int n,m,u,v,w,e,s,t;
	scanf("%d%d", &n, &m);
	
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}
	
	scanf("%d%d", &s, &t);
	
	
	Dijkstra(&G, s, t);
//	check_negative(&G);
	printf("%d ",pi[t]);
	return 0;
}