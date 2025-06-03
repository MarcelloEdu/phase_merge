#ifndef RUN_H
#define RUN_H

#define TAMANHO_RUN 10000 // Tamanho de cada run
// Gera arquivos temporários com blocos de 10.000 elementos cada
void gerar_runs(const char* arquivo_entrada, int tamanho_run);

// Ordena as runs geradas com heapsort (retorna número total de runs criadas)
int ordenar_runs(const char* arquivo_entrada);

#endif
