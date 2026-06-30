#include <stdio.h>
#include "filas.h"

int main() {
    int opcao = -1;

    while (opcao != 0) {
        printf("\n===================================\n");
        printf("       GERENCIADOR DE IMPRESSAO      \n");
        printf("===================================\n");
        printf("1. Enfileirar Trabalho\n");
        printf("2. Processar Proximo Trabalho\n");
        printf("3. Listar Ambas as Filas\n");
        printf("4. Buscar Trabalho por ID\n");
        printf("5. Cancelar Trabalho\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: enfileirar(); break;
            case 2: processarProximo(); break;
            case 3: listarFilas(); break;
            case 4: buscarTrabalho(); break;
            case 5: cancelarTrabalho(); break;
            case 0: printf("Encerrando o gerenciador de impressao...\n"); break;
            default: printf("Opcao invalida. Tente novamente.\n");
        }
    }

    return 0;
}
