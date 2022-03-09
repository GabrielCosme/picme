#include <stdio.h>
#include <string.h>

#define max(x, y) x > y? x: y

int m, n, j, a[100], b[100], c[100][100];

int lcs(int i, int j) {
    if (i < 0 || j < 0) {
        return 0;
    }
    else if (c[i][j] != -1){
        return c[i][j];
    }
    else if (a[i] == b[j]) {
        return c[i][j] = lcs(i-1, j-1) + 1;
    }
    else {
        return c[i][j] = max(lcs(i, j-1), lcs(i-1, j));
    }
}

int main(){
    scanf("%d %d", &m, &n);

    for (int i = 0; m != 0 && n != 0; i++){
        for (j = 0; j < m; j++){
            scanf("%d", &a[j]);
        }

        for (j = 0; j < n; j++){
            scanf("%d", &b[j]);
        }

        memset(c, -1, 10000*sizeof(int));
        printf("Twin Towers #%d\nNumber of Tiles : %d\n\n", i+1, lcs(m-1, n-1));

        scanf("%d %d", &m, &n);
    }

    return 0;
}
