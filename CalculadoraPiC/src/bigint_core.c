#include "bigint_core.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Cria um novo GrandeInteiro com a capacidade especificada
GrandeInteiro* criar_grande_inteiro(size_t capacidade_inicial) {
    GrandeInteiro *gi = (GrandeInteiro*)malloc(sizeof(GrandeInteiro));
    if (!gi) {
        fprintf(stderr, "Erro: Falha ao alocar memória para estrutura GrandeInteiro.\n");
        exit(EXIT_FAILURE);
    }
    
    // Garante pelo menos 1 de capacidade
    if (capacidade_inicial == 0) capacidade_inicial = 1;

    gi->digitos = (palavra_t*)calloc(capacidade_inicial, sizeof(palavra_t));
    if (!gi->digitos) {
        fprintf(stderr, "Erro: Falha ao alocar memória para dígitos do GrandeInteiro.\n");
        free(gi);
        exit(EXIT_FAILURE);
    }

    gi->capacidade = capacidade_inicial;
    gi->tamanho = 0; // Inicialmente zero
    gi->sinal = 0;   // Neutro
    return gi;
}

// Libera a memória de um GrandeInteiro
void liberar_grande_inteiro(GrandeInteiro *gi) {
    if (gi) {
        if (gi->digitos) {
            free(gi->digitos);
        }
        free(gi);
    }
}

// Define o valor como zero
void zerar_grande_inteiro(GrandeInteiro *gi) {
    if (gi) {
        memset(gi->digitos, 0, gi->capacidade * sizeof(palavra_t));
        gi->tamanho = 0;
        gi->sinal = 0;
    }
}

// Cria uma cópia profunda de um GrandeInteiro
GrandeInteiro* copiar_grande_inteiro(const GrandeInteiro *origem) {
    if (!origem) return NULL;

    GrandeInteiro *copia = criar_grande_inteiro(origem->capacidade);
    memcpy(copia->digitos, origem->digitos, origem->capacidade * sizeof(palavra_t));
    copia->tamanho = origem->tamanho;
    copia->sinal = origem->sinal;
    
    return copia;
}

// Redimensiona o array de dígitos se necessário
void redimensionar_grande_inteiro(GrandeInteiro *gi, size_t nova_capacidade) {
    if (nova_capacidade <= gi->capacidade) return;

    palavra_t *novos_digitos = (palavra_t*)realloc(gi->digitos, nova_capacidade * sizeof(palavra_t));
    if (!novos_digitos) {
        fprintf(stderr, "Erro: Falha ao realocar memória para GrandeInteiro.\n");
        exit(EXIT_FAILURE);
    }

    // Zera a nova área alocada
    memset(novos_digitos + gi->capacidade, 0, (nova_capacidade - gi->capacidade) * sizeof(palavra_t));

    gi->digitos = novos_digitos;
    gi->capacidade = nova_capacidade;
}

// Define um valor a partir de um uint64_t
void definir_valor_ui64(GrandeInteiro *gi, uint64_t valor) {
    zerar_grande_inteiro(gi);
    if (valor > 0) {
        gi->digitos[0] = valor;
        gi->tamanho = 1;
        gi->sinal = 1;
    }
}

// Verifica se é zero
bool eh_zero(const GrandeInteiro *gi) {
    return gi->tamanho == 0 || gi->sinal == 0;
}

// Compara a magnitude (valor absoluto) de dois números
// Retorna 1 se |a| > |b|, -1 se |a| < |b|, 0 se |a| == |b|
int comparar_magnituide(const GrandeInteiro *a, const GrandeInteiro *b) {
    if (a->tamanho > b->tamanho) return 1;
    if (a->tamanho < b->tamanho) return -1;

    for (size_t i = a->tamanho; i > 0; i--) {
        if (a->digitos[i-1] > b->digitos[i-1]) return 1;
        if (a->digitos[i-1] < b->digitos[i-1]) return -1;
    }

    return 0;
}
