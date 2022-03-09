#include "topo.h"

bool isTopoNumbering(Graph G, int topo[]){
    for (vertex v = 0; v < G->V; v++){
        for (link a = G->adj[v]; a != NULL; a = a->next){
            if (topo[v] >= topo[a->w]){
                return false;
            }
        }
    }
    return true;
}

bool topol(Graph G){
    vertex v;
    for (v = 0; v < G->V; v++){
        topo[v] = -1;
    }
    int cnt = 0;
    while (cnt < G->V){
        for (v = 0; v < G->V; v++){
            if (GRAPHindeg(G, v) == 0 && topo[v] == -1){
                break;
            }
        }
        if (v >= G->V){
            return false;
        }
        topo[v] = cnt++;
        for (link a = G->adj[v]; a != NULL; a = a->next){
            GRAPHremoveArc(G, v, a->w);
        }
    }
    return true;
}

bool GRAPHtopol(Graph G){
    int indeg[1000];
    for (vertex v = 0; v < G->V; v++){
        indeg[v] = 0;
    }
    for (vertex v = 0; v < G->V; v++){
        for (link a = G->adj[v]; a != NULL; a = a->next){
            indeg[a->w] += 1;
        }
    }
    vertex fila[1000];
    int comeco = 0, fim = 0;
    for (vertex v = 0; v < G->V; v++){
        if (indeg[v] == 0){
            fila[fim++] = v;
        }
    }
    int cnt = 0;
    while (comeco < fim){
        vertex v = fila[comeco++];
        topo[v] = cnt++;
        for (link a = G->adj[v]; a != NULL; a = a->next){
            indeg[a->w] -= 1;
            if (indeg[a->w] == 0){
                fila[fim++] = a->w;
            }
        }
    }
    return cnt >= G->V;
}
