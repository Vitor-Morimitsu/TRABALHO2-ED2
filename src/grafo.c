#include "grafo.h"

typedef struct celulaGrafo{
    void* conteudo;
    struct celulaGrafo* aresta; //vetor que armazena as aresta adjacentes
}stCelulaGrafo;