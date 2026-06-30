#include <stdio.h>
#include "estoque.h"

/* ============================================================================
 * FUNÇÃO PRINCIPAL (Ponto de Entrada do Programa)
 * ============================================================================ */
int main() {
    Produto estoque[MAX];
    int qtd = 0;
    int opcao;

    // FASE 1: Carregamento do Banco de Dados em arquivo CSV
    carregar_csv(estoque, &qtd);

    // FASE 2: Loop do Menu Iterativo
    do {
        printf("\n============================================\n");
        printf("           SISTEMA CONTROLE DE ESTOQUE      \n");
        printf("============================================\n");
        printf("1. Inserir Produto (Ordenado)\n");
        printf("2. Buscar Produto por Codigo\n");
        printf("3. Editar Produto\n");
        printf("4. Excluir Produto\n");
        printf("5. Listar Todos os Produtos\n");
        printf("0. Salvar e Sair\n");
        printf("============================================\n");
        printf("Escolha uma opcao: ");
        opcao = ler_inteiro();

        switch (opcao) {
            case 1: {
                printf("\n--- CADASTRAR NOVO PRODUTO ---\n");
                
                // Validação de Estoque Cheio (Limite de capacidade física da lista)
                if (qtd >= MAX) {
                    printf("[ERRO] Estoque Cheio! Nao é possivel cadastrar mais produtos.\n");
                    break;
                }

                printf("Digite o codigo (unico): ");
                int codigo = ler_inteiro();

                // Validação de Código Único (Impedir cadastros duplicados)
                if (buscar_indice(codigo, estoque, qtd) != -1) {
                    printf("[ERRO] Produto com codigo %d ja esta cadastrado. O codigo deve ser unico!\n", codigo);
                    break;
                }

                char nome[50];
                printf("Digite o nome: ");
                ler_string(nome, sizeof(nome));

                printf("Digite a quantidade: ");
                int quantidade = ler_inteiro();

                printf("Digite o preco (float): ");
                float preco = ler_float();

                // Chamada da função de inserção ordenada
                int resultado = inserir_produto(estoque, &qtd, codigo, nome, quantidade, preco);
                if (resultado == 0) {
                    printf("[SUCESSO] Produto cadastrado e ordenado com sucesso!\n");
                } else if (resultado == -1) {
                    printf("[ERRO] Falha ao inserir: Estoque Cheio!\n");
                } else if (resultado == -2) {
                    printf("[ERRO] Falha ao inserir: Codigo duplicado!\n");
                }
                break;
            }
            case 2: {
                printf("\n--- BUSCAR PRODUTO ---\n");
                
                // Validação de Estoque Vazio
                if (qtd == 0) {
                    printf("[ERRO] Estoque Vazio!\n");
                    break;
                }

                printf("Digite o codigo do produto a buscar: ");
                int codigo = ler_inteiro();

                // Uso da função auxiliar obrigatória para obter o índice
                int idx = buscar_indice(codigo, estoque, qtd);
                if (idx == -1) {
                    printf("[ERRO] Produto com codigo %d nao encontrado.\n", codigo);
                } else {
                    printf("\nProduto Encontrado na posicao (indice) %d:\n", idx);
                    exibir_produto(&estoque[idx]);
                }
                break;
            }
            case 3: {
                printf("\n--- EDITAR PRODUTO ---\n");
                
                if (qtd == 0) {
                    printf("[ERRO] Estoque Vazio!\n");
                    break;
                }

                printf("Digite o codigo do produto a editar: ");
                int codigo = ler_inteiro();

                int idx = buscar_indice(codigo, estoque, qtd);
                if (idx == -1) {
                    printf("[ERRO] Produto nao cadastrado.\n");
                } else {
                    printf("\nProduto Atual:\n");
                    exibir_produto(&estoque[idx]);
                    printf("---------------------------------------\n");
                    printf("Nota: O codigo do produto nao pode ser alterado.\n");
                    
                    char novo_nome[50];
                    printf("Digite o novo nome: ");
                    ler_string(novo_nome, sizeof(novo_nome));

                    printf("Digite a nova quantidade: ");
                    int nova_quantidade = ler_inteiro();

                    printf("Digite o novo preco: ");
                    float novo_preco = ler_float();

                    editar_produto(estoque, qtd, codigo, novo_nome, nova_quantidade, novo_preco);
                    printf("[SUCESSO] Produto editado com sucesso!\n");
                }
                break;
            }
            case 4: {
                printf("\n--- EXCLUIR PRODUTO ---\n");
                
                if (qtd == 0) {
                    printf("[ERRO] Estoque Vazio!\n");
                    break;
                }

                printf("Digite o codigo do produto a excluir: ");
                int codigo = ler_inteiro();

                int resultado = excluir_produto(estoque, &qtd, codigo);
                if (resultado == 0) {
                    printf("[SUCESSO] Produto removido do estoque e vetor reorganizado!\n");
                } else if (resultado == -1) {
                    printf("[ERRO] Estoque Vazio!\n");
                } else if (resultado == -2) {
                    printf("[ERRO] Produto com codigo %d nao encontrado.\n", codigo);
                }
                break;
            }
            case 5:
                listar_todos(estoque, qtd);
                break;

            case 0:
                // FASE 3: Gravação final do arquivo CSV ao sair
                salvar_csv(estoque, qtd);
                printf("Encerrando o programa de controle de estoque!\n");
                break;

            default:
                printf("[AVISO] Opcao invalida! Escolha um valor do menu (0 a 5).\n");
        }
    } while (opcao != 0);

    return 0;
}