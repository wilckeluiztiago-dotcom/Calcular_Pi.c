#ifndef BIGINT_MULTIPLICACAO_H
#define BIGINT_MULTIPLICACAO_H

#include "bigint_core.h"

// Multiplicação "Escolar" O(N^2) - Eficiente para números pequenos
void bigint_multiplicar_basico(const GrandeInteiro *a, const GrandeInteiro *b, GrandeInteiro *resultado);

// Multiplicação Karatsuba O(N^1.585) - Eficiente para números médios
void bigint_multiplicar_karatsuba(const GrandeInteiro *a, const GrandeInteiro *b, GrandeInteiro *resultado);

// Wrapper que escolhe o melhor algoritmo baseado no tamanho
void bigint_multiplicar(const GrandeInteiro *a, const GrandeInteiro *b, GrandeInteiro *resultado);

#endif // BIGINT_MULTIPLICACAO_H
