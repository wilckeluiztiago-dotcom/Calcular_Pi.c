#ifndef BIGINT_ARITMETICA_H
#define BIGINT_ARITMETICA_H

#include "bigint_core.h"

// Operações Básicas
void bigint_adicionar(const GrandeInteiro *a, const GrandeInteiro *b, GrandeInteiro *resultado);
void bigint_subtrair(const GrandeInteiro *a, const GrandeInteiro *b, GrandeInteiro *resultado);
void bigint_multiplicar_escalar(const GrandeInteiro *a, uint64_t escalar, GrandeInteiro *resultado);

// Funções auxiliares de baixo nível
void _adicionar_magnitudes(const GrandeInteiro *a, const GrandeInteiro *b, GrandeInteiro *res);
void _subtrair_magnitudes(const GrandeInteiro *a, const GrandeInteiro *b, GrandeInteiro *res);

#endif // BIGINT_ARITMETICA_H
