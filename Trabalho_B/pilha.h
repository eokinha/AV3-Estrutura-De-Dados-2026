#ifndef PILHA_H
#define PILHA_H

typedef struct {
    int protocolo;
    char local[50];
    char tipo[30];
    char horario[20];
} Chamada;

typedef struct No {
    Chamada dados;
    struct No *prox;
} No;

typedef struct {
    No *topo;
} Pilha;

void inicializarPilha(Pilha *p);
int pilhaVazia(Pilha *p);
int protocoloExiste(Pilha *p, int protocolo);
void push(Pilha *p, Chamada c);
void pop(Pilha *p);
void peek(Pilha *p);
void listarChamadas(Pilha *p);
void liberarPilha(Pilha *p);

#endif
