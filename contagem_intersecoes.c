#include <stdio.h>
#include <stdlib.h>
#include "contagem_intersecoes.h"
#include "matriz.h"
#include "Ordena.h"


void contagem_intersecoes(FILE *arq_A, FILE *arq_B, int nA, int nB, FILE *arquivo_saida){
    long **A;
    long **B;
    long *contagens;
    int inicio, fim, primeiro_iB = 0;
    A = Alocar_matriz(nA,2);
    B = Alocar_matriz(nB,2);

    contagens = (long*)calloc(nA, sizeof(long));
    /*
    for(int i = 0; i < nA; i++){
        contagens[i] = 0;
    }
    */
    for(int i = 0; i < nA; i++){
        fscanf(arq_A, "%d", &inicio);
        fscanf(arq_A, "%d", &fim);
        A[i][0] = inicio;
        A[i][1] = fim;
    }
    for(int i = 0; i < nB; i++){
        fscanf(arq_B, "%d%d", &inicio, &fim);
        B[i][0] = inicio;
        B[i][1] = fim;
    }
    OrdenaNumeros(nA, A);
    OrdenaNumeros(nB, B);

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
