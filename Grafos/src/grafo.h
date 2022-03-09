#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define vertex int

typedef struct graph{
    int V;
    int A;
    link *adj;
} *Graph;

typedef struct node *link;
struct node{
    vertex w;
    link *next;
};

static link NEWnode(vertex w, link next);

Graph GRAPHinit(int V);

void GRAPHinsertArc( Graph G, vertex v, vertex w);

void GRAPHremoveArc(Graph G, vertex v, vertex w);

int GRAPHindeg(Graph G, vertex x);