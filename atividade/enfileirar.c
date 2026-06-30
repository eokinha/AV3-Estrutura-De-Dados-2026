#include <stdio.h>
#include "filas.h"

void enfileirar() {
    Trabalho t;
    printf("\n--- Novo Trabalho de Impressao ---\n");
    printf("ID: ");
    scanf("%d", &t.id);
    printf("Nome do arquivo (ex: arquivo.pdf): ");
    scanf(" %49[^\n]", t.arquivo);
    printf("Quantidade de paginas: ");
    scanf("%d", &t.paginas);
    printf("Tipo (N - Normal, P - Prioritario): ");
    scanf(" %c", &t.tipo);

    if (t.tipo == 'P' || t.tipo == 'p') {
        t.tipo = 'P';
        enfileirarPrioridade(t);
    } else {
        t.tipo = 'N';
        enfileirarNormal(t);
    }
}
