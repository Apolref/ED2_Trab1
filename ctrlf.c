#include "ctrlf.h"
#include <stdio.h>
#include <stdlib.h>


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
                        fwrite("    ",1,strlen("    "),*arq_saida);
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