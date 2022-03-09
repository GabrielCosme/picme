#define vertex int

void PQinit(int maxN);

int PQempty(void);

void PQinsert(vertex v, int prty[]);

vertex PQdelmax(int prty[]);

void PQinc(vertex w, int prty[]);

void PQfree();
