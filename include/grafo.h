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

/// @brief Cria e retorna um grafo
/// @return Grafo criado
Grafo criarGrafo();

/// @brief Insere um vertice no grafo
/// @param g Grafo
/// @param v Vertice
/// @return Retorna o indice 
int inserirVerticeGrafo(Grafo g, Vertice v);

/// @brief Insere uma aresta entre dois índices
/// @param g Grafo
/// @param origem Origem da aresta
/// @param destino Destino da aresta
/// @param dados Dados da aresta
void inserirArestaGrafo(Grafo g, int origem, int destino, Aresta dados);

VerticeGrafo getVerticeGrafo(Grafo g);

/// @brief Busca um vertice com base na id
/// @param g Grafo
/// @param id id do vertice
/// @return id do vertice
int buscarVerticeIDGrafo(Grafo g, char* id);

/// @brief Libera a memória do grafo
/// @param g Grafo
void liberarGrafo(Grafo g);

#endif