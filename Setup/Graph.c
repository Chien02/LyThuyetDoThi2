# include <stdio.h>
 // Danh sach cung
#define MAX_M 50
    typedef struct {
        int u,v;
    } Edge;
    
    typedef struct {
        int n,m;
        Edge edges[MAX_M];
    } Graph;
    
    void init_graph(Graph *pG, int n) {
        pG->n = n;
        pG->m = 0;
    }
    
    void add_edge(Graph *pG, int u, int v) {
        if ((u<0 || u>pG->n) && (v<0 || v>pG->n)) {
            return;
        }
        pG->edges[pG->m].u = u;
        pG->edges[pG->m].v = v;
        pG->m++;
    }
    
    int adjacent(Graph *pG, int u, int v) {
        int i;
        for (i = 0; i<=pG->n; i++) {
            if ((pG->edges[i].u == u && pG->edges[i].v == v) ||
            (pG->edges[i].u == v && pG->edges[i].v == u)) {
                return 1;
            }
        }
        return 0;
    }
    
    int degree(Graph *pG, int u) {
        int i, count = 0;
        for (i=0; i<pG->m;i++) {
            if (pG->edges[i].v == u) {
        		count++;
			}
            if (pG->edges[i].u == u) {
                count++;
            }
        }
        return count;
    }
    
//    void neighbours(Graph* pG, int u) { // vo huong
//		int v;
//		for (v = 1; v <= pG->n; v++) {
//			if (adjacent(pG, u, v) != 0) {
//				printf("%d ", v);	
//			}
//		}
//		
//		printf("\n");
//	}
	
	typedef struct{
		int a[50];
		int size;
	} List;
	
    void neighbours(Graph* pG, int u) { // co huong
		int v, i, j;
		List _list;
		_list.size = 0;
		
		for (v = 0; v < pG->m; v++) {
			if (pG->edges[v].u == u) {
				_list.a[_list.size] = pG->edges[v].v;
				_list.size++; 
			}
		}
		
		if (_list.size > 0) {
			// Sort list
			for (i=0; i<_list.size; i++) {
				for (j=i; j<_list.size; j++) {
					if (_list.a[i] > _list.a[j]) {
						int temp = _list.a[i];
						_list.a[i] = _list.a[j];
						_list.a[j] = temp;
					}
				}
			}
			
			// Remove duplicate
			for (i=0; i<_list.size; i++) {
				while (_list.a[i]==_list.a[i+1]) {
					for (j=i+1; j<_list.size; j++) {
						_list.a[j] = _list.a[j+1];
					}
					_list.size--;
				}
			}
			
			// Print list
			for (i=0; i<_list.size; i++) {
				printf("%d ", _list.a[i]);
			}
		}
		
		printf("\n");
	}

	int main() {
//		freopen("dt.txt", "r", stdin);
	    Graph G;
	    int i,n,m;
	    
		scanf("%d%d", &n, &m);
		
	    //Khởi tạo đồ thị
	    init_graph(&G, n);
	    
	    for (i=0; i<m; i++) {
	    	int u, v;
	    	scanf("%d%d", &u, &v);
	    	add_edge(&G, u, v);
		}
		
	    for (i = 1; i <= n; i++) {
	    	printf("neighbours(%d) = ", i);
	        neighbours(&G, i);
		}
	        
	    return 0;
	}