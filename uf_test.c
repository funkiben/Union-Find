#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "uf.h"

void test_correctness() {
    UF* s = uf_create(10);
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            assert(i == j || uf_find(s, i) != uf_find(s, j));
        }
    }
    
    uf_union(s, 1, 2);
    uf_union(s, 1, 2);
    
    uf_union(s, 2, 5);
    
    uf_union(s, 1, 9);
    
    uf_union(s, 9, 9);
    
    assert(uf_find(s, 1) == uf_find(s, 2));
    assert(uf_find(s, 1) == uf_find(s, 5));
    assert(uf_find(s, 1) == uf_find(s, 9));
    assert(uf_find(s, 2) == uf_find(s, 5));
    assert(uf_find(s, 2) == uf_find(s, 9));
    assert(uf_find(s, 5) == uf_find(s, 9));
    
    for (int i = 0; i < 10; i++) {
        if (i != 1 && i != 2 && i != 5 && i != 9) {
            for (int j = 0; j < 10; j++) {
                assert(i == j || uf_find(s, i) != uf_find(s, j));
            }
        }
    }
    
    uf_union(s, 1, 0);
    uf_union(s, 1, 3);
    uf_union(s, 2, 4);
    uf_union(s, 9, 8);
    uf_union(s, 9, 7);
    uf_union(s, 5, 6);
    uf_union(s, 1, 2);
    uf_union(s, 0, 0);
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            assert(uf_find(s, i) == uf_find(s, j));
        }
    }
    
    uf_free(s);
}

void stress_test() {
    srand(123);
    
    UF* s = uf_create(1000);
    
    for (int i = 0; i < 100000; i++) {
        uf_union(s, rand() % 1000, rand() % 1000);
    }
    
    for (int i = 0; i < 100000; i++) {
        uf_find(s, rand() % 1000);
    }
    
    uf_free(s);
}

int main() {
    
    test_correctness();
    
    stress_test();

    printf("All tests passed!\n");
    
    return 0;
}
