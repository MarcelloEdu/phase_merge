#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

// Função auxiliar de troca
void trocar(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapfy(int arr[], int n, int i) {
    int menor = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    // Verifica se o filho da esquerda é menor que a raiz
    if (esquerda < n && arr[esquerda] < arr[menor]) {
        menor = esquerda;
    }

    // Verifica se o filho da direita é menor que o menor até agora
    if (direita < n && arr[direita] < arr[menor]) {
        menor = direita;
    }

    // Se o menor elemento não for a raiz, troca e continua a heapificação
    if (menor != i) {
        trocar(&arr[i], &arr[menor]);
        heapfy(arr, n, menor);
    }
}

void build_heap(int arr[], int n) {
    int ultimo = (n/2) - 1; // Último nó não folha
    for (int i = ultimo; i >= 0; i--) {
        heapfy(arr, n, i);
    }
}

void heapsort(int arr[], int n) {
    // Etapa 1: Construir o heap
    build_heap(arr, n);

    // 2. Extrair elementos um por um da heap
    for (int i = n - 1; i > 0; i--) {
        // Move a raiz atual (menor elemento) para o fim
        trocar(&arr[0], &arr[i]);

        // Chama heapfy na heap reduzida
        heapfy(arr, i, 0);
    }

    //inverto o array para crescente
    for (int i = 0; i < n / 2; i++) {
        trocar(&arr[i], &arr[n - i - 1]);
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

void limpar_runs(const char *nome_base_run, int num_runs) {
    printf("\nETAPA 3: Limpando arquivos temporários...\n");
    for (int i = 0; i < num_runs; i++) {
        char nome_arquivo_run[32];
        sprintf(nome_arquivo_run, "%s%d.txt", nome_base_run, i);

        if (remove(nome_arquivo_run) == 0) {
            // Sucesso, pode opcionalmente imprimir uma mensagem de depuração
            // printf("Arquivo removido: %s\n", nome_arquivo_run);
        } else {
            // Falha, imprime um erro
            fprintf(stderr, "Erro ao remover o arquivo: %s\n", nome_arquivo_run);
        }
    }
    printf("=> Limpeza concluída.\n");
}