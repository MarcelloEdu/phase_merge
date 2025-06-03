#include <stdio.h>
#include "run.h"

int main() {
    const char* arquivo_entrada = "entrada.txt";

    printf("Iniciando geração e ordenação das runs...\n");
    int total_runs = ordenar_runs(arquivo_entrada);

    if (total_runs >= 0) {
        printf("Processo concluído com sucesso.\n");
        printf("Total de runs geradas e ordenadas: %d\n", total_runs);
    } else {
        printf("Erro ao processar o arquivo de entrada.\n");
    }

    return 0;
}
