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

/// @brief Cria e retorna um grafo
/// @return Grafo criado
Grafo criarGrafo();

/// @brief Insere um vertice no grafo
/// @param g Grafo
/// @param v Vertice
/// @return Retorna o indice do vértice inserido
int inserirVerticeGrafo(Grafo g, Vertice v);

/// @brief Insere uma aresta entre dois índices
/// @param g Grafo
/// @param origem Índice do vértice de origem
/// @param destino Índice do vértice de destino
/// @param dados Dados da aresta
void inserirArestaGrafo(Grafo g, int origem, int destino, Aresta dados);

/// @brief Retorna o número de vértices do grafo
/// @param g Grafo
/// @return Número de vértices
int getNumVerticesGrafo(Grafo g);

/// @brief Retorna o vértice de um dado índice
/// @param g Grafo
/// @param idx Índice do vértice
/// @return Vertice
Vertice getVerticeGrafo(Grafo g, int idx);

/// @brief Busca um vertice com base na id
/// @param g Grafo
/// @param id id do vertice
/// @return índice do vértice, ou -1 se não encontrado
int buscarVerticeIDGrafo(Grafo g, char* id);

/// @brief Retorna a primeira célula de aresta de um vértice (cabeça da lista)
/// @param g Grafo
/// @param idx Índice do vértice
/// @return Ponteiro opaco para a célula de aresta
void* getPrimeiraArestaGrafo(Grafo g, int idx);

/// @brief Retorna a próxima célula de aresta
/// @param celulaAresta Célula atual
/// @return Ponteiro opaco para a próxima célula
void* getProximaAresta(void* celulaAresta);

/// @brief Retorna os dados (Aresta) de uma célula
/// @param celulaAresta Célula
/// @return Aresta
Aresta getDadosAresta(void* celulaAresta);

/// @brief Retorna o índice do vértice de destino de uma célula
/// @param celulaAresta Célula
/// @return Índice do vértice de destino
int getDestinoAresta(void* celulaAresta);

/// @brief Libera a memória do grafo (incluindo vértices e arestas)
/// @param g Grafo
void liberarGrafo(Grafo g);

#endif