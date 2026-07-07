#ifndef SVG_H
#define SVG_H
/*
    Arquivo responsável por manipular um svg para o primeiro trabalho de ED2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quadra.h"

// a rosa dos ventos é invertida, Sul está no norte, etc

/// @brief Abre a tag raiz do SVG
void abrirSvg(FILE* arqSvg);

/// @brief Desenha o retângulo de uma quadra no SVG
void desenharRetanguloSVG(FILE* arqSvg, Quadra q);

/// @brief Linha vertical pontilhada vermelha marcando o endereço do registrador
/// e rótulo R<n> no topo da página
void svgComandoO(FILE* svg, double x, double y, int numRegistrador);

/// @brief Bounding box de uma aresta com velocidade insuficiente
/// (retângulo azul semitransparente)
void svgComandoRegs(FILE* svg, double x1, double y1, double x2, double y2);

/// @brief Aresta selecionada pelo comando exp — linha vermelha grossa
void svgComandoExp(FILE* svg, double x1, double y1, double x2, double y2);

/// @brief Placeholder para animação do caminho mínimo (sem efeito)
void svgComandoP(FILE* svg);

/// @brief Segmento do caminho mínimo — linha colorida com extremidades arredondadas
void svgDesenharSegmentoRua(FILE* svg, double x1, double y1, double x2, double y2, char* cor);

/// @brief Marcador de início (I) ou fim (F) do caminho mínimo — círculo colorido com letra
void svgDesenharMarcadorCaminho(FILE* svg, double x, double y, char letra, char* cor);

/// @brief Desenha o caminho como <path> com id e adiciona um <circle> animado
/// que percorre o trajeto em loop por 'durSegundos' segundos.
/// @param xs        Array de coordenadas X dos vértices
/// @param ys        Array de coordenadas Y dos vértices
/// @param n         Número de vértices
/// @param corLinha  Cor da linha do caminho
/// @param corPonto  Cor do ponto animado
/// @param durSegundos Duração de um ciclo completo da animação em segundos
/// @param animId    ID único para o elemento <path> (evitar colisões entre as duas rotas)
void svgAnimarCaminho(FILE* svg, double* xs, double* ys, int n,
                      char* corLinha, char* corPonto,
                      double durSegundos, char* animId);

/// @brief Marca com um X o local de uma quadra removida
void comandoRqSvg(FILE* svg, float x, float y, float w, float h);

/// @brief Marca com um quadradinho o endereço de uma mudança
void comandoMudSvg(FILE* svg, float x, float y, float w, float h, char face, char* cpf);

/// @brief Marca com uma cruz vermelha o local de um endereço
void comandoRipSvg(FILE* svg, float x, float y);

/// @brief Exibe contagem de moradores por face e total da quadra
void comandoPqSvg(FILE* svg, Quadra q, int total, int n, int s, int l, int o);

/// @brief Desenha um círculo preto no local de um despejo
void comandoDspjSvg(FILE* svg, float x, float y);

/// @brief Fecha a tag raiz do SVG
void fecharSVG(FILE* arqSvg);

#endif