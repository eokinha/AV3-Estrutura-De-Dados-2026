#include <stdio.h>
#include "filas.h"

void listarFilas() {
    printf("\n--- Fila Prioritaria (Circular) ---\n");
    if (qtdP == 0) {
        printf("Vazia.\n");
    } else {
        for (int i = 0; i < qtdP; i++) {
            int pos = (inicioP + i) % MAX;
            printf("ID: %d | Arquivo: %s | %d pag(s)\n", filaPrioridade[pos].id, filaPrioridade[pos].arquivo, filaPrioridade[pos].paginas);
        }
    }

    printf("\n--- Fila Normal (Simples) ---\n");
    if (qtdN == 0) {
        printf("Vazia.\n");
    } else {
        for (int i = inicioN; i < fimN; i++) {
            printf("ID: %d | Arquivo: %s | %d pag(s)\n", filaNormal[i].id, filaNormal[i].arquivo, filaNormal[i].paginas);
        }
    }
}
