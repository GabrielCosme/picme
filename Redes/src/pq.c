#include "pq.h"
#include <stdlib.h>

#define smaller(i, j) (prty[pq[i]] < prty[pq[j]]? 1: 0)

static vertex *pq; 
static int N;
static int *qp; 

static void exch(int i, int j) {
    vertex t;
    t = pq[i]; pq[i] = pq[j]; pq[j] = t;
    qp[pq[i]] = i;
    qp[pq[j]] = j;
}

static void fixUp(int k, int prty[]) {
    while (k > 1 && smaller(k/2, k)) {
        exch(k/2, k);
        k = k/2;
    }
}

static void fixDown(int k, int prty[]) { 
    int j;
    while (2*k <= N) { 
        j = 2*k;
        if (j < N && smaller(j, j+1)) j++;
        if (!smaller(k, j)) break;
        exch(k, j); 
        k = j;
    }
}

void PQinit(int maxN) { 
    pq = malloc((maxN+1) * sizeof(vertex));
    qp = malloc(maxN * sizeof(int));
    N = 0; 
}

int PQempty(void) { 
    return N == 0; 
}

void PQinsert(vertex v, int prty[]) {
    qp[v] = ++N;
    pq[N] = v;
    fixUp(N, prty); 
}

vertex PQdelmax(int prty[]) { 
    exch(1, N); 
    --N; 
    fixDown(1, prty); 
    return pq[N+1]; 
}

void PQinc(vertex w, int prty[]) { 
    fixUp(qp[w], prty); 
}

void PQfree() { 
    free(pq);
    free(qp);
}
