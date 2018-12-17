#include "uf.h"
#include <stdlib.h>

typedef struct node_ {
    int val;
    int rank;
    struct node_* parent;
} Node;

struct uf_ {
    Node* nodes;
};

UF* uf_create(int n) {
    UF* s = (UF*) malloc(sizeof(UF));
    s->nodes = (Node*) malloc(sizeof(Node) * n);
    
    for (int i = 0; i < n; i++) {
        s->nodes[i].val = i;
        s->nodes[i].rank = 0;
        s->nodes[i].parent = &s->nodes[i];
    }
    
    return s;
}

// finds the root of the given node, and then sets its parent to be its root once its found
Node* find_and_compress(UF* s, Node* node) {
    if (node != node->parent) {
        node->parent = find_and_compress(s, node->parent);
    }
    return node->parent;
}

int uf_find(UF* s, int x) {
    return find_and_compress(s, &s->nodes[x])->val;
}

void uf_union(UF* s, int x, int y) {
    Node* rx = find_and_compress(s, &s->nodes[x]);
    Node* ry = find_and_compress(s, &s->nodes[y]);
    
    if (rx == ry) {
        return;
    }
    
    if (rx->rank > ry->rank) {
        ry->parent = rx;
    } else {
        rx->parent = ry;
        if (rx->rank == ry->rank) ry->rank++;
    }
}

void uf_free(UF* s) {
    free(s->nodes);
    free(s);
}
