#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estrutura.h"

//FUNÇÕES

//Criar Grafo
Grafo *criarGrafo(){
    Grafo *grafo = malloc(sizeof(Grafo));
    grafo->tamanho = 0;
    grafo->aeroportos = NULL;
    grafo->matrizAdjacencia = NULL;
    return grafo;
}

//Buscar Aeroporto 
int buscarAeroporto(Grafo *grafo, const char *codigo){
    for (int i = 0; i < grafo->tamanho; i++) {
        if (strcmp(grafo->aeroportos[i].codigo, codigo) == 0){
            return i;
        } 
    }
    return -1;
}

//Adicionar Aeroporto + Ajustar Matriz de Adjacência
void adicionarAeroporto(Grafo *grafo, const char *codigo, const char *nome) {
    
    if (buscarAeroporto(grafo, codigo) != -1) {
        printf("Aeroporto com o código '%s' já está cadastrado.\n", codigo);
        return;
    }

    // Realocar vetor de aeroportos
    Aeroporto *novoAeroportos = realloc(grafo->aeroportos, (grafo->tamanho + 1) * sizeof(Aeroporto));
    if (novoAeroportos == NULL) {
        printf("Erro ao alocar memoria para aeroportos.\n");
        return;
    }
    grafo->aeroportos = novoAeroportos;

    strcpy(grafo->aeroportos[grafo->tamanho].codigo, codigo);
    strcpy(grafo->aeroportos[grafo->tamanho].nome, nome);

    // Realocar matriz de adjacência
    int **novaMatriz = realloc(grafo->matrizAdjacencia, (grafo->tamanho + 1) * sizeof(int *));
    if (novaMatriz == NULL) {
        printf("Erro ao alocar memoria para matriz de adjacencia.\n");
        return;
    }
    grafo->matrizAdjacencia = novaMatriz;

    grafo->matrizAdjacencia[grafo->tamanho] = malloc((grafo->tamanho + 1) * sizeof(int));
    if (grafo->matrizAdjacencia[grafo->tamanho] == NULL) {
        printf("Erro ao alocar memória para nova linha da matriz.\n");
        return;
    }

    // Realocar as linhas antigas para o novo tamanho
    for (int i = 0; i < grafo->tamanho; i++) {
        int *linhaRealocada = realloc(grafo->matrizAdjacencia[i], (grafo->tamanho + 1) * sizeof(int));
        if (linhaRealocada == NULL) {
            printf("Erro ao realocar linha da matriz.\n");
            return;
        }
        grafo->matrizAdjacencia[i] = linhaRealocada;
    }

    // Inicializar a nova linha com zeros
    for (int j = 0; j < grafo->tamanho + 1; j++) {
        grafo->matrizAdjacencia[grafo->tamanho][j] = 0;
    }

    // Inicializar nova coluna nas linhas anteriores com zero
    for (int i = 0; i < grafo->tamanho; i++) {
        grafo->matrizAdjacencia[i][grafo->tamanho] = 0;
    }

    grafo->tamanho++;
    printf("Aeroporto %s (%s) cadastrado com sucesso.\n", nome, codigo);
}

//Adicionar Voo
void adicionarVoo(Grafo *grafo, const char *origem, const char *destino, int numero) {
    int i = buscarAeroporto(grafo, origem);
    int j = buscarAeroporto(grafo, destino);

    if (i == -1) {
        printf("Aeroporto de origem '%s' não encontrado.\n", origem);
        return;
    }

    if (j == -1) {
        printf("Aeroporto de destino '%s' não encontrado.\n", destino);
        return;
    }

    grafo->matrizAdjacencia[i][j] = numero;
    printf("Voo %d cadastrado de %s para %s com sucesso.\n", numero, origem, destino);
}


//Remover Voo
void removerVoo(Grafo *grafo, const char * origem, const char * destino){
    int i = buscarAeroporto(grafo, origem);
    int j = buscarAeroporto(grafo, destino);

    
    if (grafo->matrizAdjacencia[i][j] == 0) {
        printf("Nenhum voo encontrado de %s para %s.\n", origem, destino);
        return;
    }

    grafo->matrizAdjacencia[i][j] = 0;
    printf("Voo de %s para %s removido com sucesso.\n", origem, destino);
}


//Liberar Grafo
void liberarGrafo(Grafo *grafo) {
    for (int i = 0; i < grafo -> tamanho; i++) {
        free(grafo->matrizAdjacencia[i]);
    }
    free(grafo->matrizAdjacencia);
    free(grafo->aeroportos);
    free(grafo);
}

//Imprimir Matriz de Adjacência
void imprimirMatrizAdjacencia(Grafo *grafo) {
    printf("\nMatriz de Adjacencia:\n");

    // Imprime cabeçalho de colunas com os códigos dos aeroportos
    printf("     "); // Espaço inicial para alinhar com cabeçalho de linha
    for (int j = 0; j < grafo->tamanho; j++) {
        printf("%4s ", grafo->aeroportos[j].codigo);
    }
    printf("\n");

    // Imprime linha por linha com os códigos dos aeroportos na lateral
    for (int i = 0; i < grafo->tamanho; i++) {
        printf("%4s ", grafo->aeroportos[i].codigo);  // Código da linha
        for (int j = 0; j < grafo->tamanho; j++) {
            printf("%4d ", grafo->matrizAdjacencia[i][j]);
        }
        printf("\n");
    }
}
