#include <stdio.h>

void segmax(int a[], int n){
    int q, f, s[n], b[n];
    s[0] = a[0];
    b[0] = 0;

    for (q = 1; q < n; q++){
        s[q] = a[q];
        b[q] = q;
        if (s[q-1] >= 0){
            s[q] = s[q] + s[q-1];
            b[q] = b[q-1];
        }
    }

    int x = s[0];
    for (q = 1; q < n; q++){
        if (s[q] > x){
            x = s[q];
            f = q;
        }
    }

    printf("begin: %d\nend: %d\nsum: %d\n", b[f], f, x);
}

int main(){
    int n;
    scanf("%d", &n);

    int a[n];
    for (int i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }

    segmax(a, n);

    return 0;
}