#include "grafo.h"

#define UGraph Graph

int UGRAPHconComps(UGraph G);

static void dfsRconComps(UGraph G, vertex v, int id);

bool UGRAPHcircuit0(UGraph G);

bool UGRAPHcircuit(UGraph G);

static bool dfsRcircuit(UGraph G, vertex v);

void UGRAPHlo(UGraph G);

bool UGRAPHebicon3(UGraph G);
