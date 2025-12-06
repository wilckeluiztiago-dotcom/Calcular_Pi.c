#include "binary_splitting.h"
#include "bigint_aritmetica.h"
#include "bigint_multiplicacao.h"
#include <stdio.h>

// Constantes de Chudnovsky
// A = 13591409
// B = 545140134
// C = 640320

void bs_chudnovsky(size_t a, size_t b, GrandeInteiro *P, GrandeInteiro *Q, GrandeInteiro *T) {
    if (b - a == 1) {
        // Caso base: calcular P(a, a+1), Q(a, a+1), T(a, a+1)
        // P(a) = (6a - 5)(2a - 1)(6a - 1)
        // Q(a) = a^3 * C^3 / 24
        // T(a) = P(a) * (A + B*a)
        // Se a = 0:
        // P(0) = 1
        // Q(0) = 1
        // T(0) = P(0) * (A + B*0) = A = 13591409
        
        if (a == 0) {
            definir_valor_ui64(P, 1);
            definir_valor_ui64(Q, 1);
            definir_valor_ui64(T, 13591409);
        } else {
            // Implementação simplificada para demonstração
            // P = (6a-5)... requer multiplicação de inteiros grandes se 'a' for grande
            // Como 'a' é size_t, cabe em uint64 até certo ponto, mas o produto não.
            // Precisamos converter 'a' para BigInt e fazer as contas.
            
            // P = 1 (placeholder)
            definir_valor_ui64(P, 1);
            // Q = 1 (placeholder)
            definir_valor_ui64(Q, 1);
            // T = 1 (placeholder)
            definir_valor_ui64(T, 1);
        }
        return;
    }
    
    size_t m = (a + b) / 2;
    
    GrandeInteiro *P_am = criar_grande_inteiro(1);
    GrandeInteiro *Q_am = criar_grande_inteiro(1);
    GrandeInteiro *T_am = criar_grande_inteiro(1);
    
    GrandeInteiro *P_mb = criar_grande_inteiro(1);
    GrandeInteiro *Q_mb = criar_grande_inteiro(1);
    GrandeInteiro *T_mb = criar_grande_inteiro(1);
    
    // Recursão Esquerda
    bs_chudnovsky(a, m, P_am, Q_am, T_am);
    
    // Recursão Direita
    bs_chudnovsky(m, b, P_mb, Q_mb, T_mb);
    
    // Combinar:
    // P = P_am * P_mb
    // Q = Q_am * Q_mb
    // T = Q_mb * T_am + P_am * T_mb
    
    bigint_multiplicar(P_am, P_mb, P);
    bigint_multiplicar(Q_am, Q_mb, Q);
    
    GrandeInteiro *tmp1 = criar_grande_inteiro(1);
    GrandeInteiro *tmp2 = criar_grande_inteiro(1);
    
    bigint_multiplicar(Q_mb, T_am, tmp1);
    bigint_multiplicar(P_am, T_mb, tmp2);
    bigint_adicionar(tmp1, tmp2, T);
    
    liberar_grande_inteiro(P_am); liberar_grande_inteiro(Q_am); liberar_grande_inteiro(T_am);
    liberar_grande_inteiro(P_mb); liberar_grande_inteiro(Q_mb); liberar_grande_inteiro(T_mb);
    liberar_grande_inteiro(tmp1); liberar_grande_inteiro(tmp2);
}
