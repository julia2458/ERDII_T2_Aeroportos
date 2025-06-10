//Definição ESTRUTURA_H
#ifndef ESTRUTURA_H
#define ESTRUTURA_H

//Declaração das Estruturas Aeroporto e Grafo

typedef struct {
    char codigo[3];
    char nome[100];
}Aeroporto;

typedef struct {
    Aeroporto *aeroportos; // Declaração do ponteiro "aeroporto" para elementos da estrutura "Aeroporto"
    int **matrizAdjacencia;
    int tamanho; //Número de aeroportos cadastrados
}Grafo;

//Declaração das Funções Principais
Grafo* criarGrafo();
void liberarGrafo(Grafo *grafo);
int buscarAeroporto(Grafo *grafo, const char *codigo);
void adicionarAeroporto(Grafo *grafo, const char *codigo, const char *nome);
//void removerAeroporto(Grafo *grafo, int codigo);
void adicionarVoo(Grafo *grafo, int origem, int destino, int numero);
void removerVoo(Grafo *grafo, int origem, int destino);
void imprimirMatrizAdjacencia(Grafo *grafo);

#endif