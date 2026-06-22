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
    a->nome = malloc(strlen(nome) + 1);
    strcpy(a->nome, nome);
    a->ldir = malloc(strlen(ldir) + 1);
    strcpy(a->ldir, ldir);
    a->lesq = malloc(strlen(lesq) + 1);
    strcpy(a->lesq, lesq);
    a->cmp = cmp;
    a->vm = vm;
    a->v1 = NULL;
    a->v2 = NULL;
    return a;
}

void setVerticesAresta(Aresta a, Vertice v1, Vertice v2){
    if(a == NULL || v1 == NULL || v2 == NULL){
        printf("Erro em setVerticesAresta\n");
        return;
    }
    stAresta* ar = (stAresta*)a;
    ar->v1 = v1;
    ar->v2 = v2;
}

char* getNomeAresta(Aresta a){
    return ((stAresta*)a)->nome;
}

char* getCEP_ladoDireitoAresta(Aresta a){
    return ((stAresta*)a)->ldir;
}

char* getCEP_ladoEsquerdoAresta(Aresta a){
    return ((stAresta*)a)->lesq;
}

double getCmpAresta(Aresta a){
    return ((stAresta*)a)->cmp;
}

double getVmAresta(Aresta a){
    return ((stAresta*)a)->vm;
}

void liberarAresta(Aresta a){
    if(a == NULL){
        printf("Erro em liberarAresta\n");
        return;
    }
    stAresta* aresta = (stAresta*)a;
    free(aresta->nome);
    free(aresta->ldir);
    free(aresta->lesq);
    liberarVertice(aresta->v1);
    liberarVertice(aresta->v2);
    free(aresta);
}