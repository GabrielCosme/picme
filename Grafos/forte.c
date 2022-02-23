#include "grafo.h"

static int pre[1000], post[1000];
static vertex pa[1000];
static int lo[1000];
static vertex stack[1000];
static int t, cnt, k;
static int cnt, cntt;
static vertex vv[1000];


#define min(A, B) (A) < (B) ? (A) : (B)

/* Esta função faz uma busca DFS no grafo G e calcula o lowest preorder number lo[] de cada vértice de G. Também calcula os vetores pre[], post[] e pa[] correspondentes à busca DFS. */
void GRAPHlo(Graph G){
   GRAPHdfs(G); // calcula pre[], post[] e pa[]
   vertex vv[1000];
   for (vertex v = 0; v < G->V; ++v)
      vv[post[v]] = v;
   // vv[0..V-1] é permutação em pós-ordem
   for (int i = 0; i < G->V; ++i) {
      vertex v = vv[i];
      lo[v] = pre[v];
      for (link a = G->adj[v]; a != NULL; a = a->next){
         vertex w = a->w;
         if (pre[w] < pre[v]) /*A*/ 
            lo[v] = min(lo[v], pre[w]);
         else /*B*/ if (pa[w] == v)
            lo[v] = min(lo[v], lo[w]);
      }
   }
}

bool GRAPHstrongT1(Graph G){ 
   GRAPHlo(G); // calcula pre[], pa[] e lo[]
   for (vertex v = 0; v < G->V; ++v){
      if (lo[v] == pre[v] && pa[v] != v)
         return false;
   }
   int roots = 0;
   for (vertex v = 0; v < G->V; ++v){
      if (pa[v] == v) ++roots;
      if (roots > 1) 
         return false;
   }
   return true;
}

int GRAPHstrongCompsT(Graph G, int *sc){
   for (vertex v = 0; v < G->V; ++v) 
      pre[v] = sc[v] = -1;
   t = cnt = k = 0;
   for (vertex v = 0; v < G->V; ++v) 
      if (pre[v] == -1)
         dfsRstrongCompsT(G, v, sc);
   return k;
}

static void dfsRstrongCompsT(Graph G, vertex v, int *sc)
{
   pre[v] = cnt++;
   stack[t++] = v; // A
   lo[v] = pre[v]; 
   for (link a = G->adj[v]; a != NULL; a = a->next){
      vertex w = a->w;
      if (pre[w] == -1) { // B
         dfsRstrongCompsT(G, w, sc); // calcula lo[w] // C
         lo[v] = min(lo[v], lo[w]); // D
      }
      else if (pre[w] < pre[v] && sc[w] == -1) { // E
         lo[v] = min(lo[v], pre[w]); // F
      } // G
   } // H
   if (lo[v] == pre[v]) { // v é uma cabeça
      vertex u; // I
      do { // J
         u = stack[--t]; 
         sc[u] = k;
      } while (u != v); // K
      k++;
   }
}

int GRAPHstrongCompsK(Graph G, int *sc) {
   // fase 1:
   Graph GR = GRAPHreverse(G);
   cnt = cntt = 0;
   vertex v; 
   for (v = 0; v < GR->V; ++v) pre[v] = -1;
   for (v = 0; v < GR->V; ++v) 
      if (pre[v] == -1)
         dfsR(GR, v); 
   for (v = 0; v < GR->V; ++v) 
      vv[post[v]] = v;
   // vv[0..V-1] é permutação de GR em pós-ordem

   // fase 2:
   for (v = 0; v < G->V; ++v) sc[v] = -1;
   int k = 0;
   for (int i = G->V-1; i >= 0; --i) {
      v = vv[i];
      if (sc[v] == -1) { // nova etapa
         dfsRstrongCompsK(G, v, sc, k);
         k++;
      }
   }
   GRAPHdestroy(GR);
   return k;
}

/* Constrói o reverso do grafo G. */
Graph GRAPHreverse(Graph G){
   Graph GR = GRAPHinit( G->V);
   for (vertex v = 0; v < G->V; ++v) 
      for (link a = G->adj[v]; a != NULL; a = a->next)
         GRAPHinsertArc(GR, a->w, v);
   return GR;
}

/* Armazena no vetor post[] uma numeração em pós-ordem do grafo GR. O vetor pre[] marca os vértices já descobertos. */
static void dfsR(Graph GR, vertex v){ 
   pre[v] = cnt++; 
   for (link a = GR->adj[v]; a != NULL; a = a->next)
      if (pre[a->w] == -1) 
         dfsR(GR, a->w); 
   post[v] = cntt++;
}

/* Atribui o rótulo k a todo vértice w ao alcance de v que ainda não foi rotulado. Os rótulos são armazenados no vetor sc[]. */
static void dfsRstrongCompsK(Graph G, vertex v, int *sc, int k){ 
   sc[v] = k;
   for (link a = G->adj[v]; a != NULL; a = a->next)
      if (sc[a->w] == -1) 
         dfsRstrongCompsK(G, a->w, sc, k);
}