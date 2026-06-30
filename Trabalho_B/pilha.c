#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

void inicializarPilha(Pilha *p){ p->topo = NULL; }

int pilhaVazia(Pilha *p){ return p->topo == NULL; }

int protocoloExiste(Pilha *p, int protocolo){
    No *aux = p->topo;
    while(aux != NULL){
        if(aux->dados.protocolo == protocolo) return 1;
        aux = aux->prox;
    }
    return 0;
}

void push(Pilha *p, Chamada c){
    No *novo = malloc(sizeof(No));
    if(novo == NULL){
        printf("Erro de memoria!\n");
        return;
    }
    novo->dados = c;
    novo->prox = p->topo;
    p->topo = novo;
    printf("Chamada registrada com sucesso!\n");
}

void pop(Pilha *p){
    if(pilhaVazia(p)){
        printf("Nenhuma chamada para atender.\n");
        return;
    }
    No *remover = p->topo;
    printf("\nAtendendo protocolo %d\n", remover->dados.protocolo);
    p->topo = remover->prox;
    free(remover);
}

void peek(Pilha *p){
    if(pilhaVazia(p)){
        printf("Pilha vazia.\n");
        return;
    }
    printf("\nUltima chamada registrada:\n");
    printf("Protocolo: %d\n", p->topo->dados.protocolo);
    printf("Local: %s\n", p->topo->dados.local);
    printf("Tipo: %s\n", p->topo->dados.tipo);
    printf("Horario: %s\n", p->topo->dados.horario);
}

void listarChamadas(Pilha *p){
    if(pilhaVazia(p)){
        printf("Nenhuma chamada cadastrada.\n");
        return;
    }
    No *aux = p->topo;
    while(aux != NULL){
        printf("\nProtocolo: %d\n", aux->dados.protocolo);
        printf("Local: %s\n", aux->dados.local);
        printf("Tipo: %s\n", aux->dados.tipo);
        printf("Horario: %s\n", aux->dados.horario);
        aux = aux->prox;
    }
}

void liberarPilha(Pilha *p){
    No *aux;
    while(p->topo != NULL){
        aux = p->topo;
        p->topo = p->topo->prox;
        free(aux);
    }
}
