#define repeticoes 1 //PADRAO 10
#define N_entradas 1 //PADRAO 7
#include <stdio.h>
#include "CtrlF.h"
#include "contagem_intersecoes.h"
#include <math.h>
#include <time.h>


int main() {
    long n_genes, n_fragmentos;
    char *leitura = NULL;
    clock_t ciclos_ini, soma_ciclos;
    FILE *arquivo_genoma, *arquivo_fragmentos, *pos_genes, *pos_fragmentos, *arquivo_saida;

    arquivo_saida = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1temp\\arquivos\\saida.txt","w");
    pos_fragmentos = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1temp\\arquivos\\pos_fragmentos.txt", "w");
    printf("\n// GENOMA // FRAGMENTOS // POS GENES //");
    for(int i=1; i<=N_entradas; i++) {// DEFININDO ENTRADAS - PEQUENAS/MEDIAS/GRANDES
        switch (1) {
            case 1:
                printf("\n-----PGG-----");
                pos_genes = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1temp\\arquivos\\pos_genes_pequeno.csv", "r");
                arquivo_genoma = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1temp\\arquivos\\genoma_grande.txt", "r");
                arquivo_fragmentos = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1temp\\arquivos\\fragmentos_grande.txt", "r");
                break;
            case 2:
                printf("\n-----MGG-----");
                pos_genes = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1temp\\arquivos\\pos_genes_medio.csv", "r");
                arquivo_genoma = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1temp\\arquivos\\genoma_grande.txt", "r");
                arquivo_fragmentos = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1temp\\arquivos\\fragmentos_grande.txt", "r");
                break;
            case 3:
                printf("\n-----GPG-----");
                pos_genes = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1temp\\arquivos\\pos_genes_grande.csv", "r");
                arquivo_genoma = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1temp\\arquivos\\genoma_pequeno.txt", "r");
                arquivo_fragmentos = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1temp\\arquivos\\fragmentos_grande.txt", "r");
                break;
            case 4:
                printf("\n-----GMG-----");
                pos_genes = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1temp\\arquivos\\pos_genes_grande.csv", "r");
                arquivo_genoma = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1temp\\arquivos\\genoma_medio.txt", "r");
                arquivo_fragmentos = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1temp\\arquivos\\fragmentos_grande.txt", "r");
                break;
            case 5:
                printf("\n-----GGP-----");
                pos_genes = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1temp\\arquivos\\pos_genes_grande.csv", "r");
                arquivo_genoma = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1temp\\arquivos\\genoma_grande.txt", "r");
                arquivo_fragmentos = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1temp\\arquivos\\fragmentos_pequeno.txt", "r");
                break;
            case 6:
                printf("\n-----GGM-----");
                pos_genes = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1temp\\arquivos\\pos_genes_grande.csv", "r");
                arquivo_genoma = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1temp\\arquivos\\genoma_grande.txt", "r");
                arquivo_fragmentos = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1temp\\arquivos\\fragmentos_medio.txt", "r");
                break;
            case 7:
                printf("\n-----GGG-----");
                pos_genes = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1temp\\arquivos\\pos_genes_grande.csv", "r");
                arquivo_genoma = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1temp\\arquivos\\genoma_grande.txt", "r");
                arquivo_fragmentos = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1temp\\arquivos\\fragmentos_grande.txt", "r");
                break;
            default:
                printf("SwitchCase falhou, posicao invalida!\n");
                return -1;
        }
        if (pos_genes == NULL || arquivo_genoma == NULL || arquivo_fragmentos == NULL ||pos_fragmentos == NULL || arquivo_saida == NULL) {
            printf("Problemas na para acessar ou criar um dos arquivos!\n");
            return -1;
        }
        for (int j = 0; j < repeticoes; j++) {//REPETINDO 10 VEZES CADA ENTRADA
            soma_ciclos = 0;

// *** ---------- INICIO EXECUCAO DA MAIN( ) ---------- ***
            CtrlF(arquivo_genoma, arquivo_fragmentos, &pos_fragmentos);
            fclose(pos_fragmentos);
            pos_fragmentos = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1temp\\arquivos\\pos_fragmentos.txt", "r");
            if (pos_fragmentos == NULL) {
                printf("Problemas na leitura do arquivo POS FRAGMENTOS\n");
                return -1;
            }
            n_genes = 0;
            while (ler_arq(&leitura, pos_genes, '\n') == 1)
                n_genes++;
            n_fragmentos = 0;
            while (ler_arq(&leitura, pos_fragmentos, '\n') == 1)
                n_fragmentos++;
            contagem_intersecoes(pos_genes, pos_fragmentos, n_genes, n_fragmentos, arquivo_saida);
// *** ---------- FIM EXECUCAO DA MAIN( ) ---------- ***

            soma_ciclos += clock() - ciclos_ini;
            fclose(pos_fragmentos);
            printf("\n%d/%d", j+((i-1)*repeticoes), repeticoes*N_entradas);
        }
        printf("\nTempo: %lfs", (((double) soma_ciclos) / repeticoes) / CLOCKS_PER_SEC);
    }
    printf("\n%d/%d\n", repeticoes*N_entradas, repeticoes*N_entradas);
    fclose(pos_genes);
    fclose(arquivo_genoma);
    fclose(arquivo_fragmentos);
    fclose(arquivo_saida);
    return 0;
}