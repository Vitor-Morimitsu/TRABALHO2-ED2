#ifndef QRY_H
#define QRY_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "quadra.h"
#include "grafo.h"
#include "vertice.h"
#include "via.h"
#include "registrador.h"
#include "svg.h"

/*
    Arquivo responsável pelas operações .qry no segundo trabalho de estrutura de dados 2
*/

/*
    Armazena a posição geográfica do endereço cep/face/num no registrador reg.
    Svg: linha vertical pontilhada vermelha mostrando a posição do endereço e colocar o numero do registrador na outra extremidade da linha (topo da página)
    Txt: reportar a coordenada relativa ao endereço
*/
void comandoO(FILE* svg, FILE* txt, int numRegistrador, char* cep, char face, int num, Arvore quadras, Registrador regs[]);

/*
    Atualiza a velocidade média das arestas dentro da região (x,y,w,h) para velocidadeNova
*/
void comandoMvm(Grafo grafo, double velocidadeNova, double x, double y, double w, double h);

/*
    Reporta e desenha as arestas com velocidade abaixo de vInsuficiente
*/
void comandoRegs(FILE* txt, FILE* svg, Arvore quadras, Grafo grafo, double vInsuficiente);

/*
    Calcula e desenha a bounding box de uma aresta no SVG
*/
void calcularBoundingBox(FILE* svg, Aresta a);

/*
    Aumenta a velocidade em 50% das arestas com vm abaixo de velocidade
*/
void comandoExp(FILE* svg, Grafo grafo, Arvore quadras, double velocidade);

/*
    Realiza o comando P?: calcula o menor caminho entre dois registradores
*/
void comandoP(FILE* svg, FILE* txt, Arvore quadras, Grafo grafo, Registrador reg1, Registrador reg2, char* cc, char* cr);

/// @brief Função principal para ler o qry
/// @param qry Arquivo qry
/// @param svg Arquivo svg final
/// @param txt Arquivo txt
/// @param quadras Arvore que contenha as quadras
/// @param grafo Grafo com os vertices
/// @param regs array de registradores
void lerQry(FILE* qry, FILE* svg, FILE* txt, Arvore quadras, Grafo grafo, Registrador regs[]);

#endif