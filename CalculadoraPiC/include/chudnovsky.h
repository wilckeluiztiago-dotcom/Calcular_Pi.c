#ifndef CHUDNOVSKY_H
#define CHUDNOVSKY_H

#include "bigint_core.h"

// Constantes do algoritmo de Chudnovsky
// A = 13591409
// B = 545140134
// C = 640320
// C^3 / 24 = 10939058860032000

// Função principal para calcular Pi
// precisao_digitos: número de dígitos decimais desejados
void calcular_pi_chudnovsky(size_t precisao_digitos, GrandeInteiro *pi_resultado);

#endif // CHUDNOVSKY_H
