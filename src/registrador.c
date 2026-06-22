#include "registrador.h"

typedef struct{
    char* cep;
    char face;
    int num;
    int ativo
}stRegistrador;

Registrador criarRegistrador(char* cep, char face, int num){
    stRegistrador* r = malloc(sizeof(stRegistrador));
    r->cep = malloc(strlen(cep));
    strcpy(r->cep, cep);
    r->face = face;
    r->num = num;
    r->ativo = 0;
}

char* getCepRegistrador(Registrador r){
    return ((stRegistrador*)r)->cep;
}

char getFaceRegistrador(Registrador r){
    return ((stRegistrador*)r)->face;
}

int getNumRegistrador(Registrador r){
    return ((stRegistrador*)r)->num;
}

int getAtivoRegistrador(Registrador r){
    return ((stRegistrador*)r)->ativo;
}

void liberarRegistrador(Registrador r){
    if(r == NULL){
        printf("Erro em liberarRegistrador\n");
        return;
    }
    stRegistrador* re = (stRegistrador*)r;
    free(re->cep);
    free(re);
}