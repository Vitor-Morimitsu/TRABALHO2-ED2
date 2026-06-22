#ifndef REGISTRADOR_H
#define REGISTRADOR_H
#include <stdio.h>
#include <stdlib.h>
#include "quadra.h"

/*
    Arquivo responsável por criar e gerenciar 11 registradores
*/
typedef void* Registrador;

/// @brief Cria e retorna um registrador
/// @param cep Cep da quadra
/// @param face face da quadra
/// @param num numero
/// @return registrador
Registrador criarRegistrador(char* cep, char face, int num);

/// @brief Retorna o cep da quadra contida no registrador
/// @param r registrador
/// @return cep
char* getCepRegistrador(Registrador r);

/// @brief Retorna a face da quadra contida no registrador
/// @param r registrador
/// @return face
char getFaceRegistrador(Registrador r);

/// @brief Retorna o numero da quadra contida no registrador
/// @param r registrador 
/// @return numero
int getNumRegistrador(Registrador r);

/// @brief Retorna 1 se estiver ativo e 0 se não estiver ativo
/// @param r registrador
/// @return numero de confirmação
int getAtivoRegistrador(Registrador r);

/// @brief libera a memoria alocada para registrador
/// @param r registrador
void liberarRegistrador(Registrador r);

#endif