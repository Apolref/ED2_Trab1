#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"


long **Alocar_matriz(int m, int n){
    long **v;
    int i;
    if (m < 1 || n < 1) {
        printf ("** Erro: Parametro invalido **\n");
        return (NULL);
    }
    v = (long **) calloc (m, sizeof(long *));
    if (v == NULL) {
        printf ("** Erro: Memoria Insuficiente **");
        return (NULL);
    }
    for ( i = 0; i < m; i++ ) {
        v[i] = (long*) calloc (n, sizeof(long));
        if (v[i] == NULL) {
            printf ("** Erro: Memoria Insuficiente **");
            return (NULL);
        }
    }
    return (v);
}

long **Liberar_matriz (int m, int n, long **v) {
    int i;
    if (v == NULL) return (NULL);
    if (m < 1 || n < 1) {
        printf ("** Erro: Parametro invalido **\n");
        return (v);
    }
    for (i = 0; i < m; i++) {
        free (v[i]);
    }
    free (v);
    return (NULL);
}