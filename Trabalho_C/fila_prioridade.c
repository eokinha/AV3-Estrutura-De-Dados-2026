#include <stdio.h>
#include "filas.h"

Trabalho filaPrioridade[MAX];
int inicioP = 0;
int fimP = 0;
int qtdP = 0;

void enfileirarPrioridade(Trabalho t) {
    if (qtdP >= MAX) {
        printf("Erro: Fila de prioridade cheia!\n");
        return;
    }
    filaPrioridade[fimP] = t;
    fimP = (fimP + 1) % MAX;
    qtdP++;
    printf("Trabalho '%s' adicionado a fila Prioritaria.\n", t.arquivo);
}
