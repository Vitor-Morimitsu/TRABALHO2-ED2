#ifndef VIA_H
#define VIA_H

#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include "vertice.h"
#include "aresta.h"
#include "grafo.h"
/*
    Arquivo responsável por criar e manipular um arquivo via
*/

/// @brief Função responsável por ler um arquivo via para gerar as quadras e grafos
/// @param via Arquivo
/// @param quadras arvore que contém as quadras que serão inseridas
void lerVia(FILE* via,Arvore quadras,Grafo grafo);

#endif