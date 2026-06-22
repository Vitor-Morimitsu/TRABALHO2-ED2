#include "vertice.h"

typedef struct{
    char* id;
    double x;
    double y;
}stVertice;

Vertice criarVertice(char* id, double x, double y){
    stVertice* v = malloc(sizeof(stVertice));
    if (v == NULL) {
        printf("Erro ao criar um novo vertice\n");
        return NULL;
    }
    v->id = malloc(strlen(id) + 1);  // +1 para o '\0'
    strcpy(v->id, id);
    v->x = x;
    v->y = y;
    return (Vertice)v;
}

char* getIDVertice(Vertice v){
    return ((stVertice*)v)->id;
}

double getXVertice(Vertice v){
    return ((stVertice*)v)->x;
}

double getYVertice(Vertice v){
    return ((stVertice*)v)->y;
}

void liberarVertice(Vertice v){
    if(v == NULL){
        printf("Erro em liberarVertice\n");
        return;
    }
    stVertice* vertice = (stVertice*)v;
    free(vertice->id);
    free(vertice);
}
