#include <stdio.h>

#define MAXN 100
#define NO_EDGE 0
#define INFINITY 1000

	int mark[MAXN][MAXN];
	int pi[MAXN][MAXN];
	int p[MAXN][MAXN];
	
	typedef struct {
		int m,n;
		int L[MAXN][MAXN];
	} Graph;
	
	void init_graph(Graph* G, int m, int n) {
		G->m = m;
		G->n = n;
		int i, j;
		for (i = 1; i <= m; i++)
			for (j = 1; j <= n; j++)
				G->L[i][j] = NO_EDGE;
	}
    	
    void add_edge(Graph *pG, int u, int v, int w) {
        pG->L[u][v] = w;
        pG->L[v][u] = w;
    }
	
	void Dijkstra(Graph* G, int s1, int s2) {
		
		int u, v, ii, jj, i, j, it, k;
		
		// Initial
		for (i = 1; i <= G->m; i++) {
			for (j = 1; j <= G->n; j++) {
				pi[i][j] = INFINITY;
				mark[i][j] = 0;
			}	
		}
		
		pi[s1][s2] = 0;
		p[s1][s2] = -1; //trước đỉnh s không có đỉnh nào cả
	 
		// lặp n hoặc n-1 lần đều được
		for (it = 1; it < G->n; it++) {
			 //1. Tìm i có mark[i] == 0 va có pi[i] nhỏ nhất
			int min_pi = INFINITY;
			for (i = 1; i <= G->m; i++)
				for (j = 1; j <= G->n; j++)
					if (mark[i][j] == 0 && pi[i][j] < min_pi) {
						min_pi = pi[i][j];
						u = i;
						v = j;
					}
		 //Đánh dấu i đã xét
		mark[u][v] = 1;
		 //2. Cập nhật pi và p của các đỉnh kề của i (nếu thoả)
		int di[] = {-1, 1, 0, 0};
		int dj[] = { 0, 0, -1, 1};
		//Duyệt qua các ô kề của ô (i, j)
		for (k = 0; k < 4; k++) {
			ii = u + di[k];
			jj = v + dj[k];
			//Kiểm tra ô (ii,jj) có nằm trong mê cung không
			if (ii >= 0 && ii < G->m && jj >= 0 && jj < G->n) {
				if (pi[u][v] + G->L[u][v] < pi[ii][jj]) {
					pi[ii][jj] = pi[u][v] + G->L[u][v];
//					p[ii][jj] = ;
			 	}
			}
		}
		for (i = 1; i <= G->m; i++)
		for (j = 1; j<=G->n; j++) {
			if (pi[i][j] == INFINITY) {
				pi[i][j] = -1;
			}
		}
	}
}

int main() {
	freopen("dt.txt", "r", stdin);
	Graph G;
	int n,m,u,v,w,e;
	scanf("%d%d", &m, &n);
	
	init_graph(&G, m, n);
	
	for (e = 0; e < m*n; e++) {
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}
	
	Dijkstra(&G, 1, 1);
	printf("%d", pi[m][n]);
	return 0;
}