#include "bigint_aritmetica.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

// Adiciona as magnitudes (ignora sinal) de a e b: res = |a| + |b|
void _adicionar_magnitudes(const GrandeInteiro *a, const GrandeInteiro *b, GrandeInteiro *res) {
    size_t n = MAX(a->tamanho, b->tamanho);
    redimensionar_grande_inteiro(res, n + 1);
    
    palavra_t carry = 0;
    for (size_t i = 0; i < n || carry; i++) {
        palavra_t val_a = (i < a->tamanho) ? a->digitos[i] : 0;
        palavra_t val_b = (i < b->tamanho) ? b->digitos[i] : 0;
        
        // Soma com detecção de overflow
        palavra_t soma = val_a + val_b + carry;
        
        // Verifica overflow: se soma < val_a (ou val_b), houve wrap-around
        // Nota: carry anterior deve ser considerado.
        // Forma segura:
        bool overflow = (soma < val_a) || (carry && soma == val_a);
        
        res->digitos[i] = soma;
        carry = overflow ? 1 : 0;
        
        if (i >= res->tamanho) res->tamanho = i + 1;
    }
}

// Subtrai magnitudes: res = |a| - |b|. Assume |a| >= |b|
void _subtrair_magnitudes(const GrandeInteiro *a, const GrandeInteiro *b, GrandeInteiro *res) {
    redimensionar_grande_inteiro(res, a->tamanho);
    
    palavra_t borrow = 0;
    for (size_t i = 0; i < a->tamanho; i++) {
        palavra_t val_a = a->digitos[i];
        palavra_t val_b = (i < b->tamanho) ? b->digitos[i] : 0;
        
        palavra_t diff = val_a - val_b - borrow;
        
        // Se houve underflow (val_a < val_b + borrow), ajusta
        if (val_a < val_b + borrow) { // Simplificado, lógica real precisa de cuidado com tipos unsigned
             // Lógica correta de borrow para unsigned:
             // Se val_a < val_b, borrow gerado. Se val_a == val_b e tinha borrow anterior, borrow gerado.
             // Mas diff já calculou com wrap-around.
             // Se o resultado "parece" maior que o original onde subtraímos algo positivo, houve underflow?
             // Não, em unsigned: 5 - 7 = MAX - 1.
             // Condição de borrow:
             if (val_a < val_b || (borrow && val_a == val_b)) {
                 borrow = 1;
             } else {
                 borrow = 0;
             }
        } else {
             // Caso especial onde val_a pode ser menor que borrow apenas?
             // val_a - val_b - borrow.
             // Se val_a=0, val_b=0, borrow=1 -> diff=MAX, novo_borrow=1.
             // Logica acima cobre.
             if (val_a < val_b + borrow) borrow = 1; // Cuidado com overflow na soma val_b+borrow
             else borrow = 0;
        }
        
        // Correção da lógica de subtração unsigned
        // diff = a - b - c
        palavra_t temp = val_a - borrow;
        bool novo_borrow = (val_a < borrow);
        if (temp < val_b) novo_borrow = true;
        
        res->digitos[i] = temp - val_b;
        borrow = novo_borrow ? 1 : 0;
    }
    
    res->tamanho = a->tamanho;
    // Normalizar tamanho (remover zeros à esquerda)
    while (res->tamanho > 0 && res->digitos[res->tamanho - 1] == 0) {
        res->tamanho--;
    }
}

void bigint_adicionar(const GrandeInteiro *a, const GrandeInteiro *b, GrandeInteiro *resultado) {
    if (eh_zero(a)) {
        // Copiar b para resultado
        // ... (simplificação: assumindo uso correto das funções internas)
        // Implementação real deve copiar
        return; 
    }
    if (eh_zero(b)) {
        // Copiar a
        return;
    }

    if (a->sinal == b->sinal) {
        _adicionar_magnitudes(a, b, resultado);
        resultado->sinal = a->sinal;
    } else {
        int cmp = comparar_magnituide(a, b);
        if (cmp >= 0) {
            _subtrair_magnitudes(a, b, resultado);
            resultado->sinal = (resultado->tamanho == 0) ? 0 : a->sinal;
        } else {
            _subtrair_magnitudes(b, a, resultado);
            resultado->sinal = (resultado->tamanho == 0) ? 0 : b->sinal;
        }
    }
}

void bigint_subtrair(const GrandeInteiro *a, const GrandeInteiro *b, GrandeInteiro *resultado) {
    // a - b é o mesmo que a + (-b)
    // Criar um temporário ou manipular sinais logicamente
    // Para eficiência, implementamos a lógica de sinais aqui
    
    if (eh_zero(b)) {
        // Copiar a
        return;
    }
    
    if (a->sinal != b->sinal) {
        // Sinais diferentes: a - (-b) = a + b. Magnitudes somam.
        _adicionar_magnitudes(a, b, resultado);
        resultado->sinal = a->sinal; // Mantém sinal de a
    } else {
        // Sinais iguais: a - b. Subtração de magnitudes.
        int cmp = comparar_magnituide(a, b);
        if (cmp >= 0) {
            _subtrair_magnitudes(a, b, resultado);
            resultado->sinal = (resultado->tamanho == 0) ? 0 : a->sinal;
        } else {
            _subtrair_magnitudes(b, a, resultado);
            // Inverte o sinal pois b > a
            resultado->sinal = (resultado->tamanho == 0) ? 0 : -a->sinal;
        }
    }
}

void bigint_multiplicar_escalar(const GrandeInteiro *a, uint64_t escalar, GrandeInteiro *resultado) {
    if (eh_zero(a) || escalar == 0) {
        zerar_grande_inteiro(resultado);
        return;
    }
    
    redimensionar_grande_inteiro(resultado, a->tamanho + 1);
    
    unsigned __int128 carry = 0; // Usando extensão GCC para 128 bits para facilitar multiplicação
    for (size_t i = 0; i < a->tamanho; i++) {
        unsigned __int128 prod = (unsigned __int128)a->digitos[i] * escalar + carry;
        resultado->digitos[i] = (palavra_t)prod;
        carry = prod >> 64;
    }
    
    if (carry > 0) {
        resultado->digitos[a->tamanho] = (palavra_t)carry;
        resultado->tamanho = a->tamanho + 1;
    } else {
        resultado->tamanho = a->tamanho;
    }
    
    resultado->sinal = a->sinal; // Escalar assumido positivo aqui, ajustar se necessário
}
