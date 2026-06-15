#include "grafo.h"

typedef struct verticeGrafo{
    void* conteudo;
    struct verticeGrafo* arestas; //vetor que armazena as aresta adjacentes
}stVerticeGrafo;

typedef struct arestaGrafo{
    int destino; //indice do vertice de destino
    struct arestaGrafo* prox; //proxima aresta da lista
}stArestaGrafo;

typedef struct{
    stVerticeGrafo* vertices; //array de vertices
    int numVertices;
    int capacidade;
}stGrafo;

Grafo criarGrafo(){
    stGrafo* grafo = malloc(sizeof(stGrafo));
    if(grafo == NULL){
        printf("Erro em criarGrafo\n");
        return NULL;
    }
    grafo->numVertices = 0;
    grafo->capacidade = 5;
    grafo->vertices = calloc(grafo->capacidade,sizeof(stVerticeGrafo));
    if(grafo->vertices == NULL){
        free(grafo);
        return NULL;
    }
    return (Grafo)grafo;
}

void inserirVerticeGrafo(Grafo g, void* conteudo){
    stGrafo* grafo = (stGrafo*)g;
    if(grafo->numVertices >= grafo->capacidade){
        //o grafo está cheio
        int novaCapacidade = grafo->capacidade * 2;
        stVerticeGrafo* temp = realloc(grafo->vertices, novaCapacidade* sizeof(stVerticeGrafo));
        if(temp == NULL){
            printf("Erro ao expandir o grafo\n");
            return;
        }
    }

}

void removerGrafo(Grafo g, Vertice v);

void liberarGrafo(Grafo g, Vertice v);