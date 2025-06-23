#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void trocar(int* a, int* b);

// Organiza o heap a partir do índice i
void heapfy(int vetor[], int tam, int i); 

// Constrói o heap a partir do vetor
void build_heap(int vetor[], int tam);

// Ordena um vetor com heapsort
void heapsort(int* vetor, int tam);

// Gera o nome de um arquivo runX.txt a partir do índice (0, 1, ...)
void gerar_nome_run(char* buffer, int indice);

// Conta quantas runs foram geradas (opcional, se preferir separar)
int contar_runs();

void remover_temporarios();
int verificar_ordenacao(const char* arquivo_saida);


#endif