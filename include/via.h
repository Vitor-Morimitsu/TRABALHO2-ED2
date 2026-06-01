#ifndef VIA_H
#define VIA_H

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/*
    Arquivo responsável por criar e manipular um arquivo via
*/

/// @brief Função responsável por ler um arquivo via para gerar as quadras e grafos
/// @param via Arquivo
/// @param quadras lista que contém as quadras que serão inseridas
void lerVia(FILE* via,Lista quadras);

#endif