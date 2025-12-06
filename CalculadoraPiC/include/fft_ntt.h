#ifndef FFT_NTT_H
#define FFT_NTT_H

#include "bigint_core.h"

// Multiplicação usando Transformada Numérica Teórica (NTT)
// Ideal para números extremamente grandes, complexidade O(N log N)
void bigint_multiplicar_fft(const GrandeInteiro *a, const GrandeInteiro *b, GrandeInteiro *resultado);

#endif // FFT_NTT_H
