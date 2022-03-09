#include <stdio.h>

void sscmax(int a[], int n){
    int i, c[n], r = 0, b, p[n], aux;

    for (int m = 0; m < n; m++){
        c[m] = 1;
        for (i = m - 1; i >= 0; i--){
           if (a[i] <= a[m] && c[i] + 1 > c[m]){
               c[m] = c[i] + 1;
               p[m] = i;
           }
        }
        if (c[m] > r){
            r = c[m];
            b = m;
        }
    }

    for (i = p[b]; c[b] != 1; i = aux){
        aux = p[i];
        p[i] = b;
        b = i;
    }

    //O array c tambem representa a CSSED minima, no qual cada valor representa uma subsequencia

    printf("seq:");
    for (i = b; c[i] != r; i = p[i]){
        printf(" %d", i);
    }
    printf(" %d\nsize: %d\n", i, r);
}

int main(){
    int n;
    scanf("%d", &n);

    int a[n];
    for (int i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }

    sscmax(a, n);

    return 0;
}