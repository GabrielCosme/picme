#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int w, c;
} Turtle;

int comp(const void* a, const void* b) {
    return ((Turtle *)a)->c - ((Turtle *)b)->c;
}

int turtles(int n, Turtle t[]) {
    int a[5608];    //a[j] armazena o menor peso de uma pilha válida com j tartarugas
    int i, j;

    a[0] = 0;
    for (i = 0; i < n; i++) {
        //a[j] só considera as tartarugas de 0 a i-1
        a[i+1] = __INT_MAX__;
        for (j = i; j >= 0; j--) {
            if (a[j] <= t[i].c - t[i].w && a[j] + t[i].w < a[j+1]) {
                a[j+1] = a[j] + t[i].w;
            }
            printf("%d ", a[j+1]);
        }
        printf("%d\n", a[0]);
    }

	while (a[n] == __INT_MAX__) {
        n--;
    }
    return n;
}

int main() {
    int n = 0;
    Turtle t[5607];

	while (scanf("%d%d", &t[n].w, &t[n].c) == 2) {
		n++;
    }

    //Uma tartaruga de capacidade menor nunca vai estar carregando uma de capacidade maior
    qsort(t, n, sizeof(Turtle), comp);

    printf("%d\n", turtles(n, t));

    return 0;
}
