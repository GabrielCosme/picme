#define vertex int

typedef struct node *link;
struct node {
   vertex w; 
   int c;
   int flow;
   int type;
   link twin; 
   link next;
};

struct graph {
   int V; 
   int A; 
   link *adj; 
};
typedef struct graph *Graph;

Graph GraphInit(int V);

void insertArc(Graph G, vertex v, vertex w, int c);

void GraphFree(Graph G);
