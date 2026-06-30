#ifndef FILAS_H
#define FILAS_H

#include "trabalho.h"

extern Trabalho filaNormal[MAX];
extern int inicioN;
extern int fimN;
extern int qtdN;

extern Trabalho filaPrioridade[MAX];
extern int inicioP;
extern int fimP;
extern int qtdP;

void enfileirarNormal(Trabalho t);
void enfileirarPrioridade(Trabalho t);
void enfileirar(void);
void processarProximo(void);
void listarFilas(void);
void buscarTrabalho(void);
void cancelarTrabalho(void);

#endif
