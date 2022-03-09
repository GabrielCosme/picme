#include <stdio.h>
#include <stdbool.h>

#define max(x, y) x > y? x: y

int mochila(int p[], int v[], int c, int n) {
    int t[c+1][n+1], i, j;

    for (i = 0; i <= c; i++) {
        t[i][0] = 0;
    }

    for (j = 0; j <= n; j++) {
        t[0][j] = 0;
    }

    for (i = 1; i <= c; i++) {
        for (j = 0; j < n; j++) {
            if (p[j] > i) {
                t[i][j+1] = t[i][j];
            }
            else {
                t[i][j+1] = max(t[i][j], v[j] + t[i-p[j]][j]);
            }
            //printf("%d ", t[i][j+1]);
        }
            //printf("\n");
    }

    return t[c][n];
}

int main() {
    int n, c;
    scanf("%d %d", &c, &n);

    int p[n], v[n];
    for (int i = 0; i < n; i++){
        scanf("%d %d", &p[i], &v[i]);
    }

    printf("%d\n", mochila(p, v, c, n));

    return 0;
}