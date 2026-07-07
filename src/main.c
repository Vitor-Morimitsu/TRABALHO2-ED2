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

/*
 * Uso: ./ted -f <arquivo.geo> -v <arquivo.via> [-q <arquivo.qry>] -o <diretorio_saida>
 *
 * Saídas geradas em <diretorio_saida>:
 *   <nome_geo>.svg   — mapa base com as quadras (sempre gerado)
 *   <nome_geo>.txt   — relatório do mapa base    (sempre gerado)
 *   <nome_qry>.svg   — mapa + resultado do qry   (apenas se -q for fornecido)
 *   <nome_qry>.txt   — relatório do qry           (apenas se -q for fornecido)
 */

/* Extrai o nome-base de um caminho de arquivo (sem extensão) */
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
    char* geoPath = NULL;
    char* viaPath = NULL;
    char* qryPath = NULL;
    char* outDir  = NULL;

    for (int i = 1; i < argc; i++) {
        if      (strcmp(argv[i], "-f") == 0 && i + 1 < argc) geoPath = argv[++i];
        else if (strcmp(argv[i], "-v") == 0 && i + 1 < argc) viaPath = argv[++i];
        else if (strcmp(argv[i], "-q") == 0 && i + 1 < argc) qryPath = argv[++i];
        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) outDir  = argv[++i];
    }

    if (!geoPath || !viaPath || !outDir) {
        fprintf(stderr, "Uso: %s -f <geo> -v <via> [-q <qry>] -o <dir_saida>\n", argv[0]);
        return 1;
    }

    /* Abre os arquivos de entrada */
    FILE* geoFile = fopen(geoPath, "r");
    if (!geoFile) { fprintf(stderr, "Erro ao abrir %s\n", geoPath); return 1; }

    FILE* viaFile = fopen(viaPath, "r");
    if (!viaFile) { fprintf(stderr, "Erro ao abrir %s\n", viaPath); fclose(geoFile); return 1; }

    /* Nomes-base */
    char geoBase[256];
    extrairBaseName(geoPath, geoBase, sizeof(geoBase));

    /* ------------------------------------------------------------------ */
    /*  PASSO 1 — Gera o SVG do geo (mapa base) e constrói a BST          */
    /* ------------------------------------------------------------------ */
    char geoSvgPath[512], geoTxtPath[512];
    snprintf(geoSvgPath, sizeof(geoSvgPath), "%s/%s.svg", outDir, geoBase);
    snprintf(geoTxtPath, sizeof(geoTxtPath), "%s/%s.txt", outDir, geoBase);

    FILE* geoSvg = fopen(geoSvgPath, "w");
    if (!geoSvg) {
        fprintf(stderr, "Erro ao criar %s\n", geoSvgPath);
        fclose(geoFile); fclose(viaFile); return 1;
    }
    FILE* geoTxt = fopen(geoTxtPath, "w");
    if (!geoTxt) {
        fprintf(stderr, "Erro ao criar %s\n", geoTxtPath);
        fclose(geoFile); fclose(viaFile); fclose(geoSvg); return 1;
    }

    Arvore quadras = criarArvore();
    Grafo  grafo   = criarGrafo();

    abrirSvg(geoSvg);
    lerGeo(geoFile, geoSvg, quadras);   /* lê o .geo, desenha quadras e popula a BST */
    fecharSVG(geoSvg);
    fclose(geoSvg);
    fclose(geoTxt);   /* txt do geo fica vazio (sem qry não há relatório) */

    lerVia(viaFile, quadras, grafo);    /* constrói o grafo de ruas */

    /* ------------------------------------------------------------------ */
    /*  PASSO 2 — Se houver .qry, gera o SVG do qry                       */
    /* ------------------------------------------------------------------ */
    if (qryPath) {
        char qryBase[256];
        extrairBaseName(qryPath, qryBase, sizeof(qryBase));

        char qrySvgPath[512], qryTxtPath[512];
        snprintf(qrySvgPath, sizeof(qrySvgPath), "%s/%s.svg", outDir, qryBase);
        snprintf(qryTxtPath, sizeof(qryTxtPath), "%s/%s.txt", outDir, qryBase);

        FILE* qrySvg = fopen(qrySvgPath, "w");
        if (!qrySvg) { fprintf(stderr, "Erro ao criar %s\n", qrySvgPath); goto cleanup; }

        FILE* qryTxt = fopen(qryTxtPath, "w");
        if (!qryTxt) { fprintf(stderr, "Erro ao criar %s\n", qryTxtPath); fclose(qrySvg); goto cleanup; }

        FILE* qryFile = fopen(qryPath, "r");
        if (!qryFile) { fprintf(stderr, "Erro ao abrir %s\n", qryPath); fclose(qrySvg); fclose(qryTxt); goto cleanup; }

        /* Redesenha o mapa base no SVG do qry (rebobina o .geo) */
        abrirSvg(qrySvg);
        rewind(geoFile);
        Arvore tempQuadras = criarArvore();   /* BST temporária apenas para o desenho */
        lerGeo(geoFile, qrySvg, tempQuadras);
        liberarArvore(tempQuadras);

        /* Aplica os comandos do .qry (usa a BST e o grafo originais) */
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
    fclose(viaFile);

    return 0;
}
