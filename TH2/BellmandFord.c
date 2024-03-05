#include <stdio.h>

#define MAXN 100
#define NO_EDGE 0
#define INFINITY 1000

	int mark[MAXN];
	int pi[MAXN];
	int p[MAXN];
	
	typedef struct {
		int u, v; // đỉnh đầu v, đỉnh cuối v
		int w; // trọng số w
	} Edge;
	typedef struct {
		int n, m; // n: đỉnh, m: cung
		Edge edges[1000]; // lưu các cung của đồ thị
	} Graph;
	
	void init_graph(Graph* G, int n) {
		G->n = n;
		G->m = 0;
	}
    	
    void add_edge(Graph* G, int u, int v, int w) {
		G->edges[G->m].u = u;
		G->edges[G->m].v = v;
		G->edges[G->m].w = w;
		G->m++;
	}
	
	void BellmanFord(Graph* G, int s) {
		int i, it, k;
		for (i = 1; i <= G->n; i++) {
			pi[i] = INFINITY;
		}
		pi[s] = 0;
		p[s] = -1; //trước đỉnh s không có đỉnh nào cả
		 
		// lặp n hoặc n-1 lần đều được
		for (it = 1; it < G->n; it++) {
	 	// Duyệt qua các cung và cập nhật (nếu thoả)
			for (k = 0; k < G->m; k++) {
				int u = G->edges[k].u;
				int v = G->edges[k].v;
				int w = G->edges[k].w;
				if (pi[u] + w < pi[v]) { 
					pi[v] = pi[u] + w;
					p[v] = u;
				}
			}
		}
		
//		for (i = 1; i <= G->n; i++)
// 			printf("pi[%d] = %d, p[%d] = %d\n", i, pi[i], i, p[i]);
		
//		int flag = 0; //bai 8
//		for (k = 0; k < G->m; k++) {
//			int u = G->edges[k].u;
//			int v = G->edges[k].v;
//			int w = G->edges[k].w;
//			if (pi[u] + w < pi[v]) { // negative cycle
//				flag = 1;
//			}
//		}
//		if (flag == 1) {
//			printf("YES");
//		}
//		else {
//			printf("NO");
//		}
	}
	
int main() {
	freopen("dt.txt", "r", stdin);
	Graph G;
	int n,m,u,v,w,e,s,i;
	scanf("%d%d", &n, &m);
	
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}
	
	BellmanFord(&G, s);
	

	return 0;
}