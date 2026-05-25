#include "aresta.h"

typedef struct{
    char* nome;
    char* ldir;
    char* lesq;
    double cmp;
    double vm;
    Vertice v1;
    Vertice v2;
}stAresta;

Aresta criarAresta(char* nome, char* ldir, char* lesq, double cmp,double vm){
    stAresta* a = malloc(sizeof(stAresta));
    if(a == NULL){
        printf("Erro ao criar a aresta\n");
        return NULL;
    }
    a->nome = nome;
    a->ldir = ldir;
    a->lesq = lesq;
    a->cmp = cmp;
    a->vm = vm;
    a->v1 = NULL;
    a->v2 = NULL;
}

void setVerticesAresta(Aresta a, Vertice v1, Vertice v2){
    if(a == NULL || v1 == NULL || v2 == NULL){
        printf("Erro em setVerticesAresta\n");
        return;
    }
}
