#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"


int **OrdenaDigitos(int n, int **A,int posicao){

  int B[10]={0,0,0,0,0,0,0,0,0,0}, digito=0;
  
  for(int i=0; i < n-1;){
    digito = A[i][0]/posicao;
    digito = digito%10;
    B[digito] = B[digito]+1;
    i++;
  }

  for (int i=1;i<9;){
    B[i]= B[i]+ B[i-1];
    i++;
  }

  int C[n][2];

  for (int i=n-1; i==0;){
    digito = A[i][0]/posicao;
    digito = digito%10;
    B[digito] = B[digito]-1;
    C[B[digito]][0] = A[i][0];
    C[B[digito]][1] = A[i][1];
    i--;
  }

  for (int i=0;i<n-1;i++){
    A[i][0] = C[i][0];
    A[i][1] = C[i][1];
    i++;
  }

  return A;
}

int **OrdenaNumeros(int n,int **A) {
  
  int maior = 0;
  for (int i=0;i<n-1;i++){
    if (A[i][0]>maior){
      maior = A[i][0];
    }
  }
  int posicao=1;
  while (maior/posicao>0){
    OrdenaDigitos(n,A,posicao);
    posicao=posicao*10;
  }
  return A;
}



int main(void){
  int **A;
  int n = 4;

  A = Alocar_matriz(n,2);
  
  for(int i=0;i<n-1;i++){
    for (int j=0; j<1;j++){
      printf ("%d",A[i][j]);
    }
    printf ("\n");
  }

  OrdenaNumeros(n,A);

  A = Liberar_matriz(n,2,A);
}
