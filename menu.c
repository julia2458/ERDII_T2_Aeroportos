#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "estrutura.h"

// Listar todos os voos a partir de um aeroporto
void listarVoos(Grafo *grafo, const char *codigoOrigem) {
    int origem = buscarAeroporto(grafo, codigoOrigem);
    if (origem == -1) {
        printf("Aeroporto de origem nao encontrado.\n");
        return;
    }

    printf("Voos a partir de %s (%s):\n", grafo->aeroportos[origem].nome, grafo->aeroportos[origem].codigo);
    int encontrou = 0;
    for (int j = 0; j < grafo->tamanho; j++) {
        if (grafo->matrizAdjacencia[origem][j] != 0) {
            printf("Voo %d -> %s (%s)\n", grafo->matrizAdjacencia[origem][j],
                   grafo->aeroportos[j].nome, grafo->aeroportos[j].codigo);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhum voo encontrado a partir deste aeroporto.\n");
    }
}

bool encontrouCaminho;

// Função auxiliar (recursiva) para busca em profundidade (DFS)
void dfs(Grafo *grafo, int atual, int destino, bool *visitado, int *caminho, int nivel) {
    visitado[atual] = true;
    caminho[nivel] = atual;

    if (atual == destino) {
        encontrouCaminho = true;
        printf("Caminho encontrado: ");
        for (int i = 0; i <= nivel; i++) {
            printf("%s", grafo->aeroportos[caminho[i]].codigo);
            if (i != nivel) printf(" -> ");
        }
        printf("\n");
        visitado[atual] = false;
        return;
    }

    for (int i = 0; i < grafo->tamanho; i++) {
        if (grafo->matrizAdjacencia[atual][i] != 0 && !visitado[i]) {
            dfs(grafo, i, destino, visitado, caminho, nivel + 1);
        }
    }

    visitado[atual] = false;
}

// Função principal para buscar caminhos entre dois aeroportos
void buscarTrajetos(Grafo *grafo, const char *origemCod, const char *destinoCod) {
    int origem = buscarAeroporto(grafo, origemCod);
    int destino = buscarAeroporto(grafo, destinoCod);

    if (origem == -1 || destino == -1) {
        printf("Erro: Aeroporto de origem ou destino nao encontrado.\n");
        return;
    }

    bool *visitado = calloc(grafo->tamanho, sizeof(bool));
    int *caminho = malloc(grafo->tamanho * sizeof(int));
    encontrouCaminho = false;

    printf("Buscando caminhos de %s para %s...\n", origemCod, destinoCod);
    dfs(grafo, origem, destino, visitado, caminho, 0);

    if (!encontrouCaminho) {
        printf("Nenhum caminho encontrado de %s para %s.\n", origemCod, destinoCod);
    }

    free(visitado);
    free(caminho);
}

// Menu interativo
void menu(Grafo *grafo) {
    int opcao;
    char codOrigem[4], codDestino[4], nome[100];
    int numero;

    do {
        printf("\n======= MENU =======\n");
        printf("1. Cadastrar aeroporto\n");
        printf("2. Cadastrar voo\n");
        printf("3. Remover voo\n");
        printf("4. Listar voos de um aeroporto\n");
        printf("5. Buscar trajetos entre aeroportos\n");
        printf("6. Mostrar matriz de adjacencia\n");
        printf("0. Sair\n");
        printf("====================\n");
        char entrada[10];
        printf("Escolha: ");
        fgets(entrada, sizeof(entrada), stdin);

        entrada[strcspn(entrada, "\n")] = '\0';

        bool valido = true;
        for (int i = 0; entrada[i] != '\0'; i++) {
            if (entrada[i] < '0' || entrada[i] > '9') {
                valido = false;
                break;
            }
        }

        if (!valido) {
            printf("Entrada invalida. Digite apenas numeros.\n");
            continue;
        }

        opcao = atoi(entrada);

        switch (opcao) {
            case 1:
                printf("Codigo do aeroporto (3 letras): ");
                scanf("%3s", codOrigem);
                getchar();  // limpa \n
                printf("Nome da cidade: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                adicionarAeroporto(grafo, codOrigem, nome);
                break;

            case 2:
                printf("Codigo da origem: ");
                scanf("%3s", codOrigem);
                getchar();
                printf("Codigo do destino: ");
                scanf("%3s", codDestino);
                getchar();
                printf("Numero do voo: ");
                scanf("%d", &numero);
                getchar();
                adicionarVoo(grafo, codOrigem, codDestino, numero);
                break;

            case 3:
                printf("Numero do voo: ");
                scanf("%d", &numero);
                getchar();
                removerVoo(grafo, numero);
                break;

            case 4:
                printf("Codigo do aeroporto: ");
                scanf("%3s", codOrigem);
                getchar();
                listarVoos(grafo, codOrigem);
                break;

            case 5:
                printf("Codigo da origem: ");
                scanf("%3s", codOrigem);
                getchar();
                printf("Codigo do destino: ");
                scanf("%3s", codDestino);
                getchar();
                buscarTrajetos(grafo, codOrigem, codDestino);
                break;

            case 6:
                imprimirMatrizAdjacencia(grafo);
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);
}
