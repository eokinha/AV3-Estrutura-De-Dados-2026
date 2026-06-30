#include <stdio.h>
#include "filas.h"

Trabalho filaNormal[MAX];
int inicioN = 0;
int fimN = 0;
int qtdN = 0;

void enfileirarNormal(Trabalho t) {
    if (fimN >= MAX) {
        printf("Erro: Fila normal cheia!\n");
        return;
    }
    filaNormal[fimN] = t;
    fimN++;
    qtdN++;
    printf("Trabalho '%s' adicionado a fila Normal.\n", t.arquivo);
}
