#include "conexo.h"
#include "dfs.h"

#define min(A, B) (A) < (B) ? (A) : (B);

int cc[1000];
static int lo[1000];
static int pre[1000], post[1000];
static int cnt, cntt;
static vertex pa[1000];
int ebc[1000];

int UGRAPHconComps(UGraph G){
    int id = 0;
    for (vertex v = 0; v < G->V; v++){
        cc[v] = -1;
    }
    for (vertex v = 0; v < G->V; v++){
        if (cc[v] == -1){
            dfsRconComps(G, v, id++);
        }
    }
    return id;
}

static void dfsRconComps(UGraph G, vertex v, int id){
    cc[v] = id;
    for (link a = G->adj[v]; a != NULL; a = a->next){
        if (cc[a->w] == -1){
            dfsRconComps(G, a->w, id);
        }
    }
}

bool UGRAPHcircuit0(UGraph G){
    GRAPHdfs(G);

    for (vertex v = 0; v < G->V; v++){
        for (link a = G->adj[v]; a != NULL; a = a->next){
            vertex w = a->w;
            if (pre[w] < pre[v]){
                if (w != pa[v]){
                    return true;
                }
            }
        }
    } 
    return false;
}

bool UGRAPHcircuit(UGraph G){
    cnt = 0;
    for (vertex v = 0; v < G->V; v++){
        pre[v] = -1;
    }
    for (vertex v = 0; v < G->V; v++){
        if (pre[v] == -1){
            pa[v] = v;
            if (dfsRcircuit(G, v)){
                return true;
            }
        }
    }
    return false;
}

static bool dfsRcircuit(UGraph G, vertex v){ 
    pre[v] = cnt++;
    for (link a = G->adj[v]; a != NULL; a = a->next){
        vertex w = a->w;
        if (pre[w] == -1){
            pa[w] = v; 
            if (dfsRcircuit(G, w)){
                return true;
            }
        }
        else{
            if (w != pa[v]){
                return true;
            }
        }
    }
    return false;
}

void UGRAPHlo(UGraph G){
    GRAPHdfs(G);
    vertex vv[1000];
    for (vertex v = 0; v < G->V; v++){
        vv[post[v]] = v;
    }
    for (int i = 0; i < G->V; i++){
        vertex v = vv[i];
        lo[v] = pre[v];
        for (link a = G->adj[v]; a != NULL; a = a->next){
            vertex w = a->w;
            if (pre[w] < pre[v]){
                if (w != pa[v]){
                    lo[v] = min(lo[v], pre[w]);
                }
            }
            else{
                if (pa[w] == v){
                    lo[v] = min(lo[v], lo[w]);
                }
            }
        }
    }
}

bool UGRAPHebicon3(UGraph G){ 
    UGRAPHlo(G);
    int roots = 0;
    for (vertex v = 0; v < G->V; v++){
        if (pa[v] == v){
            roots++;
        }
        if (roots > 1){
            return false;
        }
    }
    for (vertex v = 0; v < G->V; v++){
        if (lo[v] == pre[v] && pa[v] != v){
            return false;
        }
    }
    return true;
}

/* A função UGRAPHebiconComps3() devolve o número (quantidade) de componentes aresta-biconexas do grafo não-dirigido G e armazena no vetor ebc[] uma numeração dos vértices dotada da seguinte propriedade: ebc[v] == ebc[w] se e somente se v e w estão na mesma componente. */
int UGRAPHebiconComps3(UGraph G){
    UGRAPHlo(G); // calcula lo[]
    // também calcula pre[], post[] e pa[]
    for (vertex v = 0; v < G->V; ++v)
        ebc[v] = -1;
    vertex vv[1000];
    for (vertex v = 0; v < G->V; ++v)
        vv[post[v]] = v;
    // vv[0..V-1] é permutação em pós-ordem
    int id = 0;
    for (int j = 0; j < G->V; ++j){ 
        vertex v = vv[j];
        if (lo[v] == pre[v]) // ebc[v] == -1
            // v é cabeça de componente
            ebiconCompR(G, v, id++); 
    } 
    return id;
}

/* Esta função faz ebc[x] = id para todo vértice x que seja descendente de v na floresta radicada representada por pa[] e tenha ebc[x] == -1. */
static void ebiconCompR(UGraph G, vertex v, int id){ 
    ebc[v] = id; 
    for (link a = G->adj[v]; a != NULL; a = a->next){
        vertex w = a->w;
        if (pa[w] == v && ebc[w] == -1)
            ebiconCompR(G, w, id); 
   }
}
