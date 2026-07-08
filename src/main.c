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

static void extrairBaseName(const char* path, char* dest, size_t destSize) {
    const char* slash = strrchr(path, '/');
    if (!slash) slash = strrchr(path, '\\');
    const char* src = slash ? slash + 1 : path;
    strncpy(dest, src, destSize - 1);
    dest[destSize - 1] = '\0';
    char* dot = strrchr(dest, '.');
    if (dot) *dot = '\0';
}

int main(int argc, char* argv[]) {
    char* baseDir = NULL;
    char* geoPath = NULL;
    char* viaPath = NULL;
    char* qryPath = NULL;
    char* outDir  = NULL;

    for (int i = 1; i < argc; i++) {
        if      (strcmp(argv[i], "-e") == 0 && i + 1 < argc) baseDir = argv[++i];
        else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) geoPath = argv[++i];
        else if (strcmp(argv[i], "-v") == 0 && i + 1 < argc) viaPath = argv[++i];
        else if (strcmp(argv[i], "-q") == 0 && i + 1 < argc) qryPath = argv[++i];
        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) outDir  = argv[++i];
    }

    if (!geoPath || !outDir) {
        fprintf(stderr, "Uso: %s [-e <dir_entrada>] -f <geo> [-v <via>] [-q <qry>] -o <dir_saida>\n", argv[0]);
        return 1;
    }

    char geoFull[512], viaFull[512], qryFull[512];
    if (baseDir) {
        snprintf(geoFull, sizeof(geoFull), "%s/%s", baseDir, geoPath);
        if (viaPath) snprintf(viaFull, sizeof(viaFull), "%s/%s", baseDir, viaPath);
        if (qryPath) snprintf(qryFull, sizeof(qryFull), "%s/%s", baseDir, qryPath);
    } else {
        snprintf(geoFull, sizeof(geoFull), "%s", geoPath);
        if (viaPath) snprintf(viaFull, sizeof(viaFull), "%s", viaPath);
        if (qryPath) snprintf(qryFull, sizeof(qryFull), "%s", qryPath);
    }

    /* Abre os arquivos de entrada */
    FILE* geoFile = fopen(geoFull, "r");
    if (!geoFile) { fprintf(stderr, "Erro ao abrir %s\n", geoFull); return 1; }

    FILE* viaFile = NULL;
    if (viaPath) {
        viaFile = fopen(viaFull, "r");
        if (!viaFile) { fprintf(stderr, "Erro ao abrir %s\n", viaFull); fclose(geoFile); return 1; }
    }

    char geoBase[256];
    extrairBaseName(geoPath, geoBase, sizeof(geoBase));

    char geoSvgPath[512], geoTxtPath[512];
    snprintf(geoSvgPath, sizeof(geoSvgPath), "%s/%s.svg", outDir, geoBase);
    snprintf(geoTxtPath, sizeof(geoTxtPath), "%s/%s.txt", outDir, geoBase);

    FILE* geoSvg = fopen(geoSvgPath, "w");
    if (!geoSvg) {
        fprintf(stderr, "Erro ao criar %s\n", geoSvgPath);
        fclose(geoFile); if (viaFile) fclose(viaFile); return 1;
    }
    FILE* geoTxt = fopen(geoTxtPath, "w");
    if (!geoTxt) {
        fprintf(stderr, "Erro ao criar %s\n", geoTxtPath);
        fclose(geoFile); if (viaFile) fclose(viaFile); fclose(geoSvg); return 1;
    }

    Arvore quadras = criarArvore();
    Grafo  grafo   = criarGrafo();

    abrirSvg(geoSvg);
    lerGeo(geoFile, geoSvg, quadras); 
    fecharSVG(geoSvg);
    fclose(geoSvg);
    fclose(geoTxt);  

    if (viaFile) {
        lerVia(viaFile, quadras, grafo); 
    }
    if (qryPath) {
        char qryBase[256];
        extrairBaseName(qryPath, qryBase, sizeof(qryBase));

        char qrySvgPath[512], qryTxtPath[512];
        snprintf(qrySvgPath, sizeof(qrySvgPath), "%s/%s-%s.svg", outDir, geoBase, qryBase);
        snprintf(qryTxtPath, sizeof(qryTxtPath), "%s/%s-%s.txt", outDir, geoBase, qryBase);

        FILE* qrySvg = fopen(qrySvgPath, "w");
        if (!qrySvg) { fprintf(stderr, "Erro ao criar %s\n", qrySvgPath); goto cleanup; }

        FILE* qryTxt = fopen(qryTxtPath, "w");
        if (!qryTxt) { fprintf(stderr, "Erro ao criar %s\n", qryTxtPath); fclose(qrySvg); goto cleanup; }

        FILE* qryFile = fopen(qryFull, "r");
        if (!qryFile) { fprintf(stderr, "Erro ao abrir %s\n", qryFull); fclose(qrySvg); fclose(qryTxt); goto cleanup; }

        abrirSvg(qrySvg);
        rewind(geoFile);
        Arvore tempQuadras = criarArvore();   
        lerGeo(geoFile, qrySvg, tempQuadras);
        liberarArvore(tempQuadras);

        Registrador regs[MAX_REGISTRADORES];
        for (int i = 0; i < MAX_REGISTRADORES; i++) regs[i] = criarRegistrador("", 'N', 0);

        lerQry(qryFile, qrySvg, qryTxt, quadras, grafo, regs);

        for (int i = 0; i < MAX_REGISTRADORES; i++) liberarRegistrador(regs[i]);

        fecharSVG(qrySvg);
        fclose(qryFile);
        fclose(qrySvg);
        fclose(qryTxt);
    }

cleanup:
    liberarGrafo(grafo);
    liberarArvore(quadras);
    fclose(geoFile);
    if (viaFile) fclose(viaFile);

    return 0;
}
