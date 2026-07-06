#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "svg.h"
#include "geo.h"
#include "via.h"
#include "qry.h"
#include "arvore.h"
#include "grafo.h"
#include "registrador.h"

#define MAX_REGISTRADORES 10

int main(int argc, char* argv[]) {
    char* geoPath = NULL;
    char* viaPath = NULL;
    char* qryPath = NULL;
    char* outDir  = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            geoPath = argv[++i];
        } else if (strcmp(argv[i], "-v") == 0 && i + 1 < argc) {
            viaPath = argv[++i];
        } else if (strcmp(argv[i], "-q") == 0 && i + 1 < argc) {
            qryPath = argv[++i];
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            outDir = argv[++i];
        }
    }

    if (!geoPath || !viaPath || !outDir) {
        fprintf(stderr, "Uso: %s -f <geo> -v <via> [-q <qry>] -o <dir_saida>\n", argv[0]);
        return 1;
    }

    /* --- Abre o arquivo .geo --- */
    FILE* geoFile = fopen(geoPath, "r");
    if (!geoFile) {
        fprintf(stderr, "Erro ao abrir %s\n", geoPath);
        return 1;
    }

    /* --- Abre o arquivo .via --- */
    FILE* viaFile = fopen(viaPath, "r");
    if (!viaFile) {
        fprintf(stderr, "Erro ao abrir %s\n", viaPath);
        fclose(geoFile);
        return 1;
    }

    /* Extrai o nome-base do arquivo .geo para nomear as saídas */
    char baseName[256];
    const char* slash = strrchr(geoPath, '/');
    if (!slash) slash = strrchr(geoPath, '\\');
    const char* src = slash ? slash + 1 : geoPath;
    strncpy(baseName, src, sizeof(baseName) - 1);
    baseName[sizeof(baseName) - 1] = '\0';
    /* Remove extensão */
    char* dot = strrchr(baseName, '.');
    if (dot) *dot = '\0';

    /* --- Monta os caminhos de saída --- */
    char svgPath[512];
    char txtPath[512];
    snprintf(svgPath, sizeof(svgPath), "%s/%s.svg", outDir, baseName);
    snprintf(txtPath, sizeof(txtPath), "%s/%s.txt", outDir, baseName);

    FILE* svgFile = fopen(svgPath, "w");
    if (!svgFile) {
        fprintf(stderr, "Erro ao criar %s\n", svgPath);
        fclose(geoFile); fclose(viaFile);
        return 1;
    }

    FILE* txtFile = fopen(txtPath, "w");
    if (!txtFile) {
        fprintf(stderr, "Erro ao criar %s\n", txtPath);
        fclose(geoFile); fclose(viaFile); fclose(svgFile);
        return 1;
    }

    /* --- Estruturas de dados --- */
    Arvore quadras = criarArvore();
    Grafo  grafo   = criarGrafo();

    /* Array de registradores pré-alocados */
    Registrador regs[MAX_REGISTRADORES];
    for (int i = 0; i < MAX_REGISTRADORES; i++) {
        regs[i] = criarRegistrador("", 'N', 0);
    }

    /* --- Leitura e processamento --- */
    abrirSvg(svgFile);
    lerGeo(geoFile, svgFile, quadras);
    lerVia(viaFile, quadras, grafo);

    if (qryPath) {
        FILE* qryFile = fopen(qryPath, "r");
        if (!qryFile) {
            fprintf(stderr, "Erro ao abrir %s\n", qryPath);
        } else {
            lerQry(qryFile, svgFile, txtFile, quadras, grafo, regs);
            fclose(qryFile);
        }
    }

    fecharSVG(svgFile);

    /* --- Liberação de memória --- */
    for (int i = 0; i < MAX_REGISTRADORES; i++) {
        liberarRegistrador(regs[i]);
    }
    liberarGrafo(grafo);
    liberarArvore(quadras);

    fclose(geoFile);
    fclose(viaFile);
    fclose(svgFile);
    fclose(txtFile);

    return 0;
}
