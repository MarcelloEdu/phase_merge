#include <stdio.h>
#include <stdlib.h>

#include "run.h"
#include "utils.h" // Inclui para ter acesso ao heapsort() e trocar()

int gerar_runs(const char* arquivo_entrada, int memoria_max_elementos, const char* nome_base_run) {
    FILE* f_entrada = fopen(arquivo_entrada, "r");
    if (!f_entrada) {
        perror("Erro ao abrir o arquivo de entrada");
        return -1;
    }

    int* buffer = (int*) malloc(memoria_max_elementos * sizeof(int));
    if (!buffer) {
        perror("Falha ao alocar buffer de memória");
        fclose(f_entrada);
        return -1;
    }

    int num_runs = 0;
    int elementos_lidos = 0;

    // Lê o arquivo de entrada em pedaços
    while ((elementos_lidos = fread(buffer, sizeof(int), memoria_max_elementos, f_entrada)) > 0) {
        char nome_arquivo_run[64];
        sprintf(nome_arquivo_run, "%s%d.txt", nome_base_run, num_runs);

        FILE* f_run = fopen(nome_arquivo_run, "w");
        if (!f_run) {
            perror("Erro ao criar arquivo de run");
            free(buffer);
            fclose(f_entrada);
            return -1;
        }

        // Escreve os elementos lidos no arquivo de run
        for (int i = 0; i < elementos_lidos; i++) {
            fprintf(f_run, "%d\n", buffer[i]);
        }

        fclose(f_run);
        num_runs++;
    }

    free(buffer);
    fclose(f_entrada);
    return num_runs;
}

int ordenar_runs(const char* arquivo_entrada, int memoria_max_elementos, const char* nome_base_run) {
    // Primeiro, apenas divide o arquivo em runs menores
    int num_runs = gerar_runs(arquivo_entrada, memoria_max_elementos, nome_base_run);
    if (num_runs <= 0) {
        return num_runs; // Retorna 0 ou -1 em caso de erro/vazio
    }

    printf("=> %d runs geradas. Ordenando cada uma...\n", num_runs);

    // Aloca o buffer uma única vez para reutilização
    int* buffer = (int*) malloc(memoria_max_elementos * sizeof(int));
    if (!buffer) {
        perror("Falha ao alocar buffer para ordenação");
        return -1;
    }

    // Agora, para cada run, carrega, ordena e salva
    for (int i = 0; i < num_runs; i++) {
        char nome_arquivo_run[64];
        sprintf(nome_arquivo_run, "%s%d.txt", nome_base_run, i);

        FILE* f_run = fopen(nome_arquivo_run, "r");
        if (!f_run) {
            fprintf(stderr, "Erro ao reabrir a run %s para ordenação.\n", nome_arquivo_run);
            continue; // Pula para a próxima run em caso de erro
        }

        // Carrega todos os números da run para a memória
        int elementos_lidos = 0;
        while (elementos_lidos < memoria_max_elementos && fscanf(f_run, "%d", &buffer[elementos_lidos]) == 1) {
            elementos_lidos++;
        }
        fclose(f_run);

        // A MÁGICA ACONTECE AQUI: Ordena o buffer usando Heapsort
        heapsort(buffer, elementos_lidos);

        // Reabre o mesmo arquivo em modo de escrita para substituir o conteúdo
        f_run = fopen(nome_arquivo_run, "w");
        if (!f_run) {
            fprintf(stderr, "Erro ao reabrir a run %s para escrita.\n", nome_arquivo_run);
            continue;
        }

        // Salva os dados agora ordenados de volta no arquivo da run
        for (int j = 0; j < elementos_lidos; j++) {
            fprintf(f_run, "%d\n", buffer[j]);
        }
        fclose(f_run);
    }

    free(buffer);
    return num_runs;
}