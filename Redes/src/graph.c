#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

Graph GraphInit(int V) {
    Graph G = malloc(sizeof(struct graph));
    G->V = V;
    G->A = 0;

    G->adj = malloc(V * sizeof(link));
    for (vertex v = 0; v < V; v++) 
        G->adj[v] = NULL;

    return G;
}

void insertArc(Graph G, vertex v, vertex w, int c) {
    G->A++;

    link a = malloc(sizeof(struct node));
    link b = malloc(sizeof(struct node));

    a->w = w;
    b->w = v;

    a->twin = b;
    b->twin = a;

    a->next = G->adj[v];
    G->adj[v] = a;

    b->next = G->adj[w];
    G->adj[w] = b;

    a->type = +1;
    b->type = -1;

    a->c = c;
    b->c = 0;

    a->flow = 0;
    b->flow = 0;
}

void GraphFree(Graph G) {
    for (vertex v = 0; v < G->V; v++) {
        if (G->adj[v] != NULL) {
            free(G->adj[v]);
            G->adj[v] = NULL;
        }
    }

    free(G->adj);
    free(G);
}
