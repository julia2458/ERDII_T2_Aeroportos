#include <stdio.h>
#include "estrutura.h"

int main() {
    // Cria estrutura do grafo
    Grafo *grafo = criarGrafo();

    // Adiciona aeroportos
    adicionarAeroporto(grafo, "CPQ", "Campinas");
    adicionarAeroporto(grafo, "GRU", "Guarulhos");
    adicionarAeroporto(grafo, "GIG", "Rio de Janeiro");
    adicionarAeroporto(grafo, "CNF", "Belo Horizonte");
    adicionarAeroporto(grafo, "SSA", "Salvador");
    adicionarAeroporto(grafo, "BSB", "Brasília");

    // Adiciona voos entre eles
    adicionarVoo(grafo, "SSA", "CNF", 215);
    adicionarVoo(grafo, "BSB", "SSA", 107);
    adicionarVoo(grafo, "CNF", "SSA", 214);
    adicionarVoo(grafo, "CNF", "GIG", 555);
    adicionarVoo(grafo, "GIG", "CNF", 554);
    adicionarVoo(grafo, "CNF", "GRU", 101);
    adicionarVoo(grafo, "GRU", "CNF", 102);
    adicionarVoo(grafo, "GRU", "GIG", 089);
    adicionarVoo(grafo, "GIG", "GRU", 090);
    adicionarVoo(grafo, "GRU", "BSB", 050);

    // Mostra a matriz
    imprimirMatrizAdjacencia(grafo);

    Remove um voo e imprime novamente
    //removerVoo(grafo, "SSA", "CNF");
    //printarMatriz(grafo);

    // Libera tudo
    //liberarGrafo(grafo);

    return 0;
}