#include <stdio.h>
#include "filas.h"

void processarProximo() {
    printf("\n--- Processando Proximo Trabalho ---\n");

    if (qtdP > 0) {
        Trabalho t = filaPrioridade[inicioP];
        inicioP = (inicioP + 1) % MAX;
        qtdP--;
        printf("Processado [PRIORIDADE]: ID %d | %s | %d pag(s)\n", t.id, t.arquivo, t.paginas);
    }
    else if (qtdN > 0) {
        Trabalho t = filaNormal[inicioN];
        inicioN++;
        qtdN--;
        printf("Processado [NORMAL]: ID %d | %s | %d pag(s)\n", t.id, t.arquivo, t.paginas);
    }
    else {
        printf("A fila de impressao esta vazia.\n");
    }
}
