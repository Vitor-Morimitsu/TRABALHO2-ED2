#ifndef GEO_H
#define GEO_H

#include <stdio.h>
#include <stdlib.h>
#include "vertice.h"
#include "aresta.h"
#include "svg.h"
#include "lista.h"

/*
    Arquivo .geo responsável por ler um arquivo geo e gerar as formas em svg.
*/

/// @brief Função responsável por ler um arquivo geo,criar as quadras e gerar um svg correspondente
/// @param geo Arquivo .geo já aberto
/// @param svg Arquivo .svg já aberto
/// @param l Lista de quadras
void lerGeo(FILE* geo, FILE* svg, Lista quadras);

#endif