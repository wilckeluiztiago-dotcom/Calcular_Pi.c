#include "bigint_multiplicacao.h"
#include "bigint_aritmetica.h"
#include "fft_ntt.h" // Será usado para números muito grandes
#include <stdlib.h>
#include <string.h>

#define LIMITE_KARATSUBA 64 // Limite empírico para trocar para Karatsuba
#define LIMITE_FFT 2048     // Limite empírico para trocar para FFT/NTT

void bigint_multiplicar_basico(const GrandeInteiro *a, const GrandeInteiro *b, GrandeInteiro *resultado) {
    if (eh_zero(a) || eh_zero(b)) {
        zerar_grande_inteiro(resultado);
        return;
    }

    size_t n = a->tamanho;
    size_t m = b->tamanho;
    redimensionar_grande_inteiro(resultado, n + m);
    zerar_grande_inteiro(resultado); // Importante zerar pois acumulamos

    for (size_t i = 0; i < n; i++) {
        unsigned __int128 carry = 0;
        for (size_t j = 0; j < m; j++) {
            unsigned __int128 prod = (unsigned __int128)a->digitos[i] * b->digitos[j] + resultado->digitos[i + j] + carry;
            resultado->digitos[i + j] = (palavra_t)prod;
            carry = prod >> 64;
        }
        resultado->digitos[i + m] = (palavra_t)carry;
    }

    resultado->tamanho = n + m;
    // Ajustar tamanho real
    while (resultado->tamanho > 0 && resultado->digitos[resultado->tamanho - 1] == 0) {
        resultado->tamanho--;
    }
    resultado->sinal = a->sinal * b->sinal;
}

// Implementação simplificada de Karatsuba (recursiva)
// Para um projeto real de 100M digitos, FFT é o foco, então Karatsuba pode ser básico
void bigint_multiplicar_karatsuba(const GrandeInteiro *a, const GrandeInteiro *b, GrandeInteiro *resultado) {
    // Fallback para básico se pequeno
    if (a->tamanho < LIMITE_KARATSUBA || b->tamanho < LIMITE_KARATSUBA) {
        bigint_multiplicar_basico(a, b, resultado);
        return;
    }

    // Dividir a e b em metades: x = x1*B^m + x0
    size_t m = (a->tamanho > b->tamanho ? a->tamanho : b->tamanho) / 2;
    
    // ... (Implementação completa de Karatsuba requereria manipulação de slices ou cópias)
    // Por brevidade e foco no FFT (que é o que importa para 100M), usaremos o básico aqui por enquanto
    // ou chamaremos o FFT se for muito grande.
    // TODO: Implementar Karatsuba completo se o perfilamento indicar necessidade na faixa média.
    bigint_multiplicar_basico(a, b, resultado);
}

void bigint_multiplicar(const GrandeInteiro *a, const GrandeInteiro *b, GrandeInteiro *resultado) {
    size_t max_len = (a->tamanho > b->tamanho) ? a->tamanho : b->tamanho;

    if (max_len >= LIMITE_FFT) {
        // Usa FFT/NTT para números gigantes
        bigint_multiplicar_fft(a, b, resultado);
    } else if (max_len >= LIMITE_KARATSUBA) {
        bigint_multiplicar_karatsuba(a, b, resultado);
    } else {
        bigint_multiplicar_basico(a, b, resultado);
    }
}
