#include <stdio.h>
#include <stdlib.h>

int **Alocar_matriz(int m, int n){
  int **v;
  int i; 
  if (m < 1 || n < 1) {
    printf ("** Erro: Parametro invalido **\n");
  return (NULL);
  }
  v = (int **) calloc (m, sizeof(int *));
  if (v == NULL) {
    printf ("** Erro: Memoria Insuficiente **");
  return (NULL);
  }
  for ( i = 0; i < m; i++ ) {
    v[i] = (int*) calloc (n, sizeof(int));
    if (v[i] == NULL) {
      printf ("** Erro: Memoria Insuficiente **");
      return (NULL);
    }
  }
return (v); 
}

int **Liberar_matriz (int m, int n, int **v) {
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