#include <stdio.h>
#include "estrutura.h"

void menu(Grafo *grafo);

int main() {
    Grafo *grafo = criarGrafo();

    // Adiciona aeroportosAdd commentMore actions
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
    adicionarVoo(grafo, "GRU", "GIG", 89);
    adicionarVoo(grafo, "GIG", "GRU", 90);
    adicionarVoo(grafo, "GRU", "BSB", 50);

    menu(grafo);
    liberarGrafo(grafo);
    return 0;
}
