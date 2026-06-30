#ifndef TRABALHO_H
#define TRABALHO_H

#define MAX 100

typedef struct {
    int id;
    char arquivo[50];
    int paginas;
    char tipo; // 'N' para Normal, 'P' para Prioritário
} Trabalho;

#endif
