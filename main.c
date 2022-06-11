//#include "ctrlf.h"
#include <stdio.h>
#include <stdlib.h>


//*******************************************************************************************************************************************//


#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"
/*
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
*/

void OrdenaDigitos(int n, int **A, int posicao){

  int B[10]={0,0,0,0,0,0,0,0,0,0}, digito=0;
  int **C;

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

void OrdenaNumeros(int n,int **A) {
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



//*******************************************************************************************************************************************//


void contagem_intersecoes(FILE *arq_A, FILE *arq_B, int nA, int nB, FILE *arquivo_saida){
    int **A; 
    int **B; 
    int *contagens;
    int inicio, fim, primeiro_iB = 0;
    A = Alocar_matriz(nA,2);
    B = Alocar_matriz(nB,2);
    
    contagens = (int*)calloc((nA, sizeof(int))
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
        fprintf(arquivo_saida, "%d\n", contagens[i]);
    }
    
    free(contagens)
    Liberar_matriz(n,2,A);
    Liberar_matriz(n,2,B);  
}



//*******************************************************************************************************************************************//


int ler_arq(char **str, FILE *arq, char stop_char){//extrai todo o conteudo do arquivo p/ uma string
    int tam=1;//Eh o tamanho da string, aumenta dinamicamente
    int flag=1;//flag que diz se é o arquivo já está no final, ates de começar a leitura
    for (char c = getc(arq); !((c == stop_char)||(c == EOF)); c = getc(arq)){//lendo arquivo char p/ char
        if(c=='\n')//pela logica do exemplo do PDF "pull'\n'request" e "pull' 'request" devem ser tratados iguais
            c=' ';
        *str = realloc(*str, (tam+1) * sizeof(char));
        if(*str==NULL) {
            printf("Falha ao alocar memoria para a string texto");
            free(*str);
            return -1;
        }
        (*str)[tam-1]=c;//inserindo o char na string
        tam++;
        flag=0;
    }
    if(flag==1)//arquivo já está no fim
        return -1;
    (*str)[tam-1]='\0';//indicando o fim da string
    return 1;
}


long b10(int n){//retorna bases de 10,ou seja, faz 10^n p/ n>0
    if(n<0)
        return -1;
    long result=1;
    for (; n>0; n--){
        result = result * 10;
    }
    return result;
}


int pLinhaCSV(char **str, long n, long m){//transfoma 2 numeros em uma string no formato de linha do .CSV "n,m\n"
    int tam = 0;// tamanho da string
    int cursor=0;//cursor de escrita em str
    int cont;//contador de quantas casas decimais tem um número
    *str = realloc(*str, (tam+=3) * sizeof(char));//criando espaço para ';' '\n' '\0' em str
    if(*str==NULL) {
        printf("Falha ao alocar memoria para a string str");
        free(*str);
        return -1;
    }
    if(n<0){//caso n seja negativo
        n*=-1;
        *str = realloc(*str, (tam+=1) * sizeof(char));//criando espaço para '-' em str
        if(*str==NULL) {
            printf("Falha ao alocar memoria para a string str");
            free(*str);
            return -1;
        }
        (*str)[cursor] = '-';//inserindo sinal negativo
        cursor++;
    }
    for(cont=0; (n/b10(cont))>9; cont++){}//definindo quantas casas decimais tem n
    *str = realloc(*str, (tam+=(cont+1)) * sizeof(char));//criando espaço para n em str
    if(*str==NULL) {
        printf("Falha ao alocar memoria para a string str");
        free(*str);
        return -1;
    }
    for(int i=0; i<=cont; i++) {//inserindo n em str
        (*str)[cursor] = (n/b10(cont-i))+'0';
        n=(n%b10(cont-i));
        cursor++;
    }
    (*str)[cursor]=',';//inserindo ',' em str
    cursor++;
    if(m<0){//caso m seja negativo
        m*=-1;
        *str = realloc(*str, (tam+=1) * sizeof(char));//criando espaço para '-' em str
        if(*str==NULL) {
            printf("Falha ao alocar memoria para a string str");
            free(*str);
            return -1;
        }
        (*str)[cursor] = '-';//inserindo sinal negativo
        cursor++;
    }
    for(cont=0; (m/b10(cont))>9; cont++){}//definindo quantas casas decimais tem n
    *str = realloc(*str, (tam+=(cont+1)) * sizeof(char)); //criando espaço para m em str
    if(*str==NULL) {
        printf("Falha ao alocar memoria para a string str");
        free(*str);
        return -1;
    }
    for(int i=0; i<=cont; i++) {//inserindo n em str
        (*str)[cursor] = (m/b10(cont-i))+'0';
        m=(m%b10(cont-i));
        cursor++;
    }
    (*str)[cursor]='\n';//inserindo '\n' em str
    cursor++;
    (*str)[cursor]='\0';//inserindo '\0' em str
    return cursor;
}


int CtrlF(FILE *arq_texto, FILE *arq_trechos, FILE **arq_saida) {//método de busca exigido pelo o trabalho
    char *trecho = NULL;
    char *texto = NULL;
    char *saida = NULL;
    int n;
// *** AQUI COMECA A IMPLEMENTACAO DA FUNCAO SEGUNDO AS EXPECIFICACOES DO PDF *** //
/*   1   */ ler_arq(&texto, arq_texto, EOF);
/* 2 e 3 */ while ( ler_arq(&trecho, arq_trechos, '\n') != -1) {
/*   4   */     long i = 0;
/*   5   */     while (texto[i] != '\0') {
/*   6   */         long j = 0;
/*   7   */         while ((trecho[j] != '\0') && (texto[i + j] == trecho[j])) {
/*   8   */             j++;
/*   9   */         }
/*   10  */         if (trecho[j] == '\0' ) {
/*   11  */             n = pLinhaCSV(&saida,i,i+j-1);
/*   11  */             fwrite(saida , 1,n, *arq_saida );
/*   12  */             //break;//ISSO FAZ BUSCAR SÓ A PRIMEIRA OCORRÊNCIA!!!
/*   13  */         }
/*   14  */         i++;
/*   15  */     }
/*   16  */ }
// *** AQUI TERMINA A IMPLEMENTACAO DA FUNCAO SEGUNDO AS EXPECIFICACOES DO PDF *** //

    free(trecho);
    free(texto);
    free(saida);
    return 1;
}


//*******************************************************************************************************************************************//


int main() {
    int n_genes, n_fragmentos;
    char *leitura = NULL;

    FILE *pos_genes;
    pos_genes = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1\\pos_genes_pequeno.txt", "r");
    if (pos_genes == NULL){
        printf("Problemas na criação do arquivo POS GENES\n");
        return -1;
    }
    FILE *arquivo_genoma;
    arquivo_genoma = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1\\genoma_pequeno.txt", "r");
    if (arquivo_genoma == NULL){
        printf("Problemas na criação do arquivo GENOMA\n");
        return -1;
    }
    FILE *arquivo_fragmentos;
    arquivo_fragmentos = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1\\fragmentos_pequeno.txt", "r");
    if (arquivo_fragmentos == NULL){
        printf("Problemas na criação do arquivo ARQUIVOS FRAGMENTOS\n");
        return -1;
    }
    FILE *pos_fragmentos;
    pos_fragmentos = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1\\saida.txt", "w");
    if (pos_fragmentos == NULL){
        printf("Problemas na criação do arquivo POS FRAGMENTOS\n");
        return -1;
    }
    FILE *arquivo_saida;
    arquivo_saida = fopen("C:\\Users\\Fernando Calaza\\Documents\\Faculdade\\ED2\\T1\\saida.txt", "w");
    if (arquivo_saida == NULL){
        printf("Problemas na criação do arquivo SAIDA\n");
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

