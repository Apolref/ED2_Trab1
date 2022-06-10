#include <stdio.h>
#include <stdlib.h>
#include "ordena.h"
int OrdenaDigitos(int n, int **A,int posicao){

  int B[10]={0,0,0,0,0,0,0,0,0,0}, digito=0;
  
  for(int i = 0; i < n;){
    digito = A[i][0]/posicao;
    digito = digito%10;
    //printf("\n %d \n", digito);
    B[digito] = B[digito]+1;

    i++;
  }

  for (int i=1;i<9;i++){
    B[i]= B[i]+ B[i-1];

  }

  int C[n][2];

  for (int i=n-1; i==0;i--){
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

  return 1;
}

int OrdenaNumeros(int n,int **A) {
  
  int maior = 0;
  for (int i=0;i<n;i++){
    if (A[i][0]>maior){
      maior = A[i][0];
    }
  }

  //printf("\n %d \n", maior);
  
  int posicao = 1;
  while (maior/posicao>0){
    OrdenaDigitos(n,A,posicao);
    posicao = posicao*10;
  }
  return 1;
  
}

int Alocar_matriz(int m, int n, int **v){
  int i; 
  if (m < 1 || n < 1) {
    printf ("** Erro: Parametro invalido **\n");
  return 0;
  }
  v = (int **) calloc (m, sizeof(int *));
  if (v == NULL) {
    printf ("** Erro: Memoria Insuficiente **");
  return 0;
  }
  for ( i = 0; i < m; i++ ) {
    v[i] = (int*) calloc (n, sizeof(int));
    if (v[i] == NULL) {
      printf ("** Erro: Memoria Insuficiente **");
      return 0;
    }
  }
return 1; 
}

int Liberar_matriz (int m, int n, int **v) {
  int i;
  if (v == NULL) return 0;
  if (m < 1 || n < 1) {
    printf ("** Erro: Parametro invalido **\n");
  return 0;
  }
  for (i = 0; i < m; i++) {
    free (v[i]); 
  }
  free (v);
  return 1;
}
