#ifndef ARVORE_H
#define ARVORE_H
#include <stdio.h>
#include <stdlib.h>
#include "quadra.h"

/*
    Arquivo responsável pela criação e manipulação de uma árvore que envelopa todos os void* em nós para que possa ser trabalhado
*/

typedef void* Arvore;
typedef void* CelulaArvore;

Arvore criarArvore();

void inserirArvore(void* cont, Arvore a);

void removerArvore(Quadra q, Arvore a);

void* getRaizArvore(Arvore a);

void* buscarCelula(char* chave, CelulaArvore cel);

void* buscarArvore(char* chave, Arvore a);

void liberarArvore(Arvore a);


#endif