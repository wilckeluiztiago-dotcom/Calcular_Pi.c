#ifndef UTILS_H
#define UTILS_H

#include <time.h>

// Inicia um cronômetro
void iniciar_cronometro();

// Para o cronômetro e retorna o tempo decorrido em segundos
double parar_cronometro();

// Imprime uma barra de progresso
void atualizar_progresso(double porcentagem);

#endif // UTILS_H
