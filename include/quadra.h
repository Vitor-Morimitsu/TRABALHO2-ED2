#ifndef QUADRA_H
#define QUADRA_H

#include <stdio.h>
#include <stdlib.h>

/*
    Arquivo .h destinado à criação e manupulação de quadras
*/

typedef void* Quadra;

/// @brief Cria e retorna uma quadra
/// @return Quadra
Quadra criarQuadra();

/// @brief Define o CEP de uma quadra
/// @param q Quadra Pré existente
/// @param cepQuadra CEP que será definido
void setCEPQuadra(Quadra q, char* cepQuadra);

/// @brief Define as dimensões da quadra
/// @param q Quadra já existente
/// @param x Localização da âncora no eixo x
/// @param y Localização da âncora no eixo y
/// @param w Tamanho do comprimento
/// @param h Tamanho da altura
void setDimensoesQuadra(Quadra q, float x, float y, float w, float h);

/// @brief Define os parâmetros de preenchimento da quadra
/// @param q Quadra já existente
/// @param sw Espessura da borda
/// @param cfill Cor de preenchimento
/// @param cstrk Cor preenchimento da borda
void setPreenchimentoQuadra(Quadra q, char* sw, char* cfill, char* cstrk);

char* getSwQuadra(Quadra q);

char* getCfillQuadra(Quadra q);

char* getCstrkQuadra(Quadra q);

/// @brief Retorna o CEP de uma quadra 
/// @param q Quadra já existente
/// @return CEP
char* getCEPQuadra(Quadra q);

/// @brief Retorna a coordenada X da quadra
/// @param q Quadra
/// @return coordenada x
float getXQuadra(Quadra q);

/// @brief retorna a coordenada Y da Quadra
/// @param q Quadra
/// @return coordenada Y
float getYQuadra(Quadra q);

/// @brief Retorna a largura da quadra
/// @param q Quadra
/// @return largura
float getWQuadra(Quadra q);

/// @brief Retorna a altura da quadra
/// @param q Quadra
/// @return altura
float getHQuadra(Quadra q);

/// @brief Libera a memória da quadra
/// @param q Quadra
void liberarQuadra(Quadra q);
#endif