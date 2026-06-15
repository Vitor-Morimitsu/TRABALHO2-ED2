#include "filaPrioridades.h"

typedef struct stcelfila{
    double parametro;
    int idVertice;
    struct stcelfila* prox;
}stCelulaFila;

typedef struct{
    stCelulaFila* inicio;
    int tamanho;
    stCelulaFila* fim;
}stFila;

FilaPrioridades criarFilaDePrioridade(){
    stFila* f = malloc(sizeof(stFila));
    if(f == NULL){
        printf("Erro ao alocar memoria para fila de prioridades\n");
        return NULL;
    }
    f->inicio = NULL;
    f->tamanho = 0;
    f->fim = NULL;
    return (FilaPrioridades)f;
}

int verificarFilaVazia(FilaPrioridades fila){
    stFila* f = (stFila*)fila;
    if(f->tamanho == 0){
        return 0; // vazia
    }else {
        return 1; //contem elementos
    }

}

void inserirFilaPrioridades(FilaPrioridades fila, int idVertice, double parametro){
    stFila* f = (stFila*)fila;

    stCelulaFila* novaCel = malloc(sizeof(stCelulaFila));
    if(novaCel == NULL){
        printf("Erro ao alocar memoria\n");
        return;
    }
    novaCel->idVertice = idVertice;
    novaCel->parametro = parametro;
    novaCel->prox = NULL;

    //fila vazia OU novo elemento tem prioridade menor que o primeiro
    if(f->inicio == NULL || parametro < f->inicio->parametro){
        novaCel->prox = f->inicio;
        f->inicio = novaCel;
        if(f->fim == NULL){
            f->fim = novaCel; // primeira inserção
        }
    } else {
        //percorre até achar a posição correta
        stCelulaFila* atual = f->inicio;
        while(atual->prox != NULL && atual->prox->parametro <= parametro){
            atual = atual->prox;
        }
        novaCel->prox = atual->prox;
        atual->prox = novaCel;
        if(novaCel->prox == NULL){
            f->fim = novaCel; //inseriu no fim
        }
    }
    f->tamanho++;
}

void removerFilaPrioridades(FilaPrioridades fila){
    int resposta = verificarFilaVazia(fila);
    if(resposta == 0){
        return; 
    }
    stFila* f = (stFila*)fila;
    stCelulaFila* temp = f->inicio;
    f->inicio = temp->prox;
    free(temp);
    f->tamanho--;
    if(f->inicio == NULL){
        f->fim = NULL;
    }
}

void liberarFila(FilaPrioridades fila){
    stFila* f = (stFila*)fila;
    if(f == NULL) return;
    stCelulaFila* atual = f->inicio;
    while(atual != NULL){
        stCelulaFila* prox = atual->prox; 
        free(atual);
        atual = prox;
    }
    free(f);
}