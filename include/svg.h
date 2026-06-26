#ifndef SVG_H
#define SVG_H
/*
    Arquivo responsável por manipular um svg para o primeiro trabalho de ED2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quadra.h"

//a rosa dos ventos é invertida, Sul está no norte,etc

/*
    Função responsável por abrir o arquivo Svg passado como parâmetro aberto na main
*/
void abrirSvg(FILE* arqSvg);

void svgComandoO(FILE* svg);

void svgComandoRegs(FILE* svg);

void svgComandoExp(FILE* svg);

void svgComandoP(FILE* svg);

/// @brief Realiza o comando de encerramento do arquivo svg
/// @param arqSvg Arquivo
void fecharSVG(FILE* arqSvg);

#endif