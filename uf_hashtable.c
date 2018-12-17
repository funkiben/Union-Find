#include "uf.h"
#include <stdlib.h>

#define NODES_HASHTABLE_SIZE 200

typedef struct node_ {
    int val;
    int rank;
    struct node_* parent;
    struct node_* next; // used for hash conflicts
} Node;

struct uf_ {
    Node** nodes;
};

// gets the node of the given element
Node* get_node(UF* s, int x) {
    Node* node = s->nodes[x % NODES_HASHTABLE_SIZE];
    
    while (node != NULL && node->val != x) {
        node = node->next;
    }
    
    return node;
}

// creates a new node for the given element
// the new node is disjoint from all other unions
void create_node(UF* s, int x) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->val = x;
    new_node->rank = 0;
    new_node->parent = new_node;
    new_node->next = s->nodes[x % NODES_HASHTABLE_SIZE];
    
    s->nodes[x % NODES_HASHTABLE_SIZE] = new_node;
}

UF* uf_create(int n) {
    UF* s = (UF*) malloc(sizeof(UF));
    s->nodes = (Node**) malloc(sizeof(Node*) * NODES_HASHTABLE_SIZE);
    
    for (int i = 0; i < NODES_HASHTABLE_SIZE; i++) {
        s->nodes[i] = NULL;
    }
    
    for (int i = 0; i < n; i++) {
        create_node(s, i);
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
    return find_and_compress(s, get_node(s, x))->val;
}

void uf_union(UF* s, int x, int y) {
    Node* rx = find_and_compress(s, get_node(s, x));
    Node* ry = find_and_compress(s, get_node(s, y));
    
    if (rx == ry) {
        return;
    }
    
    if (rx->rank > ry->rank) {
        ry->parent = rx;
    } else {
        rx->parent = ry;
        if (rx->rank == ry->rank) {
            ry->rank++;
        }
    }
}

void uf_free(UF* s) {
    Node* node;
    Node* temp;
    for (int i = 0; i < NODES_HASHTABLE_SIZE; i++) {
        node = s->nodes[i];
        while (node != NULL) {
            temp = node->next;
            free(node);
            node = temp;
        }
    }
    free(s->nodes);
    free(s);
}
