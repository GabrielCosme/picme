#include <stdio.h>

#define max(x, y) x > y? x: y

//Relacionado ao problema da subsequencia comum maxima

int lcs(int a[], int b[], int m, int n){
    int c[m+1][n+1];

    for (int i = 0; i <= m; i++){
        c[i][0] = 0;
    }

    for (int j = 0; j <= n; j++){
        c[0][j] = 0;
    }

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
        {
            if (a[i - 1] == b[j - 1])
                c[i][j] = c[i-1][j-1] + 1;
            else
                c[i][j] = max(c[i][j-1], c[i-1][j]);
        }

    return c[m][n];
}

int main(){
    int m, n, j, a[101], b[101];
    
    scanf("%d %d", &m, &n);
    for (int i = 0; m != 0 && n != 0; i++){
        for (j = 0; j < m; j++){
            scanf("%d", &a[j]);
        }

        for (j = 0; j < n; j++){
            scanf("%d", &b[j]);
        }

        printf("Twin Towers #%d\nNumber of Tiles : %d\n\n", i+1, lcs(a, b, m, n));

        scanf("%d %d", &m, &n);
    }

    return 0;
}