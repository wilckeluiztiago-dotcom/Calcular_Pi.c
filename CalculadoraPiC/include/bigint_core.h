#ifndef BIGINT_CORE_H
#define BIGINT_CORE_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

// Definição do tipo base para os dígitos (64 bits para eficiência em sistemas modernos)
typedef uint64_t palavra_t;
#define BITS_PALAVRA 64

// Estrutura principal para representar um Grande Inteiro
typedef struct {
    palavra_t *digitos;     // Array dinâmico de dígitos
    size_t capacidade;      // Tamanho alocado do array
    size_t tamanho;         // Número de dígitos usados
    int sinal;              // 1 para positivo, -1 para negativo, 0 para zero
} GrandeInteiro;

// Funções de gerenciamento de memória e inicialização
GrandeInteiro* criar_grande_inteiro(size_t capacidade_inicial);
void liberar_grande_inteiro(GrandeInteiro *gi);
void zerar_grande_inteiro(GrandeInteiro *gi);
GrandeInteiro* copiar_grande_inteiro(const GrandeInteiro *origem);
void redimensionar_grande_inteiro(GrandeInteiro *gi, size_t nova_capacidade);
void definir_valor_ui64(GrandeInteiro *gi, uint64_t valor);

// Utilitários
bool eh_zero(const GrandeInteiro *gi);
int comparar_magnituide(const GrandeInteiro *a, const GrandeInteiro *b);

#endif // BIGINT_CORE_H
