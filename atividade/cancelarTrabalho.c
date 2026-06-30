#include <stdio.h>
#include "filas.h"

void cancelarTrabalho() {
    int idCancela, cancelado = 0;
    printf("\nDigite o ID do trabalho para cancelar: ");
    scanf("%d", &idCancela);

    for (int i = 0; i < qtdP; i++) {
        int pos = (inicioP + i) % MAX;
        if (filaPrioridade[pos].id == idCancela) {
            for (int j = i; j < qtdP - 1; j++) {
                int atual = (inicioP + j) % MAX;
                int prox = (inicioP + j + 1) % MAX;
                filaPrioridade[atual] = filaPrioridade[prox];
            }
            fimP = (fimP - 1 + MAX) % MAX;
            qtdP--;
            cancelado = 1;
            printf("Trabalho ID %d cancelado com sucesso da Fila Prioritaria.\n", idCancela);
            break;
        }
    }

    if (!cancelado) {
        for (int i = inicioN; i < fimN; i++) {
            if (filaNormal[i].id == idCancela) {
                for (int j = i; j < fimN - 1; j++) {
                    filaNormal[j] = filaNormal[j + 1];
                }
                fimN--;
                qtdN--;
                cancelado = 1;
                printf("Trabalho ID %d cancelado com sucesso da Fila Normal.\n", idCancela);
                break;
            }
        }
    }

    if (!cancelado) {
        printf("Falha: Trabalho ID %d nao encontrado.\n", idCancela);
    }
}
