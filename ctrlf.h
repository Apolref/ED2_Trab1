//
// Created by Fernando Calaza on 04/06/2022.
//
#include <stdio.h>

#ifndef T1_CTRLF_H
#define T1_CTRLF_H

#endif //T1_CTRLF_H
int ler_arq(char **texto, FILE *arq_texto, char stop_char);         //extrai todo o conteudo do arquivo p/ uma string
long b10(int n);                                                    //retorna bases de 10,ou seja, faz 10^n p/ n>0
int pLinhaCSV(char **str, long n, long m);                          //transfoma 2 numeros em uma string no formato de linha do .CSV "n,m\n"
int CtrlF(FILE *arq_texto, FILE *arq_trechos, FILE **arq_saida);    //método de busca exigido pelo o trabalho