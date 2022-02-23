#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int n, i, j = 0;
    srand(time(NULL));

    printf("Number of Players: ");
    scanf("%d", &n);

    double x[n], total, falta = 0, aux;

    for (i = 0; i < n; i++){
        x[i] = ((double)rand() / RAND_MAX) / n;
    }

    while (j >= -1){
        falta = 1;
        for (i = 0; i < n; i++){
            falta -= x[i];
        }

        printf("\nTotal Band: %.04lf = 1 - %.04lf\n\n", 1-falta, falta);
        puts(" i |  x[i]  | gain");

        total = 0;
        for (i = 0; i < n; i++){
            aux = x[i]*falta;
            printf("%02d | %.04lf | %.04lf\n", i, x[i], aux);
            total += aux;
        }

        j++;
        if (j == 10)
            j = 0;
        if (j >= -1){
            aux = 2;
            if (aux < 0)
                aux = ((double)1) / (2*n);
            if (j >= 0){
                if (aux > 1)
                    aux = (falta + x[j]) / 2;
                x[j] = aux;
            }
            else{
                if (aux > 1)
                    aux = ((double)1) / (n + 1);
                for (i = 0; i < n; i++){
                    x[i] = aux;
                }
            }
        }
    }

    return 0;
}