#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "merge.h"
#include "utils.h"

#define MAX_RUNS 1024  // limite de arquivos simultâneos abertos

typedef struct {
    int valor;
    int origem; // índice do arquivo da run
} ElementoHeap;

static void trocar_heap(ElementoHeap* a, ElementoHeap* b) {
    ElementoHeap temp = *a;
    *a = *b;
    *b = temp;
}

static void heapify(ElementoHeap heap[], int n, int i) {
    int menor = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if (esq < n && heap[esq].valor < heap[menor].valor)
        menor = esq;
    if (dir < n && heap[dir].valor < heap[menor].valor)
        menor = dir;

    if (menor != i) {
        trocar_heap(&heap[i], &heap[menor]);
        heapify(heap, n, menor);
    }
}

static void construir_heap(ElementoHeap heap[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(heap, n, i);
    }
}

void intercalar_runs(const char* arquivo_saida, int total_runs) {
    FILE* saida = fopen(arquivo_saida, "w");
    if (!saida) {
        perror("Erro ao criar arquivo de saída");
        return;
    }

    FILE* arquivos[MAX_RUNS];
    ElementoHeap heap[MAX_RUNS];
    int ativos = 0;

    // Abre todas as runs e preenche o heap inicial
    for (int i = 0; i < total_runs; i++) {
        char nome[32];
        gerar_nome_run(nome, i);
        arquivos[i] = fopen(nome, "r");

        if (!arquivos[i]) {
            perror("Erro ao abrir run para leitura");
            continue;
        }

        int num;
        if (fscanf(arquivos[i], "%d", &num) == 1) {
            heap[ativos].valor = num;
            heap[ativos].origem = i;
            ativos++;
        }
    }

    construir_heap(heap, ativos);

    while (ativos > 0) {
        // Menor elemento está no topo do heap
        ElementoHeap menor = heap[0];
        fprintf(saida, "%d\n", menor.valor);

        // Tenta ler o próximo número da mesma run
        int prox;
        if (fscanf(arquivos[menor.origem], "%d", &prox) == 1) {
            heap[0].valor = prox; // substitui e reheapifica
        } else {
            // Remove esse arquivo do heap
            heap[0] = heap[ativos - 1];
            ativos--;
        }

        heapify(heap, ativos, 0);
    }

    // Fecha todos os arquivos
    for (int i = 0; i < total_runs; i++) {
        if (arquivos[i]) fclose(arquivos[i]);
    }

    fclose(saida);
}
