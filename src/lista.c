#include "lista.h"

typedef struct celula{
    void* conteudo;
    struct celula* anterior;
    struct celula* proximo;
}stCelula;


typedef struct{
    stCelula* inicio;
    stCelula* fim;
    int tamanho;
}stLista;

Lista criarLista(){
    stLista* lista = malloc(sizeof(stLista));
    if(lista == NULL){
        printf("Erro ao criar lista\n");
        return NULL;
    }

    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;
    return lista;
}

void insereLista(Lista l, void* conteudo){
    if(l == NULL || conteudo == NULL){
        printf("Erro ao inserir pacote na lista\n");
        return;
    }
    stLista* lista = (stLista*)l;
    stCelula* novo = malloc(sizeof(stCelula));
    if(novo == NULL){
        printf("Erro ao inserir novo elemento na lista\n");
        return;
    }

    novo->conteudo = conteudo;
    novo->proximo = NULL;
    if(lista->inicio == NULL){
        //lista vazia
        lista->inicio = novo;
        novo->anterior = NULL;
    }else{
        lista->fim->proximo = novo;
        novo->anterior = lista->fim;       
    }
    lista->fim = novo;
    lista->tamanho++;
}

int getTamanhoLista(Lista l){
    if(l == NULL){
        printf("Erro em getTamanhoLista\n");
        return -1;
    }

    return ((stLista*)l)->tamanho;
}

void* getConteudoCelula(CelulaLista celula){
    if(celula == NULL){
        printf("Erro em getConteudoCelula: celula NULL\n");
        return NULL;
    }
    
    stCelula* cel = (stCelula*)celula;
    return cel->conteudo;
}

CelulaLista getPrimeiraCelulaLista(Lista l){
    if(l == NULL){
        printf("Erro em getPrimeiraCelulaLista\n");
        return NULL;
    }

    stLista* lista = (stLista*)l;
    stCelula* cel = lista->inicio;
    return (CelulaLista)cel;
}

CelulaLista getProximaCelulaLista(CelulaLista celula){
    if(celula == NULL){
        printf("Erro em getProximaCelulaLista\n");
        return NULL;
    }

    stCelula* cel = (stCelula*)celula;
    return (CelulaLista)cel->proximo;
}

CelulaLista getUltimaCelulaLista(Lista l){
    if(l == NULL){
        printf("Erro em getUltimaCelulaLista\n");
        return NULL;
    }

    stLista* lista = (stLista*)l;
    return (CelulaLista)lista->fim;
}

void liberarLista(Lista l){
    if(l == NULL){
        printf("Erro em liberarLista\n");
        return;
    }
    stLista* lista = (stLista*)l;
    stCelula* atual = lista->inicio;
    for(int i = 0; i<lista->tamanho;i++){
        stCelula* proximo = atual->proximo;
        liberarQuadra(atual->conteudo);
        free(atual);
        atual = proximo;
    }
    free(lista);
}