#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"
#include "Ordena.h"


void OrdenaDigitos(int n, long **A, int posicao){

    int B[10]={0,0,0,0,0,0,0,0,0,0}, digito=0;
    long **C;

    C = Alocar_matriz(n,2);

    for(int i=0; i < n ;i++){
        digito = A[i][0]/posicao;
        digito = digito%10;
        B[digito] = B[digito]+1;
    }

    for (int i=1;i<=9;i++){
        B[i]= B[i]+ B[i-1];
    }

    for (int i=n-1; i>=0;i--){
        digito = A[i][0]/posicao;
        digito = digito%10;
        B[digito] = B[digito]-1;
        C[B[digito]][0] = A[i][0];
        C[B[digito]][1] = A[i][1];
    }

    for (int i=0;i<n;i++){
        A[i][0] = C[i][0];
        A[i][1] = C[i][1];
    }

    Liberar_matriz(n,2,C);
}

void OrdenaNumeros(int n,long **A) {
    int posicao = 1;
    int maior = 0;

    for (int i=0;i<n-1;i++){
        if (A[i][0]>maior){
            maior = A[i][0];
        }
    }

    while ((maior/posicao)>0){
        OrdenaDigitos(n,A,posicao);
        posicao=posicao*10;
    }
}
