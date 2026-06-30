#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estoque.h"

/* ============================================================================
 * IMPLEMENTAÇÃO DAS FUNÇÕES AUXILIARES E DE ENTRADA
 * ============================================================================ */
void ler_string(char *destino, int tamanho) {
    if (fgets(destino, tamanho, stdin) != NULL) {
        int len = strlen(destino);
        // Remove a quebra de linha (\n ou \r) deixada pelo fgets
        if (len > 0 && (destino[len - 1] == '\n' || destino[len - 1] == '\r')) {
            destino[strcspn(destino, "\r\n")] = '\0';
        } else {
            // Se o usuário digitou mais caracteres do que o buffer suporta, limpa o buffer restante da stdin
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}

/**
 * Lê uma linha de entrada de texto e converte em inteiro (robusto contra lixo de buffer).
 */
int ler_inteiro() {
    char buffer[50];
    ler_string(buffer, sizeof(buffer));
    return atoi(buffer);
}

/**
 * Lê uma linha de entrada de texto e converte em float (robusto contra lixo de buffer).
 */
float ler_float() {
    char buffer[50];
    ler_string(buffer, sizeof(buffer));
    return atof(buffer);
}

/**
 * Exibe os dados estruturados de um único produto de forma legível.
 */
void exibir_produto(const Produto *p) {
    printf("  Codigo:     %d\n", p->codigo);
    printf("  Nome:       %s\n", p->nome);
    printf("  Quantidade: %d unidades\n", p->quantidade);
    printf("  Preco:      R$ %.2f\n", p->preco);
}

/* ============================================================================
 * OPERAÇÕES DA LISTA SEQUENCIAL (Algoritmos e Estruturas de Dados)
 * ============================================================================ */

int buscar_indice(int codigo, const Produto estoque[], int qtd) {
    for (int i = 0; i < qtd; i++) {
        if (estoque[i].codigo == codigo) {
            return i; // Retorna o índice onde o código foi encontrado
        }
    }
    return -1; // Retorna -1 indicando que o produto não foi encontrado
}

int inserir_produto(Produto estoque[], int *qtd, int codigo, const char nome[], int quantidade, float preco) {
    // 1. Validação de capacidade
    if (*qtd >= MAX) {
        return -1;
    }

    // 2. Garantia de Unicidade de Chave
    if (buscar_indice(codigo, estoque, *qtd) != -1) {
        return -2;
    }

    // 3. Encontrar a posição correta de inserção ordenada
    int pos = 0;
    while (pos < *qtd && estoque[pos].codigo < codigo) {
        pos++;
    }

    // 4. Deslocamento para a Direita (para abrir espaço)
    // Começa do último elemento atual (*qtd) e vai copiando para a direita até chegar em 'pos'
    for (int i = *qtd; i > pos; i--) {
        estoque[i] = estoque[i - 1];
    }

    // 5. Inserir o elemento na posição aberta
    estoque[pos].codigo = codigo;
    strncpy(estoque[pos].nome, nome, sizeof(estoque[pos].nome) - 1);
    estoque[pos].nome[sizeof(estoque[pos].nome) - 1] = '\0'; // Segurança da string
    estoque[pos].quantidade = quantidade;
    estoque[pos].preco = preco;

    // 6. Atualiza o controle lógico de quantidade
    (*qtd)++;

    return 0;
}

int editar_produto(Produto estoque[], int qtd, int codigo, const char nome[], int quantidade, float preco) {
    int idx = buscar_indice(codigo, estoque, qtd);
    if (idx == -1) {
        return -1;
    }

    // Atualiza os dados (O código do produto NUNCA muda)
    strncpy(estoque[idx].nome, nome, sizeof(estoque[idx].nome) - 1);
    estoque[idx].nome[sizeof(estoque[idx].nome) - 1] = '\0';
    estoque[idx].quantidade = quantidade;
    estoque[idx].preco = preco;

    return 0;
}
int excluir_produto(Produto estoque[], int *qtd, int codigo) {
    // 1. Validação de Estoque Vazio
    if (*qtd == 0) {
        return -1;
    }

    // 2. Encontrar o índice do elemento a ser excluído
    int idx = buscar_indice(codigo, estoque, *qtd);
    if (idx == -1) {
        return -2;
    }

    // 3. Deslocamento para a Esquerda (sobrepor o buraco de remoção)
    // Copia o elemento da direita para a posição atual
    for (int i = idx; i < *qtd - 1; i++) {
        estoque[i] = estoque[i + 1];
    }

    // 4. Decrementa a quantidade lógica da lista
    (*qtd)--;

    return 0;
}

void listar_todos(const Produto estoque[], int qtd) {
    printf("\n--- RELATORIO GERAL DE ESTOQUE ---\n");
    if (qtd == 0) {
        printf("[INFO] Estoque Vazio!\n");
        return;
    }

    printf("%-6s | %-25s | %-10s | %-12s\n", "Codigo", "Nome do Produto", "Quantidade", "Preco (Unit)");
    printf("-----------------------------------------------------------------\n");
    for (int i = 0; i < qtd; i++) {
        printf("%-6d | %-25s | %-10d | R$ %-9.2f\n", 
               estoque[i].codigo, 
               estoque[i].nome, 
               estoque[i].quantidade, 
               estoque[i].preco);
    }
    printf("Total de tipos de produtos cadastrados: %d / %d\n", qtd, MAX);
}

/* ============================================================================
 * FASE DE PERSISTÊNCIA (Operações de Arquivo CSV)
 * ============================================================================ */

void carregar_csv(Produto estoque[], int *qtd) {
    FILE *arq = fopen("dados_a.csv", "r");
    if (!arq) {
        // Regra: se o arquivo não existir, tratar erro sem quebrar o programa
        printf("[INFO] Arquivo de persistencia 'dados_a.csv' nao encontrado.\n");
        printf("       Iniciando aplicacao com estoque vazio.\n");
        return;
    }

    char linha[256];
    
    // Ignorar a primeira linha (cabeçalho: codigo;nome;quantidade;preco)
    if (!fgets(linha, sizeof(linha), arq)) {
        fclose(arq);
        return;
    }

    int linhas_carregadas = 0;

    // Processamento linha a linha
    while (fgets(linha, sizeof(linha), arq)) {
        // Tratamento da quebra de linha no final do buffer
        linha[strcspn(linha, "\r\n")] = '\0';

        if (strlen(linha) == 0) {
            continue; // ignora linhas em branco
        }

        // fgets + strtok com separador ';'
        char *token_codigo = strtok(linha, ";");
        char *token_nome = strtok(NULL, ";");
        char *token_qtd = strtok(NULL, ";");
        char *token_preco = strtok(NULL, ";");

        // Validação se a linha CSV possui todas as colunas
        if (token_codigo && token_nome && token_qtd && token_preco) {
            int codigo = atoi(token_codigo);
            int quantidade = atoi(token_qtd);
            float preco = (float)atof(token_preco);

            // Inserir de forma ordenada para manter a integridade da lista
            int res = inserir_produto(estoque, qtd, codigo, token_nome, quantidade, preco);
            if (res == 0) {
                linhas_carregadas++;
            } else if (res == -1) {
                printf("[ALERTA-CSV] Limite de %d produtos atingido ao ler o CSV!\n", MAX);
                break;
            } else if (res == -2) {
                printf("[ALERTA-CSV] Codigo duplicado no CSV detectado: %d (Item ignorado).\n", codigo);
            }
        }
    }

    fclose(arq);
    if (linhas_carregadas > 0) {
        printf("[INFO] Base de dados carregada! %d produtos importados de 'dados_a.csv'.\n", linhas_carregadas);
    }
}

/**
 * GRAVA OS DADOS DO VETOR EM "dados_a.csv":
 * Utiliza o separador ';' e gera obrigatoriamente a primeira linha como cabeçalho:
 * codigo;nome;quantidade;preco
 */
void salvar_csv(const Produto estoque[], int qtd) {
    FILE *arq = fopen("dados_a.csv", "w");
    if (!arq) {
        printf("[ERRO] Nao foi possivel abrir/criar o arquivo 'dados_a.csv' para gravacao.\n");
        return;
    }

    // Gravação estrita da primeira linha de cabeçalho
    fprintf(arq, "codigo;nome;quantidade;preco\n");

    // Gravação dos produtos ordenados
    for (int i = 0; i < qtd; i++) {
        fprintf(arq, "%d;%s;%d;%.2f\n", 
                estoque[i].codigo, 
                estoque[i].nome, 
                estoque[i].quantidade, 
                estoque[i].preco);
    }

    fclose(arq);
    printf("[INFO] Dados salvos com sucesso em 'dados_a.csv'!\n");
}
