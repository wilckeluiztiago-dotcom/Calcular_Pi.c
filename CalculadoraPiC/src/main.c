#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bigint_core.h"
#include "chudnovsky.h"
#include "io_manager.h"
#include "utils.h"

#define DIGITOS_PADRAO 1000

void exibir_banner() {
    printf("================================================================\n");
    printf("   Calculadora de Pi de Alta Precisão (C) - Luiz Tiago Wilcke   \n");
    printf("================================================================\n");
    printf("Algoritmo: Chudnovsky com Binary Splitting\n");
    printf("Bibliotecas: BigInt Customizado, FFT/NTT (Simulado/Base)\n");
    printf("================================================================\n\n");
}

int main(int argc, char *argv[]) {
    exibir_banner();

    size_t digitos = DIGITOS_PADRAO;

    if (argc > 1) {
        digitos = strtoull(argv[1], NULL, 10);
    } else {
        printf("Uso: %s [numero_de_digitos]\n", argv[0]);
        printf("Nenhum argumento fornecido. Usando padrão: %zu digitos.\n\n", digitos);
    }

    if (digitos == 0) {
        fprintf(stderr, "Erro: Número de dígitos inválido.\n");
        return 1;
    }

    // Preparação
    printf("[INFO] Alocando recursos para %zu digitos...\n", digitos);
    iniciar_cronometro();

    // Como Pi é aprox 3, precisamos de espaço para a parte inteira + decimais
    // Cada digito decimal ocupa log2(10) bits ~= 3.32 bits.
    // Nossa struct BigInt cresce dinamicamente, mas podemos estimar.
    
    GrandeInteiro *pi = criar_grande_inteiro(1); // Capacidade inicial mínima, cresce sozinho

    // Cálculo
    printf("[INFO] Iniciando cálculo...\n");
    calcular_pi_chudnovsky(digitos, pi);

    double tempo_calc = parar_cronometro();
    printf("\n[SUCESSO] Cálculo concluído em %.4f segundos.\n", tempo_calc);

    // Salvamento
    printf("[INFO] Salvando resultado em 'pi_resultado.txt'...\n");
    salvar_pi_em_arquivo(pi, "pi_resultado.txt");

    // Limpeza
    liberar_grande_inteiro(pi);
    
    printf("\nProcesso finalizado com sucesso.\n");
    return 0;
}
