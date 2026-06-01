#ifndef GRAFO_H
#define GRAFO_H
#include <stdio.h>
#include <stdlib.h>
#include "vertice.h"
#include "aresta.h"
/*
    Arquivo responsável por criar e manipular um grafo
*/
typedef void* Grafo;

Grafo criarGrafo();

void inserirGrafo(Grafo g, Vertice v);

void removerGrafo(Grafo g, Vertice v);

void liberarGrafo(Grafo g, Vertice v);

#endif