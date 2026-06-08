#ifndef QRY_H
#define QRY_H
#include <stdio.h>
#include <stdlib.h>
#include "quadra.h"
#include "grafo.h"
#include "vertice.h"
#include "via.h"

/*
    Arquivo responsável pelas operações .qry no segundo trabalho de estrutura de dados 2
*/

/*
    Armazena a posição geografica do endereço cep/face/num no registrador reg.
    Svg: linha vertical pontilhada vermelha mostrando a posição do endereço e colocar o numero do registrados na outra extremidade da linha(topo da pagina)
    Txt: reportar a coordenada relatica ao endereço
*/
void comandoO(FILE* svg, FILE* txt,int numRegistrador, char* cep, char face, int num);

/// @brief Função principal para ler o qry
/// @param qry Arquivo qry
/// @param svg Arquivo svg final
/// @param txt Arquivo txt
/// @param quadras Arvore que contenha as quadras
/// @param grafo Grafo com os vertices
void lerQry(FILE* qry, FILE* svg, FILE* txt, Arvore quadras, Grafo grafo);

#endif