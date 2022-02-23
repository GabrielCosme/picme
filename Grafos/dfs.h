#include "grafo.h"

static int cnt, pre[1000];
static int cntt, post[1000];
static vertex pa[1000];

void GRAPHdfs(Graph G);

static void dfsR(Graph G, vertex v);

bool GRAPHcycle0(Graph G);

bool GRAPHcycle(Graph G);

static bool dfsRhcy(Graph G, vertex v);