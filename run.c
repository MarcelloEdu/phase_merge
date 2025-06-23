#include <stdio.h>
#include <stdlib.h>

#include "run.h"
#include "utils.h" // Inclui para ter acesso ao heapsort() e trocar()

void gerar_runs(const char* arquivo_entrada, int run_size) {
    FILE* entrada = fopen(arquivo_entrada, "r");
    if (!entrada) {
        perror("Erro ao abrir arquivo de entrada");
        return;
    }

    int* buffer = malloc(run_size * sizeof(int));
    if (!buffer) {
        perror("Erro ao alocar memória para a run");
        fclose(entrada);
        return;
    }

    int run_index = 0;
    int n_lidos;

    while (!feof(entrada)) {
        n_lidos = 0;

        for (int i = 0; i < run_size; i++) {
            if (fscanf(entrada, "%d", &buffer[i]) == 1) {
                n_lidos++;
            } else {
                break;
            }
        }

        if (n_lidos == 0) break;

        char nome_run[32];
        gerar_nome_run(nome_run, run_index++);

        FILE* run = fopen(nome_run, "w");
        if (!run) {
            perror("Erro ao criar arquivo de run");
            break;
        }

        for (int i = 0; i < n_lidos; i++) {
            fprintf(run, "%d\n", buffer[i]);
        }

        fclose(run);
    }

    free(buffer);
    fclose(entrada);
}

int ordenar_runs(const char* arquivo_entrada) {
    // 1. Gera as runs brutas a partir do arquivo original
    gerar_runs(arquivo_entrada, TAMANHO_RUN);

    // 2. Conta quantas runs foram geradas
    int total_runs = contar_runs();

    // 3. Buffer para leitura dos dados
    int* buffer = malloc(TAMANHO_RUN * sizeof(int));
    if (!buffer) {
        perror("Erro ao alocar memória para a run");
        return -1;
    }

    // 4. Abre, ordena e reescreve cada run
    for (int i = 0; i < total_runs; i++) {
        char nome_arquivo[32];
        gerar_nome_run(nome_arquivo, i);

        FILE* run = fopen(nome_arquivo, "r");
        if (!run) {
            perror("Erro ao abrir run para ordenação");
            continue;
        }

        int n_lidos = 0;
        for (int j = 0; j < TAMANHO_RUN; j++) {
            if (fscanf(run, "%d", &buffer[j]) == 1) {
                n_lidos++;
            } else {
                break;
            }
        }

        fclose(run);

        // Ordena os dados da run
        heapsort(buffer, n_lidos);

        // Reabre o mesmo arquivo para sobrescrever
        run = fopen(nome_arquivo, "w");
        if (!run) {
            perror("Erro ao reabrir run para sobrescrever");
            continue;
        }

        for (int j = 0; j < n_lidos; j++) {
            fprintf(run, "%d\n", buffer[j]);
        }

        fclose(run);
    }

    free(buffer);
    return total_runs;
}
