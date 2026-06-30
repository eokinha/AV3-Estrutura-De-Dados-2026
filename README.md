# AV3 — Estruturas de Dados (2026)

Este repositório contém o projeto prático final da disciplina de **Estruturas de Dados**, composto por três aplicações desenvolvidas em linguagem **C** que aplicam os conceitos de Listas Sequenciais, Pilhas e Filas.

---

## 👥 Integrantes e Identificação

*   **Integrantes:**
    *   Lucas Duarte
    *   Luan Galdino
    *   Danilo Bomfim
*   **Turma:** `[42SIF01N3A]`
*   **Repositório:** [AV3-Estrutura-De-Dados-2026](https://github.com/eokinha/AV3-Estrutura-De-Dados-2026)

---

## 📋 Temas Escolhidos

O projeto contempla a resolução de três problemas com estruturas de dados lineares estáticas (vetores de struct):

| Etapa | Estrutura de Dados | Tema Escolhido | Descrição Breve |
| :--- | :--- | :--- | :--- |
| **Trabalho A** | Lista Simples Ordenada | **Tema A2 — Controle de Estoque** | Cadastro, busca, edição e exclusão de produtos mantendo a lista ordenada por código. |
| **Trabalho B** | Pilha Simples | **Tema B2 — Chamadas de Emergência** | Gerenciamento de ocorrências de emergência usando a lógica LIFO (Last-In, First-Out). |
| **Trabalho C** | Filas Simples e Circulares | **Tema C2 — Fila de Impressão** | Escalonamento de trabalhos de impressão (com fila normal e fila prioritária circular). |

---

## ⚙️ Explicação de Cada Programa

### 🔹 Trabalho A: Controle de Estoque (Tema A2)
*   **Objetivo:** Gerenciar o estoque físico de uma empresa com um limite máximo de `100` produtos cadastrados.
*   **Estrutura Utilizada:** Lista linear estática sequencial, implementada via vetor de struct com uma variável de controle para a quantidade lógica de itens.
*   **Regra de Negócio:**
    *   A lista permanece **ordenada automaticamente por código** a cada inserção.
    *   A busca, edição e exclusão são feitas pelo código do produto.
    *   O código de um produto é sua chave primária (única) e não pode ser alterado após o cadastro.
*   **Persistência:** Salva e carrega automaticamente de um arquivo chamado [dados_a.csv](file:///home/lucas/Documentos/Github/AV3-Estrutura-De-Dados-2026/Trabalho_A/dados_a.csv).

### 🔹 Trabalho B: Chamadas de Emergência (Tema B2)
*   **Objetivo:** Simular o despacho de incidentes para viaturas ou equipes de resgate.
*   **Estrutura Utilizada:** Pilha sequencial (LIFO - Last-In, First-Out). O último chamado registrado no sistema é sempre o primeiro a receber atendimento.
*   **Regra de Negócio:**
    *   Registrar chamada equivale ao *empilhamento (push)*.
    *   Atender chamada equivale ao *desempilhamento (pop)*.
    *   Consultar a última ocorrência cadastrada equivale a visualizar o *topo (peek)*.
    *   Cada chamada possui: protocolo (único), local da ocorrência, tipo e horário.
*   **Persistência:** Salva e carrega os dados em arquivo CSV.

### 🔹 Trabalho C: Fila de Impressão (Tema C2)
*   **Objetivo:** Simular uma central de impressão que processa trabalhos normais e prioritários.
*   **Estrutura Utilizada:** Duas filas estáticas distintas:
    1.  Uma **Fila Normal** simples.
    2.  Uma **Fila Circular** simples destinada exclusivamente a trabalhos prioritários.
*   **Regra de Negócio:**
    *   Trabalhos prioritários (tipo `P`) têm precedência absoluta de processamento. Eles sempre são impressos/processados primeiro.
    *   Trabalhos normais (tipo `N`) são processados apenas se a fila prioritária estiver completamente vazia.
    *   Caso ambas as filas estejam vazias, o sistema aguarda novas entradas.
    *   Permite cancelar trabalhos que ainda estão na fila, reorganizando a estrutura de forma linear ou circular.
*   **Persistência:** Salva e carrega os dados em arquivo CSV.

---

## 🛠️ Instruções para Compilar e Executar

As aplicações foram projetadas para compilação em ambiente Linux utilizando o compilador `gcc`.

### 📂 Trabalho A (Controle de Estoque)
Para compilar e executar o controle de estoque, utilize os seguintes comandos no terminal:

1.  Navegue até a pasta do Trabalho A:
    ```bash
    cd Trabalho_A
    ```
2.  Compile o código-fonte:
    ```bash
    gcc -Wall trabalho_a.c estoque.c -o programa
    ```
3.  Execute a aplicação:
    ```bash
    ./programa
    ```

### 📂 Trabalho B (Chamadas de Emergência)
1.  Navegue até a pasta do Trabalho B (quando criada):
    ```bash
    cd Trabalho_B
    ```
2.  Compile o código-fonte:
    ```bash
    gcc -Wall trabalho_b.c -o programa
    ```
3.  Execute a aplicação:
    ```bash
    ./programa
    ```

### 📂 Trabalho C (Fila de Impressão)
1.  Navegue até a pasta do Trabalho C (quando criada):
    ```bash
    cd Trabalho_C
    ```
2.  Compile o código-fonte:
    ```bash
    gcc -Wall trabalho_c.c -o programa
    ```
3.  Execute a aplicação:
    ```bash
    ./programa
    ```

---

## 🔍 Observações sobre o Funcionamento

*   **Gravação de Arquivos:** Ao selecionar a opção `0. Salvar e Sair` nos menus interativos, os programas efetuam a escrita completa da estrutura no arquivo CSV correspondente. Se o programa for fechado abruptamente (ex: `Ctrl + C`), as alterações da sessão atual não serão persistidas.
*   **Validação de Buffer de Entrada:** Para evitar travamentos infinitos comuns ao tentar ler inteiros/floats inválidos em C (ex: digitação de letras no menu), foi implementada uma leitura robusta que lê toda a linha via string (`fgets`) e a converte usando funções de conversão numérica (`atoi` e `atof`), limpando o excedente do buffer do console.
*   **Limites de Capacidade:** Por utilizarem alocação estática (vetores de struct com tamanho fixo), os limites definidos pelas constantes de capacidade máxima (`MAX`) devem ser respeitados, gerando erros adequados de "Estrutura Cheia" de forma amigável ao usuário.

---

## ⚠️ Dificuldades Encontradas

1.  **Inserção Ordenada com Deslocamento de Vetor (Trabalho A):** A principal dificuldade na lista sequencial foi garantir que novos produtos fossem inseridos de forma ordenada pelo código. Isso exigiu a implementação manual do algoritmo de deslocamento para a direita de todos os elementos superiores ao novo código sem corromper as posições originais.
2.  **Limpeza e Sincronização do Buffer do Teclado (`stdin`):** O manuseio de strings em C juntamente com a leitura de inteiros e decimais frequentemente causava o vazamento de quebras de linha (`\n`), fazendo com que o console pulasse leituras de dados. A criação de funções especializadas como `ler_string` e `ler_inteiro` solucionou esse problema.
3.  **Implementação de Filas Circulares e Tratamento de Índices:** Controlar o início, o fim e o número atual de registros em uma fila circular requer aritmética modular e lógica de controle rigorosa para evitar condições de colisão entre ponteiros lógicos.
