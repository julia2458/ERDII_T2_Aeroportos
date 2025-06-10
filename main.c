#include <stdio.h>
#include "estrutura.h"

void menu(Grafo *grafo);

int main() {
    Grafo *grafo = criarGrafo();
    menu(grafo);
    liberarGrafo(grafo);
    return 0;
}
