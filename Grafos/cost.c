#include "grafo.h"
#include <limits.h>

#define UGraph Graph
#define UGRAPHinit GRAPHinit

#define INFINITY INT_MAX

/* Insere no grafo não-dirigido G uma aresta com pontas v e w e custo c. A função supõe que v e w são distintos, positivos e menores que G->V. Se o grafo já tem um arco v-w, a função não faz nada. */
void UGRAPHinsertEdge(Graph G, vertex v, vertex w, int c) { 
    if (G->adj[v][w] == INFINITY) {
        G->adj[v][w] = c; 
        G->adj[w][v] = c; 
        G->A += 2;
    }
}

void UGRAPHinsertEdge(Graph G, vertex v, vertex w, int c) { 
    for (link a = G->adj[v]; a != NULL; a = a->next) 
        if (a->w == w) return;
    G->adj[v] = NEWnode( w, G->adj[v], c);
    G->adj[w] = NEWnode( v, G->adj[w], c);
    G->A += 2;
}

/* Recebe um grafo não-dirigido conexo G com custos arbitrários nas arestas e calcula uma MST de G.
A função trata a MST como uma árvore radicada com raiz 0 e armazena a árvore no vetor de pais pa[0..V-1] alocado pelo usuário.*/
void UGRAPHmstP1(UGraph G, vertex *pa){ 
    bool tree[1000];
    int preco[1000];
    
    // inicialização:
    for (vertex v = 0; v < G->V; ++v)
        pa[v] = -1, tree[v] = false, preco[v] = INFINITY; 
    pa[0] = 0, tree[0] = true;

    for (link a = G->adj[0]; a != NULL; a = a->next)
        pa[a->w] = 0, preco[a->w] = a->c; 

    while (true) { 
        int min = INFINITY;
        vertex y; 
        for (vertex w = 0; w < G->V; ++w) {
            if (!tree[w] && preco[w] < min)
                min = preco[w], y = w;
        }
        if (min == INFINITY) break;
        // a aresta pa[y]-y é a mais barata da franja
        tree[y] = true;
        // atualização dos preços e ganchos:
        for (link a = G->adj[y]; a != NULL; a = a->next) {
            if (!tree[a->w] && a->c < preco[a->w]) {
                preco[a->w] = a->c;
                pa[a->w] = y;
            }
        }
    }
}

bool GRAPHcptBF(Graph G, vertex s, vertex *pa, int *dist)
{
    QUEUEinit(G->A);
    bool onqueue[1000];
    for (vertex u = 0; u < G->V; ++u)
        pa[u] = -1, dist[u] = INT_MAX, onqueue[u] = false;
    pa[s] = s, dist[s] = 0;
    QUEUEput(s);
    onqueue[s] = true;
    vertex V = G->V; // pseudovértice
    QUEUEput(V); // sentinela
    int k = 0;

    while (true) { 
        vertex v = QUEUEget();
        if (v < V) {
            for (link a = G->adj[v]; a != NULL; a = a->next) {
                if (dist[v] + a->c < dist[a->w]) {
                dist[a->w] = dist[v] + a->c; 
                pa[a->w] = v;
                if (onqueue[a->w] == false) {
                    QUEUEput(a->w);
                    onqueue[a->w] = true;
                }
                }
            }
        } else {
            if (QUEUEempty()) return true; // A
            if (++k >= G->V) return false; // B
            QUEUEput(V); // sentinela
            for (vertex u = 0; u < G->V; ++u) 
                onqueue[u] = false;
        }
    }
}

#define Dag Graph

void DAGcpt(Dag G, vertex *vv, vertex s, vertex *pa, int *dist) 
{
    for (vertex v = 0; v < G->V; ++v)
        pa[v] = -1, dist[v] = INT_MAX;

    pa[s] = s, dist[s] = 0;
    for (int j = 0; j < G->V; ++j) {
        vertex v = vv[j];
        if (dist[v] == INT_MAX) continue;
        for (link a = G->adj[v]; a != NULL; a = a->next) {
            if (dist[v] + a->c < dist[a->w]) {
                dist[a->w] = dist[v] + a->c; 
                pa[a->w] = v;
            }
        }
    }
}

void GRAPHcptD1( Graph G, vertex s, vertex *pa, int *dist){
    bool mature[1000];
    for (vertex v = 0; v < G->V; ++v)
        pa[v] = -1, mature[v] = false, dist[v] = INT_MAX;
    pa[s] = s, dist[s] = 0;

    while (true) {
        // escolha de y:
        int min = INT_MAX;
        vertex y;
        for (vertex z = 0; z < G->V; ++z) {
            if (mature[z]) continue;
            if (dist[z] < min) 
                min = dist[z], y = z;
        }
        if (min == INT_MAX) break;
        // atualização de dist[] e pa[]:
        for (link a = G->adj[y]; a != NULL; a = a->next) {
            if (mature[a->w]) continue;
            if (dist[y] + a->c < dist[a->w]) {
                dist[a->w] = dist[y] + a->c;
                pa[a->w] = y;
            }
        }
        mature[y] = true;
    }
}

static bool mark[1000];

/* Recebe um grafo G com custos positivos nos arcos e vértices s e t. Devolve o custo de um caminho simples de custo máximo de s a t. (Em particular, devolve 0 se s == t.) Se não existe caminho algum de s a t, devolve -1 (que representa infinito negativo). Cuidado! Esta função só é razoável para grafos muito pequenos. (O código foi inspirado no programa 17.12 de Sedgewick.) */
int GRAPHmaxCostPath(Graph G, vertex s, vertex t){
    for (vertex v = 0; v < G->V; ++v) 
        mark[v] = false;
    return dfsRmaxCostPath(G, s, t);
}

/* Esta função recebe um grafo G com custos positivos nos arcos, um conjunto de vértices marcados, e vértices não marcados v e t (possivelmente iguais). A função examina o conjunto, digamos C, de todos os caminhos simples de v a t que não têm vértices marcados. Se C é vazio, devolve -1. Senão, devolve o custo do caminho mais caro de C. (Em particular, devolve 0 se v == t.) A função não altera o conjunto de vértice marcados. */
static int dfsRmaxCostPath(Graph G, vertex v, vertex t){
    if (v == t) 
        return 0;
    mark[v] = true;
    int m = -1;
    for (link a = G->adj[v]; a != NULL; a = a->next){
        if (!mark[a->w]) {
            int mw = dfsRmaxCostPath(G, a->w, t);
            if (mw != -1 && a->c + mw > m) 
                m = a->c + mw;
        }
    }
    mark[v] = false; // atenção! backtrack
    return m;
}
