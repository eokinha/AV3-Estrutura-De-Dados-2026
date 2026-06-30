#include <stdio.h>
#include "filas.h"

void buscarTrabalho() {
    int idBusca, encontrado = 0;
    printf("\nDigite o ID do trabalho que deseja buscar: ");
    scanf("%d", &idBusca);

    for (int i = 0; i < qtdP; i++) {
        int pos = (inicioP + i) % MAX;
        if (filaPrioridade[pos].id == idBusca) {
            printf("Status: Encontrado na Fila PRIORITARIA | Arquivo: %s | %d pag(s)\n", filaPrioridade[pos].arquivo, filaPrioridade[pos].paginas);
            encontrado = 1;
        }
    }

    for (int i = inicioN; i < fimN; i++) {
        if (filaNormal[i].id == idBusca) {
            printf("Status: Encontrado na Fila NORMAL | Arquivo: %s | %d pag(s)\n", filaNormal[i].arquivo, filaNormal[i].paginas);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Trabalho ID %d nao encontrado em nenhuma fila.\n", idBusca);
    }
}
