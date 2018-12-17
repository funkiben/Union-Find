#include <stdio.h>
#include <stdlib.h>
#include "uf.h"

typedef struct edge_ {
    int a;
    int b;
    int w;
    int mst;
} Edge;

// compares the edges in ascending order of weights
int compare_edges(const void* a, const void* b) {
    Edge edge_a = *((Edge*) a);
    Edge edge_b = *((Edge*) b);
    
    if (edge_a.w == edge_b.w) return 0;
    else if (edge_a.w < edge_b.w) return -1;
    else return 1;
}

// n = # of vertices, m = # of edges
// E gets sorted, and the edges in the MST are marked
void kruskals(int n, int m, Edge* E) {
    qsort(E, m, sizeof(Edge), compare_edges);
    
    UF* uf = uf_create(n);
    
    for (Edge* e = E; e < &E[m]; e++) {
        if (uf_find(uf, e->a) != uf_find(uf, e->b)) {
            uf_union(uf, e->a, e->b);
            e->mst = 1;
        } else {
            e->mst = 0;
        }
    }
    
    uf_free(uf);
}

// tests kruskals on the given graph
// makes sure kruskals gives a MST with the given weight, and the graph includes all vertices
// assumes the given graph is connected to begin with
void test_kruskals(int n, int m, int expected_mst_weight, Edge* E) {
    printf("Testing kruskals on graph with %d vertices and %d edges...\n", n, m);
    
    kruskals(n, m, E);
    
    int actual_mst_weight = 0;
    int mst_edges_count = 0;
    int mst_vertices[n];
    
    for (Edge* e = E; e < &E[m]; e++) {
        if (e->mst) {
            actual_mst_weight += e->w;
            mst_edges_count++;
            mst_vertices[e->a] = 1;
            mst_vertices[e->b] = 1;
        }
    }
    
    if (expected_mst_weight != actual_mst_weight) {
        printf("Expected MST weight of %d but got %d\n", expected_mst_weight, actual_mst_weight);
    }
    
    if (mst_edges_count != n - 1) {
        printf("MST does not have V-1=%d edges, instead has %d\n", n - 1, mst_edges_count);
    }

    for (int i = 0; i < n; i++) {
        if (!mst_vertices[i]) {
            printf("MST is missing vertex %d\n", i);
        }
    }
    
    printf("Finished\n");
}

int main() {
    
    Edge E[] = {
        {0, 2, 1},
        {0, 1, 2},
        {1, 2, 2},
        {1, 3, 1},
        {2, 3, 2},
        {2, 4, 3},
        {3, 4, 3},
        {4, 5, 1},
        {3, 5, 4}
    };
    
    test_kruskals(6, 9, 8, E);
    
}
