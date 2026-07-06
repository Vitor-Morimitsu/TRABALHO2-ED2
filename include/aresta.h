#ifndef ARESTA_H
#define ARESTA_H
#include <stdio.h>
#include <stdlib.h>
#include "vertice.h"
/*
    Arquivo responsável pela criação e manipulação de uma aresta
*/

typedef void* Aresta;

/// @brief Cria e retorna uma aresta
/// @param nome Nome da rua
/// @param ldir cep da quadra que está ao lado direito do segmento
/// @param lesq cep da quadra que está do lado esquerdo do segmento
/// @param cmp comprimento(em metros) do segmento da rua
/// @param vm velocidade méida(m/s) que os carros trafegam neste segmento da rua
/// @return 
Aresta criarAresta(char* nome, char* ldir, char* lesq, double cmp,double vm);

/// @brief Define os vertices da aresta
/// @param a aresta
/// @param v1 vertice de inicio
/// @param v2 vertice de fim
void setVerticesAresta(Aresta a, Vertice v1, Vertice v2);

/// @brief Retorna o nome da aresta
/// @param a aresta
/// @return nome da aresta
char* getNomeAresta(Aresta a);

/// @brief Retorna o cep da quadra do lado direito
/// @param a aresta
/// @return CEP da quadra da direita
char* getCEP_ladoDireitoAresta(Aresta a);

/// @brief Retorna o cep da quadra do lado esquerdo
/// @param a aresta
/// @return CEP da quadra da esquerda
char* getCEP_ladoEsquerdoAresta(Aresta a);

/// @brief Retorna o comprimento da aresta
/// @param a aresta
/// @return comprimento
double getCmpAresta(Aresta a);

void setVmAresta(Aresta a, double novaVm);

/// @brief Retorna a velocidade media(m/s) da via
/// @param a aresta
/// @return Velocidade media
double getVmAresta(Aresta a);

/// @brief Retorna o primeiro vértice da aresta
/// @param a Aresta
/// @return Vertice
Vertice getVerticeV1(Aresta a);

/// @brief Retorna o segundo vértice da aresta
/// @param a Aresta
/// @return Vertice
Vertice getVerticeV2(Aresta a);

/// @brief Libera a memória alocada para uma aresta
/// @param a Aresta
void liberarAresta(Aresta a);

#endif