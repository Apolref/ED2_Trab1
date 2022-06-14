#include <stdio.h>
#include "CtrlF.h"
#include "contagem_intersecoes.h"


int main() {
    int n_genes, n_fragmentos;
    char *leitura = NULL;

    FILE *pos_genes;
    pos_genes = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1temp\\arquivos\\pos_genes_pequeno.csv", "r");
    if (pos_genes == NULL){
        printf("Problemas na criacao do arquivo POS GENES\n");
        return -1;
    }
    FILE *arquivo_genoma;
    arquivo_genoma = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1temp\\arquivos\\genoma_pequeno.txt", "r+");
    if (arquivo_genoma == NULL){
        printf("Problemas na criacao do arquivo GENOMA\n");
        return -1;
    }
    FILE *arquivo_fragmentos;
    arquivo_fragmentos = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1temp\\arquivos\\fragmentos_pequeno.txt", "r+");
    if (arquivo_fragmentos == NULL){
        printf("Problemas na criacao do arquivo ARQUIVOS FRAGMENTOS\n");
        return -1;
    }
    FILE *pos_fragmentos;
    pos_fragmentos = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1temp\\arquivos\\pos_fragmentos.txt", "r");
    if (pos_fragmentos == NULL){
        printf("Problemas na criacao do arquivo POS FRAGMENTOS\n");
        return -1;
    }
    FILE *arquivo_saida;
    arquivo_saida = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1temp\\arquivos\\saida.txt", "w");
    if (arquivo_saida == NULL){
        printf("Problemas na criacao do arquivo SAIDA\n");
        return -1;
    }


    CtrlF(arquivo_genoma, arquivo_fragmentos, &pos_fragmentos);
    n_genes = 0;
    while( ler_arq(&leitura, pos_genes, '\n') == 1 )
        n_genes++;
    n_fragmentos = 0;
    while( ler_arq(&leitura, pos_fragmentos, '\n') == 1 )
        n_fragmentos++;
    contagem_intersecoes(pos_genes, pos_fragmentos, n_genes, n_fragmentos, arquivo_saida);


    fclose(pos_genes);
    fclose(arquivo_genoma);
    fclose(arquivo_fragmentos);
    fclose(pos_fragmentos);
    fclose(arquivo_saida);
    return 0;
}