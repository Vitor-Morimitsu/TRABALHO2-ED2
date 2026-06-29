#include "registrador.h"

typedef struct{
    char* cep;
    char face;
    int num;
    int ativo;
}stRegistrador;

Registrador criarRegistrador(char* cep, char face, int num){
    stRegistrador* r = malloc(sizeof(stRegistrador));
    r->cep = malloc(strlen(cep) + 1);
    strcpy(r->cep, cep);
    r->face = face;
    r->num = num;
    r->ativo = 1;
    return r;
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

void setCepRegistrador(Registrador r, char* cep){
    if(r == NULL){
        printf("Erro em setCepRegistrador\n");
        return;
    }
    stRegistrador* reg = (stRegistrador*)r;
    if( reg->cep != NULL) free(reg->cep);
    reg->cep = malloc(strlen(cep)+1);
    strcpy(reg->cep, cep);
}

void setFaceRegistrador(Registrador r, char face){
    if(r == NULL){
        printf("Erro em setFaceRegistrador\n");
        return;
    }
    stRegistrador* reg = (stRegistrador*)r;
    reg->face = face;

}

void setNumRegistrador(Registrador r, int num){
    if(r == NULL){
        printf("Erro em setNumRegistrador\n");
        return;
    }
    stRegistrador* reg = (stRegistrador*)r;
    reg->num = num;
}

void ativarRegistrador(Registrador r){
    if(r == NULL){
        printf("Erro em ativarRegistrador\n");
        return;
    }
    stRegistrador* reg = (stRegistrador*)r;
    reg->ativo = 1;
}

void desativarRegistrador(Registrador r){
    if(r == NULL){
        printf("Erro em desativarRegistrador\n");
        return;
    }
    stRegistrador* reg = (stRegistrador*)r;
    reg->ativo = 0;
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