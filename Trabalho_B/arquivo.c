#include <stdio.h>
#include "arquivo.h"

void carregarArquivo(Pilha *p){
    FILE *arq = fopen("chamadas.csv", "r");
    if(arq == NULL){
        printf("Arquivo inexistente. Sera criado ao salvar.\n");
        return;
    }

    char linha[200];
    fgets(linha, sizeof(linha), arq);

    while(fgets(linha, sizeof(linha), arq)){
        Chamada c;
        int campos = sscanf(linha,"%d;%49[^;];%29[^;];%19[^\n]",
                            &c.protocolo,c.local,c.tipo,c.horario);

        if(campos != 4){
            printf("Linha invalida ignorada: %s", linha);
            continue;
        }

        if(protocoloExiste(p, c.protocolo)){
            printf("Protocolo duplicado ignorado: %d\n", c.protocolo);
            continue;
        }

        push(p, c);
    }
    fclose(arq);
}

void salvarArquivo(Pilha *p){
    FILE *arq = fopen("chamadas.csv", "w");
    if(arq == NULL){
        printf("Erro ao salvar.\n");
        return;
    }

    fprintf(arq,"protocolo;local;tipo;horario\n");

    No *aux = p->topo;
    while(aux != NULL){
        fprintf(arq,"%d;%s;%s;%s\n",
                aux->dados.protocolo,
                aux->dados.local,
                aux->dados.tipo,
                aux->dados.horario);
        aux = aux->prox;
    }
    fclose(arq);
}
