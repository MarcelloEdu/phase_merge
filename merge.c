#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "merge.h"
#include "utils.h"

#define MAX_RUNS 1024  // limite de arquivos simultâneos abertos
#define MAX_K 64    // limite de runs no grupo

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

void intercalar_grupo(char** arquivos, int n_arquivos, const char* destino){
     FILE* entrada[MAX_K];
    FILE* saida = fopen(destino, "w");
    if (!saida) {
        perror("Erro ao criar arquivo destino");
        return;
    }

    ElementoHeap heap[MAX_K];
    int ativos = 0;

    // Abre arquivos e insere primeiro valor no heap
    for (int i = 0; i < n_arquivos; i++) {
        entrada[i] = fopen(arquivos[i], "r");
        if (!entrada[i]) {
            perror("Erro ao abrir run no grupo");
            continue;
        }

        int num;
        if (fscanf(entrada[i], "%d", &num) == 1) {
            heap[ativos].valor = num;
            heap[ativos].origem = i;
            ativos++;
        }
    }

    construir_heap(heap, ativos);

    while (ativos > 0) {
        ElementoHeap menor = heap[0];
        fprintf(saida, "%d\n", menor.valor);

        int prox;
        if (fscanf(entrada[menor.origem], "%d", &prox) == 1) {
            heap[0].valor = prox;
        } else {
            heap[0] = heap[ativos - 1];
            ativos--;
        }

        heapify(heap, ativos, 0);
    }

    for (int i = 0; i < n_arquivos; i++) {
        if (entrada[i]) fclose(entrada[i]);
    }

    fclose(saida);
}

void intercalar_runs(const char* arquivo_saida, int total_runs) {
    // 1. Gera os nomes iniciais: run0.txt, run1.txt, ...
    char** arquivos = malloc(sizeof(char*) * total_runs);
    for (int i = 0; i < total_runs; i++) {
        arquivos[i] = malloc(32);
        gerar_nome_run(arquivos[i], i);
    }

    int rodada = 0;
    int num_arquivos = total_runs;

    while (num_arquivos > 1) {
        int novos = 0;
        int grupos = (num_arquivos + MAX_K - 1) / MAX_K;

        char** novos_arquivos = malloc(sizeof(char*) * grupos);

        for (int i = 0; i < grupos; i++) {
            int inicio = i * MAX_K;
            int fim = inicio + MAX_K;
            if (fim > num_arquivos) fim = num_arquivos;

            // Prepara nomes para o grupo atual
            int tamanho_grupo = fim - inicio;
            char** grupo = malloc(sizeof(char*) * tamanho_grupo);
            for (int j = 0; j < tamanho_grupo; j++) {
                grupo[j] = arquivos[inicio + j];
            }

            // Nome do arquivo temporário de saída
            novos_arquivos[i] = malloc(32);
            sprintf(novos_arquivos[i], "temp_%d_%d.txt", rodada, i);

            // Faz a intercalação deste grupo
            intercalar_grupo(grupo, tamanho_grupo, novos_arquivos[i]);

            free(grupo);
            novos++;
        }

        // Libera arquivos antigos
        for (int i = 0; i < num_arquivos; i++) {
            free(arquivos[i]);
        }
        free(arquivos);

        // Prepara para próxima rodada
        arquivos = novos_arquivos;
        num_arquivos = novos;
        rodada++;
    }

    // Renomeia o último arquivo para arquivo_saida
    rename(arquivos[0], arquivo_saida);
    free(arquivos[0]);
    free(arquivos);
}