#ifndef LISTA_H
#define LISTA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quadra.h"

typedef void* Lista;
typedef void* CelulaLista;

Lista criarLista();

/*
Insere um pacote no final da lista.
*/
void insereLista(Lista l, void* conteudo);

/*
Retorna o tamanho da lista.
*/
int getTamanhoLista(Lista l);

/*
Retorna o conteudo de uma celula.
*/
void* getConteudoCelula(CelulaLista celula);

/*
Retorna a primeira celula da lista.
*/
CelulaLista getPrimeiraCelulaLista(Lista l);

/*
Retorna a proxima celula da lista.
*/
CelulaLista getProximaCelulaLista(CelulaLista celula);

/*
Retorna a ultima celula da lista.
*/
CelulaLista getUltimaCelulaLista(Lista l);

/// @brief Libera a memória da lista
/// @param l Lista que será liberada
void liberarLista(Lista l);
#endif