#include "grafo.h"

#define UGraph Graph

int color[1000];
bool cover[1000];
static vertex pa[1000];

int UGRAPHseqColoring(UGraph G, int *color){ 
   int k = 0;
   for (vertex v = 0; v < G->V; ++v) color[v] = -1;

   for (vertex v = 0; v < G->V; ++v){
      bool available[100];
      int c; 
      for (c = 0; c < k; ++c) available[c] = true;
      for (link a = G->adj[v]; a != NULL; a = a->next){
         if (color[a->w] != -1)
            available[color[a->w]] = false;
      } // A
      c = 0;
      while (c < k && !available[c]) ++c;
      if (c < k) color[v] = c;
      else color[v] = k++;
   }
   return k;
}


int UGRAPHtwoColor(UGraph G){
    int w;
    for (vertex v = 0; v < G->V; ++v) 
        color[v] = -1;
    for (vertex v = 0; v < G->V; ++v)
        if (color[v] == -1) // começa nova etapa
            if ((w = dfsRtwoColor(G, v, 0)) >= 0) 
                return w;
    return -1;
}

static int dfsRtwoColor(UGraph G, vertex v, int c){ 
    color[v] = c;
    for (link a = G->adj[v]; a != NULL; a = a->next) {
        vertex w = a->w;
        if (color[w] == -1) {
            pa[w] = a;
            if (dfsRtwoColor(G, w, 1-c) >= 0) 
                return w; 
        }
        else { // v-w é de avanço ou de retorno
            if (color[w] == c) // base da recursão
                pa[w] = a;
                return w;
        }
    }
    return -1;
}

static void newMatching(vertex *match, vertex t){ 
   vertex x;
   do{
      x = pa[t];
      match[t] = x;
      match[x] = t;
      t = pa[x]; 
   } while (t != x);
}

static bool visited[1000];

int UGRAPHbipMatching(UGraph G, int *color, vertex *match){ 
    for (vertex v = 0; v < G->V; ++v) match[v] = -1;
    int size = 0, sizec = 0;
    while (augmentMatching(G, color, match))
    size++;
    for (vertex v = 0; v < G->V; ++v) 
    if (color[v] == 1 && visited[v] || color[v] == 0 && !visited[v]){
        cover[v] = true;
        sizec++;
    }
    else cover[v] = false;
    if (size != sizec){
        printf("Erro no bipMatching\n");
    }
    return size;
}

static bool augmentMatching(UGraph G, int *color, vertex *match){ 
   for (vertex v = 0; v < G->V; ++v) visited[v] = false;
   QUEUEinit( G->V);
   for (vertex s = 0; s < G->V; ++s){
      if (color[s] == 0 && match[s] == -1){
         visited[s] = true; 
         pa[s] = s;
         QUEUEput(s); 
      }
   } 
   // a fila contém todos os vértices solteiros de cor 0

   while (!QUEUEempty()){ 
      // color[v] == 0 para todo v na fila
      vertex v = QUEUEget();
      for (link a = G->adj[v]; a != NULL; a = a->next){
         vertex w = a->w; // color[w] == 1
         if (!visited[w]) { 
            visited[w] = true; 
            pa[w] = v; 
            if (match[w] == -1){ // caminho aumentador!
               newMatching(match, w);
               QUEUEfree();
               return true;
            }
            vertex x = match[w]; // visited[x] == false
            visited[x] = true;
            pa[x] = w; // caminho ganhou segmento v-w-x
            QUEUEput(x); 
         }
      }
   }

   QUEUEfree();
   return false;
}
