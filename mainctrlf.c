#include "ctrlf.h"
#include <stdio.h>

int main() {
    FILE *texto;
    texto = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1\\texto.txt", "r");
    if (texto == NULL){
        printf("Problemas na criação do arquivo TEXTO\n");
        return -1;
    }
    FILE *trechos;
    trechos = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1\\trechos.txt", "r");
    if (trechos == NULL){
        printf("Problemas na criação do arquivo TRECHOS\n");
        return -1;
    }
    FILE *saida;
    saida = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1\\saida.txt", "w");
    if (saida == NULL){
        printf("Problemas na criação do arquivo SAIDA\n");
        return -1;
    }

    int out = CtrlF(texto, trechos, &saida);

    fclose(texto);
    fclose(trechos);
    fclose(saida);
    return out;
}
