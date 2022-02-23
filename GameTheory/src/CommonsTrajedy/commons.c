#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int n, i, j = 0;
    srand(time(NULL));

    printf("Number of Players: ");
    scanf("%d", &n);

    double x[n], total, left, aux;

    for (i = 0; i < n; i++){
        printf("Band of player %d (-1 for random): ", i);
        scanf("%lf", &aux);
        x[i] = (aux < 0? (((double)rand() / RAND_MAX) / n): aux);
    }

    while (j >= -1){
        left = 1;
        for (i = 0; i < n; i++){
            left -= x[i];
        }

        printf("\nTotal Band: %.04lf = 1 - %.04lf\n\n", 1-left, left);
        puts(" i |  x[i]  | gain");

        total = 0;
        for (i = 0; i < n; i++){
            aux = x[i]*left;
            printf("%02d | %.04lf | %.04lf\n", i, x[i], aux);
            total += aux;
        }

        printf("Total Gain: %.04lf\n\nWhich player you want to change(-1 for all): ", total);
        scanf("%d", &j);
        if (j < -1) return 0;

        printf("Value to change(-1 for OPT, 2 for best choice): ");
        scanf("%lf", &aux);

        if (aux < 0) aux = ((double)1) / (2*n);

        if (j >= 0){
            if (aux > 1)
                aux = (left + x[j]) / 2;
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

    return 0;
}