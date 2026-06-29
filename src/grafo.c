#include "grafo.h"

typedef struct stCelulaAresta {
    int destino; //indice do vertice de destino   
    Aresta dados;                
    struct stCelulaAresta* prox; 
} stCelulaAresta;

typedef struct {
    Vertice dados; 
    stCelulaAresta* arestas; 
} stVerticeGrafo;

typedef struct {
    stVerticeGrafo* vertices; //array de vertices
    int numVertices;
    int capacidade;
} stGrafo;

Grafo criarGrafo(){
    stGrafo* grafo = malloc(sizeof(stGrafo));
    if(grafo == NULL){
        printf("Erro em criarGrafo\n");
        return NULL;
    }
    grafo->numVertices = 0;
    grafo->capacidade = 10;
    grafo->vertices = calloc(grafo->capacidade,sizeof(stVerticeGrafo));
    if(grafo->vertices == NULL){
        free(grafo);
        return NULL;
    }
    return (Grafo)grafo;
}

int inserirVerticeGrafo(Grafo g, Vertice v){
    stGrafo* grafo = (stGrafo*)g;
    //se o array estiver cheio, dobra a capacidade
    if (grafo->numVertices >= grafo->capacidade) {
        int novaCapacidade = grafo->capacidade * 2;
        stVerticeGrafo* temp = realloc(grafo->vertices,novaCapacidade * sizeof(stVerticeGrafo));
        if (temp == NULL) {
            printf("Erro ao expandir o grafo\n");
            return -1; 
        }
        grafo->vertices = temp;
        grafo->capacidade = novaCapacidade;
    }

    int idx = grafo->numVertices;
    grafo->vertices[idx].dados = v;
    grafo->vertices[idx].arestas = NULL; 
    grafo->numVertices++;
    return idx;

}

int buscarVerticeIDGrafo(Grafo g, char* id){
    stGrafo* grafo = (stGrafo*)g;
    for(int i = 0; i< grafo->numVertices;i++){
        if(strcmp(getIDVertice(grafo->vertices[i].dados),id) == 0){
            return i;
        }
    }
    return -1; //não encontrou
}

void inserirArestaGrafo(Grafo g, int origem, int destino, Aresta dados){
    stGrafo* grafo = (stGrafo*)g;

    if (origem < 0 || origem >= grafo->numVertices ||
        destino < 0 || destino >= grafo->numVertices) {
        printf("Erro em inserirArestaGrafo: índice inválido\n");
        return;
    }

    stCelulaAresta* nova = malloc(sizeof(stCelulaAresta));
    if (nova == NULL) {
        printf("Erro ao alocar célula de aresta\n");
        return;
    }
    nova->destino = destino;
    nova->dados = dados;
    nova->prox = grafo->vertices[origem].arestas; // insere na cabeça
    grafo->vertices[origem].arestas = nova;
}

stVerticeGrafo* getVerticeGrafo(Grafo g){
    if(g == NULL){
        printf("Erro em getVerticeGrafo\n");
        return NULL;
    }
    stGrafo* grafo = (stGrafo*)g;
    return grafo->vertices; 
}

void liberarGrafo(Grafo g){
    if (g == NULL) return;
    stGrafo* grafo = (stGrafo*)g;

    for (int i = 0; i < grafo->numVertices; i++) {
        stCelulaAresta* atual = grafo->vertices[i].arestas;
        while (atual != NULL) {
            stCelulaAresta* prox = atual->prox;
            liberarAresta(atual->dados);
            free(atual);         
            atual = prox;
        }
        free(grafo->vertices[i].dados);
    }

    free(grafo->vertices); 
    free(grafo);           
}