#define repeticoes 10 //PADRAO 10
#define N_entradas 7 //PADRAO 7
#include <stdio.h>
#include "CtrlF.h"
#include "contagem_intersecoes.h"
#include <math.h>
#include <time.h>


int main() {
    long n_genes, n_fragmentos;
    char *leitura = NULL;
    char entrada[4];
    clock_t ciclos_ini, soma_ciclos,soma_ciclosA,soma_ciclosB;
    FILE *arquivo_genoma, *arquivo_fragmentos, *pos_genes, *pos_fragmentos, *arquivo_saida;

    printf("\n// GENOMA // FRAGMENTOS // POS GENES //");
    printf("\n    || %d/%d", 0, repeticoes*N_entradas);
    for(int i=1; i<=N_entradas; i++) {// DEFININDO ENTRADAS - PEQUENAS/MEDIAS/GRANDES
        soma_ciclos = 0;
        soma_ciclosA = 0;
        soma_ciclosB = 0;
        for (int j = 0; j < repeticoes; j++) {//REPETINDO 10 VEZES CADA ENTRADA
            switch (i) {//COLOQUE NO LUGAR DO "i" QUAL CASO DE TESTE VC DESEJA RODAR, ex: "  switch (2) {  "
                case 1:
                    entrada[0] ='P';
                    entrada[1] ='G';
                    entrada[2] ='G';
                    entrada[3] ='\0';
                    pos_genes = fopen("pos_genes_pequeno.csv", "r");
                    arquivo_genoma = fopen("genoma_grande.txt", "r");
                    arquivo_fragmentos = fopen("fragmentos_grande.txt", "r");
                    break;
                case 2:
                    entrada[0] ='M';
                    entrada[1] ='G';
                    entrada[2] ='G';
                    entrada[3] ='\0';
                    pos_genes = fopen("pos_genes_medio.csv", "r");
                    arquivo_genoma = fopen("genoma_grande.txt", "r");
                    arquivo_fragmentos = fopen("fragmentos_grande.txt", "r");
                    break;
                case 3:
                    entrada[0] ='G';
                    entrada[1] ='P';
                    entrada[2] ='G';
                    entrada[3] ='\0';
                    pos_genes = fopen("pos_genes_grande.csv", "r");
                    arquivo_genoma = fopen("genoma_pequeno.txt", "r");
                    arquivo_fragmentos = fopen("fragmentos_grande.txt", "r");
                    break;
                case 4:
                    entrada[0] ='G';
                    entrada[1] ='M';
                    entrada[2] ='G';
                    entrada[3] ='\0';
                    pos_genes = fopen("pos_genes_grande.csv", "r");
                    arquivo_genoma = fopen("genoma_medio.txt", "r");
                    arquivo_fragmentos = fopen("fragmentos_grande.txt", "r");
                    break;
                case 5:
                    entrada[0] ='G';
                    entrada[1] ='G';
                    entrada[2] ='P';
                    entrada[3] ='\0';
                    pos_genes = fopen("pos_genes_grande.csv", "r");
                    arquivo_genoma = fopen("genoma_grande.txt", "r");
                    arquivo_fragmentos = fopen("fragmentos_pequeno.txt", "r");
                    break;
                case 6:
                    entrada[0] ='G';
                    entrada[1] ='G';
                    entrada[2] ='M';
                    entrada[3] ='\0';
                    pos_genes = fopen(":pos_genes_grande.csv", "r");
                    arquivo_genoma = fopen("genoma_grande.txt", "r");
                    arquivo_fragmentos = fopen("fragmentos_medio.txt", "r");
                    break;
                case 7:
                    entrada[0] ='G';
                    entrada[1] ='G';
                    entrada[2] ='G';
                    entrada[3] ='\0';
                    pos_genes = fopen("pos_genes_grande.csv", "r");
                    arquivo_genoma = fopen("genoma_grande.txt", "r");
                    arquivo_fragmentos = fopen("fragmentos_grande.txt", "r");
                    break;
                default:
                    printf("SwitchCase falhou, posicao invalida!\n");
                    return -1;
            }
            arquivo_saida = fopen("saida.txt","w");
            pos_fragmentos = fopen("pos_fragmentos.txt", "w");
            if (pos_genes == NULL || arquivo_genoma == NULL || arquivo_fragmentos == NULL ||pos_fragmentos == NULL || arquivo_saida == NULL) {
                printf("Problemas na para acessar ou criar um dos arquivos!\n");
                return -1;
            }
            ciclos_ini = clock();

/*   *//* ---------- INICIO EXECUCAO DA MAIN( ) ---------- */
/* 1 */   CtrlF(arquivo_genoma, arquivo_fragmentos, &pos_fragmentos);
/*   *//* ---------- PAUSA EXECUCAO DA MAIN( ) ---------- */
/*   */   soma_ciclos += clock() - ciclos_ini;
/*   */   fclose(pos_fragmentos);//FCLOSE E FOPEN NÃO FAZEM PARTE DO ALGORITMO, POR ISSO DEVEM SER DESCONSIDERADOS
/*   */   pos_fragmentos = fopen("pos_fragmentos.txt", "r");
/*   */   if (pos_fragmentos == NULL) {
/*   */       printf("Problemas na reabertura para ler do arquivo POS FRAGMENTOS\n");
/*   */       return -1;
/*   */   }
/*   */   ciclos_ini = clock();
/*   *//* ---------- RETOMADA EXECUCAO DA MAIN( ) ---------- */
/* 2 */   n_genes = 0;
/* 3 */   while (ler_arq(&leitura, pos_genes, '\n') == 1)
/* 4 */       n_genes++;
/* 5 */   n_fragmentos = 0;
/* 6 */   while (ler_arq(&leitura, pos_fragmentos, '\n') == 1)
/* 7 */       n_fragmentos++;
/* 8 */   contagem_intersecoes(pos_genes, pos_fragmentos, n_genes, n_fragmentos, arquivo_saida, &soma_ciclosA, &soma_ciclosB);
/*   *//* ---------- FIM EXECUCAO DA MAIN( ) ---------- */

            soma_ciclos += clock() - ciclos_ini;
            fclose(pos_fragmentos);
            fclose(pos_genes);
            fclose(arquivo_genoma);
            fclose(arquivo_fragmentos);
            fclose(arquivo_saida);
            printf("\n%s || %d/%d", entrada, j+1+((i-1)*repeticoes), repeticoes*N_entradas);

        }
        printf("\n%s || Tempo OrdNum PosGen[%ld]: %lfs", entrada, n_genes, (((double) soma_ciclosA) / repeticoes) / CLOCKS_PER_SEC);
        printf("\n%s || Tempo OrdNum PosFrag[%ld]: %lfs", entrada, n_fragmentos, (((double) soma_ciclosB) / repeticoes) / CLOCKS_PER_SEC);
        printf("\n%s || Tempo Total: %lfs", entrada, (((double) soma_ciclos) / repeticoes) / CLOCKS_PER_SEC);
    }
    printf("\nFIM!\n");
    return 0;
}