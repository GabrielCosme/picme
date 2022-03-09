#include "dfs.h"

void GRAPHdfs(Graph G){
    cnt = cntt = 0;
    for (vertex v = 0; v < G->V; ++v){
        pre[v] = -1;
    }
    for (vertex v = 0; v < G->V; ++v){
        if (pre[v] == -1){
            pa[v] = v;
            dfsR(G, v);
        }
    }
}

static void dfsR(Graph G, vertex v){
    pre[v] = cnt++;
    for (link a = G->adj[v]; a != NULL; a = a->next){
        if (pre[a->w] == -1){
            pa[a->w] = v;
            dfsR(G, a->w);
        }
    }
    post[v] = cntt++;
}

bool GRAPHcycle0(Graph G){
    GRAPHdfs(G);
    for (vertex v = 0; v < G->V; ++v){
        for (link a = G->adj[v]; a != NULL; a = a->next){
            vertex w = a->w;
            if (post[v] < post[w]){
                return true;
            }
        }
    }
    return false;
}

bool GRAPHcycle(Graph G){
    cnt = cntt = 0;
    for (vertex v = 0; v < G->V; ++v){
        pre[v] = post[v] = -1;
    }
    for (vertex v = 0; v < G->V; ++v){
        if (pre[v] == -1){
            if (dfsRhcy( G, v)) return true;
        }
    }
    return false;
}

static bool dfsRhcy(Graph G, vertex v){
    pre[v] = cnt++;
    for (link a = G->adj[v]; a != NULL; a = a->next){
        vertex w = a->w;
        if (pre[w] == -1){
            if (dfsRhcy(G, w)){
                return true;
            }
        }
        else{
            if (post[w] == -1){
                return true;
            }
        }
    }
    post[v] = cntt++;
    return false;
}