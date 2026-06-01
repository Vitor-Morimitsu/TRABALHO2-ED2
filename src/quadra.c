#include "quadra.h"
#include <string.h>

typedef struct {
    char  CEP[32];
    float x, y, w, h;   // coordenadas e dimensões (float para SVG)
    char  sw[16];        // espessura da borda  (ex: "1.0px")
    char  fill[32];      // cor de preenchimento (ex: "black")
    char  cstrk[32];     // cor da borda
} stQuadra;

Quadra criarQuadra() {
    stQuadra* novaQuadra = malloc(sizeof(stQuadra)); // corrigido: sizeof(stQuadra)
    if (novaQuadra == NULL) {
        printf("Erro em criarQuadra\n");
        return NULL;
    }
    novaQuadra->CEP[0] = '\0';
    novaQuadra->x = novaQuadra->y = novaQuadra->w = novaQuadra->h = 0.0f;
    novaQuadra->sw[0] = novaQuadra->fill[0] = novaQuadra->cstrk[0] = '\0';

    return (Quadra)novaQuadra;
}

void setCEPQuadra(Quadra q, char* cepQuadra) {
    if (q == NULL) {
        printf("Erro em setCEPQuadra\n");
        return;
    }
    strncpy(((stQuadra*)q)->CEP, cepQuadra, 31);
    ((stQuadra*)q)->CEP[31] = '\0';
}

void setDimensoesQuadra(Quadra q, float x, float y, float w, float h) {
    if (q == NULL) {
        printf("Erro em setDimensoesQuadra\n");
        return;
    }
    stQuadra* quadra = (stQuadra*)q;
    quadra->x = x;
    quadra->y = y;
    quadra->w = w;
    quadra->h = h;
}

void setPreenchimentoQuadra(Quadra q, char* sw, char* cfill, char* cstrk) {
    if (q == NULL) {
        printf("Erro em setPreenchimentoQuadra\n");
        return;
    }
    stQuadra* quadra = (stQuadra*)q;
    strncpy(quadra->sw,    sw,    sizeof(quadra->sw)    - 1);
    strncpy(quadra->fill,  cfill, sizeof(quadra->fill)  - 1);
    strncpy(quadra->cstrk, cstrk, sizeof(quadra->cstrk) - 1);
    quadra->sw[sizeof(quadra->sw) - 1]       = '\0';
    quadra->fill[sizeof(quadra->fill) - 1]   = '\0';
    quadra->cstrk[sizeof(quadra->cstrk) - 1] = '\0';
}

char* getCEPQuadra(Quadra q) {
    return ((stQuadra*)q)->CEP;
}

float getXQuadra(Quadra q){
    return ((stQuadra*)q)->x;
}

float getYQuadra(Quadra q){
    return ((stQuadra*)q)->y;
}

float getWQuadra(Quadra q){
    return ((stQuadra*)q)->w;
}

float getHQuadra(Quadra q){
    return ((stQuadra*)q)->h;
}

char* getSwQuadra(Quadra q){
    return ((stQuadra*)q)->sw;
}

char* getCfillQuadra(Quadra q){
    return ((stQuadra*)q)->fill;
}

char* getCstrkQuadra(Quadra q){
    return ((stQuadra*)q)->cstrk;
}

void liberarQuadra(Quadra q) {
    if (q == NULL) {
        printf("Erro em liberarQuadra\n");
        return;
    }
    free(q);
}
