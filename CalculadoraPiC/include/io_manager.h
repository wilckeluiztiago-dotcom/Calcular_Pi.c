#ifndef IO_MANAGER_H
#define IO_MANAGER_H

#include "bigint_core.h"

// Salva o GrandeInteiro em um arquivo de texto, convertendo para decimal
// Esta função deve ser otimizada para não estourar a memória ao converter números gigantes
void salvar_pi_em_arquivo(const GrandeInteiro *pi, const char *caminho_arquivo);

#endif // IO_MANAGER_H
