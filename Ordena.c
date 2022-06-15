#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"
#include "Ordena.h"


void OrdenaDigitos(int n, long **A, int posicao){

    int B[10]={0,0,0,0,0,0,0,0,0,0}, digito=0; //Declaração do Vetor Auxiliar B
    long **C; //Declaração de matriz auxiliar C
    
    C = Alocar_matriz(n,2); 

    for(int i=0; i < n ;i++){//Armazena em B quantos numeros de cada da posição posicao tem na matriz A
        digito = A[i][0]/posicao;
        digito = digito%10;
        B[digito] = B[digito]+1;
    }

    for (int i=1;i<=9;i++){// Transforma o vetor B em uma espécie de contagem de menores
        B[i]= B[i]+ B[i-1];
    }

    for (int i=n-1; i>=0;i--){//Armazena os valores ordenados na matriz auxiliar C, indo do ultimo elemento de A pro primeiro
        digito = A[i][0]/posicao;
        digito = digito%10;
        B[digito] = B[digito]-1;
        C[B[digito]][0] = A[i][0];
        C[B[digito]][1] = A[i][1];
    }

    for (int i=0;i<n;i++){//Troca A matriz ja ordenada na posição em especifico com A
        A[i][0] = C[i][0];
        A[i][1] = C[i][1];
    }

    Liberar_matriz(n,2,C);
}

void OrdenaNumeros(int n,long **A) {
    int posicao = 1, maior = 0; // Declaração da variável que controla a posição a ser ordenada, e a que armazena o maior valor da matriz

    for (int i=0;i<n-1;i++){//Armazena qual é o maior valor da matriz, para utilizar o seu numero de digitos como numero de vezes em que a OrdenaDigitos executará
        if (A[i][0]>maior){
            maior = A[i][0];
        }
    }

    while ((maior/posicao)>0){//Loop principal que executará a função m(numero de digitos do maior) vezes
        OrdenaDigitos(n,A,posicao);
        posicao=posicao*10;
    }
}
