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

    if (verificar_ordenacao("saida.txt")){
        printf("✅ Arquivo final está ordenado corretamente.\n");
    }else{
        printf("❌ Arquivo final NÃO está ordenado corretamente.\n");
    }

    remover_temporarios(); // limpa runs e arquivos intermediários


    return 0;
}