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
typedef void* VerticeGrafo;
typedef void* ArestaGrafo;

Grafo criarGrafo();

void inserirVerticeGrafo(Grafo g, void* conteudo);

void removerGrafo(Grafo g, Vertice v);

void liberarGrafo(Grafo g, Vertice v);

#endif