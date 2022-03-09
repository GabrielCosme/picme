#include <stdlib.h>
#include "queue.h"

static vertex *queue; 
static int begin, end;

void QUEUEinit(int N) { 
    queue = malloc(N * sizeof(vertex));
    begin = end = 0; 
}

int QUEUEempty(void) { 
    return begin == end; 
}

void QUEUEput(vertex v) {
    queue[end++] = v;
}

vertex QUEUEget(void) { 
    return queue[begin++];
}

void QUEUEfree(void) {
    free(queue);
}
