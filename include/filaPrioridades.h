#ifndef FILAPRIORIDADES_H
#define FILAPRIORIDADES_H
#include <stdio.h>
#include <stdlib.h>
/*
    Arquivo responsável pela implementação de uma fila de prioridades para ajudar a descobrir o caminho com menor custo
*/

typedef void* FilaPrioridades;

/// @brief Cria e retorna uma fila de prioridades
/// @return Fila
FilaPrioridades criarFilaDePrioridade();

/// @brief Verifica se uma fila está vazia
/// @param fila Fila de prioridades
/// @return 0 - vazia ou 1 - contém elementos
int verificarFilaVazia(FilaPrioridades fila);

/// @brief Insere um dado na fila de prioridades
/// @param fila Fila
/// @param idVertice id do vértice
/// @param parametro Parametro que será inserido 
void inserirFilaPrioridades(FilaPrioridades fila, int idVertice, double parametro);

/// @brief Remove o elemento com a menor prioridade
/// @param fila Fila de prioridades
void removerFilaPrioridades(FilaPrioridades fila);

/// @brief Libera a memoria alocada por uma fila de prioridades
/// @param fila Fila de prioridades
void liberarFila(FilaPrioridades fila);

#endif