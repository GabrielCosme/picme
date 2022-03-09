#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "graph.h"
#include "queue.h"
#include "pq.h"

#define M 1000000
#define AugmPath MaxCapAugmPath
#define min(a,b) (((a) < (b))? (a): (b))

vertex pa[2000000]; // parent vertex
link parc[2000000]; // parent arc

bool visited[2000000]; 

int ShrtAugmPath(Graph G, vertex s, vertex t, vertex pa[], link parc[]) { 
    for (vertex v = 0; v < G->V; v++) visited[v] = false; 
    QUEUEinit(G->V); 
    visited[s] = true;
    QUEUEput(s); 

    while (!QUEUEempty()) {
        vertex v = QUEUEget();
        if (v == t) break;
        for (link a = G->adj[v]; a != NULL; a = a->next) {
            // a pode ser original ou artificial
            int residual = a->c - a->flow;
            if (residual > 0 && !visited[a->w]) {
                visited[a->w] = true;
                pa[a->w] = v; parc[a->w] = a; 
                QUEUEput(a->w); 
            }
        }
    }

    if (!visited[t]) return 0; 
    int delta = M;
    for (vertex w = t; w != s; w = pa[w]) { 
        link a = parc[w]; 
        delta = min(delta, a->c - a->flow);
    }
    QUEUEfree();
    return delta;
}

int MaxCapAugmPath(Graph G, vertex s, vertex t, vertex pa[], link parc[]) {
    int *cprd;
    cprd = malloc(G->V * sizeof(int));
    if (cprd == NULL) {
        printf("Acabou a memoria :(\n");
    }
    PQinit(G->V); 
    for (vertex x = 0; x < G->V; ++x) {
        cprd[x] = 0;
        PQinsert(x, cprd); 
    }
    cprd[s] = M; 
    PQinc(s, cprd); 

    while (!PQempty()) {
        vertex x = PQdelmax(cprd);
        if (cprd[x] == 0 || x == t) break;
        for (link a = G->adj[x]; a != NULL; a = a->next) {
            int residual = min(cprd[x], a->c - a->flow);
            if (residual > cprd[a->w]) { 
                cprd[a->w] = residual; 
                pa[a->w] = x, parc[a->w] = a; 
                PQinc(a->w, cprd); 
            }
        }
    }
    PQfree();
    return cprd[t];
}

int maxFlow(Graph G, vertex s, vertex t) {
    int count = 0;

    int intensity = 0;
    while (true) {
        count++;
        int delta = AugmPath(G, s, t, pa, parc);
        // delta = cap residual de caminho aumentador
        if (delta == 0) break;
        for (vertex w = t; w != s; w = pa[w]) { 
            link a = parc[w]; 
            a->flow += delta; 
            a->twin->flow -= delta; 
        }
        intensity += delta;
    }
    printf("%d\n", count);

    return intensity;
}

int main() {
    int v, w, c, N, ar;
    double aux;

    scanf("%d %d", &N, &ar);
    Graph G = GraphInit(N);

    for (int i = 0; i < ar; i++) {
        scanf("%d %d %lf", &v ,&w, &aux);
        c = (int)(aux * 100000000.0);
        insertArc(G, v, w, c);
    }

    printf("%d\n", maxFlow(G, 0, N-1));

    GraphFree(G);

    return 0;
}
