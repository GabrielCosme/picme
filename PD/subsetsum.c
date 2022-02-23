#include <stdio.h>
#include <stdbool.h>

bool subsetsum(int a[], int n, int c){
    int i, j, aux;
    bool t[n+1][c+1];

    for (i = 0; i <= n; i++){
        t[i][0] = true;
    }
    
    for (j = 1; j <= c; j++){
        t[0][j] = false;
        for (i = 1; i <= n; i++){
            aux = t[i-1][j];
            if (aux == false && a[i-1] <= j){
                aux = t[i-1][j-a[i-1]];
            }
            t[i][j] = aux;
        }
    }

    if (t[n][c] == true){
        j = c;
        for (i = n; i > 0; i--){
            if (t[i-1][j] == false){
                printf("%d ", i-1);
                j -= a[i-1];
            }
        }
    }

    return t[n][c];
}

int main(){
    int n, c;
    scanf("%d %d", &n, &c);

    int a[n];
    for (int i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }

    printf(subsetsum(a, n, c)? "True\n": "False\n");

    return 0;
}