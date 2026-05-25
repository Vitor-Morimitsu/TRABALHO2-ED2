#ifndef VERTICE_H
#define VERTICE_H
#include <stdio.h>
#include <stdlib.h>
/*
    Arquivo .h responsável pela criação e manipulação de um vértice.
*/

typedef void* Vertice;

/// @brief Cria e retorna um novo vértice
/// @param id Id do novo vertice
/// @param x Coordenada x
/// @param y Coordenada y
/// @return Vertice criado
Vertice criarVertice(char* id, double x, double y);

/// @brief Retorna o ID do vertice 
/// @param v Vertice
/// @return Id
char* getIDVertice(Vertice v);

/// @brief Retorna a coordenada x do vertice
/// @param v Vertice
/// @return Coordenada x
double getXVertice(Vertice v);

/// @brief Retorna a coordenada y do vertice
/// @param v Vertice
/// @return Coordenada y
double getYVertice(Vertice v);

#endif