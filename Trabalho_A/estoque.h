#ifndef ESTOQUE_H
#define ESTOQUE_H

#define MAX 100

// Definição estrita da Struct Produto conforme especificação do Tema A2.
// Nota Pedagógica: Como 'char nome[]' não pode ser de tamanho indefinido dentro de uma
// struct alocada estaticamente na pilha, definimos um limite seguro de 50 caracteres.
typedef struct {
    int codigo;
    char nome[50];
    int quantidade;
    float preco;
} Produto;

// Funções de leitura e utilidades
void ler_string(char *destino, int tamanho);
int ler_inteiro();
float ler_float();
void exibir_produto(const Produto *p);
void listar_todos(const Produto estoque[], int qtd);

// Operações da Lista Sequencial
int buscar_indice(int codigo, const Produto estoque[], int qtd);
int inserir_produto(Produto estoque[], int *qtd, int codigo, const char nome[], int quantidade, float preco);
int editar_produto(Produto estoque[], int qtd, int codigo, const char nome[], int quantidade, float preco);
int excluir_produto(Produto estoque[], int *qtd, int codigo);

// Fase de Persistência (CSV)
void carregar_csv(Produto estoque[], int *qtd);
void salvar_csv(const Produto estoque[], int qtd);

#endif // ESTOQUE_H
