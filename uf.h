struct uf_;

typedef struct uf_ UF;

// creates a new union-find with n sets, each with the integers 0 to n-1 in them
UF* uf_create(int n);

// if two elements are in the same set, find will return the same integer for both
int uf_find(UF* s, int x);

// unions the set of the two elements together
void uf_union(UF* s, int x, int y);

// frees the union-find data structure
void uf_free(UF* s);
