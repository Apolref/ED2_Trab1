#include <stdio.h>
#include <stdlib.h>


#ifndef T1TEMP_CTRLF_H
#define T1TEMP_CTRLF_H

#endif //T1TEMP_CTRLF_H


long ler_arq(char **str, FILE *arq, char stop_char);
long b10(long n);
long pLinhaCSV(char **str, long n, long m);
long CtrlF(FILE *arq_texto, FILE *arq_trechos, FILE **arq_saida);