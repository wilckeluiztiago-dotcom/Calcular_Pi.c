#include "io_manager.h"
#include <stdio.h>
#include <stdlib.h>

// Função auxiliar para converter binário (base 2^64) para decimal
// Para 100M dígitos, a conversão ingênua O(N^2) é muito lenta.
// O ideal é usar Divisão e Conquista (Recursiva).
// Aqui faremos uma implementação simplificada que escreve o valor bruto (hex ou similar)
// ou uma conversão básica para demonstrar, dado que a conversão real é tão complexa quanto o cálculo.

void salvar_pi_em_arquivo(const GrandeInteiro *pi, const char *caminho_arquivo) {
    FILE *f = fopen(caminho_arquivo, "w");
    if (!f) {
        fprintf(stderr, "Erro ao abrir arquivo %s para escrita.\n", caminho_arquivo);
        return;
    }

    fprintf(f, "3.\n"); // Pi começa com 3.
    
    // Simulação de escrita dos dígitos decimais
    // Na prática, converteríamos pi->digitos (base 2^64) para base 10^9 e imprimiríamos.
    // Como o cálculo do Pi está simulado no final do chudnovsky.c, aqui também faremos algo simbólico
    // para o arquivo não ficar vazio ou com lixo.
    
    // Se o número for pequeno (nosso caso de teste), imprimimos o valor real
    if (pi->tamanho == 1) {
        fprintf(f, "%lu (Valor de teste)\n", pi->digitos[0]);
    } else {
        fprintf(f, "Conteúdo muito grande para conversão simples nesta versão.\n");
        fprintf(f, "Dígitos brutos (hex):\n");
        for (size_t i = pi->tamanho; i > 0; i--) {
            fprintf(f, "%016lx", pi->digitos[i-1]);
            if ((pi->tamanho - i + 1) % 4 == 0) fprintf(f, "\n");
        }
    }
    
    fclose(f);
    printf("Resultado salvo em %s\n", caminho_arquivo);
}
