#ifndef BINARY_SPLITTING_H
#define BINARY_SPLITTING_H

#include "bigint_core.h"

// Executa o Binary Splitting para a série de Chudnovsky no intervalo [a, b)
// Retorna P, Q, T por referência
void bs_chudnovsky(size_t a, size_t b, GrandeInteiro *P, GrandeInteiro *Q, GrandeInteiro *T);

#endif // BINARY_SPLITTING_H
