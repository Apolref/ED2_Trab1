#include <stdio.h>
#include <stdlib.h>
#include "contagem_intersecoes.h"
#include "matriz.h"
#include "Ordena.h"
#include <time.h>


void contagem_intersecoes(FILE *arq_A, FILE *arq_B, long nA, long nB, FILE *arquivo_saida, clock_t *soma_ciclosA,clock_t *soma_ciclosB){
    long **A;
    long **B;
    long *contagens;
    long inicio, fim, primeiro_iB = 0;
    clock_t ciclos_ini;
    A = Alocar_matriz(nA,2);
    //A = (long **) malloc (2, sizeof(long *));
    //for ( i = 0; i < 2; i++ ) {
    //    A[i] = (long*) malloc (2, sizeof(long));
    //    if (v[i] == NULL) {
    //        printf ("** Erro: Memoria Insuficiente **");
    //        return (NULL);
    //    }
    //}
    B = Alocar_matriz(nB,2);

    contagens = (long*)calloc(nA, sizeof(long));

    for(int i = 0; i < nA; i++){
        fscanf(arq_A, "%ld[^,]", &inicio);
        getc(arq_A);
        fscanf(arq_A, "%ld", &fim);
        A[i][0] = inicio;
        A[i][1] = fim;
    }

    for(int i = 0; i < nB; i++){
        fscanf(arq_B, "%ld[^,]", &inicio);
        getc(arq_B);
        fscanf(arq_B, "%ld", &fim);
        B[i][0] = inicio;
        B[i][1] = fim;
    }
    ciclos_ini = clock();
    OrdenaNumeros(nA, A);
    (*soma_ciclosA) += clock() - ciclos_ini;
    ciclos_ini = clock();
    OrdenaNumeros(nB, B);
    (*soma_ciclosB) += clock() - ciclos_ini;


    for(int iA = 0; iA < nA; iA++){
        for(int iB = primeiro_iB; iB < nB; iB++){
            if(A[iA][1] < B[iB][0] || A[iA][0] > B[iB][1]){
                if(contagens[iA] == 0){
                    primeiro_iB = iB;
                }
            }else{
                contagens[iA]++;
            }
        }
    }
    for(int i = 0; i < nA; i++){
        fprintf(arquivo_saida, "%ld\n", contagens[i]);
    }

    free(contagens);
    Liberar_matriz(nA,2,A);
    Liberar_matriz(nB,2,B);
}
