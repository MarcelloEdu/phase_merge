#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

// Função auxiliar de troca
void trocar(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Organiza o heap a partir do índice i
void heapfy(int vetor[], int tam, int i) {
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if (esq < tam && vetor[esq] > vetor[maior]) {
        maior = esq;
    }

    if (dir < tam && vetor[dir] > vetor[maior]) {
        maior = dir;
    }

    if (maior != i) {
        trocar(&vetor[i], &vetor[maior]);
        heapfy(vetor, tam, maior); // chamada recursiva
    }
}

void heapsort(int* vetor, int tam) {
    // Constrói o heap
    for (int i = tam / 2 - 1; i >= 0; i--) {
        heapfy(vetor, tam, i);
    }

    // Extrai os elementos do heap um a um
    for (int i = tam - 1; i > 0; i--) {
        trocar(&vetor[0], &vetor[i]);
        heapfy(vetor, i, 0);
    }
}

void gerar_nome_run(char* buffer, int indice) {
    sprintf(buffer, "run%d.txt", indice);
}

int contar_runs() {
    int count = 0;
    FILE* file;

    while (1) {
        char nome_arquivo[32];
        gerar_nome_run(nome_arquivo, count);

        file = fopen(nome_arquivo, "r");
        if (!file) break;

        fclose(file);
        count++;
    }

    return count;
}
