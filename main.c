#include <stdio.h>
#include "run.h"
#include "merge.h"
#include "utils.h"

int main() {
    const char* arquivo_entrada = "entrada.txt";
    const char* arquivo_saida = "saida.txt";

    printf("Gerando e ordenando runs...\n");
    int total_runs = ordenar_runs(arquivo_entrada);
    printf("Total de runs geradas e ordenadas: %d\n", total_runs);

    printf("Intercalando runs...\n");
    intercalar_runs(arquivo_saida, total_runs);
    printf("Arquivo final ordenado salvo como '%s'\n", arquivo_saida);

    return 0;
}