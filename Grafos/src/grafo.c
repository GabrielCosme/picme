#include "grafo.h"

static link NEWnode(vertex w, link next){
    link a = malloc(sizeof(struct node));
    a->w = w;
    a->next = next;
    return a;
}

Graph GRAPHinit(int V){
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = malloc(V * sizeof(link));
    for (vertex v = 0; v < V; v++){
        G->adj[v] = NULL;
    }
    return G;
}

void GRAPHinsertArc(Graph G, vertex v, vertex w){ 
    for (link a = G->adj[v]; a != NULL; a = a->next){
        if (a->w == w) return;
    }
    G->adj[v] = NEWnode(w, G->adj[v]);
    G->A++;
}

void GRAPHremoveArc(Graph G, vertex v, vertex w){
    link a, b;
    if (G->adj[v]->w == w){
        b = G->adj[v]->next;
        free(G->adj[v]);
        G->adj[v] = b;
        return;
    }
    for (a = G->adj[v]; a->next != NULL; a = a->next){
        b = a->next;
        if (b->w == w){
            a->next = b->next;
            free(b);
        }
    }
}

int GRAPHindeg(Graph G, vertex x){
    int cnt = 0;
    for (vertex v = 0; v < G->V; v++){
        for (link a = G->adj[v]; a != NULL; a = a->next){
            if (a->w == x){
                cnt++;
            }
        }
    }
    return cnt;
}