#include "utils.h"
#include <stdio.h>
#include <time.h>

static clock_t inicio;

void iniciar_cronometro() {
    inicio = clock();
}

double parar_cronometro() {
    clock_t fim = clock();
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

void atualizar_progresso(double porcentagem) {
    int barra_largura = 50;
    
    printf("\r[");
    int pos = (int)(barra_largura * porcentagem);
    for (int i = 0; i < barra_largura; ++i) {
        if (i < pos) printf("=");
        else if (i == pos) printf(">");
        else printf(" ");
    }
    printf("] %d %%", (int)(porcentagem * 100.0));
    fflush(stdout);
}
